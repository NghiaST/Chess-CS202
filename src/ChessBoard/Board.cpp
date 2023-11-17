#include "Board.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <functional>
#include <bits.h>

// Constructor and Destructor

Board::Board() {
    isWhiteTurn = true;
    cntMoves = 0;
    Reset();
}

Board::Board(const Board &board) {
    pieces = board.pieces;
    isWhiteTurn = board.isWhiteTurn;
    cntMoves = board.cntMoves;
    presentGameState = board.presentGameState;
    gameStateHistory = board.gameStateHistory;
    movesHistory = board.movesHistory;
}

Board::~Board() {}

// Loading Positions

void Board::LoadPosition(PositionInfo posInfo) {
    Reset();
    pieces = posInfo.squarePieces;
    isWhiteTurn = posInfo.whiteToMove;
    presentGameState.castlingRights = posInfo.castlingRights;
    presentGameState.enPassantFile = posInfo.enPassantFile;
    presentGameState.fiftyMoveCounter = posInfo.fiftyMoveCounter;
    cntMoves = posInfo.fullmoveNumber * 2 - (isWhiteTurn ? 2 : 1);

    presentGameState = GameState(PIECE::None, posInfo.enPassantFile, posInfo.castlingRights, posInfo.fiftyMoveCounter);
    gameStateHistory.push_back(presentGameState);
}

void Board::LoadPosition(std::string FEN_notation) {
    PositionInfo posInfo = Fen::FenToPosition(FEN_notation);
    LoadPosition(posInfo);
}

void Board::LoadBasicPosition() {
    LoadPosition(Fen::StartPosition);
}

void Board::Reset() {
    gameStateHistory.clear();
    movesHistory.clear();
    presentGameState = GameState();
    gameStateHistory.push_back(presentGameState);

    isWhiteTurn = true;
    cntMoves = 0;
}

// More Validation

bool Board::ifCheck() const {
    int kingPos = getKingSquareIndex(isWhiteTurn);
    ulong attackedSquares = getAttackedSquares(isWhiteTurn ^ 1);
    return Bits::GetBit(attackedSquares, kingPos);
}

bool Board::ifCheckMate() {
    return ifCheck() && getLegalMoveList().size() == 0;
}

bool Board::ifStaleMate() {
    return !ifCheck() && getLegalMoveList().size() == 0;
}

bool Board::isBoardLegal() {
    int kingPos = getKingSquareIndex(isWhiteTurn ^ 1);
    ulong attackedSquares = getAttackedSquares(isWhiteTurn);
    return !Bits::GetBit(attackedSquares, kingPos);
}

bool Board::isPseudoMoveLegal(Move move) {
    if (!isPseudoMoveLegalWithoutCheck(move)) return false;
    std::vector<int> tmppieces = pieces;
    MakeMove(move, true);
    bool ans = isBoardLegal();
    UnmakeMove(move, true);
    if (tmppieces != pieces) {
        printf("ERROR\n");
        for(int i = 0; i < 64; i++) {
            printf("%d %d %d\n", i, tmppieces[i], pieces[i]);
        }
        exit(1);
    }
    return ans;
}

// Move History
bool Board::isHistoryEmpty() const {
    return movesHistory.size() == 0;
}

int Board::getMoveCount() const {
    return cntMoves;
}

Move Board::getLastMove() const
{
    return movesHistory.back();
}

std::vector<Move> Board::getMovesHistory() const {
    return movesHistory;
}

// Accessors

bool Board::ifWhiteTurn() const {
    return isWhiteTurn;
}
std::vector<int> Board::getAllPieces() const {
    return this->pieces;
}

// Game Functions

void Board::NewGame() {
    LoadBasicPosition();
}

