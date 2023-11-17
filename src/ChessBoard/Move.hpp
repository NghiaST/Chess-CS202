#ifndef __Move_hpp__
#define __Move_hpp__

#include "../DataControl/Include.hpp"

class Move {
public:
    enum FLAG {
        NoFlag = 0,
        EnPassant,
        Castle,
        PawnTwoStep,
        PromotionQueen,
        PromotionKnight,
        PromotionBishop,
        PromotionRook
    };
public:
    Move();
    Move(int startSquare, int targetSquare, FLAG flag);
    bool operator == (const Move& move) const;

public:
    bool isPromotion();
    int getPromotionType();
    void setPromotionType(int promotionType);

public:
    int startSquare, targetSquare;
    int flag;
};

// class GeneralMove {
// public:
//     GeneralMove();
//     GeneralMove(int startSquare, int targetSquare, int startPiece, int targetPiece, int flag, int sameTargetSquare = GeneralMove::SameNone);

// public:
//     bool isPromotion();
//     int getPromotionType();

// public:
//     enum FLAG {
//         Illegal = -1,
//         NoFlag = 0,
//         Capture = 1,
//         EnPassant = 2,
//         Castle = 3,
//         PawnTwoStep = 4,
//         PromotionQueen = 5,
//         PromotionKnight = 6,
//         PromotionBishop = 7,
//         PromotionRook = 8
//     };
//     enum SAMETARGETSQUARE {
//         SameNone = 0,
//         SameRow = 1,
//         SameCol = 2
//     };

// public:
//     int startSquare, targetSquare;
//     int startPiece, targetPiece;
//     int flag;
//     int sameTargetSquare;
// };

#endif