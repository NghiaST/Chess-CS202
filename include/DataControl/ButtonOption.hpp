#ifndef __ButtonOption_hpp__
#define __ButtonOption_hpp__

#include <DataControl/Button.hpp>
#include <Graphic.hpp>

class ButtonOption : public Graphic {
public:
    ButtonOption(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, 
            const sf::Font* sfFont, const ColorButMulti& colorButMulti, unsigned int sizeText = 12, 
            std::vector<std::string> textOptions = std::vector<std::string>(), int currentSelection = 0, float thickness = -1, Point renderOffsetText = Point(0, 0));
    ~ButtonOption();
    bool handleEvent(const sf::Event& event);
    void update(sf::Time deltaTime);
    // void updateRender();
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

    void setColorBM(const ColorButMulti& colorButMulti);
    void setCurrentSelection(int currentSelection);
    int getCurrentSelection() const;

private:
    Button* mainButton;
    Button* rollLeft;
    Button* rollRight;
    std::vector<std::string> textOptions;
    int currentSelection;
};

#endif