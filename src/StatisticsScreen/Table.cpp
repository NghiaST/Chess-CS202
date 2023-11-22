#include <StatisticsScreen/Table.hpp>

Table::Table(int tableID, Point renderPosition, Point renderSizeButton, const sf::Font * sfFont, const ColorButMulti & colorButMulti, unsigned int sizeText, std::vector<std::vector<std::string>> textArr, float thickness) {
    this->rowCount = textArr.size();
    this->columnCount = this->rowCount ? textArr[0].size() : 0;
    Graphic::setRenderPosition(renderPosition);
    Graphic::setRenderSize(Point(renderSizeButton.x * columnCount, renderSizeButton.y * rowCount));

    this->isHighLightFirstColumn = false;
    this->isHighLightFirstRow = false;
    this->tableID = tableID;

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            Point renderPositionButton = renderPosition + Point(j * renderSizeButton.x, i * renderSizeButton.y);
            bool isPositionCenter = false;
            bool isRenderTextOrigin = true;
            std::string text = textArr[i][j];
            Point renderOffsetText = Point(0, 0);

            addButton(i * columnCount + j, renderPositionButton, renderSizeButton, isPositionCenter, isRenderTextOrigin, sfFont, colorButMulti, sizeText, text, thickness, renderOffsetText);
        }
    }
}

Table::~Table() {
    for (auto* button : buttons) {
        delete button;
    }
}

void Table::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (auto* button : buttons) {
        target.draw(*button, states);
    }
}

bool Table::handleEvent(const sf::Event& event) {
    for (auto* button : buttons) {
        button->handleEvent(event);
    }
    return false;
}

void Table::addButton(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, 
        const sf::Font* sfFont, const ColorButMulti& colorButMulti, unsigned int sizeText, std::string text, float thickness, 
        Point renderOffsetText) {
    buttons.push_back(new Button(buttonID, renderPosition, renderSize, isPositionCenter, isRenderTextOrigin, sfFont, 
                colorButMulti, sizeText, text, thickness, renderOffsetText));
}

void Table::setButtonState(int buttonID, ButtonStates buttonState) {
    buttons[buttonID]->setButtonState(buttonState);
}

void Table::setColorBM(int buttonID, const ColorButMulti& colorButMulti) {
    buttons[buttonID]->setColorBM(colorButMulti);
}

void Table::setHighLightFirstColumn(bool isHighLightFirstColumn) {
    this->isHighLightFirstColumn = isHighLightFirstColumn;
}

void Table::setHighLightFirstRow(bool isHighLightFirstRow) {
    this->isHighLightFirstRow = isHighLightFirstRow;
}

int Table::getButtonState(int buttonID) const {
    return buttons[buttonID]->getButtonState();
}

const ColorButMulti& Table::getColorBM(int buttonID) const {
    return buttons[buttonID]->getColorBM();
}

bool Table::getHighLightFirstColumn() const {
    return isHighLightFirstColumn;
}

bool Table::getHighLightFirstRow() const {
    return isHighLightFirstRow;
}

void Table::clear() {
    for (auto* button : buttons) {
        delete button;
    }
    buttons.clear();
}