#ifndef __PromotionManager_hpp__
#define __PromotionManager_hpp__

#include <Graphic.hpp>
#include <IngameScreen/PiecePrint.hpp>
#include <DataControl/Theme.hpp>
#include <DataControl/Image.hpp>
#include <DataControl/Button.hpp>

class PromotionManager : public Graphic {
public:
    PromotionManager(int id, Point renderPosition, Point renderSize);
    ~PromotionManager();

    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

    bool handleEvent(const sf::Event& event);
    void setPromotionFile(int promotionFile);
    void setIsWhite(bool isWhite);
    void setIsRotate(bool isRotate);
    void updateRender();

    int getPiecePromotionType() const;

private:
    std::vector<PiecePrint> pieces; // Queen, Rook, Bishop, Knight
    std::vector<Button*> buttonPieces;
    std::vector<int> pieceType;

    int promotionFile;
    bool isWhite;
    bool isRotate;

    bool isClicked;
    int pieceClicked;
};

#endif