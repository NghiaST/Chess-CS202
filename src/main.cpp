#include <main.hpp>
#include <Application.hpp>

int main()
{
    Application* chess = new Application();
    chess->run();
    delete chess;
    return 0;
}