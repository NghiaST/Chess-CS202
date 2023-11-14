#ifndef __FileInit_hpp__
#define __FileInit_hpp__

#include <string>
#include <filesystem>
#include "../IngameScreen/Board.hpp"
#include "../IngameScreen/Move.hpp"
#include "Theme.hpp"

class FileInit {
public:
    static void Init();

    // Save
    // static void ExtractGame(std::string filename);
    static void SaveGame(const std::vector<Move>& movesHistory, int mode, int level, int timeWhite, int timeBlack);
    static void SaveTheme(const ThemeIndex& themeIndex);
    static void SaveOptions(int mode, int level, bool isBotHelp);
    static void SaveConfig(const ThemeIndex& themeIndex, int mode, int level, bool isBotHelp);

    // Load
    static bool LoadGame(std::vector<Move>& movesHistory, int& mode, int& level, int& timeWhite, int& timeBlack);
    static ThemeIndex LoadTheme();
    static void LoadOptions(int& mode, int& level, bool& isBotHelp);
    static void LoadConfig(ThemeIndex& themeIndex, int& mode, int& level, bool& isBotHelp);
    static int LoadMode();

    static const std::string datConfig;
    static const std::string datGame;
    static const std::string datStatistics;
    static const std::string datOnlineGame;
    static const std::string datUsers;
};

#endif