#include "Color.hpp"

ColorButton::ColorButton() 
  : FillColor(sf::Color::White), 
    TextColor(sf::Color::Black), 
    OutlineColor(sf::Color::Black) {}

ColorButton::ColorButton(sf::Color FillColor, sf::Color TextColor, sf::Color OutlineColor)
  : FillColor(FillColor),
    TextColor(TextColor),
    OutlineColor(OutlineColor) {}

ColorButMulti::ColorButMulti() {}

ColorButMulti::ColorButMulti(std::vector<ColorButton> listColor) 
  : listColor(listColor) {}

ColorButton ColorButMulti::get(int statusColor) const {
    if (statusColor >= 0 && statusColor < (int) listColor.size()) {
        return listColor[statusColor];
    } else {
        return ColorButton();
    }
}

int ColorButMulti::getSize() const {
    return listColor.size();
}
