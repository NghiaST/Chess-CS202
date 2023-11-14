#ifndef __FileInit_hpp__
#define __FileInit_hpp__

#include <string>
#include <filesystem>
#include "../IngameScreen/NewBoard.hpp"
#include "../IngameScreen/Move.hpp"
#include "Theme.hpp"

class FileInit {
public:
    static void Init();
    static void Save(std::vector<Move> movesHistory, int mode, int level, int color, int timeWhite, int timeBlack);
    static bool Load(std::vector<Move>& movesHistory, int& mode, int& level, int& color, int& timeWhite, int& timeBlack);
    static ThemeIndex LoadTheme();
    static int LoadMode();
    static void SaveConfig(const ThemeIndex& themeIndex);
    // static void Load();

    static const std::string datConfig;
    static const std::string datGame;
    static const std::string datStatistics;
    static const std::string datOnlineGame;
    static const std::string datUsers;
};

#endif