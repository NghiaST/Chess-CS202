#ifndef __Color_hpp__
#define __Color_hpp__

#include <SFML/Graphics.hpp>
#include <vector>

struct ColorItem {
    sf::Color FillColor;
    sf::Color TextColor;
    sf::Color OutlineColor;
    ColorItem();
    ColorItem(sf::Color FillColor, sf::Color TextColor, sf::Color OutlineColor);
};

class ColorItemMulti { /// note: statusColor = 0: none, 1: pointed, 2: selected, 3: hold
protected :
    std::vector<ColorItem> listColor; /// suggested: size = 4
public :
    ColorItemMulti(std::vector<ColorItem> listColor);
    ColorItem getColor(int statusColor);
};

struct Color {
    static const sf::Color SilverColor;
    static const sf::Color DimGrayColor;
    static const sf::Color RedColor;
    static const sf::Color GreenColor;
    static const sf::Color BlueColor;
    static const sf::Color BlackColor;
    static const sf::Color WhiteColor;
    static const sf::Color OrangeColor;
    static const sf::Color YellowColor;
    static const sf::Color LightGreenColor;
    static const sf::Color LightYellowColor;

    static const sf::Color LavenderBushColor;
    static const sf::Color EerieBlackColor;
    static const sf::Color AntiFlashWhiteColor;

    static const sf::Color RoyalPurpleColor;
    static const sf::Color VistaBlueColor;
    static const sf::Color MediumSlateBlueColor;
    static const sf::Color UranianBlueColor;
    static const sf::Color DarkCyanColor;

    static const sf::Color LightRedColor;
    static const sf::Color TeaRoseColor;
    static const sf::Color BrightPinkColor;
    static const sf::Color TransparentColor;

    static const ColorItem ColorItemNoButton;
    static const ColorItem ColorItemDefault;
    static const ColorItem ColorItemRed;
    static const ColorItem ColorItemGreen;
    static const ColorItem ColorItemBlue;
    static const ColorItem ColorItemBlack;
    static const ColorItem ColorItemWhite;
    static const ColorItem ColorItemOrange;
    static const ColorItem ColorItemYellow;
    static const ColorItem ColorItemLightGreen;
    static const ColorItem ColorItemLightYellow;
    static const ColorItem ColorItemLavenderBush;

    static const ColorItemMulti ColorItemMultiNoButton;
    static const ColorItemMulti ColorItemMultiDefault;
    static const ColorItemMulti ColorItemMultiRed;
    static const ColorItemMulti ColorItemMultiGreen;
    static const ColorItemMulti ColorItemMultiBlue;
    static const ColorItemMulti ColorItemMultiBlack;
    static const ColorItemMulti ColorItemMultiWhite;
    static const ColorItemMulti ColorItemMultiOrange;
};

#endif