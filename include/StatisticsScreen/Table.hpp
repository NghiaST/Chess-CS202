#ifndef __Table_hpp__
#define __Table_hpp__

#include <DataControl/Button.hpp>
#include <Graphic.hpp>

class Table : public Graphic {
public:
    Table(int tableID, Point renderPosition, Point renderSizeButton,
            const sf::Font* sfFont, const ColorButMulti& colorButMulti, unsigned int sizeText = 12,
            std::vector<std::vector<std::string>> textArr = {}, float thickness = -1);
    ~Table();
    void addButton(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin,
            const sf::Font* sfFont, const ColorButMulti& colorButMulti, unsigned int sizeText = 12,
            std::string text = "", float thickness = -1, Point renderOffsetText = Point(0, 0));
    bool handleEvent(const sf::Event& event);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    // Mutators
    void setButtonState(int buttonID, ButtonStates buttonState);
    void setColorBM(int buttonID, const ColorButMulti& colorButMulti);
    void setHighLightFirstColumn(bool isHighLightFirstColumn);
    void setHighLightFirstRow(bool isHighLightFirstRow);

    // Accessors
    int getButtonState(int buttonID) const;
    const ColorButMulti& getColorBM(int buttonID) const;
    bool getHighLightFirstColumn() const;
    bool getHighLightFirstRow() const;

    void clear();

private:
    std::vector<Button*> buttons;
    bool isHighLightFirstColumn;
    bool isHighLightFirstRow;
    int tableID;
    int rowCount;
    int columnCount;
};

#endif