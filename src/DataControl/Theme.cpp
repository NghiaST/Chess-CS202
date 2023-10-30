#include "Theme.hpp"

///-----------------------------------------------------------------
///-----------------------------ThemeData---------------------------
const std::string ThemeData::BackgroundDirectory = "asset/image/background/";
const std::string ThemeData::PieceDirectory = "asset/image/piece/";
const std::string ThemeData::BoardDirectory = "asset/image/board/";
const std::string ThemeData::FontDirectory = "asset/font/";

const std::vector<std::string> ThemeData::BackgroundNameList = {"universe-boom.jpg", "Background_01.png", "Background_02.png", "Background_03.png", "Background_04.png", "Background_05.png", "Background_06.png", "Background_07.png", "Background_08.png", "Background_09.png"};
const std::vector<std::string> ThemeData::PieceNameList = {"default", "Piece_01", "Piece_02", "Piece_03", "Piece_04", "Piece_05", "Piece_06", "Piece_07", "Piece_08", "Piece_09"};
const std::vector<std::string> ThemeData::BoardNameList = {"lichess.png", "Board_01.png", "Board_02.png", "Board_03.png", "Board_04.png", "Board_05.png", "Board_06.png", "Board_07.png", "Board_08.png", "Board_09.png"};
const std::vector<std::string> ThemeData::FontNameList = {"arial.ttf", "Font_01.ttf", "Font_02.ttf", "Font_03.ttf", "Font_04.ttf", "Font_05.ttf", "Font_06.ttf", "Font_07.ttf", "Font_08.ttf", "Font_09.ttf"};
const std::vector<int> ThemeData::FontSizeList = {8, 10, 12, 14, 16, 18, 20, 22, 24, 26};
const int ThemeData::ThemeCount = 10;
const ThemeIndex ThemeData::ThemeIndexDefault = ThemeIndex(0, 0, 0, 0, 0);
const std::vector<ThemeIndex> ThemeData::themeIndexList = {
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

///-----------------------------------------------------------------
///-----------------------------ThemeIndex--------------------------

ThemeIndex::ThemeIndex(int BackgroundIndex, int PieceIndex, int BoardIndex, int ButtonIndex, int TextIndex)
{
    this->BackgroundIndex = BackgroundIndex;
    this->PieceIndex = PieceIndex;
    this->BoardIndex = BoardIndex;
    this->ButtonIndex = ButtonIndex;
    this->TextIndex = TextIndex;
}

ThemeIndex::~ThemeIndex()
{
}

void ThemeIndex::setThemeIndex(const ThemeIndex themeIndex)
{
    this->BackgroundIndex = themeIndex.BackgroundIndex;
    this->PieceIndex = themeIndex.PieceIndex;
    this->BoardIndex = themeIndex.BoardIndex;
    this->ButtonIndex = themeIndex.ButtonIndex;
    this->TextIndex = themeIndex.TextIndex;
}

///-----------------------------------------------------------------
///-----------------------------ThemePiece--------------------------

ThemePiece::ThemePiece()
{
    PieceTexture.resize(24);
    for(auto it = PieceTexture.begin(); it != PieceTexture.end(); ++it)
    {
        *it = std::make_unique<sf::Texture>();
    }
}

ThemePiece::~ThemePiece()
{
    for(auto it = PieceTexture.begin(); it != PieceTexture.end(); ++it)
    {
        *it = nullptr;
    }
}

void ThemePiece::buildTexture(std::string PieceName)
{
    const static std::string makeColor = " wb";
    const static std::string makeName = " KQBNRP";
    const static std::string suffix = ".png";
    for(int chesscolor = 1; chesscolor <= 2; chesscolor++)
    {
        for (int i = 1; i <= 6; i++)
        {
            std::string FileName = PieceName + makeColor.substr(chesscolor, 1) + makeName.substr(i, 1) + suffix;
            if (!this->PieceTexture[chesscolor*8 + i]->loadFromFile(FileName)) {
                printf("Error loading piece texture: %s\n", FileName.c_str());
            }
        }
    }
}

const sf::Texture& ThemePiece::getTexture(int pieceData) const
{
    return *this->PieceTexture[pieceData];
}

///-----------------------------------------------------------------
///-----------------------------Theme-------------------------------

Theme::Theme() : ThemeIndex(ThemeData::ThemeIndexDefault)
{
    this->BackgroundTexture = std::make_unique<sf::Texture>();
    this->PieceTextureList = new ThemePiece();
    this->BoardTexture          = std::make_unique<sf::Texture>();
    this->BoardSelectedTexture  = std::make_unique<sf::Texture>();
    this->BoardMoveTexture      = std::make_unique<sf::Texture>();
    this->BoardCaptureTexture   = std::make_unique<sf::Texture>();
    this->BoardCheckTexture     = std::make_unique<sf::Texture>();
    this->BoardCheckMateTexture = std::make_unique<sf::Texture>();
    this->ColorButton = new ColorItemMulti(Color::ColorItemMultiDefault);
    this->ColorText = new ColorItemMulti(Color::ColorItemMultiNoButton);
    this->setTheme(ThemeData::ThemeIndexDefault);
}

Theme::~Theme()
{
}

void Theme::setTheme(const ThemeIndex themeIndex)
{
    this->setThemeIndex(themeIndex);
    this->BackgroundName = ThemeData::BackgroundDirectory + ThemeData::BackgroundNameList[themeIndex.BackgroundIndex];
    this->PieceName = ThemeData::PieceDirectory + ThemeData::PieceNameList[themeIndex.PieceIndex] + "/";
    this->BoardName = ThemeData::BoardDirectory + ThemeData::BoardNameList[themeIndex.BoardIndex];
    this->FontName = ThemeData::FontDirectory + ThemeData::FontNameList[themeIndex.TextIndex];

    this->FontSize = 20;
    if (!this->BackgroundTexture->loadFromFile(this->BackgroundName)) 
        printf("Error loading background texture: %s\n", BackgroundName.c_str());
    this->PieceTextureList->buildTexture(this->PieceName);
    if (!this->BoardTexture->loadFromFile(this->BoardName))
        printf("Error loading board texture: %s\n", BoardName.c_str());
    this->BoardSelectedTexture  = makeTexture(Point(60, 60), sf::Color(255, 255, 0));
    this->BoardMoveTexture      = makeTexture(Point(60, 60), sf::Color(120, 24, 136));
    this->BoardCaptureTexture   = makeTexture(Point(60, 60), sf::Color(220, 0, 0));
    this->BoardCheckTexture     = makeTexture(Point(60, 60), sf::Color(255, 255, 0));
    this->BoardCheckMateTexture = makeTexture(Point(60, 60), sf::Color(255, 0, 255));
    if (!this->FontText.loadFromFile(this->FontName))
        printf("Error loading fonttext texture: %s\n", FontName.c_str());
    
    this->ColorButton = new ColorItemMulti(Color::ColorItemMultiDefault);
    this->ColorText = new ColorItemMulti(Color::ColorItemMultiNoButton);
}

void Theme::setTheme(const int themeIndex)
{
    ThemeIndex index = ThemeData::ThemeIndexDefault;
    if (themeIndex >= 0 && themeIndex < ThemeData::ThemeCount) {
        index = ThemeData::themeIndexList[themeIndex];
    }
    this->setTheme(index);
}

const sf::Texture& Theme::getBackgroundTexture() const
{
    return *this->BackgroundTexture;
}

const sf::Texture& Theme::getPieceTexture(int pieceData) const
{
    return this->PieceTextureList->getTexture(pieceData);
}

const sf::Texture& Theme::getBoardTexture() const
{
    return *this->BoardTexture;
}

const sf::Texture& Theme::getBoardSelectedTexture() const
{
    return *this->BoardSelectedTexture;
}

const ColorItemMulti* Theme::getButtonColor() const
{
    return this->ColorButton;
}

const sf::Texture& Theme::getBoardMoveTexture() const
{
    return *this->BoardMoveTexture;
}

const sf::Texture& Theme::getBoardCaptureTexture() const
{
    return *this->BoardCaptureTexture;
}

const sf::Texture& Theme::getBoardCheckTexture() const
{
    return *this->BoardCheckTexture;
}

const sf::Texture& Theme::getBoardCheckMateTexture() const
{
    return *this->BoardCheckMateTexture;
}

const ColorItemMulti* Theme::getTextColor() const
{
    return this->ColorText;
}

const sf::Font Theme::getFont() const
{
    return this->FontText;
}

const int Theme::getFontSize() const
{
    return this->FontSize;
}

std::unique_ptr<sf::Texture> Theme::makeTexture(Point size, sf::Color sfColor)
{
    // Create a render texture
    sf::RenderTexture renderTexture;
    renderTexture.create(size.x, size.y);

    // Clear the render texture
    renderTexture.clear();

    // Create a rectangle shape
    sf::RectangleShape rectangleShape(sf::Vector2f(size.x, size.y));
    rectangleShape.setFillColor(sfColor);
    rectangleShape.setPosition(0, 0);

    // Draw the rectangle shape to the render texture
    renderTexture.draw(rectangleShape);

    // Update the render texture
    renderTexture.display();

    // Create a texture from the render texture
    std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>(renderTexture.getTexture());
    return texture;
}
