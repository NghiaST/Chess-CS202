#ifndef __Theme_hpp__
#define __Theme_hpp__

#include <SFML/Graphics.hpp>
#include "Include.hpp"
#include "Color.hpp"
#include <cstring>

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
private:
    std::string BackgroundName;
    std::string PieceName;
    std::string BoardName;
    std::string FontName;
private:
    std::unique_ptr<sf::Texture> BackgroundTexture;
    ThemePiece* PieceTextureList;
    std::unique_ptr<sf::Texture> BoardTexture;
    ColorItemMulti* ColorButton;
    ColorItemMulti* ColorText;
    sf::Font FontText;
    int FontSize;

public: // default

public:
    Theme();
    ~Theme();
    void setTheme(const ThemeIndex themeIndex);
    void setTheme(const int themeIndex);
    const sf::Texture& getBackgroundTexture() const;
    const sf::Texture& getPieceTexture(int pieceData) const;
    const sf::Texture& getBoardTexture() const;
    const ColorItemMulti* getButtonColor() const;
    const ColorItemMulti* getTextColor() const;
    const sf::Font getFont() const;
    const int getFontSize() const;
};

struct ThemeData {
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