#include <SFML/Graphics.hpp>
#include <cstring>
const std::string BackgroundName[10] = {"Background_00.png", "Background_01.png", "Background_02.png", "Background_03.png", "Background_04.png", "Background_05.png", "Background_06.png", "Background_07.png", "Background_08.png", "Background_09.png"};
const std::string PieceName[10] = {"Piece_00.png", "Piece_01.png", "Piece_02.png", "Piece_03.png", "Piece_04.png", "Piece_05.png", "Piece_06.png", "Piece_07.png", "Piece_08.png", "Piece_09.png"};
const std::string BoardName[10] = {"Board_00.png", "Board_01.png", "Board_02.png", "Board_03.png", "Board_04.png", "Board_05.png", "Board_06.png", "Board_07.png", "Board_08.png", "Board_09.png"};
const std::string ColorName[10] = {"Color_00.png", "Color_01.png", "Color_02.png", "Color_03.png", "Color_04.png", "Color_05.png", "Color_06.png", "Color_07.png", "Color_08.png", "Color_09.png"};
const std::string FontName[10] = {"Font_00.ttf", "Font_01.ttf", "Font_02.ttf", "Font_03.ttf", "Font_04.ttf", "Font_05.ttf", "Font_06.ttf", "Font_07.ttf", "Font_08.ttf", "Font_09.ttf"};
const int FontSize[10] = {8, 10, 12, 14, 16, 18, 20, 22, 24, 26};

struct Theme {
public:
    int BackgroundIndex;
    int PieceIndex;
    int BoardIndex;
    int ColorIndex;
    int FontIndex;
    int FontSizeIndex;
    // int arrowIndex;
public:
    Theme(int BackgroundIndex, int PieceIndex, int BoardIndex, int ColorIndex, int FontIndex, int FontSizeIndex);
};