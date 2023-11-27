#ifndef __GameAttributes_hpp__
#define __GameAttributes_hpp__

#include <SFML/System/Clock.hpp>
#include <string>

class GameAttributes {
public:
    GameAttributes(bool isLoad = true);
    GameAttributes(int variants, int mode, int level, int timeTotalMode, int timeExtraMode, bool isBotHelp);
    ~GameAttributes();
    void NewLoading();
    void Loading();
    void Fresh();
    void UpdateTime();
    void switchTurn();
    void updateMakeMove();
    void setTurn(bool isWhiteTurn);
    void setCountDown(bool isCountDown);

    bool isOutOfTime() const;
    bool isOutOfTime(bool isWhite) const;
    bool IsCountDown() const;
    bool IsWhiteTurn() const;
    std::string getVariantsName() const;
    int getCurrentTime() const;
    int getTime(bool isWhite) const;

    // Accessors
    int getVariants() const;
    int getMode() const;
    int getLevel() const;
    int getTimeTotalMode() const;
    int getTimeExtraMode() const;
    bool getIsBotHelp() const;

protected:
    int variants;   // 0: Standard, 1: King of the Hill, 2: Crazyhouse
    int mode;
    int level;
    int timeWhite, timeBlack;
    bool isBotHelp;
    bool isPlayerWhite;

private:
    const std::string variantsName[3] = {"standard", "kingofthehill", "atomic"};
    const int TOTAL[8] = {60, 120, 180, 300, 600, 900, 1800, 3600};
    const int EXTRA[6] = {0, 2, 5, 10, 15, 30};
    sf::Clock clock;
    bool isCountDown;
    bool isWhiteTurn;
    int timeTotalMode;
    int timeExtraMode;

    friend class FileManager;
};

#endif