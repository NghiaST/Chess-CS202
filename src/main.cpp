#include "main.hpp"
#include "Chess.hpp"

int main()
{
    Chess* chess = new Chess();
    chess->run();
    delete chess;
    return 0;
}