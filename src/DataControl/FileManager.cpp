#include <DataControl/FileManager.hpp>
#include <DataControl/Theme.hpp>
#include <DataControl/GameAttributes.hpp>
#include <Helpers/MoveUtility.hpp>
#include <Helpers/FEN.hpp>
#include <ChessBoard/Move.hpp>
#include <ChessBoard/Board.hpp>
#include <ChessBoard/LogicBoard.hpp>
#include <ChessBoard/LogicBoardStandard.hpp>
#include <fstream>
#include <filesystem>
#include <StatisticsScreen/ProcessStatistics.hpp>

const std::string FileManager::datHistory = "dat/history.dat";
const std::string FileManager::datConfig = "dat/config.dat";
const std::string FileManager::datSave = "dat/save.dat";
const std::string FileManager::datStatistics = "dat/statistics.dat";
const std::string FileManager::datOnlineGame = "dat/onlinegame.dat";
const std::string FileManager::datUsers = "dat/users.dat";

/*
    About datConfig:
        1st line: themeIndex: Background, Piece, Board, Button, Text
        2nd line: mode (PvE, EvP, PvP, EvE), bot level (1,2,3,etc), BotHelp(N/Y)
//        more: soundIndex: Sound, Music
    
    About datUsers:
        1st line: number of users
        n lines next: username password

    About datStatistics: each player have
        1st line: username
        2st line: total game played
        3nd line: game played with computer
        4nd line: game won/draw/lost with computer at level easy
        5rd line: game won/draw/lost with computer at level medium
        6th line: game won/draw/lost with computer at level hard
    
    About datGame: store last game played
        1st: mode, level (PvE, EvP, PvP, EvE)
        2nd: timeWhite, timeBlack
        3rd line: number of moves (halfmoves)
        4nd line: movesHistory

    About function: saveGame: store game saved / loadGameFromFile:
    -> 2 type of stored: FEN and movesHistory
        if (FEN)
            1st line: FEN
        else
            1st line: number of moves (halfmoves)
            2nd line: movesHistory 
          or
            line i: round i (whiteMove blackMove)
*/

void FileManager::Init() {
    if (!std::filesystem::exists("dat")) {
        std::filesystem::create_directory("dat");
    }
    // if file is not exist then create file
    if (!std::filesystem::exists(datConfig)) {
        std::ofstream file(datConfig);
        file << "0 0 0 0 0\n0 0 0 0 0 0";
        file.close();
    }
    if (!std::filesystem::exists(datStatistics)) {
        std::ofstream file(datStatistics);
        file << "0";
        file.close();
    }
}

void FileManager::StoreCompletedGame(const Board &board, const GameAttributes& gameAttributes, int result) {
    // line 1: number of games
    // then, each game have 2 lines
    /*
        1st line: mode, level, result
        2nd line: UCI moves
    */
    if (!std::filesystem::exists(datHistory)) {
        std::ofstream file(datHistory);
        file << "0";
        file.close();
    }
    std::ifstream file(datHistory);
    int cntGames;
    file >> cntGames;
    file.ignore();
    std::string all, line;
    while (getline(file, line)) {
        all += line + "\n";
    }
    file.close();

    std::ofstream file2(datHistory);
    file2 << cntGames + 1 << "\n";
    file2 << all;
    file2 << gameAttributes.variants << " " << gameAttributes.mode << " " << gameAttributes.level << " " << result << "\n";
    std::vector<Move> movesHistory = board.getMovesHistory();
    for (int i = 0; i < (int)movesHistory.size(); ++i) {
        std::string moveName = MoveUtility::GetMoveNameUCI(movesHistory[i]);
        file2 << moveName << " ";
    }
    file2.close();
}

