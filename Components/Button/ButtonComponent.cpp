/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#include "ButtonComponent.hpp"
#include "../../ClientCore.hpp"

#include <utility>

/**
 * @brief ButtonComponent constructor
 * @param core
 * @param socket
 */
ButtonComponent::ButtonComponent(ClientCore *core, std::shared_ptr<AudioEngine> engine) :
    AComponent(core, engine)
{
    _type = ComponentType::BUTTON;
    _texture.loadFromFile("assets/button.png");
    _sprite.setTexture(_texture);
    _position = sf::Vector2f(150, 100);
    _sprite.setPosition(_position);
    _size = sf::Vector2f(0.75, 0.75);
    _sprite.setScale(_size);
    _rect = sf::IntRect(0, 0, 701, 301);
    _sprite.setTextureRect(_rect);
    _attribute = "";
    std::function<void()> default_handle_click = std::bind(&ButtonComponent::defaultCallback, this);
    setCallback(default_handle_click);
}

/**
 * @brief action, call the callback function
 */
void ButtonComponent::action()
{
    _callback();
}

/**
 * @brief setTexture set the texture of the button
 * @param texture
 */
void ButtonComponent::setTexture(const sf::Texture &texture)
{
    _texture = texture;
    _sprite.setTexture(_texture);
}

/**
 * @brief setPosition set the position of the button
 * @param position
 */
void ButtonComponent::setPosition(sf::Vector2f position)
{
    _position = position;
    _sprite.setPosition(_position);
}

/**
 * @brief setSize set the size of the button
 * @param size
 */
void ButtonComponent::setSize(sf::Vector2f size)
{
    _size = size;
    _sprite.setScale(_size);
}

/**
 * @brief setRect set the rect of the button
 * @param rect
 */
void ButtonComponent::setRect(sf::IntRect rect)
{
    _rect = rect;
    _sprite.setTextureRect(_rect);
}

/**
 * @brief setAttribute set the attribute of the button
 * @param attribute
 */
void ButtonComponent::setCallback(std::function<void()> callback)
{
    _callback = std::move(callback);
}

/**
 * @brief setAttribute set the attribute of the button
 * @param window
 */
void ButtonComponent::display(sf::RenderWindow &window)
{
    window.draw(_sprite);
}

/**
 * @brief getRect get the texture of the button
 * @return rect of the button
 */
sf::IntRect ButtonComponent::getRect() const
{
    return _rect;
}

/**
 * @brief handleEvent handle the event of the button
 * @param event to handle
 * @param window
 */
void ButtonComponent::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
            if (_sprite.getGlobalBounds().contains(mousePosF)) {
                action();
            }
        }
    }
}

void ButtonComponent::defaultCallback()
{
    for (auto &component : action_target) {
        if (component->getType() == ComponentType::SOUND) {
            component->action();
        }
    }
}

void ButtonComponent::setSoundCallback() {
    _engine->reverb = !_engine->reverb;
    for (auto &component : action_target) {
        if (component->getType() == ComponentType::TEXT) {
            if (component->getAttribute() == "text reverb") {
                auto text = std::dynamic_pointer_cast<TextComponent>(component);
                if (_engine->reverb)
                    text->setText("Reverb On");
                else
                    text->setText("Reverb Off");
            }
        }
        /*if (component->getType() == ComponentType::INPUT) {
            if (component->getAttribute() == "input volume") {
                auto input = std::dynamic_pointer_cast<InputComponent>(component);
                std::string volume = input->getText();
                int volumeInt;
                if (volume.empty())
                    volumeInt = 0;
                else
                    volumeInt = std::stoi(volume);

                std::cout << volumeInt << std::endl;

                if (volumeInt > 100)
                    volumeInt = 100;
                else if (volumeInt < 0)
                    volumeInt = 0;

                _engine->setVolume(volumeInt);
            }
        }*/
    }
    for (auto &component : action_target) {
        if (component->getType() == ComponentType::SOUND) {
            component->action();
        }
    }
}
