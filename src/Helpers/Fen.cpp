#include <Helpers/Fen.hpp>
#include <ChessBoard/Board.hpp>
#include <DataControl/Include.hpp>

const std::string Fen::StartPosition = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

PositionInfo::PositionInfo(std::string fen) {
    squarePieces.assign(64, PIECE::None);

    int rank = 7;
    int file = 0;

    std::vector<std::string> tokens;
    do {
        while (fen.size() && fen[0] == ' ') {
            fen = fen.substr(1);
        }
        if (fen.find(" ") != std::string::npos) {
            tokens.push_back(fen.substr(0, fen.find(" ")));
            fen = fen.substr(fen.find(" ") + 1);
        }
        else if (fen.size()) {
            tokens.push_back(fen);
            fen = "";
        }
    } while (fen.size());
    
    if (tokens.size() != 6) {
        throw std::invalid_argument("Invalid FEN string");
        return;
    }

    for(char c : tokens[0]) {
        if (c == '/') {
            rank--;
            file = 0;
        }
        else if ('0' <= c && c <= '9') {
            file += c - '0';
        }
        else {
            squarePieces[rank * 8 + file] = PIECE::SymbolToPiece(c);
            file++;
        }
    }
    whiteToMove = (tokens[1] == "w");
    castlingRights = 0;
    if (tokens[2] != "-") {
        for(char c : tokens[2]) {
            if (c == 'K') {
                castlingRights |= CASTLING::WhiteKingSide;
            }
            else if (c == 'Q') {
                castlingRights |= CASTLING::WhiteQueenSide;
            }
            else if (c == 'k') {
                castlingRights |= CASTLING::BlackKingSide;
            }
            else if (c == 'q') {
                castlingRights |= CASTLING::BlackQueenSide;
            }
        }
    }
    enPassantFile = (tokens[3] == "-" ? -1 : tokens[3][0] - 'a');
    fiftyMoveCounter = std::stoi(tokens[4]);
    fullmoveNumber = std::stoi(tokens[5]);
}

PositionInfo::PositionInfo(std::vector<int> squarePieces, bool whiteToMove, int castlingRights, int enPassantFile, int fiftyMoveCounter, int fullmoveNumber) {
    this->squarePieces = squarePieces;
    this->whiteToMove = whiteToMove;
    this->castlingRights = castlingRights;
    this->enPassantFile = enPassantFile;
    this->fiftyMoveCounter = fiftyMoveCounter;
    this->fullmoveNumber = fullmoveNumber;
}

PositionInfo PositionInfo::BoardToPosition(const Board &board) {
    std::vector<int> pieces = board.getAllPieces();
    GameState gameState = board.getGameState();
    int cntMoves = board.getMoveCount();
    return PositionInfo(pieces, !(cntMoves & 1), gameState.castlingRights, gameState.enPassantFile, gameState.fiftyMoveCounter, cntMoves);
}

std::string Fen::PositionToFen(PositionInfo position) {
    std::string fen = "";
    int emptySquares = 0;

    for(int rank = 7; rank >= 0; rank--) {
        for(int file = 0; file < 8; file++) {
            int piece = position.squarePieces[rank * 8 + file];
            if (piece == PIECE::None) {
                emptySquares++;
            }
            else {
                if (emptySquares > 0) {
                    fen += std::to_string(emptySquares);
                    emptySquares = 0;
                }
                fen += PIECE::PieceToSymbol(piece);
            }
        }
        if (emptySquares > 0) {
            fen += std::to_string(emptySquares);
            emptySquares = 0;
        }
        if (rank > 0) {
            fen += "/";
        }
    }

    fen += position.whiteToMove ? " w " : " b ";

    if (position.castlingRights == 0) {
        fen += "-";
    }
    else {
        if (position.castlingRights & CASTLING::WhiteKingSide) {
            fen += "K";
        }
        if (position.castlingRights & CASTLING::WhiteQueenSide) {
            fen += "Q";
        }
        if (position.castlingRights & CASTLING::BlackKingSide) {
            fen += "k";
        }
        if (position.castlingRights & CASTLING::BlackQueenSide) {
            fen += "q";
        }
    }

    fen += " ";

    if (position.enPassantFile == -1) {
        fen += "-";
    }
    else {
        fen += (char)('a' + position.enPassantFile);
        fen += position.whiteToMove ? "6" : "3";
    }

    fen += " ";
    fen += std::to_string(position.fiftyMoveCounter);
    fen += " ";
    fen += std::to_string(position.fullmoveNumber);

    return fen;
}

PositionInfo Fen::FenToPosition(std::string fen) {
    return PositionInfo(fen);
}