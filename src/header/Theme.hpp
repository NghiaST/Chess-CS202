#include <SFML/Graphics.hpp>
#include <cstring>
#include "include.hpp"
#include "Color.hpp"

const std::string BackgroundDirectory = "asset/image/";
const std::string PieceDirectory = "asset/image/";
const std::string BoardDirectory = "asset/image/";
const std::string FontDirectory = "asset/font/";

const std::string BackgroundName[] = {"Background_00.png", "Background_01.png", "Background_02.png", "Background_03.png", "Background_04.png", "Background_05.png", "Background_06.png", "Background_07.png", "Background_08.png", "Background_09.png"};
const std::string PieceName[] = {"Piece_00", "Piece_01", "Piece_02", "Piece_03", "Piece_04", "Piece_05", "Piece_06", "Piece_07", "Piece_08", "Piece_09"};
const std::string BoardName[] = {"Board_00.png", "Board_01.png", "Board_02.png", "Board_03.png", "Board_04.png", "Board_05.png", "Board_06.png", "Board_07.png", "Board_08.png", "Board_09.png"};
const std::string FontName[] = {"Font_00.ttf", "Font_01.ttf", "Font_02.ttf", "Font_03.ttf", "Font_04.ttf", "Font_05.ttf", "Font_06.ttf", "Font_07.ttf", "Font_08.ttf", "Font_09.ttf"};
const int FontSize[] = {8, 10, 12, 14, 16, 18, 20, 22, 24, 26};

struct ThemeIndex {
public:
    int BackgroundIndex;
    int PieceIndex;
    int BoardIndex;
    int ButtonIndex;
    int TextIndex;
    // int ArrowIndex; ???

public:
    ThemeIndex(int BackgroundIndex, int PieceIndex, int BoardIndex, int ButtonIndex, int TextIndex);
    ~ThemeIndex();
    void setThemeIndex(const ThemeIndex themeIndex);
};

ThemeIndex themeIndex[] = {
    ThemeIndex(0, 0, 0, 0, 0),
    ThemeIndex(1, 1, 1, 1, 1),
    ThemeIndex(2, 2, 2, 2, 2),
    ThemeIndex(3, 3, 3, 3, 3),
    ThemeIndex(4, 4, 4, 4, 4),
    ThemeIndex(5, 5, 5, 5, 5),
    ThemeIndex(6, 6, 6, 6, 6),
    ThemeIndex(7, 7, 7, 7, 7),
    ThemeIndex(8, 8, 8, 8, 8),
    ThemeIndex(9, 9, 9, 9, 9)
};

class ThemePiece {
private:
    std::vector<sf::Texture> PieceTexture;
public:
    ThemePiece() {}
    ~ThemePiece() {}
    void buildTexture(std::string PieceName);
    const sf::Texture& getTexture(int pieceData) const;
};

class Theme : private ThemeIndex {
private:
    std::string BackgroundName;
    std::string PieceName;
    std::string BoardName;
    std::string FontName;
private:
    sf::Texture BackgroundTexture;
    ThemePiece PieceTextureList;
    sf::Texture BoardTexture;
    ColorItemMulti ColorButton;
    ColorItemMulti ColorText;
    sf::Font FontText;
    int FontSize;

public: // default

public:
    Theme(const ThemeIndex themeIndex = themeIndex[0]);
    ~Theme();
    void setTheme(const ThemeIndex themeIndex);
};