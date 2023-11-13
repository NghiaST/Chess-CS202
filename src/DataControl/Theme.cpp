#include "Theme.hpp"

///-----------------------------------------------------------------
///-----------------------------ThemeData---------------------------
const std::string ThemeData::ThemeDataFile = "dat/theme.dat";
const std::string ThemeData::BackgroundDirectory = "asset/image/background/";
const std::string ThemeData::PieceDirectory = "asset/image/piece/";
const std::string ThemeData::BoardDirectory = "asset/image/board/";
const std::string ThemeData::FontDirectory = "asset/font/";
const std::string ThemeData::FontTitleName = "asset/font/KeeponTruckin.ttf";

const std::vector<std::string> ThemeData::BackgroundNameList = {"cherry-blossom.jpg", "haibara-1.jpg", "universe-boom.jpg", "lightdark.jpg", "surface_earth.jpg", "beautiful_image.jfif", "modern-futuristic-neon.jpg", "brown-wooden-wall.jpg", "wall.jpg", "palace.jpg"};
const std::vector<std::string> ThemeData::PieceNameList = {"caliente", "cburnett", "celtic", "dubrovny", "fresca", "frugale", "gioco", "governor", "kiwen-suwi", "maestro", "usual"};
const std::vector<std::string> ThemeData::BoardNameList = {"pink-pyramid.png", "blue.png",  "blue-marble.png", "canvas.png", "green-plastic.png", "leather.png", "maple.png", "ncf-board.png", "purple-diag.png", "wood.png", "wood2.png"};
const std::vector<std::string> ThemeData::FontNameList = {"Arial-bold.ttf", "Arial.ttf", "ShortBaby.ttf", "CarryYou.ttf", "ChristmasJumper.ttf", "CuteMonster.ttf", "Hippiemods.otf", "MouldyCheese.ttf", "TimesNewRoman-bold.ttf", "TimesNewRoman.ttf", "Vni-times-bold.ttf", "Vni-times.ttf", "KeeponTruckin.ttf"};
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
///-----------------------------TextureMaking-----------------------

