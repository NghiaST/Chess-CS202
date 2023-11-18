#include <DataControl/Include.hpp>

int PIECE::MakePiece(int pieceType, int pieceColor) {
    return pieceType | pieceColor;
}
bool PIECE::isWhite(int piece) {
    return (piece & White) != 0;
}
bool PIECE::isPieceYourTurn(int piece, bool isWhiteTurn) {
    if (piece == None) return false;
    return (isWhite(piece) == isWhiteTurn);
}
int PIECE::boolToColor(bool isWhite) {
    return isWhite ? White : Black;
}
int PIECE::PieceColor(int piece)
{
    return piece & AllColor;
}
int PIECE::PieceType(int piece) {
    return piece & AllType;
}
char PIECE::PieceToSymbol(int piece) {
    switch (piece) {
        case WhitePawn: return 'P';
        case WhiteKnight: return 'N';
        case WhiteBishop: return 'B';
        case WhiteRook: return 'R';
        case WhiteQueen: return 'Q';
        case WhiteKing: return 'K';
        case BlackPawn: return 'p';
        case BlackKnight: return 'n';
        case BlackBishop: return 'b';
        case BlackRook: return 'r';
        case BlackQueen: return 'q';
        case BlackKing: return 'k';
        default: return ' ';
    }
}
int PIECE::SymbolToPiece(char symbol) {
    switch (symbol) {
        case 'P': return WhitePawn;
        case 'N': return WhiteKnight;
        case 'B': return WhiteBishop;
        case 'R': return WhiteRook;
        case 'Q': return WhiteQueen;
        case 'K': return WhiteKing;
        case 'p': return BlackPawn;
        case 'n': return BlackKnight;
        case 'b': return BlackBishop;
        case 'r': return BlackRook;
        case 'q': return BlackQueen;
        case 'k': return BlackKing;
        default: return 0;
    }
}

char PIECE::PieceTypeToChar(int pieceType) {
    switch (pieceType) {
        case Pawn: return 'P';
        case Knight: return 'N';
        case Bishop: return 'B';
        case Rook: return 'R';
        case Queen: return 'Q';
        case King: return 'K';
        default: return ' ';
    }
}

char PIECE::SymbolToPieceType(char symbol) {
    switch (symbol) {
        case 'P': return Pawn;
        case 'N': return Knight;
        case 'B': return Bishop;
        case 'R': return Rook;
        case 'Q': return Queen;
        case 'K': return King;
        default: return 0;
    }
}

int PIECE::PieceValue(int piece) {
    switch (piece) {
        case WhitePawn: return 100;
        case WhiteKnight: return 320;
        case WhiteBishop: return 330;
        case WhiteRook: return 500;
        case WhiteQueen: return 900;
        case WhiteKing: return 0;
        case BlackPawn: return -100;
        case BlackKnight: return -320;
        case BlackBishop: return -330;
        case BlackRook: return -500;
        case BlackQueen: return -900;
        case BlackKing: return 0;
        default: return 0;
    }
}