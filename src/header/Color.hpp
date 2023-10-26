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

struct ColorItemMulti { /// note: statusColor = 0: none, 1: pointed, 2: selected, 3: hold
protected :
    std::vector<ColorItem> listColor; /// suggested: size = 4
public :
    ColorItemMulti();
    ColorItemMulti(std::vector<ColorItem> listColor);
    ColorItem getColor(int statusColor);
};

const sf::Color SilverColor(185, 180, 174);
const sf::Color DimGrayColor(105, 105, 105);
const sf::Color RedColor(255, 0, 0);
const sf::Color GreenColor(0, 255, 0);
const sf::Color BlueColor(0, 0, 255);
const sf::Color BlackColor(0, 0, 0);
const sf::Color WhiteColor(255, 255, 255);
const sf::Color OrangeColor(255, 128, 0);
const sf::Color YellowColor(255, 255, 0);
const sf::Color LightGreenColor(82, 188, 105);
const sf::Color LightYellowColor(255, 217, 61);

const sf::Color LavenderBushColor(255, 245, 248);
const sf::Color EerieBlackColor(30, 30, 30);
const sf::Color AntiFlashWhiteColor(235, 235, 235);

const sf::Color RoyalPurpleColor(108, 74, 182);
const sf::Color VistaBlueColor(185, 224, 255);
const sf::Color MediumSlateBlueColor(141, 114, 225);
const sf::Color UranianBlueColor(141, 158, 255);
const sf::Color DarkCyanColor(14, 131, 136);

const sf::Color LightRedColor(255, 148, 148);
const sf::Color TeaRoseColor(255, 209, 209);
const sf::Color BrightPinkColor(238, 75, 106);
const sf::Color TransparentColor(0, 0, 0, 0);

const ColorItem ColorItemNoButton = ColorItem(TransparentColor, BlackColor, TransparentColor);
const ColorItem ColorItemDefault = ColorItem(WhiteColor, BlackColor, BlackColor);
const ColorItem ColorItemRed = ColorItem(RedColor, WhiteColor, BlackColor);
const ColorItem ColorItemGreen = ColorItem(GreenColor, WhiteColor, BlackColor);
const ColorItem ColorItemBlue = ColorItem(BlueColor, WhiteColor, BlackColor);
const ColorItem ColorItemBlack = ColorItem(BlackColor, WhiteColor, BlackColor);
const ColorItem ColorItemWhite = ColorItem(WhiteColor, BlackColor, BlackColor);
const ColorItem ColorItemOrange = ColorItem(OrangeColor, WhiteColor, BlackColor);
const ColorItem ColorItemYellow = ColorItem(YellowColor, WhiteColor, BlackColor);
const ColorItem ColorItemLightGreen = ColorItem(LightGreenColor, WhiteColor, BlackColor);
const ColorItem ColorItemLightYellow = ColorItem(LightYellowColor, WhiteColor, BlackColor);
const ColorItem ColorItemLavenderBush = ColorItem(LavenderBushColor, BlackColor, BlackColor);

const ColorItemMulti ColorItemMultiNoButton = ColorItemMulti(std::vector<ColorItem>{ColorItemNoButton, ColorItemNoButton, ColorItemNoButton, ColorItemNoButton});
const ColorItemMulti ColorItemMultiDefault = ColorItemMulti(std::vector<ColorItem>{ColorItemDefault, ColorItemGreen, ColorItemYellow, ColorItemLavenderBush});
const ColorItemMulti ColorItemMultiRed = ColorItemMulti(std::vector<ColorItem>{ColorItemRed, ColorItemRed, ColorItemRed, ColorItemRed});
const ColorItemMulti ColorItemMultiGreen = ColorItemMulti(std::vector<ColorItem>{ColorItemGreen, ColorItemGreen, ColorItemGreen, ColorItemGreen});
const ColorItemMulti ColorItemMultiBlue = ColorItemMulti(std::vector<ColorItem>{ColorItemBlue, ColorItemBlue, ColorItemBlue, ColorItemBlue});
const ColorItemMulti ColorItemMultiBlack = ColorItemMulti(std::vector<ColorItem>{ColorItemBlack, ColorItemBlack, ColorItemBlack, ColorItemBlack});
const ColorItemMulti ColorItemMultiWhite = ColorItemMulti(std::vector<ColorItem>{ColorItemWhite, ColorItemWhite, ColorItemWhite, ColorItemWhite});
const ColorItemMulti ColorItemMultiOrange = ColorItemMulti(std::vector<ColorItem>{ColorItemOrange, ColorItemOrange, ColorItemOrange, ColorItemOrange});

#endif