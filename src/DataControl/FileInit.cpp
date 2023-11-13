#include "FileInit.hpp"
#include <fstream>

const std::string FileInit::datConfig = "dat/config.dat";
const std::string FileInit::datGame = "dat/game.dat";
const std::string FileInit::datStatistics = "dat/statistics.dat";
const std::string FileInit::datOnlineGame = "dat/onlinegame.dat";
const std::string FileInit::datUsers = "dat/users.dat";

/*
    About datConfig:
        1st line: themeIndex: Background, Piece, Board, Button, Text
        2nd line: mode (PvE, PvP, EvE), level (1,2,3,etc)
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
        1st: mode, level (PvP, PvE, EvE), color(if PvE)
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
        file << "0 0 0 0 0\n0 0";
        file.close();
    }
    if (!std::filesystem::exists(datStatistics)) {
        std::ofstream file(datStatistics);
        file << "0";
        file.close();
    }
}

void FileInit::Save(std::vector<Move> movesHistory, int mode, int level, int color, int timeWhite, int timeBlack) {
    // std::ofstream file(datGame);
    // for (int i = 0; i < (int)movesHistory.size(); ++i) {
    //     if (!(i & 1)) file << i/2 + 1 << ". ";
    //     file << movesHistory[i].startSquare << " " << movesHistory[i].targetSquare << " " << movesHistory[i].flag << " ";
    //     /// should update to use string to store game
    //     if (i & 1) file << '\n';
    // }
    // file.close();
}

bool FileInit::Load(std::vector<Move>& movesHistory, int& mode, int& level, int& color, int& timeWhite, int& timeBlack) {
    // std::ifstream file(datGame);
    // if (!file.is_open()) return false;
    // std::string line;
    // int cntMoves;
    // file >> mode >> level >> color >> timeWhite >> timeBlack >> cntMoves;
    // for (int i = 0; i < cntMoves; i++) {
    //     if (!(i&1)) file >> line;
    //     Move move;
    //     file >> move.startSquare >> move.targetSquare >> move.flag;
    //     movesHistory.push_back(move);
    // }
    // file.close();
    return true;
}

ThemeIndex FileInit::LoadTheme() {
    if (!std::filesystem::exists(datConfig)) {
        std::ofstream file(datConfig);
        file << "0 0 0 0 0\n0 0";
        file.close();
    }
    std::ifstream file(datConfig);
    ThemeIndex themeIndex;
    file >> themeIndex.BackgroundIndex >> themeIndex.PieceIndex >> themeIndex.BoardIndex >> themeIndex.ButtonIndex >> themeIndex.TextIndex;
    file.close();
    return themeIndex;
}

void FileInit::SaveConfig(const ThemeIndex& themeIndex) {
    std::ofstream file(datConfig);
    file << themeIndex.BackgroundIndex << " " << themeIndex.PieceIndex << " " << themeIndex.BoardIndex << " " << themeIndex.ButtonIndex << " " << themeIndex.TextIndex << "\n0 0";
    file.close();
}
