#include "FileInit.hpp"
#include "../Helpers/MoveUtility.hpp"
#include "../Helpers/FEN.hpp"
#include "../ChessBoard/Move.hpp"
#include "../ChessBoard/Board.hpp"
#include "Theme.hpp"
#include "GameAttributes.hpp"
#include <fstream>
#include <filesystem>

const std::string FileInit::datHistory = "dat/history.dat";
const std::string FileInit::datConfig = "dat/config.dat";
const std::string FileInit::datSave = "dat/save.dat";
const std::string FileInit::datStatistics = "dat/statistics.dat";
const std::string FileInit::datOnlineGame = "dat/onlinegame.dat";
const std::string FileInit::datUsers = "dat/users.dat";

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

void FileInit::Init() {
    if (!std::filesystem::exists("dat")) {
        std::filesystem::create_directory("dat");
    }
    // if file is not exist then create file
    if (!std::filesystem::exists(datConfig)) {
        std::ofstream file(datConfig);
        file << "0 0 0 0 0\n0 0 0";
        file.close();
    }
    if (!std::filesystem::exists(datStatistics)) {
        std::ofstream file(datStatistics);
        file << "0";
        file.close();
    }
}

void FileInit::StoreCompletedGame(const Board &board, int mode, int level, int result) {
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
    file2 << mode << " " << level << " " << result << "\n";
    std::vector<Move> movesHistory = board.getMovesHistory();
    for (int i = 0; i < (int)movesHistory.size(); ++i) {
        std::string moveName = MoveUtility::GetMoveNameUCI(movesHistory[i]);
        file2 << moveName << " ";
    }
    file2.close();
}

void FileInit::SaveGame(const Board& board, const GameAttributes& gameAttributes) {
    std::vector<Move> movesHistory = board.getMovesHistory();
    int cntMoves = board.getMoveCount();
    if (cntMoves == (int) movesHistory.size()) {
        SaveGameMoves(movesHistory, gameAttributes);
    }
    else {
        SaveGameFEN(board, gameAttributes);
    }
}

void FileInit::SaveGameMoves(const std::vector<Move>& movesHistory, const GameAttributes& gameAttributes) {
    Board board;
    std::ofstream file(datSave);
    file << gameAttributes.mode << " " << gameAttributes.level << " " << gameAttributes.timeWhite << " " << gameAttributes.timeBlack << "\n";
    file << "UCI\n";
    for (int i = 0; i < (int)movesHistory.size(); ++i) {
        std::string moveName = MoveUtility::GetMoveNameUCI(movesHistory[i]);
        file << moveName << " \n"[i & 1];
    }
    file.close();
}

void FileInit::SaveGameFEN(const Board& board, const GameAttributes& gameAttributes) {
    std::ofstream file(datSave);
    file << gameAttributes.mode << " " << gameAttributes.level << " " << gameAttributes.timeWhite << " " << gameAttributes.timeBlack << "\n";
    file << "FEN\n";
    std::string FEN = Fen::PositionToFen(PositionInfo::BoardToPosition(board));
    file << FEN;
    file.close();
}

void FileInit::SaveTheme(const ThemeIndex& themeIndex) {
    int mode;
    int level;
    bool isBotHelp;
    LoadOptions(mode, level, isBotHelp);
    SaveConfig(themeIndex, mode, level, isBotHelp);
}

void FileInit::SaveOptions(int mode, int level, bool isBotHelp) {
    ThemeIndex themeIndex = LoadTheme();
    LoadOptions(mode, level, isBotHelp);
    SaveConfig(themeIndex, mode, level, isBotHelp);
}

void FileInit::SaveConfig(const ThemeIndex& themeIndex, int mode, int level, bool isBotHelp) {
    std::ofstream file(datConfig);
    file << themeIndex.BackgroundIndex << " " << themeIndex.PieceIndex << " " << themeIndex.BoardIndex << " " << themeIndex.ButtonIndex << " " << themeIndex.TextIndex << "\n" << mode << " " << level << " " << isBotHelp;
    file.close();
}

bool FileInit::LoadGame(Board &board, GameAttributes &gameAttributes) {
    std::ifstream file(datSave);
    if (!file.is_open()) {
        board.LoadBasicPosition();
        LoadOptions(gameAttributes.mode, gameAttributes.level, gameAttributes.isBotHelp);
        return false;
    }
    file >> gameAttributes.mode >> gameAttributes.level >> gameAttributes.timeWhite >> gameAttributes.timeBlack;
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

ThemeIndex FileInit::LoadTheme()
{
    if (!std::filesystem::exists(datConfig)) {
        std::ofstream file(datConfig);
        file << "0 0 0 0 0\n0 0 0";
        file.close();
    }
    std::ifstream file(datConfig);
    ThemeIndex themeIndex;
    file >> themeIndex.BackgroundIndex >> themeIndex.PieceIndex >> themeIndex.BoardIndex >> themeIndex.ButtonIndex >> themeIndex.TextIndex;
    file.close();
    return themeIndex;
}

void FileInit::LoadOptions(int& mode, int& level, bool& isBotHelp) {
    if (!std::filesystem::exists(datConfig)) {
        std::ofstream file(datConfig);
        file << "0 0 0 0 0\n0 0 0";
        file.close();
    }
    std::ifstream file(datConfig);
    int x;
    file >> x >> x >> x >> x >> x >> mode >> level >> isBotHelp;
    file.close();
}

void FileInit::LoadConfig(ThemeIndex& themeIndex, int& mode, int& level, bool& isBotHelp) {
    if (!std::filesystem::exists(datConfig)) {
        std::ofstream file(datConfig);
        file << "0 0 0 0 0\n0 0 0";
        file.close();
    }
    std::ifstream file(datConfig);
    file >> themeIndex.BackgroundIndex >> themeIndex.PieceIndex >> themeIndex.BoardIndex >> themeIndex.ButtonIndex >> themeIndex.TextIndex >> mode >> level >> isBotHelp;
    file.close();
}

int FileInit::LoadMode() {
    if (!std::filesystem::exists(datConfig)) {
        std::ofstream file(datConfig);
        file << "0 0 0 0 0\n0 0 0";
        file.close();
    }
    std::ifstream file(datConfig);
    ThemeIndex themeIndex;
    int mode;
    file >> themeIndex.BackgroundIndex >> themeIndex.PieceIndex >> themeIndex.BoardIndex >> themeIndex.ButtonIndex >> themeIndex.TextIndex >> mode;
    file.close();
    return mode;
}

void FileInit::RemoveSaveGame() {
    std::filesystem::remove(datSave);
}
