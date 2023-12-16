#ifndef __PieceInboardListPrint_hpp__
#define __PieceInboardListPrint_hpp__

#include <IngameScreen/PiecePrint.hpp>

class PieceInboardListPrint : public sf::Drawable {
public:
    PieceInboardListPrint(Point boardPosition, int cellSize);
    ~PieceInboardListPrint();
    void setPieceList(std::vector<int> pieceList);
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;
    const PiecePrint* operator [] (int index) const;

private:
    std::vector<PiecePrint*> piecePrintList;
};

#endif