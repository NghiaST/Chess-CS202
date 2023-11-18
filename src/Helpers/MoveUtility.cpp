#include <Helpers/MoveUtility.hpp>
#include <Helpers/BoardHelpers.hpp>
#include <ChessBoard/Move.hpp>
#include <ChessBoard/Board.hpp>

Move MoveUtility::GetMoveFromNameUCI(std::string moveName, Board board) {
    int startSquare = BoardHelpers::SquareIndexFromName(moveName.substr(0, 2));
    int targetSquare = BoardHelpers::SquareIndexFromName(moveName.substr(2, 2));

    int pieceType = PIECE::PieceType(board.getPiece(startSquare));
    Point start2D = BoardHelpers::CoordFromID(startSquare);
    Point target2D = BoardHelpers::CoordFromID(targetSquare);

    Move::FLAG flag = Move::NoFlag;


    if (pieceType == PIECE::Pawn) {
        // Promotion
        if (moveName.length() > 4)
        {
            switch (moveName[4])
            {
                case 'q':
                    flag = Move::PromotionQueen;
                    break;
                case 'r':
                    flag = Move::PromotionRook;
                    break;
                case 'b':
                    flag = Move::PromotionBishop;
                    break;
                case 'n':
                    flag = Move::PromotionKnight;
                    break;
            }
        }
        // Pawn two steps
        else if (std::abs(start2D.x - target2D.x) == 2)
        {
            flag = Move::PawnTwoStep;
        }
        // En-passant
        else if (start2D.y != target2D.y && board.getPiece(targetSquare) == PIECE::None)
        {
            flag = Move::EnPassant;
        }
    }
    else if (pieceType == PIECE::King)
    {
        // Castle
        if (std::abs(start2D.y - target2D.y) == 2)
        {
            flag = Move::Castle;
        }
    }

    return Move(startSquare, targetSquare, flag);
}

std::string MoveUtility::GetMoveNameUCI(Move move) {
    std::string moveName = "";
    moveName += BoardHelpers::SquareNameFromIndex(move.startSquare);
    moveName += BoardHelpers::SquareNameFromIndex(move.targetSquare);

    if (move.flag == Move::PromotionQueen)
        moveName += "q";
    else if (move.flag == Move::PromotionRook)
        moveName += "r";
    else if (move.flag == Move::PromotionBishop)
        moveName += "b";
    else if (move.flag == Move::PromotionKnight)
        moveName += "n";

    return moveName;
}

std::string MoveUtility::GetMoveNameSAN(Move move, Board board) {
    int movePieceType = PIECE::PieceType(board.getPiece(move.startSquare));
    int capturedPieceType = PIECE::PieceType(board.getPiece(move.targetSquare));

    if (movePieceType == PIECE::King && move.flag == Move::Castle)
    {
        if (move.targetSquare == BoardHelpers::g1 || move.targetSquare == BoardHelpers::g8)
            return "O-O";
        else
            return "O-O-O";
    }

    std::string moveNotation = "";
    if (movePieceType != PIECE::Pawn) {
        moveNotation += PIECE::PieceTypeToChar(movePieceType);
    }
    std::vector<Move> moves = board.getLegalMoveList();

    if (movePieceType != PIECE::Pawn && movePieceType != PIECE::King) {
        bool showAny = false;
        bool showFile = false;
        bool showRank = false;
        for (Move altMove : moves) {
            if (altMove.startSquare != move.startSquare && altMove.targetSquare == move.targetSquare) {
                if (PIECE::PieceType(board.getPiece(altMove.startSquare)) == movePieceType) {
                    int fromFileIndex = BoardHelpers::FileID(move.startSquare);
                    int alternateFromFileIndex = BoardHelpers::FileID(altMove.startSquare);
                    int fromRankIndex = BoardHelpers::RankID(move.startSquare);
                    int alternateFromRankIndex = BoardHelpers::RankID(altMove.startSquare);

                    showAny = true;
                    if (fromRankIndex == alternateFromRankIndex) {
                        showFile = true;
                    }
                    else if (fromFileIndex == alternateFromFileIndex) {
                        showRank = true;
                    }
                }
            }
        }
        if (showAny && showFile == false && showRank == false) {
            showFile = true;
        }
        if (showFile) {
            moveNotation += BoardHelpers::FileName(BoardHelpers::FileID(move.startSquare));
        }
        if (showRank) {
            moveNotation += BoardHelpers::RankName(BoardHelpers::RankID(move.startSquare));
        }
    }

    if (capturedPieceType != PIECE::None) {
        if (movePieceType == PIECE::Pawn) {
            moveNotation += BoardHelpers::FileName(BoardHelpers::FileID(move.startSquare));
        }
        moveNotation += "x";
    }
    else {
        if (move.flag == Move::EnPassant) {
            moveNotation += BoardHelpers::FileName(BoardHelpers::FileID(move.startSquare));
            moveNotation += "x";
        }
    }

    moveNotation += BoardHelpers::SquareNameFromIndex(move.targetSquare);

    switch (move.flag) {
        case Move::PromotionQueen:
            moveNotation += "=Q";
            break;
        case Move::PromotionRook:
            moveNotation += "=R";
            break;
        case Move::PromotionBishop:
            moveNotation += "=B";
            break;
        case Move::PromotionKnight:
            moveNotation += "=N";
            break;
        default:
            break;
    }

    board.MakeMove(move, true);
    if (board.ifCheck()) {
        if (board.ifCheckMate()) {
            moveNotation += "#";
        }
        else {
            moveNotation += "+";
        }
    }
    board.UnmakeMove(move, true);

    return moveNotation;
}

