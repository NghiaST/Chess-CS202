#ifndef __GameSettings_hpp__
#define __GameSettings_hpp__

struct GameSettings {
private:
    int firstturn;
    int time;
    int mode;
    int difficulty;
public:
    GameSettings();
    ~GameSettings();
    void setFirstTurn(int firstturn);
    void setTime(int time);
    void setMode(int mode);
    void setDifficulty(int difficulty);
    int getFirstTurn();
    int getTime();
    int getMode();
    int getDifficulty();
};

#endif