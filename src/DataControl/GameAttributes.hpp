#ifndef __GameAttributes_hpp__
#define __GameAttributes_hpp__

class GameAttributes {
public:
    GameAttributes();
    GameAttributes(int mode, int level, int timeWhite, int timeBlack, bool isBotHelp, bool isPlayerWhite);
    ~GameAttributes();
    void Loading();
    void Fresh();

    bool IsOutOfTime(bool isWhite) const;

public:
    int mode;
    int level;
    int timeWhite, timeBlack;
    bool isBotHelp;
    bool isPlayerWhite;
};

#endif