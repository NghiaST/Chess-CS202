#include "Move.hpp"

Move::Move() {
    startSquare = -1;
    targetSquare = -1;
    flag = Move::NoFlag;
}

Move::Move(int startSquare, int targetSquare, FLAG flag) {
    this->startSquare = startSquare;
    this->targetSquare = targetSquare;
    this->flag = flag;
}

bool Move::isPromotion() {
    return (flag >= Move::PromotionQueen);
}

int Move::getPromotionType() {
    switch (flag) {
        case Move::PromotionQueen: return PIECE::Queen;
        case Move::PromotionKnight: return PIECE::Knight;
        case Move::PromotionBishop: return PIECE::Bishop;
        case Move::PromotionRook: return PIECE::Rook;
        default: printf("Promotion Bug\n"); exit(12); return PIECE::None;
    }
}


// GeneralMove::GeneralMove() {
//     startSquare = -1;
//     targetSquare = -1;
//     startPiece = PIECE::None;
//     targetPiece = PIECE::None;
//     flag = GeneralMove::NoFlag;
//     sameTargetSquare = GeneralMove::SameNone;
// }

// GeneralMove::GeneralMove(int startSquare, int targetSquare, int startPiece, int targetPiece, int flag, int sameTargetSquare) {
//     this->startSquare = startSquare;
//     this->targetSquare = targetSquare;
//     this->startPiece = startPiece;
//     this->targetPiece = targetPiece;
//     this->flag = flag;
//     this->sameTargetSquare = sameTargetSquare;
// }

// bool GeneralMove::isPromotion() {
//     return (flag >= GeneralMove::PromotionQueen);
// }

// int GeneralMove::getPromotionType() {
//     switch (flag) {
//         case GeneralMove::PromotionQueen: return PIECE::Queen;
//         case GeneralMove::PromotionKnight: return PIECE::Knight;
//         case GeneralMove::PromotionBishop: return PIECE::Bishop;
//         case GeneralMove::PromotionRook: return PIECE::Rook;
//         default: printf("Promotion Bug\n"); exit(12); return PIECE::None;
//     }
// }