void FileManager::ExtractGame(const std::vector<Move>& movesHistory) {
    std::ofstream file("extract.txt");
    SBoard sBoard("standard");
    Board* board = sBoard.getBoard();
    for (int i = 0; i < (int)movesHistory.size(); ++i) {
        std::string moveName = MoveUtility::GetMoveNameSAN(movesHistory[i], *board);
        file << moveName << " \n"[i & 1];
        board->MakeMove(movesHistory[i]);
    }
    file.close();
}

void FileManager::SaveGame(const Board& board, const GameAttributes& gameAttributes) {
    std::vector<Move> movesHistory = board.getMovesHistory();
    int cntMoves = board.getMoveCount();
    if (cntMoves == (int) movesHistory.size()) {
        SaveGameMoves(movesHistory, gameAttributes);
    }
    else {
        SaveGameFEN(board, gameAttributes);
    }
}

void FileManager::SaveGameMoves(const std::vector<Move>& movesHistory, const GameAttributes& gameAttributes) {
    std::ofstream file(datSave);
    file << gameAttributes.variants << " " << gameAttributes.mode << " " << gameAttributes.level << " " << gameAttributes.timeWhite << " " << gameAttributes.timeBlack << "\n";
    file << "UCI\n";
    for (int i = 0; i < (int)movesHistory.size(); ++i) {
        std::string moveName = MoveUtility::GetMoveNameUCI(movesHistory[i]);
        file << moveName << " \n"[i & 1];
    }
    file.close();
}

void FileManager::SaveGameFEN(const Board& board, const GameAttributes& gameAttributes) {
    std::ofstream file(datSave);
    file << gameAttributes.mode << " " << gameAttributes.level << " " << gameAttributes.timeWhite << " " << gameAttributes.timeBlack << "\n";
    file << "FEN\n";
    std::string FEN = Fen::PositionToFen(PositionInfo::BoardToPosition(board));
    file << FEN;
    file.close();
}

void FileManager::SaveTheme(const ThemeIndex& themeIndex) {
    GameAttributes gameAttributes;
    SaveThemeConfig(themeIndex, gameAttributes);
}

void FileManager::SaveConfig(const GameAttributes& gameAttributes) {
    ThemeIndex themeIndex = LoadTheme();
    SaveThemeConfig(themeIndex, gameAttributes);
}

void FileManager::SaveThemeConfig(const ThemeIndex& themeIndex, const GameAttributes& gameAttributes) {
    std::ofstream file(datConfig);
    file << themeIndex.BackgroundIndex << " " << themeIndex.PieceIndex << " " << themeIndex.BoardIndex << " " << themeIndex.ButtonIndex << " " << themeIndex.TextIndex << "\n";
    file << gameAttributes.variants << " " << gameAttributes.mode << " " << gameAttributes.level << " " << gameAttributes.timeTotalMode << " " << gameAttributes.timeExtraMode << " " << gameAttributes.isBotHelp;
    file.close();
}

bool FileManager::LoadGame(Board &board, GameAttributes &gameAttributes) {
    CheckConfigAndSave();
    std::ifstream file(datSave);
    if (!file.is_open()) {
        board.LoadBasicPosition();
        LoadConfig(gameAttributes);
        return false;
    }
    file >> gameAttributes.variants >> gameAttributes.mode >> gameAttributes.level >> gameAttributes.timeWhite >> gameAttributes.timeBlack;
    file.ignore();
    std::string line;
    getline(file, line);
    if (line == "UCI") {
        board.LoadBasicPosition();
        while (file >> line) {
            Move move = MoveUtility::GetMoveFromNameUCI(line, board);
            board.MakeMove(move);
        }
        return true;
    }
    else if (line == "FEN") {
        std::string FEN;
        getline(file, FEN);
        board.LoadPosition(Fen::FenToPosition(FEN));
        return true;
    }
    return false;
}

