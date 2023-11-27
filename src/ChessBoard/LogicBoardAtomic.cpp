#include <ChessBoard/LogicBoardAtomic.hpp>
#include <ChessBoard/LogicBoard.hpp>
#include <ChessBoard/Move.hpp>
#include <ChessBoard/Board.hpp>
#include <ChessBoard/GameState.hpp>

LogicBoardAtomic::LogicBoardAtomic()
  : LogicBoard() 
{
    BitboardUtility::Initialize(); 
    Reset();
    LoadBasicPosition();
    this->mIsMovesGeneratorInCache = false;
}

LogicBoardAtomic::~LogicBoardAtomic() {
}

Board *LogicBoardAtomic::clone() const {
    LogicBoardAtomic *cloneBoard = new LogicBoardAtomic();
    *cloneBoard = *this;
    return cloneBoard;
}
// More Validation

void LogicBoardAtomic::LoadPosition(PositionInfo posInfo) {
    Reset();
    pieces = posInfo.squarePieces;
    piecesHistory.push_back(pieces);
    mIsWhiteTurn = posInfo.whiteToMove;
    presentGameState.castlingRights = posInfo.castlingRights;
    presentGameState.enPassantFile = posInfo.enPassantFile;
    presentGameState.fiftyMoveCounter = posInfo.fiftyMoveCounter;
    cntMoves = posInfo.fullmoveNumber * 2 - (mIsWhiteTurn ? 2 : 1);

    presentGameState = GameState(PIECE::None, posInfo.enPassantFile, posInfo.castlingRights, posInfo.fiftyMoveCounter);
    gameStateHistory.push_back(presentGameState);
}

void LogicBoardAtomic::Reset()
{
    gameStateHistory.clear();
    movesHistory.clear();
    piecesHistory.clear();
    presentGameState = GameState();
    gameStateHistory.push_back(presentGameState);
    mIsWhiteTurn = true;
    cntMoves = 0;
    mUndoMoves.clear();
    mIsMovesGeneratorInCache = false;
}

bool LogicBoardAtomic::isCheck() const {
    int kingPos = getKingSquareIndex(mIsWhiteTurn);
    int kingPosB = getKingSquareIndex(!mIsWhiteTurn);
    int dis = std::max(abs(kingPos / 8 - kingPosB / 8), abs(kingPos % 8 - kingPosB % 8));
    return (kingPos != -1 && kingPosB != -1 && dis != 1 && isSquareUnderAttack(kingPos, mIsWhiteTurn ^ 1));
    // ulong attackedSquares = getAttackedSquares(isWhiteTurn ^ 1);
    // return Bits::GetBit(attackedSquares, kingPos);
}

bool LogicBoardAtomic::isCheckMate() {
    return !isKingDead() && isCheck() && isNextMoveImpossible();
}

bool LogicBoardAtomic::isStaleMate() {
    return !isKingDead() && !isCheck() && isNextMoveImpossible();
}

bool LogicBoardAtomic::isBoardLegal() {
    int kingPos = getKingSquareIndex(mIsWhiteTurn ^ 1);
    int kingPosB = getKingSquareIndex(mIsWhiteTurn);
    int dis = std::max(abs(kingPos / 8 - kingPosB / 8), abs(kingPos % 8 - kingPosB % 8));
    return kingPos != -1 && (kingPosB == -1 || dis == 1 || !isSquareUnderAttack(kingPos, mIsWhiteTurn));
    // ulong attackedSquares = getAttackedSquares(isWhiteTurn);
    // return !Bits::GetBit(attackedSquares, kingPos);
}

bool LogicBoardAtomic::isEndGame() {
    if (isKingDead()) {
        return true;
    }
    return isKingDead() || isCheckMate() || isStaleMate() || isFiftyMove();
}

bool LogicBoardAtomic::isWin() {
    return isKingDead() || isCheckMate();
}

bool LogicBoardAtomic::isDraw() {
    return !isKingDead() && (isStaleMate() || isFiftyMove());
}

Board::EndFlag LogicBoardAtomic::getEndFlag() {
    if (isKingDead()) return EndFlag::KingDead;
    if (isCheckMate()) return EndFlag::Checkmate;
    if (isStaleMate()) return EndFlag::Stalemate;
    if (isFiftyMove()) return EndFlag::FiftyMove;
    return EndFlag::Unknown;
}

