#ifndef __GameSettings_hpp__
#define __GameSettings_hpp__

class GameSettings {
private:
    enum Mode {
        PvE = 0,
        EvP = 1,
        PvP = 2,
        EvE = 3
    };
    enum Difficulty {
        Easy = 0,
        Medium = 1,
        Hard = 2
    };
    // Bullet, Blitz, Rapid, Classical, Correspondence
    const int TimeTotal[11] = { 30, 60, 180, 180, 300, 300, 600, 600, 900, 1800, 3600 };
    const int TimeExtra[11] = {  0,  0,   0,   2,    0,  5,   0,   10,  10,   15,   30 };

private:
    int mode;
    int difficulty;
    int timeMode;
    bool isTime;
    bool isWhite;
    bool isBotHelp;

public:
    GameSettings();
    GameSettings(int mode, int difficulty, int timeMode, int extraTime, bool isTime, bool isWhite, bool isBotHelp);
    ~GameSettings();

    // Modifiers
    void setMode(int mode);
    void setDifficulty(int difficulty);
    void setTimeMode(int timeMode);
    void setIsTime(bool isTime);
    void setIsWhite(bool isWhite);
    void setIsBotHelp(bool isBotHelp);

    // Accessors
    int getMode() const;
    int getDifficulty() const;
    int getTimeTotal() const;
    int getTimeExtra() const;
    bool getIsTime() const;
    bool getIsWhite() const;
    bool getIsBotHelp() const;
};

#endif