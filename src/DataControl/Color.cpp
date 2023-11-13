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

const ColorButton Color::ColorButtonDefault = ColorButton(WhiteColor, BlackColor, BlackColor);
const ColorButton Color::ColorButtonRed = ColorButton(RedColor, WhiteColor, BlackColor);
const ColorButton Color::ColorButtonGreen = ColorButton(GreenColor, WhiteColor, BlackColor);
const ColorButton Color::ColorButtonBlue = ColorButton(BlueColor, WhiteColor, BlackColor);
const ColorButton Color::ColorButtonBlack = ColorButton(BlackColor, WhiteColor, BlackColor);
const ColorButton Color::ColorButtonWhite = ColorButton(WhiteColor, BlackColor, BlackColor);
const ColorButton Color::ColorButtonOrange = ColorButton(OrangeColor, WhiteColor, BlackColor);
const ColorButton Color::ColorButtonYellow = ColorButton(YellowColor, BlackColor, BlackColor);
const ColorButton Color::ColorButtonLightGreen = ColorButton(LightGreenColor, BlackColor, BlackColor);
const ColorButton Color::ColorButtonLightYellow = ColorButton(LightYellowColor, BlackColor, BlackColor);
const ColorButton Color::ColorButtonLavenderBush = ColorButton(LavenderBushColor, BlackColor, BlackColor);
const ColorButton Color::ColorButtonTextDefault = ColorButton(TransparentColor, BlackColor, TransparentColor);
const ColorButton Color::ColorButtonTextRed = ColorButton(TransparentColor, RedColor, TransparentColor);
const ColorButton Color::ColorButtonTextGreen = ColorButton(TransparentColor, GreenColor, TransparentColor);
const ColorButton Color::ColorButtonTextBlue = ColorButton(TransparentColor, BlueColor, TransparentColor);
const ColorButton Color::ColorButtonTextBlack = ColorButton(TransparentColor, BlackColor, TransparentColor);
const ColorButton Color::ColorButtonTextWhite = ColorButton(TransparentColor, WhiteColor, TransparentColor);
const ColorButton Color::ColorButtonTextOrange = ColorButton(TransparentColor, OrangeColor, TransparentColor);
const ColorButton Color::ColorButtonTextYellow = ColorButton(TransparentColor, YellowColor, TransparentColor);
const ColorButton Color::ColorButtonTextLightGreen = ColorButton(TransparentColor, LightGreenColor, TransparentColor);
const ColorButton Color::ColorButtonTextLightYellow = ColorButton(TransparentColor, LightYellowColor, TransparentColor);
const ColorButton Color::ColorButtonTextLavenderBush = ColorButton(TransparentColor, LavenderBushColor, TransparentColor);

const ColorButMulti Color::ColorButMultiDefault = ColorButMulti(std::vector<ColorButton>{ColorButtonDefault, ColorButtonGreen, ColorButtonYellow, ColorButtonLavenderBush});
const ColorButMulti Color::ColorButMultiStatic = ColorButMulti(std::vector<ColorButton>{ColorButtonDefault, ColorButtonDefault, ColorButtonDefault, ColorButtonDefault});
const ColorButMulti Color::ColorButMultiLight = ColorButMulti(std::vector<ColorButton>{ColorButtonLightGreen, ColorButtonOrange, ColorButtonRed, ColorButtonLavenderBush});
const ColorButMulti Color::ColorButMultiDark = ColorButMulti(std::vector<ColorButton>{ColorButtonBlack, ColorButtonLightYellow, ColorButtonRed, ColorButtonBlue});
const ColorButMulti Color::ColorButMultiTextDefault = ColorButMulti(std::vector<ColorButton>{ColorButtonTextDefault, ColorButtonTextGreen, ColorButtonTextYellow, ColorButtonTextLavenderBush});
const ColorButMulti Color::ColorButMultiTextStatic = ColorButMulti(std::vector<ColorButton>{ColorButtonTextDefault, ColorButtonTextDefault, ColorButtonTextDefault, ColorButtonTextDefault});
const ColorButMulti Color::ColorButMultiTextFullColor = ColorButMulti(std::vector<ColorButton>{ColorButtonTextRed, ColorButtonTextGreen, ColorButtonTextBlue, ColorButtonTextBlack, ColorButtonTextWhite, ColorButtonTextOrange, ColorButtonTextYellow, ColorButtonTextLightGreen, ColorButtonTextLightYellow, ColorButtonTextLavenderBush});

ColorButton::ColorButton() {
    FillColor = sf::Color::White;
    TextColor = sf::Color::Black;
    OutlineColor = sf::Color::Black;
}

ColorButton::ColorButton(sf::Color FillColor, sf::Color TextColor, sf::Color OutlineColor) {
    this->FillColor = FillColor;
    this->TextColor = TextColor;
    this->OutlineColor = OutlineColor;
}

ColorButMulti::ColorButMulti() {}

ColorButMulti::ColorButMulti(std::vector<ColorButton> listColor) {
    this->listColor = listColor;
}

ColorButton ColorButMulti::get(int statusColor) {
    if (statusColor >= 0 && statusColor < listColor.size()) {
        return listColor[statusColor];
    } else {
        return ColorButton();
    }
}