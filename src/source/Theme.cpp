#include "Theme.hpp"

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

void ThemePiece::buildTexture(std::string PieceName)
{
    const static std::string makeColor = " wb";
    const static std::string makeName = " KQBNRP";
    const static std::string suffix = ".png";
    this->PieceTexture.clear();
    this->PieceTexture.assign(24, sf::Texture());
    for(int chesscolor = 1; chesscolor <= 2; chesscolor++)
    {
        for (int i = 1; i <= 6; i++)
        {
            sf::Texture texture;
            std::string FileName = makeColor.substr(chesscolor, 1) + makeName.substr(i, 1) + suffix;
            if (!texture.loadFromFile(PieceDirectory + PieceName + "/" + FileName)) {
                printf("Error loading piece texture: %s\n", FileName.c_str());
            }
            this->PieceTexture[i] = texture;
        }
    }
}

const sf::Texture& ThemePiece::getTexture(int pieceData) const
{
    return this->PieceTexture[pieceData];
}

///-----------------------------------------------------------------
///-----------------------------Theme-------------------------------

Theme::Theme(const ThemeIndex themeIndex) : ThemeIndex(themeIndex)
{
    this->setTheme(themeIndex);
}

Theme::~Theme()
{
}

void Theme::setTheme(const ThemeIndex themeIndex)
{
    this->setThemeIndex(themeIndex);
    this->BackgroundName = BackgroundDirectory + std::to_string(themeIndex.BackgroundIndex);
    this->PieceName = PieceDirectory + std::to_string(themeIndex.PieceIndex) + "/";
    this->BoardName = BoardDirectory + std::to_string(themeIndex.BoardIndex);
    this->FontName = FontDirectory + std::to_string(themeIndex.TextIndex);

    this->FontSize = 20;
    this->BackgroundTexture.loadFromFile(this->BackgroundName);
    this->PieceTextureList.buildTexture(std::to_string(themeIndex.PieceIndex));
    this->BoardTexture.loadFromFile(this->BoardName);
    this->ColorButton = ColorItemMultiDefault;
    this->ColorText = ColorItemMultiNoButton;
    this->FontText.loadFromFile(this->FontName);
}
