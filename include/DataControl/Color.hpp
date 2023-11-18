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
    std::vector<ColorButton> listColor; /// suggested: size = 4, except Color::ColorButMultiTextFullColor
public :
    ColorButMulti();
    ColorButMulti(std::vector<ColorButton> listColor);
    ColorButton get(int statusColor) const;
    int getSize() const;
};

namespace Color {
    const sf::Color Silver           = sf::Color(192, 192, 192);
    const sf::Color DimGray          = sf::Color(105, 105, 105);
    const sf::Color Red              = sf::Color(255, 0, 0);
    const sf::Color Green            = sf::Color(0, 128, 0);
    const sf::Color Blue             = sf::Color(0, 0, 255);
    const sf::Color Black            = sf::Color(0, 0, 0);
    const sf::Color White            = sf::Color(255, 255, 255);
    const sf::Color Orange           = sf::Color(255, 165, 0);
    const sf::Color Yellow           = sf::Color(255, 255, 0);
    const sf::Color IndianRed        = sf::Color(176, 23, 31);
    const sf::Color OrangeRed        = sf::Color(255, 69, 0);
    const sf::Color LightGreen       = sf::Color(144, 238, 144);
    const sf::Color LawnGreen        = sf::Color(124, 252, 0);
    const sf::Color MediumSpringGreen= sf::Color(0, 250, 154);
    const sf::Color SpringGreen      = sf::Color(0, 255, 127);
    const sf::Color LightSeaGreen    = sf::Color(32, 178, 170);
    const sf::Color LightYellow      = sf::Color(255, 255, 224);
    const sf::Color LavenderBlush    = sf::Color(255, 240, 245);
    const sf::Color EerieBlack       = sf::Color(27, 27, 27);
    const sf::Color AntiFlashWhite   = sf::Color(242, 243, 244);
    const sf::Color RoyalPurple      = sf::Color(120, 81, 169);
    const sf::Color VistaBlue        = sf::Color(124, 158, 217);
    const sf::Color DarkBlue         = sf::Color(0, 0, 139);
    const sf::Color MediumSlateBlue  = sf::Color(123, 104, 238);
    const sf::Color UranianBlue      = sf::Color(175, 219, 245);
    const sf::Color DeepSkyBlue      = sf::Color(0, 191, 255);
    const sf::Color DarkCyan         = sf::Color(0, 139, 139);
    const sf::Color LightRed         = sf::Color(255, 127, 80);
    const sf::Color SandyBrown       = sf::Color(244, 164, 96);
    const sf::Color TeaRose          = sf::Color(248, 131, 121);
    const sf::Color BrightPink       = sf::Color(255, 105, 180);
    const sf::Color LightBlue        = sf::Color(173, 216, 230);
    const sf::Color LightCyan        = sf::Color(224, 255, 255);
    const sf::Color LightPink        = sf::Color(255, 182, 193);
    const sf::Color Purple           = sf::Color(128, 0, 128);
    const sf::Color Turquoise        = sf::Color(64, 224, 208);
    const sf::Color Magenta          = sf::Color(255, 0, 255);
    const sf::Color Gold             = sf::Color(255, 215, 0);
    const sf::Color Crimson          = sf::Color(220, 20, 60);
    const sf::Color Teal             = sf::Color(0, 128, 128);
    const sf::Color Transparent      = sf::Color(0, 0, 0, 0);

