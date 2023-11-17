#include "Bot.hpp"

Bot::Bot() {
    board = new Board();
    searchDepth = 2;
    timeThinkingMs = 2500;
    isThinkingDone = false;
    moveSearching = new MoveSearching(searchDepth);
}

Bot::~Bot() {
    delete board;
    delete moveSearching;
}

void Bot::LoadBoard(const Board& board) {
    delete this->board;
    delete moveSearching;
    this->board = new Board(board);
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
    if (moveSearching->IsSearchCompleted() || currentTimeThinkingMs <= 0) {
        if (moveSearching->IsSearchCompleted())
            printf("Thinking Complete in %d ms\n", timeThinkingMs - currentTimeThinkingMs);
        else 
            printf("Don't think enough\n");
        bestMove = moveSearching->GetBestMove();
        isThinkingDone = true;
    }
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