void Board::MakeMove(Move move, bool inSearch) {
    int startSquare = move.startSquare;
    int targetSquare = move.targetSquare;
    int flag = move.flag;
    bool isPromotion = move.isPromotion();
    bool isEnpassant = (move.flag == Move::FLAG::EnPassant);

    int movePiece = pieces[startSquare];
    int movePieceType = PIECE::PieceType(movePiece);

    int capturedSquare = isEnpassant ? targetSquare + (isWhiteTurn ? -8 : 8) : targetSquare;
    int capturedPiece = pieces[capturedSquare];
    int capturedPieceType = PIECE::PieceType(pieces[capturedSquare]);

    int newCastlingRights = presentGameState.castlingRights;
    int newEnpassantFile = -1;

    // Handle captures (remove piece captured)
    if (capturedPiece != PIECE::None) {
        // iBoard.removePieceAtSquare(capturedPiece, capturedSquare);
        pieces[capturedSquare] = PIECE::None;
    }

    /// Note: After handle captures, piece can move to targetSquare
    MovePiece(movePiece, startSquare, targetSquare);

    // Handle King
    if (PIECE::PieceType(movePiece) == PIECE::King) {
        newCastlingRights &= (isWhiteTurn ? GameState::ClearWhiteCastleMask : GameState::ClearBlackCastleMask);

        if (move.flag == Move::FLAG::Castle) {
            // Move Rook
            int rookStartSquare = startSquare + (targetSquare < startSquare ? -4 : 3);
            int rookTargetSquare = startSquare + (targetSquare < startSquare ? -1 : 1);
            MovePiece(pieces[rookStartSquare], rookStartSquare, rookTargetSquare);
        }
    }

    // Handle Pawn (Promotion)
    if (isPromotion) {
        int promotionPiece = move.getPromotionType() + PIECE::boolToColor(isWhiteTurn);
        // iBoard.removePieceAtSquare(movePiece, targetSquare);
        // iBoard.addPieceAtSquare(promotionPiece, targetSquare);
        pieces[targetSquare] = promotionPiece;
    }

    /////////////////////// Update Current State ///////////////////////

    // Update move 2 square, allow enpassant
    if (move.flag == Move::PawnTwoStep) {
        newEnpassantFile = startSquare % 8;
    }
    
    // Update CastlingRights
    if (newCastlingRights != 0) {
        if (startSquare == 0 || targetSquare == 0) newCastlingRights &= GameState::ClearWhiteQueensideMask;
        if (startSquare == 7 || targetSquare == 7) newCastlingRights &= GameState::ClearWhiteKingsideMask;
        if (startSquare == 56 || targetSquare == 56) newCastlingRights &= GameState::ClearBlackQueensideMask;
        if (startSquare == 63 || targetSquare == 63) newCastlingRights &= GameState::ClearBlackKingsideMask;
        if (startSquare == 4) newCastlingRights &= GameState::ClearWhiteCastleMask;
        if (startSquare == 60) newCastlingRights &= GameState::ClearBlackCastleMask;
    }

    /// Note: may add zobrist key here (coming soon)  ///

    isWhiteTurn ^= 1;
    int newFiftyMoveCounter = presentGameState.fiftyMoveCounter + 1;
    cntMoves++;
    /// UpdateSliderBitboards();

    /// If pawn moves or piece is captured, reset fiftyMoveCounter
    if (movePieceType == PIECE::Pawn || capturedPieceType != PIECE::None) {
        newFiftyMoveCounter = 0;
    }

    GameState newGameState = GameState(capturedPieceType, newEnpassantFile, newCastlingRights, newFiftyMoveCounter); //, presentGameState.zobristKey);
    gameStateHistory.push_back(newGameState);
    presentGameState = newGameState;

    if (inSearch == false) {
        movesHistory.push_back(move);
    }
}

