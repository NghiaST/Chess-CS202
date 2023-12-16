#ifndef __ButttonPiece_hpp__
#define __ButttonPiece_hpp__

#include <IngameScreen/PiecePrint.hpp>
#include <DataControl/Button.hpp>

class ButtonPiece : public sf::Drawable {
public:
    ButtonPiece(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin,
        const sf::Font* sfFont, const ColorButMulti& colorButMulti, float thickness = -1);
    ~ButtonPiece();
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

    // Accessors
    Button* getButton();
    PiecePrint* getImage();

    int getButtonID() const;
    const ColorButMulti& getColorButMulti() const;
    int getButtonState() const;

    // Mutators
    void TurnPiece(bool isTurnOn);
    void setColorBM(const ColorButMulti& colorButMulti);
    void setMainPosition(Point renderPosition);
    void setRenderSize(Point renderSize);

    // Functions
    bool handleEvent(const sf::Event& event);

private:
    Button* button;
    PiecePrint* image;
};
    
#endif