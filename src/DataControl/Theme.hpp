#ifndef __Theme_hpp__
#define __Theme_hpp__

#include "Include.hpp"
#include "Color.hpp"
#include <SFML/Graphics.hpp>
#include <cstring>
#include <fstream>
#include <memory>

class TextureMaking {
public:
    static std::unique_ptr<sf::Texture> Make(Point size, sf::Color sfColor);
};
// Arrow

struct ThemeIndex {
public:
    int BackgroundIndex;
    int PieceIndex;
    int BoardIndex;
    int ButtonIndex;
    int TextIndex;

public:
    ThemeIndex();
    ThemeIndex(int BackgroundIndex, int PieceIndex, int BoardIndex, int ButtonIndex, int TextIndex);
    ~ThemeIndex();
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

class Theme : protected ThemeIndex {
private:
    // Constructors and destructor
    Theme();
    ~Theme();

public:
    // Singleton
    static Theme* getInstance();
    static void destroyInstance();

public:
    // Accessors
    const ColorButMulti& getColorDefault() const;
    const ColorButMulti& getColorStatic() const;
    const ColorButMulti& getColorTitle() const;
    const ColorButMulti& getColorText() const;
    const ColorButMulti& getColorHome() const;
    const ColorButMulti& getColorIngame() const;
    const sf::Font& getFont() const;
    const sf::Font& getFontTitle() const;
    const int getFontSize() const;
    const sf::Texture& getTitleScreenTexture() const;
    const sf::Texture& getBackgroundTexture() const;
    const TexturePieces& getTexturePieces() const;
    const TextureBoard& getTextureBoard() const;
    const sf::Texture& getPieceTexture(int piece) const;
    const sf::Texture& getBoardTexture(TextureBoard::TYPE type) const;
    ThemeIndex getThemeIndex() const;

public:
    // Mutators
    void setBackground(int BackgroundIndex);
    void setPiece(int PieceIndex);
    void setBoard(int BoardIndex);
    void setButton(int ButtonIndex);
    void setText(int TextIndex);
    void setThemeID(const ThemeIndex& themeIndex);

private:
    // Helper functions
    void freshNameURL();

private:
    // Singleton pattern variable
    static Theme* instance;

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

    std::string BackgroundName;
    std::string PieceName;
    std::string BoardName;
    std::string FontName;

    std::string BackgroundURL;
    std::string PieceDir;
    std::string BoardURL;
    std::string FontURL;
};

namespace ThemeData {
    const std::string ThemeDataFile = "dat/theme.dat";
    const std::string BackgroundDirectory = "asset/image/background/";
    const std::string PieceDirectory = "asset/image/piece/";
    const std::string BoardDirectory = "asset/image/board/";
    const std::string FontDirectory = "asset/font/";
    const std::string FontTitleName = "asset/font/KeeponTruckin.ttf";
    const std::string TitleImageFile = "asset/image/home/TitleImage.png";

    const std::vector<std::string> BackgroundNameList = {"nature_morning.png", "cherry-blossom.jpg", "haibara-1.png", "universe-boom.jpg", "lightdark.jpg", "surface_earth.jpg", "space.jfif", "futuristic-neon.jpg", "wooden-wall.jpg", "wall.jpg", "palace.jpg", "anime-girl-1.png"};
    const std::vector<std::string> PieceNameList = {"caliente", "cburnett", "celtic", "dubrovny", "fresca", "frugale", "gioco", "governor", "kiwen-suwi", "maestro", "usual"};
    const std::vector<std::string> BoardNameList = {"pink-pyramid.png", "blue.png",  "blue-marble.png", "canvas.png", "green-plastic.png", "leather.png", "maple.png", "ncf-board.png", "purple-diag.png", "wood.png", "wood2.png", "wood3.jpg", "metal.jpg", "olive.jpg"};
    const std::vector<std::string> FontNameList = {"Arial-bold.ttf", "Arial.ttf", "ShortBaby.ttf", "CarryYou.ttf", "ChristmasJumper.ttf", "CuteMonster.ttf", "Hippiemods.otf", "MouldyCheese.ttf", "TimesNewRoman-bold.ttf", "TimesNewRoman.ttf", "Vni-times-bold.ttf", "Vni-times.ttf", "KeeponTruckin.ttf"};
    const std::vector<std::string> ColorBM_NameList = {"Default", "Light1", "Light2", "Light3", "Funny", "Humor", "Lucky", "Sad", "Chill", "Love", "Hehe", "Dark"};
    const std::vector<ColorButMulti> ColorBM_DefaultList = {Color::ButMultiDefault, Color::ButMultiLight1, Color::ButMultiLight2, Color::ButMultiLight3, Color::ButMultiFunny, Color::ButMultiHumor, Color::ButMultiLucky, Color::ButMultiSad, Color::ButMultiChill, Color::ButMultiLove, Color::ButMultiHehe, Color::ButMultiDark};
    const std::vector<int> FontSizeList = {8, 10, 12, 14, 16, 18, 20, 22, 24, 26};
    const ThemeIndex ThemeIndexDefault = ThemeIndex(0, 0, 0, 0, 0);
};

#endif