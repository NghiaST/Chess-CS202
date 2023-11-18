#include <DataControl/Theme.hpp>
#include <DataControl/FileInit.hpp>
#include <iostream>

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

Theme* Theme::instance = nullptr;

Theme::Theme() : ThemeIndex(ThemeData::ThemeIndexDefault)
{
    this->TitleScreenTexture = std::make_unique<sf::Texture>();
    this->BackgroundTexture = std::make_unique<sf::Texture>();
    this->texturePieces = new TexturePieces();
    this->textureBoard = new TextureBoard();
    this->ColorBM_Default   = Color::ButMultiDefault;
    this->ColorBM_Static    = Color::ButMultiStatic;
    this->ColorBM_Title     = Color::ButMultiTextFullColor;
    this->ColorBM_Text      = Color::ButMultiTextStatic;
    this->ColorBM_Home      = Color::ButMultiDefault;
    this->ColorBM_Ingame    = Color::ButMultiDefault;

    if (!this->TitleScreenTexture->loadFromFile(ThemeData::TitleImageFile)) printf("Error loading title screen texture\n");
    if (!this->FontTitle.loadFromFile(ThemeData::FontTitleName)) printf("Error loading fonttitle texture\n");
    this->setThemeID(FileInit::LoadTheme());
}

Theme::~Theme() {
    this->TitleScreenTexture = nullptr;
    this->BackgroundTexture = nullptr;
    delete texturePieces;
    delete textureBoard;
}

Theme* Theme::getInstance() {
    if (Theme::instance == nullptr) {
        Theme::instance = new Theme();
    }
    return instance;
}

void Theme::destroyInstance() {
    if (Theme::instance != nullptr) {
        delete Theme::instance;
        Theme::instance = nullptr;
    }
}

void Theme::freshNameURL() {
    BackgroundName = ThemeData::BackgroundNameList[BackgroundIndex];
    PieceDir = ThemeData::PieceNameList[PieceIndex];
    BoardName = ThemeData::BoardNameList[BoardIndex];
    FontName = ThemeData::FontNameList[TextIndex];

    BackgroundURL = ThemeData::BackgroundDirectory + BackgroundName;
    PieceDir = ThemeData::PieceDirectory + PieceDir;
    BoardURL = ThemeData::BoardDirectory + BoardName;
    FontURL = ThemeData::FontDirectory + FontName;
}

void Theme::setThemeID(const ThemeIndex& themeIndex)
{
    ThemeIndex::operator=(themeIndex);
    freshNameURL();

    FontSize = 20;
    if (!BackgroundTexture->loadFromFile(this->BackgroundURL)) printf("Error loading background texture: %s\n", BackgroundName.c_str());
    texturePieces->buildTexture(this->PieceDir);
    textureBoard->buildTexture(BoardURL);
    
    this->ColorBM_Default = ThemeData::ColorBM_DefaultList[ButtonIndex];
    if (!FontText.loadFromFile(this->FontURL)) printf("Error loading fonttext texture: %s\n", FontName.c_str());
}

void Theme::setBackground(int BackgroundIndex) {
    this->BackgroundIndex = BackgroundIndex;
    freshNameURL();
    if (!BackgroundTexture->loadFromFile(this->BackgroundURL)) printf("Error loading background texture: %s\n", BackgroundName.c_str());
}

void Theme::setPiece(int PieceIndex) {
    this->PieceIndex = PieceIndex;
    freshNameURL();
    texturePieces->buildTexture(this->PieceDir);
}

void Theme::setBoard(int BoardIndex) {
    this->BoardIndex = BoardIndex;
    freshNameURL();
    textureBoard->buildTexture(BoardURL);
}

void Theme::setButton(int ButtonIndex) {
    this->ButtonIndex = ButtonIndex;
    this->ColorBM_Default = ThemeData::ColorBM_DefaultList[ButtonIndex];
}

void Theme::setText(int TextIndex) {
    this->TextIndex = TextIndex;
    freshNameURL();
    if (!FontText.loadFromFile(this->FontURL)) printf("Error loading fonttext texture: %s\n", FontName.c_str());
}

ThemeIndex Theme::getThemeIndex() const {
    return ThemeIndex(BackgroundIndex, PieceIndex, BoardIndex, ButtonIndex, TextIndex);
}

const sf::Texture &Theme::getTitleScreenTexture() const
{
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
