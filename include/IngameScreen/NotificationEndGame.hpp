#ifndef __NotificationEndGame_hpp__
#define __NotificationEndGame_hpp__

#include <DataControl/Button.hpp>
#include <Graphic.hpp>

class NotificationEndGame : public Graphic {
public:
    enum Onclick { NEW_GAME = 1, BACK, CLOSE };
public:
    NotificationEndGame(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, 
            const sf::Font* sfFont, int result, std::string EndGameFlag);
    ~NotificationEndGame();
    bool handleEvent(const sf::Event& event);
    void update(sf::Time deltaTime);
    void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const override;

    Onclick getOnclick() const;
    void setEndGame(int result, std::string EndGameFlag);
    void setEndGame(std::string showButtonText, std::string EndGameFlag);

private:
    TextBox *showButton;
    TextBox *text;
    Button* newGameButton;
    Button* backButton;
    Button* closeButton;
    Onclick onclick;
};

#endif