ThemeIndex FileManager::LoadTheme()
{
    if (!std::filesystem::exists(datConfig)) {
        std::ofstream file(datConfig);
        file << "0 0 0 0 0\n0 0 0 0 0 0";
        file.close();
    }
    std::ifstream file(datConfig);
    ThemeIndex themeIndex;
    file >> themeIndex.BackgroundIndex >> themeIndex.PieceIndex >> themeIndex.BoardIndex >> themeIndex.ButtonIndex >> themeIndex.TextIndex;
    file.close();
    return themeIndex;
}

void FileManager::LoadConfig(GameAttributes& gameAttributes) {
    if (!std::filesystem::exists(datConfig)) {
        std::ofstream file(datConfig);
        file << "0 0 0 0 0\n0 0 0 0 0 0";
        file.close();
    }
    std::ifstream file(datConfig);
    int x;
    file >> x >> x >> x >> x >> x;
    file >> gameAttributes.variants >> gameAttributes.mode >> gameAttributes.level >> gameAttributes.timeTotalMode >> gameAttributes.timeExtraMode >> gameAttributes.isBotHelp;
    file.close();
}

void FileManager::LoadThemeConfig(ThemeIndex& themeIndex, GameAttributes& gameAttributes) {
    if (!std::filesystem::exists(datConfig)) {
        std::ofstream file(datConfig);
        file << "0 0 0 0 0\n0 0 0 0 0 0";
        file.close();
    }
    std::ifstream file(datConfig);
    file >> themeIndex.BackgroundIndex >> themeIndex.PieceIndex >> themeIndex.BoardIndex >> themeIndex.ButtonIndex >> themeIndex.TextIndex;
    file >> gameAttributes.variants >> gameAttributes.mode >> gameAttributes.level >> gameAttributes.timeTotalMode >> gameAttributes.timeExtraMode >> gameAttributes.isBotHelp;
    file.close();
}

std::vector<StatisticsData> FileManager::LoadStatistics() {
    std::vector<StatisticsData> StatisticsList;
    StatisticsList.push_back(StatisticsData("PvEWhite"));
    StatisticsList.push_back(StatisticsData("PvEBlack"));
    StatisticsList.push_back(StatisticsData("PvP"));
    StatisticsList.push_back(StatisticsData("EvE"));

    if (!std::filesystem::exists(datHistory)) {
        std::ofstream file(datHistory);
        file << "0";
        file.close();
    }
    std::ifstream file(datHistory);
    int cntGames;
    file >> cntGames;
    file.ignore();
    for(int i = 0; i < cntGames; i++) {
        int variants, mode, level, result;
        file >> variants >> mode >> level >> result;
        file.ignore();
        std::string line;
        getline(file, line);
        StatisticsList[mode].add(variants, level, result);
    }
    file.close();
    return StatisticsList;
}

void FileManager::CheckConfigAndSave() {
    if (!std::filesystem::exists(datConfig)) {
        std::ofstream file(datConfig);
        file << "0 0 0 0 0\n0 0 0 0 0 0";
        file.close();
    }
    if (!std::filesystem::exists(datSave)) {
        std::ofstream file(datSave);
        file << "0 0 0 0 0\n0 0 0 0 0 0";
        file.close();
    }

    std::ifstream file(datConfig);
    GameAttributes gameAttributes(false);
    int x;
    file >> x >> x >> x >> x >> x;
    file >> gameAttributes.variants >> gameAttributes.mode >> gameAttributes.level >> gameAttributes.timeTotalMode >> gameAttributes.timeExtraMode >> gameAttributes.isBotHelp;
    file.close();

    std::ifstream file2(datSave);
    GameAttributes gameAttributes2(false);
    file2 >> gameAttributes2.variants >> gameAttributes2.mode >> gameAttributes2.level >> gameAttributes2.timeWhite >> gameAttributes2.timeBlack;
    file2.close();

    if (gameAttributes.variants != gameAttributes2.variants) {
        RemoveSaveGame();
    }
}

void FileManager::RemoveSaveGame() {
    std::filesystem::remove(datSave);
}
