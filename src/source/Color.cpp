#include "Color.hpp"

const sf::Color Color::SilverColor = sf::Color(185, 180, 174);
const sf::Color Color::DimGrayColor = sf::Color(105, 105, 105);
const sf::Color Color::RedColor = sf::Color(255, 0, 0);
const sf::Color Color::GreenColor = sf::Color(0, 255, 0);
const sf::Color Color::BlueColor = sf::Color(0, 0, 255);
const sf::Color Color::BlackColor = sf::Color(0, 0, 0);
const sf::Color Color::WhiteColor = sf::Color(255, 255, 255);
const sf::Color Color::OrangeColor = sf::Color(255, 128, 0);
const sf::Color Color::YellowColor = sf::Color(255, 255, 0);
const sf::Color Color::LightGreenColor = sf::Color(82, 188, 105);
const sf::Color Color::LightYellowColor = sf::Color(255, 217, 61);
const sf::Color Color::LavenderBushColor = sf::Color(255, 245, 248);
const sf::Color Color::EerieBlackColor = sf::Color(30, 30, 30);
const sf::Color Color::AntiFlashWhiteColor = sf::Color(235, 235, 235);
const sf::Color Color::RoyalPurpleColor = sf::Color(108, 74, 182);
const sf::Color Color::VistaBlueColor = sf::Color(185, 224, 255);
const sf::Color Color::MediumSlateBlueColor = sf::Color(141, 114, 225);
const sf::Color Color::UranianBlueColor = sf::Color(141, 158, 255);
const sf::Color Color::DarkCyanColor = sf::Color(14, 131, 136);
const sf::Color Color::LightRedColor = sf::Color(255, 148, 148);
const sf::Color Color::TeaRoseColor = sf::Color(255, 209, 209);
const sf::Color Color::BrightPinkColor = sf::Color(238, 75, 106);
const sf::Color Color::TransparentColor = sf::Color(0, 0, 0, 0);

const ColorItem Color::ColorItemNoButton = ColorItem(TransparentColor, BlackColor, TransparentColor);
const ColorItem Color::ColorItemDefault = ColorItem(WhiteColor, BlackColor, BlackColor);
const ColorItem Color::ColorItemRed = ColorItem(RedColor, WhiteColor, BlackColor);
const ColorItem Color::ColorItemGreen = ColorItem(GreenColor, WhiteColor, BlackColor);
const ColorItem Color::ColorItemBlue = ColorItem(BlueColor, WhiteColor, BlackColor);
const ColorItem Color::ColorItemBlack = ColorItem(BlackColor, WhiteColor, BlackColor);
const ColorItem Color::ColorItemWhite = ColorItem(WhiteColor, BlackColor, BlackColor);
const ColorItem Color::ColorItemOrange = ColorItem(OrangeColor, WhiteColor, BlackColor);
const ColorItem Color::ColorItemYellow = ColorItem(YellowColor, BlackColor, BlackColor);
const ColorItem Color::ColorItemLightGreen = ColorItem(LightGreenColor, BlackColor, BlackColor);
const ColorItem Color::ColorItemLightYellow = ColorItem(LightYellowColor, BlackColor, BlackColor);
const ColorItem Color::ColorItemLavenderBush = ColorItem(LavenderBushColor, BlackColor, BlackColor);

const ColorItemMulti Color::ColorItemMultiNoButton = ColorItemMulti(std::vector<ColorItem>{ColorItemNoButton, ColorItemNoButton, ColorItemNoButton, ColorItemNoButton});
const ColorItemMulti Color::ColorItemMultiDefault = ColorItemMulti(std::vector<ColorItem>{ColorItemDefault, ColorItemGreen, ColorItemYellow, ColorItemLavenderBush});
const ColorItemMulti Color::ColorItemMultiRed = ColorItemMulti(std::vector<ColorItem>{ColorItemRed, ColorItemRed, ColorItemRed, ColorItemRed});
const ColorItemMulti Color::ColorItemMultiGreen = ColorItemMulti(std::vector<ColorItem>{ColorItemGreen, ColorItemGreen, ColorItemGreen, ColorItemGreen});
const ColorItemMulti Color::ColorItemMultiBlue = ColorItemMulti(std::vector<ColorItem>{ColorItemBlue, ColorItemBlue, ColorItemBlue, ColorItemBlue});
const ColorItemMulti Color::ColorItemMultiBlack = ColorItemMulti(std::vector<ColorItem>{ColorItemBlack, ColorItemBlack, ColorItemBlack, ColorItemBlack});
const ColorItemMulti Color::ColorItemMultiWhite = ColorItemMulti(std::vector<ColorItem>{ColorItemWhite, ColorItemWhite, ColorItemWhite, ColorItemWhite});
const ColorItemMulti Color::ColorItemMultiOrange = ColorItemMulti(std::vector<ColorItem>{ColorItemOrange, ColorItemOrange, ColorItemOrange, ColorItemOrange});

ColorItem::ColorItem() {
    FillColor = sf::Color::White;
    TextColor = sf::Color::Black;
    OutlineColor = sf::Color::Black;
}

ColorItem::ColorItem(sf::Color FillColor, sf::Color TextColor, sf::Color OutlineColor) {
    this->FillColor = FillColor;
    this->TextColor = TextColor;
    this->OutlineColor = OutlineColor;
}

ColorItemMulti::ColorItemMulti(std::vector<ColorItem> listColor) {
    this->listColor = listColor;
}

ColorItem ColorItemMulti::getColor(int statusColor) {
    if (statusColor >= 0 && statusColor < listColor.size()) {
        return listColor[statusColor];
    } else {
        return ColorItem();
    }
}