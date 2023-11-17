#ifndef __FileInit_hpp__
#define __FileInit_hpp__

#include "../ChessBoard/Board.hpp"
#include "../ChessBoard/Move.hpp"
#include "Theme.hpp"
#include <string>
#include <filesystem>

class FileInit {
public:
    static void Init();

    // Save
    // static void ExtractGame(std::string filename);
    static void SaveGame(const Board& board, int mode, int level, int timeWhite, int timeBlack);
    static void SaveGameMoves(const std::vector<Move>& movesHistory, int mode, int level, int timeWhite, int timeBlack);
    static void SaveGameFEN(const Board& board, int mode, int level, int timeWhite, int timeBlack);
    static void SaveTheme(const ThemeIndex& themeIndex);
    static void SaveOptions(int mode, int level, bool isBotHelp);
    static void SaveConfig(const ThemeIndex& themeIndex, int mode, int level, bool isBotHelp);

    // Load
    static bool LoadGame(Board& board, int& mode, int& level, int& timeWhite, int& timeBlack);
    static ThemeIndex LoadTheme();
    static void LoadOptions(int& mode, int& level, bool& isBotHelp);
    static void LoadConfig(ThemeIndex& themeIndex, int& mode, int& level, bool& isBotHelp);
    static int LoadMode();

    static const std::string datConfig;
    static const std::string datGame;
    static const std::string saveGame;
    static const std::string datStatistics;
    static const std::string datOnlineGame;
    static const std::string datUsers;
};

#endif