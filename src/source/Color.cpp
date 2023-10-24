#include "Color.hpp"

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

ColorItemMulti::ColorItemMulti() {
    this->listColor = listColor;
    this->listColor.push_back(ColorItem());
    printf("Warning ColorItemMulti Empty Color\n");
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