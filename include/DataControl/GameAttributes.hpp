#ifndef __GameAttributes_hpp__
#define __GameAttributes_hpp__

#include <SFML/System/Clock.hpp>

class GameAttributes {
public:
    GameAttributes();
    GameAttributes(int mode, int level, int timeWhite, int timeBlack, bool isBotHelp, bool isPlayerWhite);
    ~GameAttributes();
    void NewLoading();
    void Loading();
    void Fresh();
    void UpdateTime();
    void switchTurn();
    void setTurn(bool isWhiteTurn);
    void setCountDown(bool isCountDown);

    bool isOutOfTime() const;
    bool isOutOfTime(bool isWhite) const;
    bool IsCountDown() const;
    bool IsWhiteTurn() const;
    int getCurrentTime() const;
    int getTime(bool isWhite) const;

protected:
    int mode;
    int level;
    int timeWhite, timeBlack;
    bool isBotHelp;
    bool isPlayerWhite;

private:
    sf::Clock clock;
    bool isCountDown;
    bool isWhiteTurn;
    int timeTotal;
    int timeExtra;

    friend class FileInit;
};

#endif