#include <IngameScreen/PieceInboardListPrint.hpp>

PieceInboardListPrint::PieceInboardListPrint() {
    piecePrintList.assign(64, nullptr);
    for(auto it = piecePrintList.begin(); it != piecePrintList.end(); ++it) {
        int index = std::distance(piecePrintList.begin(), it);
        *it = new PiecePrint(this->boardPosition, this->cellSize, index, PIECE::None);
    }
}