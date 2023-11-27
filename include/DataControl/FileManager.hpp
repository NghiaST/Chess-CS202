#ifndef __FileInit_hpp__
#define __FileInit_hpp__

#include <string>
#include <vector>

class Move;
class Board;
class ThemeIndex;
class GameAttributes;
class StatisticsData;

class FileManager {
public:
    static void Init();

    static void StoreCompletedGame(const Board& board, const GameAttributes& gameAttributes, int result);

    static void ExtractGame(const std::vector<Move>& movesHistory);
    static void SaveGame(const Board& board, const GameAttributes& gameAttributes);
    static void SaveGameMoves(const std::vector<Move>& movesHistory, const GameAttributes& gameAttributes);
    static void SaveGameFEN(const Board& board, const GameAttributes& gameAttributes);
    static void SaveTheme(const ThemeIndex& themeIndex);
    static void SaveConfig(const GameAttributes& gameAttributes);
    static void SaveThemeConfig(const ThemeIndex& themeIndex, const GameAttributes& gameAttributes);

    // Load
    static bool LoadGame(Board& board, GameAttributes& gameAttributes);
    static ThemeIndex LoadTheme();
    static void LoadConfig(GameAttributes& gameAttributes);
    static void LoadThemeConfig(ThemeIndex& themeIndex, GameAttributes& gameAttributes);
    static std::vector<StatisticsData> LoadStatistics();
    static void LoadPuzzles(Board& board, std::vector<Move>& movesSolution, std::string& quizName, std::string& quizLink, int puzzleNumber);

    static void CheckConfigAndSave();
    static void RemoveSaveGame();

private:
    static const std::string datHistory;
    static const std::string datConfig;
    static const std::string datSave;
    static const std::string datStatistics;
    static const std::string datOnlineGame;
    static const std::string datUsers;
    static const std::string datPuzzles;
};

#endif