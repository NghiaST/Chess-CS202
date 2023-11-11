#include "Bot.hpp"

Bot::Bot() {
    board = new NewBoard();
    searchDepth = 4;
    timeThinkingMs = 1000;
    isThinkingDone = false;
    moveSearching = new MoveSearching(searchDepth);
}

Bot::~Bot() {
    delete board;
    delete moveSearching;
}

void Bot::LoadBoard(const NewBoard& board) {
    delete this->board;
    delete moveSearching;
    this->board = new NewBoard(board);
    moveSearching = new MoveSearching(searchDepth);
    isThinkingDone = false;
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
    if (isThinkingDone) return;
    moveSearching->Searching(*board, limitThinkingTimeMs, searchDepth);
    timeThinkingMs -= limitThinkingTimeMs;
    if (moveSearching->IsSearchCompleted() || timeThinkingMs <= 0) {
        bestMove = moveSearching->GetBestMove();
        isThinkingDone = true;
    }
}

Move Bot::getBestMove() {
    return bestMove;
}

bool Bot::ifThinkingDone() {
    return isThinkingDone;
}
