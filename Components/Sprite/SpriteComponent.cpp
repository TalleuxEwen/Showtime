/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#include "SpriteComponent.hpp"

/**
 * @brief Construct a new Sprite Component:: Sprite Component object
 *
 * @param core
 * @param socket
 */
SpriteComponent::SpriteComponent(ClientCore *core, std::shared_ptr<AudioEngine> engine) :
    AComponent(core, engine)
{
    if (!_texture.loadFromFile("assets/missing.png"))
        throw std::runtime_error("Cannot load sprite texture");
    _rect = sf::IntRect(0, 0, static_cast<int>(_texture.getSize().x), static_cast<int>(_texture.getSize().y));
    _position = sf::Vector2f(0, 0);
    _sprite.setTexture(_texture);
    _sprite.setPosition(_position);
    setSize(sf::Vector2f(200, 200));
    _sprite.setTextureRect(_rect);
    _type = ComponentType::SPRITE;
}

void SpriteComponent::action()
{
}

/**
 * @brief display, display the sprite
 * @param window
 */
void SpriteComponent::display(sf::RenderWindow &window)
{
    window.draw(_sprite);
}

void SpriteComponent::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    if (getAttribute() != "output fader button")
        return;
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            _isClicked = true;
        }
    }
    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            _isClicked = false;
        }
    }
    if (event.type == sf::Event::MouseMoved) {
        if (_isClicked && event.mouseMove.y < 365 && event.mouseMove.y > 0) {
            _position.y = event.mouseMove.y;
            _sprite.setPosition(_position);

            //if _position.y == 365 volume is 0 and if _position.y == 0 volume is 100
            int volume = 100 - (_position.y * 100 / 365);
            _engine->setVolume(volume);
        }
    }
}

/**
 * @brief setTexture, set the texture
 * @param texture
 */
void SpriteComponent::setTexture(const sf::Texture &texture)
{
    _texture = texture;
    _sprite.setTexture(_texture);
}

/**
 * @brief setPosition, set the position
 * @param position
 */
void SpriteComponent::setPosition(sf::Vector2f position)
{
    _position = position;
    _sprite.setPosition(_position);
}

/**
 * @brief setSize, set the size
 * @param size
 */
void SpriteComponent::setSize(sf::Vector2f size)
{
    _size = size;
    _sprite.setScale(_size.x / _texture.getSize().x, _size.y / _texture.getSize().y);
}

/**
 * @brief setRect, set the rect
 * @param rect
 */
void SpriteComponent::setRect(sf::IntRect rect)
{
    _rect = rect;
    _sprite.setTextureRect(_rect);
}

/**
 * @brief setRect, set the rect
 * @param x
 * @param y
 */
void SpriteComponent::setPosition(float x, float y)
{
    _position = sf::Vector2f(x, y);
    _sprite.setPosition(_position);
}

void SpriteComponent::setOpacity(char opacity) {
    _sprite.setColor(sf::Color(255, 255, 255, opacity));
}
