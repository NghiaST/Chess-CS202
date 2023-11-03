#ifndef __Theme_hpp__
#define __Theme_hpp__

#include <cstring>
#include <fstream>

#include <SFML/Graphics.hpp>
#include "Include.hpp"
#include "Color.hpp"

class ThemeIndex {
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

class ThemePiece {
private:
    std::vector<std::unique_ptr<sf::Texture>> PieceTexture;
public:
    ThemePiece();
    ~ThemePiece();
    void buildTexture(std::string PieceName);
    const sf::Texture& getTexture(int pieceData) const;
};

class Theme : private ThemeIndex {
public:
    Theme();
    ~Theme();
    void loadFile();
    void setTheme(const ThemeIndex themeIndex);
    void setTheme(const int themeIndex);
    const sf::Texture& getBackgroundTexture() const;
    const sf::Texture& getPieceTexture(int pieceData) const;

    const sf::Texture& getBoardTexture() const;
    const sf::Texture& getBoardSelectedTexture() const;
    const sf::Texture& getBoardPreMoveTexture() const;
    const sf::Texture& getBoardMoveTexture() const;
    const sf::Texture& getBoardCaptureTexture() const;
    const sf::Texture& getBoardCheckTexture() const;
    const sf::Texture& getBoardCheckMateTexture() const;

    const ColorButMulti& getButtonColorMulti() const;
    const ColorButMulti& getTextColorMulti() const;
    const sf::Font& getFont() const;
    const int getFontSize() const;

public: // default
    std::unique_ptr<sf::Texture> makeTexture(Point size, sf::Color sfColor);

private:
    std::string BackgroundName;
    std::string PieceName;
    std::string BoardName;
    std::string FontName;
private:
    std::unique_ptr<sf::Texture> BackgroundTexture;
    ThemePiece* PieceTextureList;

    // board texture list
    std::unique_ptr<sf::Texture> BoardTexture;
    std::unique_ptr<sf::Texture> BoardSelectedTexture;
    std::unique_ptr<sf::Texture> BoardPreMoveTexture;
    std::unique_ptr<sf::Texture> BoardMoveTexture;
    std::unique_ptr<sf::Texture> BoardCaptureTexture;
    std::unique_ptr<sf::Texture> BoardCheckTexture;
    std::unique_ptr<sf::Texture> BoardCheckMateTexture;
    
    ColorButMulti* ColorButton;
    ColorButMulti* ColorText;
    ColorButMulti* ColorMText;

    sf::Font* FontText;
    int FontSize;
};

class ThemeData {
public:
    static const std::string ThemeDataFile;
    static const std::string BackgroundDirectory;
    static const std::string PieceDirectory;
    static const std::string BoardDirectory;
    static const std::string FontDirectory;

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