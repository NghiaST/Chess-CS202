#include <DataControl/Image.hpp>

Image::Image() : Graphic(Point(0, 0), Point(-1, -1), true, 100) {}

Image::Image(const sf::Texture& texture, Point renderPosition, Point renderSize, bool isPrint, int priorityPrint) 
    : Graphic(renderPosition, renderSize, isPrint, priorityPrint)
{
    setTexture(texture);
    setRenderPositionSize(renderPosition, renderSize);
    // setRenderSize(renderSize);
    // setRenderPosition(renderPosition);
}

void Image::setTexture(const sf::Texture& texture) {
    sprite = sf::Sprite();
    sprite.setTexture(texture);
    setRenderSize(renderSize);
}

void Image::setTextureRect(sf::IntRect textureRect) {
    setRenderPositionSize(Point(textureRect.left, textureRect.top), Point(textureRect.width, textureRect.height));
}

void Image::setRenderPositionSize(Point renderPosition, Point renderSize) {
    setRenderSize(renderSize);
    setRenderPosition(renderPosition);
}

void Image::setRenderPosition(Point renderPosition) {
    Graphic::setRenderPosition(renderPosition);
    sprite.setPosition(renderPosition.to2f());
}

void Image::setRenderSize(Point renderSize) {
    if (renderSize == Point(-1, -1) || renderSize == Point(0, 0)) {
        Graphic::setRenderSize(Point(sprite.getTextureRect().width, sprite.getTextureRect().height));
        sprite.setScale(1, 1);
        return;
    }
    Graphic::setRenderSize(renderSize);
    if (sprite.getTextureRect().width != 0 && sprite.getTextureRect().height != 0)
        sprite.setScale(renderSize.x / sprite.getTextureRect().width, renderSize.y / sprite.getTextureRect().height);
}

const sf::Sprite& Image::getSprite() const {
    return sprite;
}

void Image::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (isPrint) {
        target.draw(sprite, states);
    }
}

ImageActive::ImageActive() : Image() {}

ImageActive::ImageActive(const sf::Texture& texture, Point renderPosition, Point renderSize, bool isPrint, int priorityPrint) 
    : Image(texture, renderPosition, renderSize, isPrint, priorityPrint)
{
    setMainPosition(renderPosition);
    setMouseStatus(MOUSE::None);
}

void ImageActive::setMouseStatus(int mousestatus, Point mousePosition) {
    this->mouseStatus = (MOUSE::STATUS) mousestatus;
    this->mousePosition = mousePosition;
    if (mouseStatus == MOUSE::Hold) {
        setRenderPosition(mousePosition - renderSize / 2);
        setPriorityPrint(1);
    }
    else {
        setRenderPosition(mPosition);
        setPriorityPrint(2);
    }
}

void ImageActive::setMainPosition(Point mPosition) {
    this->mPosition = mPosition;
    if (mouseStatus != MOUSE::Hold) {
        setRenderPosition(mPosition);
    }
}

void ImageActive::setMousePosition(Point mousePosition) {
    this->mousePosition = mousePosition;
    if (mouseStatus == MOUSE::Hold) {
        setRenderPosition(mousePosition - renderSize / 2);
    }
}

bool ImageActive::handleEvent(const sf::Event &event) {
    if (event.type == sf::Event::MouseMoved) {
        setMousePosition(Point(event.mouseButton.x, event.mouseButton.y));
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (isMouseOn(mousePosition)) {
                setMouseStatus(MOUSE::Hold);
                setMousePosition(Point(event.mouseButton.x, event.mouseButton.y));
                return true;
            }
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            setMouseStatus(MOUSE::None);
            return true;
        }
    }
    return false;
}
