#include "Chess.hpp"

Chess::Chess() {
    frontEnd = new FrontEnd();
    pieceBoard = new PieceBoard();
}

Chess::~Chess() {
    delete frontEnd;
    delete pieceBoard;
}

void Chess::run() {
    while (frontEnd->isRunning()) {
        frontEnd->processEvents();
        pieceBoard->update(frontEnd);
        pieceBoard->preparePrint(frontEnd->getTheme());
        pieceBoard->print(frontEnd->getWindow());
        frontEnd->print();
    }
}