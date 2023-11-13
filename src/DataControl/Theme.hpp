#ifndef __Theme_hpp__
#define __Theme_hpp__

#include <cstring>
#include <fstream>
#include <memory>

#include <SFML/Graphics.hpp>
#include "Include.hpp"
#include "Color.hpp"

class TextureMaking {
public:
    static std::unique_ptr<sf::Texture> Make(Point size, sf::Color sfColor);
};

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

class TexturePieces {
public:
    TexturePieces();
    ~TexturePieces();
    void buildTexture(std::string PieceName);
    const sf::Texture& getTexture(int piece) const;
private:
    std::vector<std::unique_ptr<sf::Texture>> PieceTexture;
};

class TextureBoard {
public:
    enum TYPE {
        Board = 0,
        Hover,
        Selected,
        PreMoveStart,
        PreMoveTarget,
        Possible,
        PossibleCapture,
        Check,
        CheckMate,
        StaleMate
    };

public:
    TextureBoard();
    ~TextureBoard();
    void buildTexture(std::string URL);
    const sf::Texture& getTexture(TYPE type) const;

private:
    std::unique_ptr<sf::Texture> BoardTexture;  // 8x8 board
    std::unique_ptr<sf::Texture> HoverTexture;
    std::unique_ptr<sf::Texture> SelectedTexture;
    std::unique_ptr<sf::Texture> PreMoveStartTexture;
    std::unique_ptr<sf::Texture> PreMoveTargetTexture;
    std::unique_ptr<sf::Texture> PossibleTexture;
    std::unique_ptr<sf::Texture> PossibleCaptureTexture;
    std::unique_ptr<sf::Texture> CheckTexture;
    std::unique_ptr<sf::Texture> StaleMateTexture;
    std::unique_ptr<sf::Texture> CheckMateTexture;
};

class Theme : private ThemeIndex {
public:
    Theme();
    ~Theme();
    void loadFile();
    void setTheme(const ThemeIndex themeIndex);
    void setTheme(const int themeIndex);

    const sf::Texture& getTitleScreenTexture() const;
    const sf::Texture& getBackgroundTexture() const;
    const TexturePieces& getTexturePieces() const;
    const TextureBoard& getTextureBoard() const;

    const sf::Texture& getPieceTexture(int piece) const;
    const sf::Texture& getBoardTexture(TextureBoard::TYPE type) const;

    const ColorButMulti& getColorDefault() const;
    const ColorButMulti& getColorStatic() const;
    const ColorButMulti& getColorTitle() const;
    const ColorButMulti& getColorText() const;
    const ColorButMulti& getColorHome() const;
    const ColorButMulti& getColorIngame() const;
    const sf::Font& getFont() const;
    const sf::Font& getFontTitle() const;
    const int getFontSize() const;

private:
    void freshNameURL();

private:
    std::string BackgroundName;
    std::string PieceName;
    std::string BoardName;
    std::string FontName;

    std::string BackgroundURL;
    std::string PieceDir;
    std::string BoardURL;
    std::string FontURL;

private:
    // Home screen
    std::unique_ptr<sf::Texture> TitleScreenTexture;

    // Ingame screen
    std::unique_ptr<sf::Texture> BackgroundTexture;
    TexturePieces* texturePieces;
    TextureBoard* textureBoard;
    
    // Button
    ColorButMulti ColorBM_Default;
    ColorButMulti ColorBM_Static;
    ColorButMulti ColorBM_Title;
    ColorButMulti ColorBM_Text;
    ColorButMulti ColorBM_Home;
    ColorButMulti ColorBM_Ingame;

    sf::Font FontTitle;
    sf::Font FontText;
    int FontSize;
};

class ThemeData {
public:
    static const std::string ThemeDataFile;
    static const std::string BackgroundDirectory;
    static const std::string PieceDirectory;
    static const std::string BoardDirectory;
    static const std::string FontDirectory;

    static const std::string FontTitleName;

    static const std::vector<std::string> BackgroundNameList;
    static const std::vector<std::string> PieceNameList;
    static const std::vector<std::string> BoardNameList;
    static const std::vector<std::string> FontNameList;


    static const std::vector<int> FontSizeList;
    static const int ThemeCount;

    static const ThemeIndex ThemeIndexDefault;
    static const std::vector<ThemeIndex> themeIndexList;
};

#endif