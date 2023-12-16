#ifndef __ButttonPieceGroup_hpp__
#define __ButttonPieceGroup_hpp__

#include <DataControl/ButtonPiece.hpp>

class ButtonPieceGroup : public sf::Drawable {
public:
    ButtonPieceGroup(Point renderPosition);
    ~ButtonPieceGroup();

    // Accessors
    bool isPieceReleased() const;
    int getPieceReleased() const;

    // Modifiers
    void TurnOnPiece(int piece);

    // Functions
    bool handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

private:
    Button* title;
    std::vector<ButtonPiece*> buttonPieceList;
    int pieceReleased;
};

#endif