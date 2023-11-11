#include "main.hpp"
#include "Chess.hpp"
#include <SFML/Graphics.hpp>
#include "IngameScreen/Fen.hpp"

int main()
{
    Chess* chess = new Chess();
    chess->run();
    delete chess;
    return 0;
}