void LogicBoardAtomic::MakeMove(Move move, bool inSearch) {
    int startSquare = move.startSquare;
    int targetSquare = move.targetSquare;
    int flag = move.flag;
    bool isPromotion = move.isPromotion();
    bool isEnpassant = (move.flag == Move::FLAG::EnPassant);

    int movePiece = pieces[startSquare];
    int movePieceType = PIECE::PieceType(movePiece);

    int capturedSquare = isEnpassant ? targetSquare + (mIsWhiteTurn ? -8 : 8) : targetSquare;
    int capturedPiece = pieces[capturedSquare];
    int capturedPieceType = PIECE::PieceType(pieces[capturedSquare]);

    int newCastlingRights = presentGameState.castlingRights;
    int newEnpassantFile = -1;


    /// Note: After handle captures, piece can move to targetSquare
    MovePiece(movePiece, startSquare, targetSquare);

    // Handle King
    if (PIECE::PieceType(movePiece) == PIECE::King) {
        newCastlingRights &= (mIsWhiteTurn ? GameState::ClearWhiteCastleMask : GameState::ClearBlackCastleMask);

        if (move.flag == Move::FLAG::Castle) {
            // Move Rook
            int rookStartSquare = startSquare + (targetSquare < startSquare ? -4 : 3);
            int rookTargetSquare = startSquare + (targetSquare < startSquare ? -1 : 1);
            MovePiece(pieces[rookStartSquare], rookStartSquare, rookTargetSquare);
        }
    }

    // Handle Pawn (Promotion)
    if (isPromotion) {
        int promotionPiece = move.getPromotionType() + PIECE::boolToColor(mIsWhiteTurn);
        // iBoard.removePieceAtSquare(movePiece, targetSquare);
        // iBoard.addPieceAtSquare(promotionPiece, targetSquare);
        pieces[targetSquare] = promotionPiece;
    }

    // Handle captures (remove piece captured)
    if (capturedPiece != PIECE::None) {
        // iBoard.removePieceAtSquare(capturedPiece, capturedSquare);
        ulong bit = BitboardUtility::KingMoves[capturedSquare];

        for(int square = Bits::PopBit(bit); square != -1; square = Bits::PopBit(bit)) {
            if (PIECE::PieceType(pieces[square]) != PIECE::Pawn)
                pieces[square] = PIECE::None;
        }
        pieces[capturedSquare] = PIECE::None;
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

    mIsWhiteTurn ^= 1;
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
    mIsMovesGeneratorInCache = false;

    piecesHistory.push_back(pieces);
    if (inSearch == false) {
        movesHistory.push_back(move);
    }
}

void LogicBoardAtomic::UnmakeMove(Move move, bool inSearch) {
    mIsWhiteTurn ^= 1;
    cntMoves--;

    piecesHistory.pop_back();
    pieces = piecesHistory.back();
    gameStateHistory.pop_back();
    presentGameState = gameStateHistory.back();
    mIsMovesGeneratorInCache = false;

    if (inSearch == false) {
        movesHistory.pop_back();
    }
}

std::vector<Move> LogicBoardAtomic::GenerateMoves() {
    if (mIsMovesGeneratorInCache) {
        return movesGeneratorCache;
    }
    mIsMovesGeneratorInCache = true;
    movesGeneratorCache.clear();
    std::vector<Move> pseudoMoveList = GeneratePseudoMovesNotKingCheck();
    for (Move pseudoMove : pseudoMoveList) {
        if (isPseudoMoveLegal(pseudoMove)) {
            movesGeneratorCache.push_back(pseudoMove);
        }
    }
    return movesGeneratorCache;
}

std::vector<Move> LogicBoardAtomic::GenerateMovesSquare(int startSquare) {
    std::vector<Move> pseudoMoveList = GeneratePseudoMovesSquareNotKingCheck(startSquare);
    std::vector<Move> legalMoveList;
    for (Move pseudoMove : pseudoMoveList) {
        if (isPseudoMoveLegal(pseudoMove)) {
            legalMoveList.push_back(pseudoMove);
        }
    }
    return legalMoveList;
}

bool LogicBoardAtomic::isMoveLegal(Move move) {
    return isMovePseudo(move) && isPseudoMoveLegal(move);
}

/// Private

bool LogicBoardAtomic::isKingDead() const {
    return getKingSquareIndex(mIsWhiteTurn) == -1;
}

bool LogicBoardAtomic::isMovePseudo(Move move) const {
    return false;
}

bool LogicBoardAtomic::isPseudoMoveLegal(Move move) {
    if (!isPseudoMoveLegalNotKingCheck(move)) return false;
    MakeMove(move, true);
    bool ans = isBoardLegal();
    UnmakeMove(move, true);
    return ans;
}

bool LogicBoardAtomic::isPseudoMoveLegalNotKingCheck(Move move) const {
/// assert that startPiece has the same color as isWhiteTurn
    int startSquare = move.startSquare;
    int targetSquare = move.targetSquare;
    int flag = move.flag;
    bool isPromotion = move.isPromotion();
    bool isEnpassant = (move.flag == Move::FLAG::EnPassant);

    int startPiece = getPiece(startSquare);
    int startPieceType = PIECE::PieceType(startPiece);
    int startPieceColor = PIECE::PieceColor(startPiece);

    int targetPiece = getPiece(targetSquare);

    Point startIndex2D(startSquare / 8, startSquare % 8);
    Point endIndex2D(targetSquare / 8, targetSquare % 8);
    Point diff = endIndex2D - startIndex2D;

    if (targetPiece != PIECE::None && PIECE::isPieceYourTurn(targetPiece, mIsWhiteTurn)) {
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
            if (!presentGameState.IsCastlePossible(mIsWhiteTurn, isKingside)) {
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
                    if (isSquareUnderAttack(startIndex2D.x * 8 + (startIndex2D.y + i * stepFile), mIsWhiteTurn ^ 1)) {
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
            return PIECE::PieceColor(targetPiece) == PIECE::boolToColor(mIsWhiteTurn ^ 1);
        }
        else {
            if (abs(diff.x) == 1) {
                return getPiece(targetSquare) == PIECE::None;
            }
            else {
                return getPiece(targetSquare) == PIECE::None && 
                    getPiece(startSquare + diff.x * 4) == PIECE::None;
            }
        }
    }
    if (startPieceType == PIECE::King) {
        if (getPiece(targetSquare) != PIECE::None)
            return false;
        return true;
    }
    return false;
}

std::vector<Move> LogicBoardAtomic::GeneratePseudoMovesNotKingCheck() const {
    std::vector<Move> moves;
    for(int i = 0; i < 64; i++) 
    if (PIECE::PieceColor(getPiece(i)) == PIECE::boolToColor(mIsWhiteTurn)) {
        std::vector<Move> tmpMoves = BitboardProcess::getPseudoMoves(i, getPiece(i));
        for(Move move : tmpMoves) {
            if (isPseudoMoveLegalNotKingCheck(move)) 
                moves.push_back(move);
        }
    }
    return moves;
}

std::vector<Move> LogicBoardAtomic::GeneratePseudoMovesSquareNotKingCheck(int startSquare) {
    std::vector<Move> moves;
    std::vector<Move> tmpMoves = BitboardProcess::getPseudoMoves(startSquare, getPiece(startSquare));
    for(Move move : tmpMoves) {
        if (isPseudoMoveLegalNotKingCheck(move)) 
            moves.push_back(move);
    }
    return moves;
}

ulong LogicBoardAtomic::getAttackedSquares(bool isYourTurn) const {
    ulong attackedSquares = 0;
    for(int startSquare = 0; startSquare < 64; startSquare++) {
        int startPiece = getPiece(startSquare);
        if (PIECE::PieceColor(startPiece) == PIECE::boolToColor(isYourTurn)) {
            ulong tmp = BitboardProcess::getAttackedSquares(startSquare, startPiece);
            for(int targetSquare = Bits::PopBit(tmp); targetSquare != -1; targetSquare = Bits::PopBit(tmp)) {
                if (PIECE::PieceType(startPiece) == PIECE::Knight || isPreventPiece(startSquare, targetSquare) == false)
                    attackedSquares |= (1ULL << targetSquare);
            }
            attackedSquares |= tmp;
        }
    }
    return attackedSquares;
}

bool LogicBoardAtomic::isSquareUnderAttack(int targetSquare, bool isWhiteTurn) const {
    ulong attackedSquares = getAttackedSquares(isWhiteTurn);
    return Bits::GetBit(attackedSquares, targetSquare);
}

bool LogicBoardAtomic::isPreventPiece(int startSquare, int targetSquare) const {
    Point startIndex2D(startSquare / 8, startSquare % 8);
    Point endIndex2D(targetSquare / 8, targetSquare % 8);
    Point diff = endIndex2D - startIndex2D;
    int stepRank = (diff.x >= 0 ? diff.x > 0 ? 1 : 0 : -1);
    int stepFile = (diff.y >= 0 ? diff.y > 0 ? 1 : 0 : -1);
    int step = stepRank * 8 + stepFile;

    for(startSquare += step; startSquare != targetSquare; startSquare += step) {
        if (getPiece(startSquare) != PIECE::None) {
            return true;
        }
    }
    return false;
}