    const ColorButton ButtonDefault           = ColorButton(White, Black, Black);
    const ColorButton ButtonGreen             = ColorButton(Green, Black, Black);
    const ColorButton ButtonYellow            = ColorButton(Yellow, Black, Black);
    const ColorButton ButtonRed               = ColorButton(Red, LightCyan, LightGreen);
    const ColorButton ButtonBlue              = ColorButton(Blue, Black, Black);
    const ColorButton ButtonBlack             = ColorButton(Black, White, SandyBrown);
    const ColorButton ButtonWhite             = ColorButton(White, Black, Black);
    const ColorButton ButtonOrange            = ColorButton(Orange, Black, Black);
    const ColorButton ButtonLightGreen        = ColorButton(LightGreen, Black, Black);
    const ColorButton ButtonLightYellow       = ColorButton(LightYellow, IndianRed, IndianRed);
    const ColorButton ButtonEerieBlack        = ColorButton(EerieBlack, LightPink, LightRed);
    const ColorButton ButtonAntiFlashWhite    = ColorButton(AntiFlashWhite, Black, Black);
    const ColorButton ButtonRoyalPurple       = ColorButton(RoyalPurple, Black, Black);
    const ColorButton ButtonVistaBlue         = ColorButton(VistaBlue, Black, Black);
    const ColorButton ButtonDarkBlue          = ColorButton(DarkBlue, White, White);
    const ColorButton ButtonMediumSlateBlue   = ColorButton(MediumSlateBlue, Black, Black);
    const ColorButton ButtonUranianBlue       = ColorButton(UranianBlue, Black, Black);
    const ColorButton ButtonDeepSkyBlue       = ColorButton(DeepSkyBlue, Black, SandyBrown);
    const ColorButton ButtonDarkCyan          = ColorButton(DarkCyan, White, White);
    const ColorButton ButtonLightRed          = ColorButton(LightRed, DarkBlue, Orange);
    const ColorButton ButtonSandyBrown        = ColorButton(SandyBrown, Black, Black);
    const ColorButton ButtonTeaRose           = ColorButton(TeaRose, Black, Black);
    const ColorButton ButtonBrightPink        = ColorButton(BrightPink, Black, Black);
    const ColorButton ButtonLightBlue         = ColorButton(LightBlue, Black, Black);
    const ColorButton ButtonLightCyan         = ColorButton(LightCyan, Red, SpringGreen);
    const ColorButton ButtonLightPink         = ColorButton(LightPink, Black, Black);
    const ColorButton ButtonSilver            = ColorButton(Silver, Black, Black);
    const ColorButton ButtonDimGray           = ColorButton(DimGray, White, White);
    const ColorButton ButtonIndianRed         = ColorButton(IndianRed, Black, Black);
    const ColorButton ButtonOrangeRed         = ColorButton(OrangeRed, Black, Black);
    const ColorButton ButtonLawnGreen         = ColorButton(LawnGreen, Black, Black);
    const ColorButton ButtonMediumSpringGreen = ColorButton(MediumSpringGreen, Black, Black);
    const ColorButton ButtonSpringGreen       = ColorButton(SpringGreen, Black, Black);
    const ColorButton ButtonLightSeaGreen     = ColorButton(LightSeaGreen, Black, Black);
    const ColorButton ButtonLavenderBlush     = ColorButton(LavenderBlush, Black, Black);
    const ColorButton ButtonPurple            = ColorButton(Purple, Yellow, LightGreen);
    const ColorButton ButtonTurquoise         = ColorButton(Turquoise, Orange, Red);
    const ColorButton ButtonMagenta           = ColorButton(Magenta, LightGreen, Yellow);
    const ColorButton ButtonGold              = ColorButton(Gold, Purple, LightBlue);
    const ColorButton ButtonCrimson           = ColorButton(Crimson, LightYellow, LightGreen);
    const ColorButton ButtonTeal              = ColorButton(Teal, LightPink, LightYellow);

    const ColorButton ButtonTextDefault           = ColorButton(Transparent, Black, Transparent);
    const ColorButton ButtonTextGreen             = ColorButton(Transparent, Green, Transparent);
    const ColorButton ButtonTextYellow            = ColorButton(Transparent, Yellow, Transparent);
    const ColorButton ButtonTextRed               = ColorButton(Transparent, Red, Transparent);
    const ColorButton ButtonTextBlue              = ColorButton(Transparent, Blue, Transparent);
    const ColorButton ButtonTextBlack             = ColorButton(Transparent, Black, Transparent);
    const ColorButton ButtonTextWhite             = ColorButton(Transparent, White, Transparent);
    const ColorButton ButtonTextOrange            = ColorButton(Transparent, Orange, Transparent);
    const ColorButton ButtonTextLightGreen        = ColorButton(Transparent, LightGreen, Transparent);
    const ColorButton ButtonTextLightYellow       = ColorButton(Transparent, LightYellow, Transparent);
    const ColorButton ButtonTextLavenderBlush     = ColorButton(Transparent, LavenderBlush, Transparent);
    const ColorButton ButtonTextEerieBlack        = ColorButton(Transparent, White, Transparent);
    const ColorButton ButtonTextAntiFlashWhite    = ColorButton(Transparent, Black, Transparent);
    const ColorButton ButtonTextRoyalPurple       = ColorButton(Transparent, RoyalPurple, Transparent);
    const ColorButton ButtonTextVistaBlue         = ColorButton(Transparent, VistaBlue, Transparent);
    const ColorButton ButtonTextDarkBlue          = ColorButton(Transparent, DarkBlue, Transparent);
    const ColorButton ButtonTextMediumSlateBlue   = ColorButton(Transparent, MediumSlateBlue, Transparent);
    const ColorButton ButtonTextUranianBlue       = ColorButton(Transparent, UranianBlue, Transparent);
    const ColorButton ButtonTextDeepSkyBlue       = ColorButton(Transparent, DeepSkyBlue, Transparent);
    const ColorButton ButtonTextDarkCyan          = ColorButton(Transparent, DarkCyan, Transparent);
    const ColorButton ButtonTextLightRed          = ColorButton(Transparent, LightRed, Transparent);
    const ColorButton ButtonTextSandyBrown        = ColorButton(Transparent, SandyBrown, Transparent);
    const ColorButton ButtonTextTeaRose           = ColorButton(Transparent, TeaRose, Transparent);
    const ColorButton ButtonTextBrightPink        = ColorButton(Transparent, BrightPink, Transparent);
    const ColorButton ButtonTextLightBlue         = ColorButton(Transparent, LightBlue, Transparent);
    const ColorButton ButtonTextLightCyan         = ColorButton(Transparent, LightCyan, Transparent);
    const ColorButton ButtonTextLightPink         = ColorButton(Transparent, LightPink, Transparent);
    const ColorButton ButtonTextSilver            = ColorButton(Transparent, Silver, Transparent);
    const ColorButton ButtonTextDimGray           = ColorButton(Transparent, DimGray, Transparent);
    const ColorButton ButtonTextIndianRed         = ColorButton(Transparent, IndianRed, Transparent);
    const ColorButton ButtonTextOrangeRed         = ColorButton(Transparent, OrangeRed, Transparent);
    const ColorButton ButtonTextLawnGreen         = ColorButton(Transparent, LawnGreen, Transparent);
    const ColorButton ButtonTextMediumSpringGreen = ColorButton(Transparent, MediumSpringGreen, Transparent);
    const ColorButton ButtonTextSpringGreen       = ColorButton(Transparent, SpringGreen, Transparent);
    const ColorButton ButtonTextLightSeaGreen     = ColorButton(Transparent, LightSeaGreen, Transparent);
    const ColorButton ButtonTextLavenderBush      = ColorButton(Transparent, LavenderBlush, Transparent);

