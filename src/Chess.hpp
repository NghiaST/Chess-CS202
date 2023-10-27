#ifndef __Chess_hpp__
#define __Chess_hpp__

#include <SFML/Graphics.hpp>
#include "DataControl/Include.hpp"
#include "DataControl/Theme.hpp"
#include "DataControl/FrontEnd.hpp"
#include "BoardScreen/PieceBoard.hpp"

class Chess {
private:
    FrontEnd* frontEnd;
    PieceBoard* pieceBoard;
    sf::RenderWindow mWindow;
    
public:
    Chess();
    ~Chess();
    void run();
};

#endif