#include <ChessBoard/Bot.hpp>

Bot::Bot() {
    board = FactoryBoard::CreateBoard("standard");
    stopflag = std::make_unique<bool>(false);
    searchDepth = 2;
    timeThinkingMs = 2500;
    isThinkingDone = false;
    moveSearching = new MoveSearching(searchDepth, std::move(stopflag));
}

Bot::~Bot() {
    delete board;
    delete moveSearching;
    stopflag = nullptr;
}

void Bot::LoadBoard(const Board& board) {
    delete this->board;
    delete moveSearching;
    this->board = board.clone();
    this->stopflag = std::make_shared<bool>(false);
    moveSearching = new MoveSearching(searchDepth, stopflag);
    isThinkingDone = false;
    clock.restart();
    currentTimeThinkingMs = timeThinkingMs;
}

void Bot::LoadFEN(std::string fen) {
    board->LoadPosition(fen);
}

void Bot::setSearchDepth(int searchDepth) {
    this->searchDepth = searchDepth;
}

void Bot::setTimeThinkingMs(double timeThinkingMs) {
    this->timeThinkingMs = timeThinkingMs;
}

void Bot::Thinking() {
    if (isThinkingDone || *stopflag) return;
    // thinkingThread = std::thread(&MoveSearching::Searching, moveSearching, *board, limitThinkingTimeMs, searchDepth);
    // thinkingThread.join();

    moveSearching->Searching(*board, limitThinkingTimeMs, searchDepth);
    currentTimeThinkingMs -= clock.getElapsedTime().asMilliseconds();
    clock.restart();
    if (moveSearching->IsSearchCompleted() || currentTimeThinkingMs <= 0) {
        if (moveSearching->IsSearchCompleted())
            printf("Thinking Complete in %d ms\n", timeThinkingMs - currentTimeThinkingMs);
        else 
            printf("Don't think enough\n");
        bestMove = moveSearching->GetBestMove();
        isThinkingDone = true;
        *stopflag = true;
    }
}

void Bot::StopThinking() {
    *stopflag = true;
}

std::vector<Move> Bot::getRankMove(int number) {
    return moveSearching->getRankMove(number);
}

Move Bot::getBestMove() {
    return bestMove;
}

bool Bot::ifThinkingDone() {
    return isThinkingDone;
}