    const ColorButMulti ButMultiDefault         = ColorButMulti(std::vector<ColorButton>{ButtonDefault, ButtonGreen, ButtonYellow, ButtonLavenderBlush});
    const ColorButMulti ButMultiStatic          = ColorButMulti(std::vector<ColorButton>{ButtonDefault, ButtonDefault, ButtonDefault, ButtonDefault});
    const ColorButMulti ButMultiLight1          = ColorButMulti(std::vector<ColorButton>{ButtonGreen, ButtonYellow, ButtonRed, ButtonBlue});
    const ColorButMulti ButMultiLight2          = ColorButMulti(std::vector<ColorButton>{ButtonLightGreen, ButtonLightYellow, ButtonLightRed, ButtonLightBlue});
    const ColorButMulti ButMultiLight3          = ColorButMulti(std::vector<ColorButton>{ButtonLightCyan, ButtonLightPink, ButtonLightSeaGreen, ButtonLightYellow, ButtonLightBlue});
    const ColorButMulti ButMultiFunny           = ColorButMulti(std::vector<ColorButton>{ButtonTurquoise, ButtonMediumSpringGreen, ButtonTeaRose, ButtonGold});
    const ColorButMulti ButMultiHumor           = ColorButMulti(std::vector<ColorButton>{ButtonCrimson, ButtonTeal, ButtonMagenta, ButtonPurple});
    const ColorButMulti ButMultiLucky           = ColorButMulti(std::vector<ColorButton>{ButtonOrange, ButtonYellow, ButtonGold, ButtonLightYellow});
    const ColorButMulti ButMultiSad             = ColorButMulti(std::vector<ColorButton>{ButtonDeepSkyBlue, ButtonMagenta, ButtonSandyBrown, ButtonRoyalPurple});
    const ColorButMulti ButMultiChill           = ColorButMulti(std::vector<ColorButton>{ButtonIndianRed, ButtonSandyBrown, ButtonTextDimGray, ButtonCrimson});
    const ColorButMulti ButMultiLove            = ColorButMulti(std::vector<ColorButton>{ButtonBrightPink, ButtonLightPink, ButtonLightRed, ButtonLightBlue});
    const ColorButMulti ButMultiHehe            = ColorButMulti(std::vector<ColorButton>{ButtonLightGreen, ButtonOrange, ButtonRed, ButtonLavenderBlush});
    const ColorButMulti ButMultiDark            = ColorButMulti(std::vector<ColorButton>{ButtonBlack, ButtonLightYellow, ButtonRed, ButtonBlue});
    const ColorButMulti ButMultiTextDefault     = ColorButMulti(std::vector<ColorButton>{ButtonTextDefault, ButtonTextGreen, ButtonTextYellow, ButtonTextLavenderBush});
    const ColorButMulti ButMultiTextStatic      = ColorButMulti(std::vector<ColorButton>{ButtonTextDefault, ButtonTextDefault, ButtonTextDefault, ButtonTextDefault});
    const ColorButMulti ButMultiTextFullColor   = ColorButMulti(std::vector<ColorButton>{ButtonTextGreen, ButtonTextYellow, ButtonTextRed, ButtonTextBlue, ButtonTextWhite, ButtonTextOrange, ButtonTextLightGreen, ButtonTextLightYellow, ButtonTextLavenderBlush, ButtonTextRoyalPurple, ButtonTextVistaBlue, ButtonTextDarkBlue, ButtonTextMediumSlateBlue, ButtonTextUranianBlue, ButtonTextDeepSkyBlue, ButtonTextDarkCyan, ButtonTextLightRed, ButtonTextSandyBrown, ButtonTextTeaRose, ButtonTextBrightPink, ButtonTextLightBlue, ButtonTextLightPink, ButtonTextLightCyan, ButtonTextSilver, ButtonTextDimGray, ButtonTextIndianRed, ButtonTextOrangeRed, ButtonTextLawnGreen, ButtonTextMediumSpringGreen, ButtonTextSpringGreen, ButtonTextLightSeaGreen, ButtonTextLavenderBush});
}

#endif