Move MoveUtility::GetMoveFromSAN(std::string algebraicNotation, Board board) {
    algebraicNotation.erase(
        std::remove_if(algebraicNotation.begin(), algebraicNotation.end(),
                        [](char c) { return c == '+' || c == '#' || c == 'x' || c == '-'; }),
        algebraicNotation.end());
    
    std::vector<Move> allMoves = board.getLegalMoveList();
    Move move = Move();

    for (Move moveToTest : allMoves) {
        move = moveToTest;

        int moveFromIndex = move.startSquare;
        int moveToIndex = move.targetSquare;
        int movePieceType = PIECE::PieceType(board.getPiece(moveFromIndex));
        Point fromCoord = BoardHelpers::CoordFromID(moveFromIndex);
        Point toCoord = BoardHelpers::CoordFromID(moveToIndex);

        if (algebraicNotation == "OO") {
            // castle kingside
            if (movePieceType == PIECE::King && moveToIndex - moveFromIndex == 2) {
                return move;
            }
        }
        else if (algebraicNotation == "OOO") {
            // castle queenside
            if (movePieceType == PIECE::King && moveToIndex - moveFromIndex == -2) {
                return move;
            }
        }
        // Is pawn move if starts with any file indicator (e.g. 'e'4. Note that uppercase B is used for bishops) 
        else if (BoardHelpers::fileNames.find(algebraicNotation[0]) != std::string::npos) {
            if (movePieceType != PIECE::Pawn) {
                continue;
            }
            if (BoardHelpers::fileNames.find(algebraicNotation[0]) == fromCoord.y) {
                // correct starting file
                if (algebraicNotation.find('=') != std::string::npos) {
                    // is promotion
                    if (toCoord.x == 0 || toCoord.x == 7) {
                        if (algebraicNotation.length() == 5) // pawn is capturing to promote
                        {
                            char targetFile = algebraicNotation[1];
                            if (BoardHelpers::fileNames.find(targetFile) != toCoord.y) {
                                // Skip if not moving to correct file
                                continue;
                            }
                        }
                        char promotionChar = algebraicNotation[algebraicNotation.length() - 1];

                        if (move.getPromotionType() != PIECE::SymbolToPieceType(promotionChar)) {
                            continue; // skip this move, incorrect promotion type
                        }

                        return move;
                    }
                }
                else {
                    char targetFile = algebraicNotation[algebraicNotation.length() - 2];
                    char targetRank = algebraicNotation[algebraicNotation.length() - 1];

                    if (BoardHelpers::fileNames.find(targetFile) == toCoord.y) {
                        // correct ending file
                        if (targetRank == BoardHelpers::RankName(toCoord.x)) {
                            // correct ending rank
                            break;
                        }
                    }
                }
            }
        }
        else {
            // regular piece move
            char movePieceChar = algebraicNotation[0];
            if (PIECE::SymbolToPieceType(movePieceChar) != movePieceType) {
                continue; // skip this move, incorrect move piece type
            }

            char targetFile = algebraicNotation[algebraicNotation.length() - 2];
            char targetRank = algebraicNotation[algebraicNotation.length() - 1];
            if (BoardHelpers::fileNames.find(targetFile) == toCoord.y) {
                // correct ending file
                if (targetRank == BoardHelpers::RankName(toCoord.x)) {
                    // correct ending rank
                    if (algebraicNotation.length() == 5) {
                        // addition char present for disambiguation (e.g. Qa8b7)
                        char fileChar = algebraicNotation[1];
                        char rankChar = algebraicNotation[2];

                        if (BoardHelpers::fileNames.find(fileChar) == std::string::npos) {
                            continue;
                        }
                        if (BoardHelpers::rankNames.find(rankChar) == std::string::npos) {
                            continue;
                        }
                        if (rankChar != BoardHelpers::RankName(fromCoord.x)) {
                            continue;
                        }
                        if (fileChar != BoardHelpers::FileName(fromCoord.y)) {
                            continue;
                        }
                    }
                    else if (algebraicNotation.length() == 4) {
                        // addition char present for disambiguation (e.g. Nbd7 or R7e2)
                        char disambiguationChar = algebraicNotation[1];

                        if (BoardHelpers::fileNames.find(disambiguationChar) != std::string::npos) {
                            // is file disambiguation
                            if (BoardHelpers::fileNames.find(disambiguationChar) != fromCoord.y) {
                                // incorrect starting file
                                continue;
                            }
                        }
                        else {
                            // is rank disambiguation
                            if (disambiguationChar != BoardHelpers::RankName(fromCoord.x)) {
                                // incorrect starting rank
                                continue;
                            }
                        }
                    }
                    break;
                }
            }
        }
    }
    return move;
}