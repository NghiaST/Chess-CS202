#include "Bot.hpp"

Bot::Bot() {
    board = new NewBoard();
    searchDepth = 2;
    timeThinkingMs = 2500;
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
    if (isThinkingDone) return;
    moveSearching->Searching(*board, limitThinkingTimeMs, searchDepth);
    currentTimeThinkingMs -= clock.getElapsedTime().asMilliseconds();
    clock.restart();
    printf("Thinking %d\n", currentTimeThinkingMs);
    if (moveSearching->IsSearchCompleted() || currentTimeThinkingMs <= 0) {
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
