#ifndef __Chess_hpp__
#define __Chess_hpp__

#include <SFML/Graphics.hpp>
#include "Include.hpp"
#include "Theme.hpp"
#include "PieceBoard.hpp"
#include "FrontEnd.hpp"

class Chess {
private:
    FrontEnd* frontEnd;
    PieceBoard* pieceBoard;
    
public:
    Chess();
    ~Chess();
    void run();
};

#endif