void Board::UnmakeMove(Move move, bool inSearch) {
    isWhiteTurn ^= 1;
    cntMoves--;

    int startSquare = move.startSquare;
    int targetSquare = move.targetSquare;
    int flag = move.flag;
    bool isPromotion = move.isPromotion();
    bool isEnpassant = (move.flag == Move::FLAG::EnPassant);

    int movePiece = pieces[targetSquare];

    int capturedSquare = targetSquare + (isEnpassant ? (isWhiteTurn ? -8 : 8) : 0);
    int capturedPieceType = presentGameState.capturedPieceType;
    int capturedPiece = capturedPieceType + PIECE::boolToColor(isWhiteTurn ^ 1);

    /////////////////////// Move Piece + Process State ///////////////////////

    // Handle Pawn (Promotion)
    if (isPromotion) {
        int promotionPiece = movePiece;
        movePiece = PIECE::Pawn + (isWhiteTurn ? PIECE::White : PIECE::Black);
        // iBoard.removePieceAtSquare(promotionPiece, targetSquare);
        // iBoard.addPieceAtSquare(movePiece, targetSquare);
        pieces[targetSquare] = movePiece;
    }

    MovePiece(movePiece, targetSquare, startSquare);

    // Handle captures (remove piece captured)
    if (capturedPieceType != PIECE::None) {
        // iBoard.addPieceAtSquare(capturedPiece, capturedSquare);
        pieces[capturedSquare] = capturedPiece;
    }

    // Handle King
    if (move.flag == Move::FLAG::Castle) {
        // Move Rook
        int rookStartSquare = startSquare + (targetSquare < startSquare ? -4 : 3);
        int rookTargetSquare = startSquare + (targetSquare < startSquare ? -1 : 1);
        MovePiece(pieces[rookTargetSquare], rookTargetSquare, rookStartSquare);
    }
    
    /// Note: may add zobrist key here (coming soon)  ///
    /// UpdateSliderBitboards();

    gameStateHistory.pop_back();
    presentGameState = gameStateHistory.back();

    if (inSearch == false) {
        movesHistory.pop_back();
    }
}

void Board::UndoMove() {
    UnmakeMove(getLastMove(), false);
}

void Board::MovePiece(int piece, int startSquare, int targetSquare) {
    pieces[startSquare] = PIECE::None;
    pieces[targetSquare] = piece;
}

// Private Helper Functions

bool Board::isSquareUnderAttack(int targetSquare, bool isWhiteTurn) const {
    ulong attackedSquares = getAttackedSquares(isWhiteTurn);
    return Bits::GetBit(attackedSquares, targetSquare);
}

bool Board::isPseudoMoveLegalWithoutCheck(Move move) const {
/// assert that startPiece is the same color with isWhiteTurn
    int startSquare = move.startSquare;
    int targetSquare = move.targetSquare;
    int flag = move.flag;
    bool isPromotion = move.isPromotion();
    bool isEnpassant = (move.flag == Move::FLAG::EnPassant);

    int startPiece = pieces[startSquare];
    int startPieceType = PIECE::PieceType(startPiece);
    int startPieceColor = PIECE::PieceColor(startPiece);

    int targetPiece = pieces[targetSquare];

    Point startIndex2D(startSquare / 8, startSquare % 8);
    Point endIndex2D(targetSquare / 8, targetSquare % 8);
    Point diff = endIndex2D - startIndex2D;

    if (startPiece == PIECE::None) {
        printf("Start piece is none\n");
        exit(1); // assert
    }
    if (startPieceColor != PIECE::boolToColor(isWhiteTurn)) {
        printf("Move piece has wrong color");
        exit(1); // assert
    }

    if (targetPiece != PIECE::None && PIECE::isPieceYourTurn(targetPiece, isWhiteTurn)) {
        return false;
    }
    else if (move.flag == Move::FLAG::EnPassant) {
        return (presentGameState.enPassantFile == endIndex2D.y);
    }
    else if (move.flag == Move::FLAG::Castle) {
        if (startPieceType != PIECE::King) {
            return false;
        }
        else {
            int isKingside = (endIndex2D.y == 2 ? 0 : 1);
            if (!presentGameState.IsCastlePossible(isWhiteTurn, isKingside)) {
                return false;
            }
            else {
                int rookFile = isKingside * 7;
                int stepFile = (isKingside ? 1 : -1);
                int newdiffFile = abs(rookFile - startIndex2D.y);
                for(int i = 1; i < newdiffFile; i++) {
                    if (PIECE::PieceType(getPiece(startIndex2D.x, startIndex2D.y + i * stepFile)) != PIECE::None) {
                        return false;
                    }
                }
                for(int i = 0; i < 3; i++) {
                    if (isSquareUnderAttack(startIndex2D.x * 8 + (startIndex2D.y + i * stepFile), isWhiteTurn ^ 1)) {
                        return false;
                    }
                }
                return true;
            }
        }
    }
    if (startPieceType == PIECE::Queen) {
        return isPreventPiece(startSquare, targetSquare) == false;
    }
    if (startPieceType == PIECE::Bishop) {
        return isPreventPiece(startSquare, targetSquare) == false;
    }
    if (startPieceType == PIECE::Knight) {
        return true;
    }
    if (startPieceType == PIECE::Rook) {
        return isPreventPiece(startSquare, targetSquare) == false;
    }
    if (startPieceType == PIECE::Pawn) {
        if (abs(diff.y) == 1) {
            return PIECE::PieceColor(targetPiece) == PIECE::boolToColor(isWhiteTurn ^ 1);
        }
        else {
            if (abs(diff.x) == 1) {
                return pieces[targetSquare] == PIECE::None;
            }
            else {
                return pieces[targetSquare] == PIECE::None && 
                    pieces[startSquare + diff.x * 4] == PIECE::None;
            }
        }
    }
    if (startPieceType == PIECE::King) {
        return true;
    }
    return false;
}

