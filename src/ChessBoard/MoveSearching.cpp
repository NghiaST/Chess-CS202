#include <ChessBoard/MoveSearching.hpp>

MoveSearching::MoveSearching(int depth) {
    this->searchDepth = depth;
    this->maxDepth = depth;
    this->id_search = 0;
    this->isSearch = false;
    this->analysisPoint = 0;
    this->isSearchComplete = false;
}

MoveSearching::~MoveSearching() {
    for(MoveSearching* moveSearch : this->moveSearches) {
        delete moveSearch;
    }
}

int MoveSearching::Searching(Board& board, int timeSearchingMs, int searchDepth) {
    sf::Clock clock;
    clock.restart();

    if (isSearch == false) {
        isSearch = true;

        multiplyScore = board.ifWhiteTurn() ? 1 : -1;
        score = CalculateScore(board) * multiplyScore;
        if (searchDepth == 0) {
            isSearchComplete = true;
            return score;
        }
        else {
            moveSelections = board.getLegalMoveList();
            cntMoves = moveSelections.size();
            moveSearches.assign(cntMoves, nullptr);
            moveScore.assign(cntMoves, -10000);
            id_search = 0;
        }

        if (cntMoves == 0) {
            if (board.ifCheck()) {
                score = analysisPoint = -1000000;
            }
            else {
                analysisPoint = 0;
            }
            isSearchComplete = true;
        }
        else {
            bestMove = moveSelections[0];
        }
    }

    bool isChange = false;
    while (timeSearchingMs > 0 && id_search < cntMoves) {
        Move move = moveSelections[id_search];
        board.MakeMove(move, true);
        if (moveSearches[id_search] == nullptr) {
            moveSearches[id_search] = new MoveSearching(this->maxDepth - 1);
        }
        MoveSearching* moveSearch = moveSearches[id_search];

        int newAnalysis = -moveSearch->Searching(board, timeSearchingMs, searchDepth - 1);
        if (moveScore[id_search] != newAnalysis) {
            moveScore[id_search] = newAnalysis;
            isChange = true;
        }
        board.UnmakeMove(move, true);
        if (!moveSearch->IsSearchCompleted()) break;
        id_search++;

        timeSearchingMs -= clock.getElapsedTime().asMilliseconds();
        clock.restart();
    }

    if (isChange) {
        analysisPoint = moveScore[0];
        int cnt = 1;
        for(int i = 1; i < id_search; i++) {
            if (moveScore[i] > analysisPoint) {
                analysisPoint = moveScore[i];
                cnt = 1;
            }
            else if (moveScore[i] == analysisPoint) {
                cnt++;
            }
        }
        int id = rand() % cnt;
        for(int i = 0; i < id_search; i++) {
            if (moveScore[i] == analysisPoint) {
                if (id == 0) {
                    bestMove = moveSelections[i];
                    break;
                }
                else {
                    id--;
                }
            }
        }
    }

    if (id_search == cntMoves && isSearchComplete == false) {
        isSearchComplete = true;
        // if (cntMoves) {
        //     std::sort(moveSelectionsSorted.begin(), moveSelectionsSorted.end(), [] (const std::pair<int, Move>& a, const std::pair<int, Move>& b) {
        //         return a.first < b.first;
        //     });
        //     long long expected = pow(cntMoves, 3);
        //     int id = (int) pow(rand() % expected, 1.0 / 3);
        //     selectedMove = moveSelectionsSorted[id].second;
        //     selectedScore = moveSelectionsSorted[id].first;
        // }
    }

    if (isSearchComplete || id_search > 0) {
        return analysisPoint;
    }
    else {
        return score;
    }

    return analysisPoint;
}

int MoveSearching::CalculateScore(const Board& board) {
    int score = 0;
    std::vector<int> pieces = board.getAllPieces();
    for(int piece : pieces) {
        score += PIECE::PieceValue(piece);
    }
    return score;
}

std::vector<Move> MoveSearching::getRankMove(int numberMoves) {
    std::vector<std::pair<float, Move>> moveSelectionsSorted;
    for(int i = 0; i < cntMoves; i++) {
        moveSelectionsSorted.push_back(std::make_pair(moveScore[i], moveSelections[i]));
    }
    std::sort(moveSelectionsSorted.begin(), moveSelectionsSorted.end(), [] (const std::pair<float, Move>& a, const std::pair<float, Move>& b) {
        return a.first > b.first;
    });
    std::vector<Move> rankMoves;
    for(int i = 0; i < numberMoves && i < cntMoves; i++) {
        rankMoves.push_back(moveSelectionsSorted[i].second);
    }
    return rankMoves;
}

bool MoveSearching::IsSearchCompleted() const {
    return isSearchComplete;
}

Move MoveSearching::GetBestMove() const {
    return bestMove;
}
