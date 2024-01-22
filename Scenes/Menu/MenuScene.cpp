/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#include "MenuScene.hpp"
#include "../../ClientCore.hpp"

#include <utility>

/**
 * @brief Construct a new Menu Scene:: Menu Scene object
 *
 * @param clientCore
 * @param socket
 */
MenuScene::MenuScene(ClientCore *clientCore, std::shared_ptr<AudioEngine> audioEngine) :
    AScene(clientCore, std::move(audioEngine))
{
    init_scene();
    _pingTime.tv_sec = 0;
    _pingTime.tv_usec = 0;
}

/**
 * @brief init_scene,  initialize the scene
 *
 */
void MenuScene::init_scene()
{
    std::shared_ptr<TextComponent> text = std::make_shared<TextComponent>(_clientCore, _engine);
    std::shared_ptr<ButtonComponent> button_volume = std::make_shared<ButtonComponent>(_clientCore, _engine);
    std::shared_ptr<TextComponent> text_button_volume = std::make_shared<TextComponent>(_clientCore, _engine);
    std::shared_ptr<InputComponent> input_volume = std::make_shared<InputComponent>(_clientCore, _engine);
    std::shared_ptr<InputComponent> port_input = std::make_shared<InputComponent>(_clientCore, _engine);
    std::shared_ptr<SoundComponent> sound = std::make_shared<SoundComponent>(_clientCore, _engine);
    std::shared_ptr<TextComponent> text_left_stereo = std::make_shared<TextComponent>(_clientCore, _engine);
    std::shared_ptr<TextComponent> text_right_stereo = std::make_shared<TextComponent>(_clientCore, _engine);

    text->setText("");

    button_volume->addActionTarget(text);
    button_volume->addActionTarget(input_volume);
    button_volume->addActionTarget(port_input);
    button_volume->addActionTarget(sound);
    std::function<void()> handleClick = std::bind(&ButtonComponent::setSoundCallback, button_volume);
    button_volume->setCallback(handleClick);
    text_button_volume->setText("Set Volume");
    text_button_volume->setPosition(sf::Vector2f(275, 190));

    input_volume->setPosition(sf::Vector2f(150, 380));
    port_input->setPosition(sf::Vector2f(150, 475));

    input_volume->addActionTarget(port_input);
    port_input->addActionTarget(input_volume);

    input_volume->setAttribute("input volume");
    input_volume->_textEntry = "100";
    input_volume->setText();

    port_input->setAttribute("port");
    port_input->_textEntry = "4242";
    port_input->setText();
    text->setAttribute("text add serv");

    text_left_stereo->setAttribute("text left");
    text_left_stereo->setText("Stereo left : ");
    text_left_stereo->setPosition(sf::Vector2f(0, 450));
    text_right_stereo->setAttribute("text right");
    text_right_stereo->setText("Stereo right : ");
    text_right_stereo->setPosition(sf::Vector2f(0, 500));

    //addComponent(text);
    addComponent(button_volume);
    addComponent(text_button_volume);
    addComponent(input_volume);
    //addComponent(port_input);
//    addComponent(sound);
    addComponent(text_left_stereo);
    addComponent(text_right_stereo);
}

/**
 * @brief handleEvent, handle the event
 * @param event
 * @param window
 */
void MenuScene::handleEvent(const sf::Event &event, sf::RenderWindow &window)
{
    while (window.pollEvent(const_cast<sf::Event &>(event))) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }
        for (auto &component : _components) {
            component->handleEvent(event, window);
        }
    }
}

void MenuScene::update() {
    auto *in = _engine->inputBuffer;
    float vol_l = 0;
    float vol_r = 0;

    if (in == nullptr)
        return;
    for (unsigned long i = 0; i < 1024 * 2; i += 2) {
        vol_l = max(vol_l, std::abs(in[i]));
        vol_r = max(vol_r, std::abs(in[i+1]));
    }

    int vol_l_percent = 0;
    int vol_r_percent = 0;

    for (int i = 0; i < 100; i++) {
        float barProportion = i / (float)100;
        if (barProportion <= vol_l && barProportion <= vol_r) {
            vol_l_percent++;
            vol_r_percent++;
        } else if (barProportion <= vol_l) {
            vol_l_percent++;
        } else if (barProportion <= vol_r) {
            vol_r_percent++;
        }
    }

    for (auto &component : _components) {
        if (component->getAttribute() == "text left") {
            auto text = std::dynamic_pointer_cast<TextComponent>(component);
            text->setText("Stereo left : " + std::to_string(vol_l_percent) + "%");
        } else if (component->getAttribute() == "text right") {
            auto text = std::dynamic_pointer_cast<TextComponent>(component);
            text->setText("Stereo right : " + std::to_string(vol_r_percent) + "%");
        }
    }
}