std::unique_ptr<sf::Texture> TextureMaking::Make(Point size, sf::Color sfColor) {
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

///-----------------------------------------------------------------
///-----------------------------ThemeIndex--------------------------

ThemeIndex::ThemeIndex() {
    this->BackgroundIndex = 0;
    this->PieceIndex = 0;
    this->BoardIndex = 0;
    this->ButtonIndex = 0;
    this->TextIndex = 0;
}

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
///-----------------------------TexturePieces--------------------------

TexturePieces::TexturePieces()
{
    PieceTexture.resize(24);
    for(auto it = PieceTexture.begin(); it != PieceTexture.end(); ++it)
    {
        *it = std::make_unique<sf::Texture>();
    }
}

TexturePieces::~TexturePieces()
{
    for(auto& it : PieceTexture)
        it = nullptr;
}

void TexturePieces::buildTexture(std::string PieceDir)
{
    const static std::string makeColor = " wb";
    const static std::string makeName = " PNBRQK";
    const static std::string suffix = ".png";
    for(int chesscolor = 1; chesscolor <= 2; chesscolor++)
    {
        for (int i = 1; i <= 6; i++)
        {
            std::string FileName = PieceDir + "/" + makeColor.substr(chesscolor, 1) + makeName.substr(i, 1) + suffix;
            if (!this->PieceTexture[chesscolor*8 + i]->loadFromFile(FileName)) printf("Error loading piece texture: %s\n", FileName.c_str());
        }
    }
}

const sf::Texture& TexturePieces::getTexture(int piece) const
{
    return *this->PieceTexture[piece];
}

TextureBoard::TextureBoard() {
    this->BoardTexture = std::make_unique<sf::Texture>();
    this->HoverTexture     = TextureMaking::Make(Point(INTERFACE::BoardLength, INTERFACE::BoardLength), sf::Color(123, 23, 44));
    this->SelectedTexture  = TextureMaking::Make(Point(INTERFACE::BoardLength, INTERFACE::BoardLength), sf::Color(255, 255, 0));
    this->PreMoveStartTexture = TextureMaking::Make(Point(INTERFACE::BoardLength, INTERFACE::BoardLength), sf::Color(41, 235, 20));
    this->PreMoveTargetTexture = TextureMaking::Make(Point(INTERFACE::BoardLength, INTERFACE::BoardLength), sf::Color(51, 245, 30));
    this->PossibleTexture  = TextureMaking::Make(Point(INTERFACE::BoardLength, INTERFACE::BoardLength), sf::Color(0, 255, 0));
    this->PossibleCaptureTexture   = TextureMaking::Make(Point(INTERFACE::BoardLength, INTERFACE::BoardLength), sf::Color(220, 0, 0));
    this->CheckTexture     = TextureMaking::Make(Point(INTERFACE::BoardLength, INTERFACE::BoardLength), sf::Color::Red);
    this->CheckMateTexture = TextureMaking::Make(Point(INTERFACE::BoardLength, INTERFACE::BoardLength), sf::Color(255, 0, 255));
    this->StaleMateTexture = TextureMaking::Make(Point(INTERFACE::BoardLength, INTERFACE::BoardLength), sf::Color(200, 100, 200));
}

TextureBoard::~TextureBoard() {
    this->BoardTexture = nullptr;
    this->HoverTexture = nullptr;
    this->SelectedTexture = nullptr;
    this->PreMoveStartTexture = nullptr;
    this->PreMoveTargetTexture = nullptr;
    this->PossibleTexture = nullptr;
    this->PossibleCaptureTexture = nullptr;
    this->CheckTexture = nullptr;
    this->CheckMateTexture = nullptr;
    this->StaleMateTexture = nullptr;
}

void TextureBoard::buildTexture(std::string URL) {
    if (!this->BoardTexture->loadFromFile(URL)) printf("Error loading board texture: %s\n", URL.c_str());
}

const sf::Texture& TextureBoard::getTexture(TYPE type) const {
    switch(type) {
        case Board: return *this->BoardTexture;
        case Hover: return *this->HoverTexture;
        case Selected: return *this->SelectedTexture;
        case PreMoveStart: return *this->PreMoveStartTexture;
        case PreMoveTarget: return *this->PreMoveTargetTexture;
        case Possible: return *this->PossibleTexture;
        case PossibleCapture: return *this->PossibleCaptureTexture;
        case Check: return *this->CheckTexture;
        case CheckMate: return *this->CheckMateTexture;
        case StaleMate: return *this->StaleMateTexture;
        default: 
            printf("TextureBoard ERROR\n"); 
            return *this->BoardTexture;
    }
}

///-----------------------------------------------------------------
///-----------------------------Theme-------------------------------

Theme::Theme() : ThemeIndex(ThemeData::ThemeIndexDefault)
{
    this->TitleScreenTexture = std::make_unique<sf::Texture>();
    this->BackgroundTexture = std::make_unique<sf::Texture>();
    this->texturePieces = new TexturePieces();
    this->textureBoard = new TextureBoard();
    this->ColorBM_Default = Color::ColorButMultiDefault;
    this->ColorBM_Static = Color::ColorButMultiStatic;
    this->ColorBM_Title = Color::ColorButMultiTextFullColor;
    this->ColorBM_Text = Color::ColorButMultiTextStatic;
    this->ColorBM_Home = Color::ColorButMultiLight;
    this->ColorBM_Ingame = Color::ColorButMultiDefault;

    if (!this->TitleScreenTexture->loadFromFile("asset/image/home/TitleImage.png")) printf("Error loading title screen texture\n");
    if (!this->FontTitle.loadFromFile(ThemeData::FontTitleName)) printf("Error loading fonttitle texture\n");
    this->setTheme(ThemeData::ThemeIndexDefault);
}

Theme::~Theme() {
    this->TitleScreenTexture = nullptr;
    this->BackgroundTexture = nullptr;
    delete texturePieces;
    delete textureBoard;
}

void Theme::loadFile()
{
    std::fstream fin(ThemeData::ThemeDataFile, std::ios::in);
    if (fin.is_open() == false) {
        printf("WARNING: Loading theme from file FAILED: %s\n", ThemeData::ThemeDataFile.c_str());
        return;
    }
    int newBackgroundIndex, newPieceIndex, newBoardIndex, newButtonIndex, newTextIndex;
    fin >> newBackgroundIndex >> newPieceIndex >> newBoardIndex >> newButtonIndex >> newTextIndex;
    fin.close();

    setThemeIndex(ThemeIndex(newBackgroundIndex, newPieceIndex, newBoardIndex, newButtonIndex, newTextIndex));
}
#include <iostream>
void Theme::freshNameURL() {
    BackgroundName = ThemeData::BackgroundNameList[BackgroundIndex];
    PieceDir = ThemeData::PieceNameList[PieceIndex];
    BoardName = ThemeData::BoardNameList[BoardIndex];
    FontName = ThemeData::FontNameList[TextIndex];

    BackgroundURL = ThemeData::BackgroundDirectory + BackgroundName;
    PieceDir = ThemeData::PieceDirectory + PieceDir;
    BoardURL = ThemeData::BoardDirectory + BoardName;
    FontURL = ThemeData::FontDirectory + FontName;
    std::cout << FontName << std::endl;
}   

void Theme::setTheme(const ThemeIndex themeIndex)
{
    setThemeIndex(themeIndex);
    freshNameURL();

    FontSize = 20;
    if (!BackgroundTexture->loadFromFile(this->BackgroundURL)) printf("Error loading background texture: %s\n", BackgroundName.c_str());
    texturePieces->buildTexture(this->PieceDir);
    textureBoard->buildTexture(BoardURL);
    if (!FontText.loadFromFile(this->FontURL)) printf("Error loading fonttext texture: %s\n", FontName.c_str());
}

void Theme::setTheme(const int themeIndex)
{
    ThemeIndex index = ThemeData::ThemeIndexDefault;
    if (themeIndex >= 0 && themeIndex < ThemeData::ThemeCount) {
        index = ThemeData::themeIndexList[themeIndex];
    }
    this->setTheme(index);
}

const sf::Texture& Theme::getTitleScreenTexture() const {
    return *this->TitleScreenTexture;
}

const sf::Texture& Theme::getBackgroundTexture() const {
    return *this->BackgroundTexture;
}

const TexturePieces& Theme::getTexturePieces() const {
    return *this->texturePieces;
}

const TextureBoard& Theme::getTextureBoard() const {
    return *this->textureBoard;
}

const sf::Texture& Theme::getPieceTexture(int piece) const {
    return this->texturePieces->getTexture(piece);
}

const sf::Texture& Theme::getBoardTexture(TextureBoard::TYPE type) const {
    return this->textureBoard->getTexture(type);
}

const ColorButMulti &Theme::getColorDefault() const {
    return this->ColorBM_Default;
}

const ColorButMulti &Theme::getColorStatic() const {
    return this->ColorBM_Static;
}

const ColorButMulti &Theme::getColorTitle() const {
    return this->ColorBM_Title;
}

const ColorButMulti &Theme::getColorText() const {
    return this->ColorBM_Text;
}

const ColorButMulti &Theme::getColorHome() const {
    return this->ColorBM_Home;
}

const ColorButMulti &Theme::getColorIngame() const {
    return this->ColorBM_Ingame;
}

const sf::Font& Theme::getFont() const {
    return this->FontText;
}

const sf::Font &Theme::getFontTitle() const {
    return this->FontTitle;
}

const int Theme::getFontSize() const {
    return this->FontSize;
}
