#ifndef __Color_hpp__
#define __Color_hpp__

#include <SFML/Graphics.hpp>
#include <vector>

class ColorButton {
public :
    sf::Color FillColor;
    sf::Color TextColor;
    sf::Color OutlineColor;
    ColorButton();
    ColorButton(sf::Color FillColor, sf::Color TextColor, sf::Color OutlineColor);
};

class ColorButMulti { /// note: statusColor = 0: none, 1: pointed, 2: selected, 3: hold
protected :
    std::vector<ColorButton> listColor; /// suggested: size = 4
public :
    ColorButMulti();
    ColorButMulti(std::vector<ColorButton> listColor);
    ColorButton get(int statusColor);
};

class Color {
public:
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

    static const ColorButton ColorButtonNoButton;
    static const ColorButton ColorButtonDefault;
    static const ColorButton ColorButtonRed;
    static const ColorButton ColorButtonGreen;
    static const ColorButton ColorButtonBlue;
    static const ColorButton ColorButtonBlack;
    static const ColorButton ColorButtonWhite;
    static const ColorButton ColorButtonOrange;
    static const ColorButton ColorButtonYellow;
    static const ColorButton ColorButtonLightGreen;
    static const ColorButton ColorButtonLightYellow;
    static const ColorButton ColorButtonLavenderBush;

    static const ColorButMulti ColorButMultiNoButton;
    static const ColorButMulti ColorButMultiDefault;
    static const ColorButMulti ColorButMultiRed;
    static const ColorButMulti ColorButMultiGreen;
    static const ColorButMulti ColorButMultiBlue;
    static const ColorButMulti ColorButMultiBlack;
    static const ColorButMulti ColorButMultiWhite;
    static const ColorButMulti ColorButMultiOrange;
};

#endif