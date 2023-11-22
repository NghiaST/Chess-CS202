#ifndef __FileInit_hpp__
#define __FileInit_hpp__

#include <string>
#include <vector>

class Move;
class Board;
class ThemeIndex;
class GameAttributes;
class StatisticsData;

class FileInit {
public:
    static void Init();

    static void StoreCompletedGame(const Board& board, int mode, int level, int result);

    static void ExtractGame(const std::vector<Move>& movesHistory);
    static void SaveGame(const Board& board, const GameAttributes& gameAttributes);
    static void SaveGameMoves(const std::vector<Move>& movesHistory, const GameAttributes& gameAttributes);
    static void SaveGameFEN(const Board& board, const GameAttributes& gameAttributes);
    static void SaveTheme(const ThemeIndex& themeIndex);
    static void SaveOptions(int mode, int level, bool isBotHelp, int timeTotalMode, int timeExtraMode);
    static void SaveConfig(const ThemeIndex& themeIndex, int mode, int level, bool isBotHelp, int timeTotalMode, int timeExtraMode);
    // Load
    static bool LoadGame(Board& board, GameAttributes& gameAttributes);
    static ThemeIndex LoadTheme();
    static void LoadOptions(int& mode, int& level, bool& isBotHelp, int& timeTotalMode, int& timeExtraMode);
    static void LoadConfig(ThemeIndex& themeIndex, int& mode, int& level, bool& isBotHelp, int& timeTotalMode, int& timeExtraMode);
    static std::vector<StatisticsData> LoadStatistics();

    static void RemoveSaveGame();

private:
    static const std::string datHistory;
    static const std::string datConfig;
    static const std::string datSave;
    static const std::string datStatistics;
    static const std::string datOnlineGame;
    static const std::string datUsers;
};

#endif