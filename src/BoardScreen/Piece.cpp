#include "Piece.hpp"
#include "PieceBoard.hpp"
#include <algorithm>

Piece::Piece(int position, CHESS::COLOR pieceColor, PIECE::TYPE pieceType, int status)
{
    this->position = position;
    this->posx = position / 8;
    this->posy = position % 8;
    this->pieceColor = pieceColor;
    this->pieceType = pieceType;
    this->pieceData = pieceColor | pieceType;
    this->status = status;
    this->mousestatus = MOUSE::NONE;
    this->renderPosition = INTERFACE::POSBOARD;
}

Piece::Piece(int position, int pieceData, int status)
{
    this->position = position;
    this->posx = position / 8;
    this->posy = position % 8;
    this->pieceColor = (CHESS::COLOR)(pieceData & CHESS::BLACKWHITE);
    this->pieceType = (PIECE::TYPE)(pieceData & 7);
    this->pieceData = pieceData;
    this->status = status;
    this->mousestatus = MOUSE::NONE;
    this->renderPosition = INTERFACE::POSBOARD;
}

Piece::~Piece()
{
}

int Piece::ifMoveLegal(const PieceBoard* board, int position) const
{
    const static int LEGAL = 1, ILLEGAL = 0;

    if (position < 0 || position > 63 || position == this->position) {
        return ILLEGAL;
    }
    int posx = position / 8;
    int posy = position % 8;
    int diffx = posx - this->posx;
    int diffy = posy - this->posy;
    if (pieceType == PIECE::NONE) {
        return ILLEGAL;
    }
    if (board->getPiece(position)->getPieceColor() == this->pieceColor) {
        return ILLEGAL;
    }
    if (pieceType == PIECE::KING) {
        // implementation of ifMoveLegal function for king
        int distance = std::max(abs(diffx), abs(diffy));
        if (distance == 1) {
            return LEGAL;
        }
        else {
            return ILLEGAL;
        }
    }
    if (pieceType == PIECE::QUEEN) {
        // implementation of ifMoveLegal function for queen
        if (diffx != 0 && diffy != 0 && abs(diffx) != abs(diffy)) {
            return ILLEGAL;
        }
        else {
            int stepx = (diffx >= 0 ? diffx > 0 ? 1 : 0 : -1);
            int stepy = (diffy >= 0 ? diffy > 0 ? 1 : 0 : -1);
            int rright = abs(diffx) | abs(diffy);
            for (int i = 1; i < rright; i++) {
                if (board->getPiece(this->posx + i * stepx, this->posy + i * stepy)->getPieceType() != PIECE::NONE) {
                    return ILLEGAL;
                }
            }
            return LEGAL;
        }
    }
    if (pieceType == PIECE::BISHOP) {
        // implementation of ifMoveLegal function for bishop
        if (diffx == 0 || diffy == 0 || abs(diffx) != abs(diffy)) {
            return ILLEGAL;
        }
        else {
            int stepx = diffx / abs(diffx);
            int stepy = diffy / abs(diffy);
            for (int i = 1; i < abs(diffx); i++) {
                if (board->getPiece(this->posx + i * stepx, this->posy + i * stepy)->getPieceType() != PIECE::NONE) {
                    return ILLEGAL;
                }
            }
            return LEGAL;
        }

    }
    if (pieceType == PIECE::KNIGHT) {
        // implementation of ifMoveLegal function for knight
        if (abs(diffx) == 1 && abs(diffy) == 2) {
            return LEGAL;
        }
        else if (abs(diffx) == 2 && abs(diffy) == 1) {
            return LEGAL;
        }
        else {
            return ILLEGAL;
        }
    }
    if (pieceType == PIECE::ROOK) {
        // implementation of ifMoveLegal function for rook
        if (diffx != 0 && diffy != 0) {
            return ILLEGAL;
        }
        else {
            int stepx = (diffx >= 0 ? diffx > 0 ? 1 : 0 : -1);
            int stepy = (diffy >= 0 ? diffy > 0 ? 1 : 0 : -1);
            for (int i = 1; i < abs(diffx + diffy); i++) {
                if (board->getPiece(this->posx + i * stepx, this->posy + i * stepy)->getPieceType() != PIECE::NONE) {
                    return ILLEGAL;
                }
            }
            return LEGAL;
        }
    }
    if (pieceType == PIECE::PAWN) {
        // implementation of ifMoveLegal function for pawn
        int direct = (pieceColor == CHESS::WHITE) ? 1 : -1;
        if (diffx == 0 && direct * diffy == 1) {
            if (board->getPiece(position)->getPieceType() == PIECE::NONE) {
                return LEGAL;
            }
            else {
                return ILLEGAL;
            }
        }
        else if (abs(diffx) == 1 && direct * diffy == 1) {
            if (board->getPiece(position)->getPieceColor() ^ this->pieceColor == CHESS::BLACKWHITE) {
                return LEGAL;
            }
            else {
                return ILLEGAL;
            }
        }
        else if (diffx == 0 && direct * diffy == 2) {
            int horizontal = (direct == 1 ? this->posy : 7 - this->posy);
            if (horizontal < 2 && board->getPiece(position)->getPieceType() == PIECE::NONE && board->getPiece(this->posx, this->posy + direct)->getPieceType() == PIECE::NONE) {
                return LEGAL;
            }
            else {
                return ILLEGAL;
            }
        }
    }
    return ILLEGAL;
}

std::vector<int> Piece::getPossibleMove(const PieceBoard* board) const
{
    std::vector<int> legalMove;
    for (int i = 0; i < 64; i++) {
        if (ifMoveLegal(board, i)) {
            legalMove.push_back(i);
        }
    }
    return legalMove;
}

const PIECE::TYPE& Piece::getPieceType() const {
    return pieceType;
}
const CHESS::COLOR& Piece::getPieceColor() const {
    return pieceColor;
}
const int& Piece::getPieceData() const {
    return pieceData;
}
void Piece::setPieceType(int pieceType) {
    setPiece(this->pieceColor, pieceType);
}
void Piece::setPieceColor(int pieceColor) {
    setPiece(pieceColor, this->pieceType);
}
void Piece::setPieceData(int pieceData) {
    setPiece(pieceData & CHESS::ALLCOLOR, pieceData & PIECE::ALLTYPE);
}
void Piece::setPiece(int pieceColor, int pieceType) {
    this->pieceColor = (CHESS::COLOR) pieceColor;
    this->pieceType = (PIECE::TYPE) pieceType;
    this->pieceData = pieceColor | pieceType;
}
void Piece::setMouseStatus(int mousestatus)
{
    this->mousestatus = (MOUSE::STATUS) mousestatus;
}
void Piece::setPosition(int position)
{
    this->position = position;
    this->posx = position / 8;
    this->posy = position % 8;
}

void Piece::update(const Theme* theme) {
    double size_board = renderSize.x;
    const sf::Texture& texture = theme->getPieceTexture(pieceData);
    sf::Vector2u size = texture.getSize();
    if (size == sf::Vector2u(0, 0)) return;

    int printPosx = renderPosition.x + posx * size_board;
    int printPosy = renderPosition.y + (7 - posy) * size_board;
    
    sprite.setTexture(texture);
    sprite.setScale(size_board / size.x, size_board / size.y);
    sprite.setPosition(printPosx, printPosy);
}

void Piece::render(sf::RenderTarget& target, sf::RenderStates state)
{
    target.draw(sprite);
}