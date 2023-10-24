#include "Chess.hpp"

void Chess::CreateGraphicsBoard() {
    // The size of the chessboard squares
    const float squareSize = 50.0f;
    
    // Create a chessboard with alternating colors
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));

            // Alternate the square colors
            if ((row + col) % 2 == 0) {
                square.setFillColor(sf::Color::White);
            } else {
                square.setFillColor(sf::Color::Black);
            }

            // Position the square
            square.setPosition(col * squareSize, row * squareSize);

            // Draw the square
            window.draw(square);
        }
    }
}

Chess::Chess() {
    // Create the window
    window.create(sf::VideoMode(800, 650), "Chess");
}

Chess::~Chess() {
    // Close the window
    window.close();
}

void Chess::run()
{
    // Create the chessboard

    // Display the window
    window.display();

    // Wait for the user to close the window
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Red);
        CreateGraphicsBoard();
        window.display();
    }
}