int Board::getPiece(int rank, int file) const
{
    return pieces[rank * 8 + file];
}

int Board::getPiece(int square) const
{
    return pieces[square];
}

int Board::getKingSquareIndex(bool colorTurn) const {
    for(int i = 0; i < 64; i++) {
        if (pieces[i] == (PIECE::King + PIECE::boolToColor(colorTurn))) {
            return i;
        }
    }
    return -1;
}

std::vector<Move> Board::getPseudoLegalMoveList() {
    std::vector<Move> moves;
    for(int i = 0; i < 64; i++) 
    if (PIECE::PieceColor(pieces[i]) == PIECE::boolToColor(isWhiteTurn)) {
        std::vector<Move> tmpMoves = BitboardProcess::getPseudoMoves(i, pieces[i]);
        for(Move move : tmpMoves) {
            if (isPseudoMoveLegalWithoutCheck(move)) 
                moves.push_back(move);
        }
    }
    return moves;
}

std::vector<Move> Board::getPseudoLegalMoveAt(int startSquare)
{
    std::vector<Move> moves;
    std::vector<Move> tmpMoves = BitboardProcess::getPseudoMoves(startSquare, pieces[startSquare]);
    for(Move move : tmpMoves) {
        if (isPseudoMoveLegalWithoutCheck(move)) 
            moves.push_back(move);
    }
    return moves;
}

std::vector<Move> Board::getLegalMoveAt(int startSquare) {
    std::vector<Move> legalMoves;
    std::vector<Move> pseudoMoves = getPseudoLegalMoveAt(startSquare);

    for(Move move : pseudoMoves) {
        if (isPseudoMoveLegal(move))
            legalMoves.push_back(move);
    }
    return legalMoves;
}

std::vector<Move> Board::getLegalMoveList() {
    std::vector<Move> legalMoves;
    std::vector<Move> pseudoMoves = getPseudoLegalMoveList();

    for(Move move : pseudoMoves) {
        if (isPseudoMoveLegal(move))
            legalMoves.push_back(move);
    }
    return legalMoves;
}

const GameState Board::getGameState() const {
    return presentGameState;
}

ulong Board::getAttackedSquares(bool isYourTurn) const {
    ulong attackedSquares = 0;
    for(int startSquare = 0; startSquare < 64; startSquare++) {
        if (PIECE::PieceColor(pieces[startSquare]) == PIECE::boolToColor(isYourTurn)) {
            ulong tmp = BitboardProcess::getAttackedSquares(startSquare, pieces[startSquare]);
            for(int targetSquare = Bits::PopBit(tmp); targetSquare != -1; targetSquare = Bits::PopBit(tmp)) {
                if (PIECE::PieceType(pieces[startSquare]) == PIECE::Knight || isPreventPiece(startSquare, targetSquare) == false)
                    attackedSquares |= (1ULL << targetSquare);
            }
            attackedSquares |= tmp;
        }
    }
    return attackedSquares;
}

bool Board::isPreventPiece(int startSquare, int targetSquare) const {
    Point startIndex2D(startSquare / 8, startSquare % 8);
    Point endIndex2D(targetSquare / 8, targetSquare % 8);
    Point diff = endIndex2D - startIndex2D;
    int stepRank = (diff.x >= 0 ? diff.x > 0 ? 1 : 0 : -1);
    int stepFile = (diff.y >= 0 ? diff.y > 0 ? 1 : 0 : -1);
    int step = stepRank * 8 + stepFile;

    for(startSquare += step; startSquare != targetSquare; startSquare += step) {
        if (pieces[startSquare] != PIECE::None) {
            return true;
        }
    }
    return false;
}