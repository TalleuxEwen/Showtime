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
    std::shared_ptr<ButtonComponent> button_reverb = std::make_shared<ButtonComponent>(_clientCore, _engine);
    std::shared_ptr<TextComponent> text_button_reverb = std::make_shared<TextComponent>(_clientCore, _engine);
    //std::shared_ptr<InputComponent> input_volume = std::make_shared<InputComponent>(_clientCore, _engine);
    std::shared_ptr<InputComponent> port_input = std::make_shared<InputComponent>(_clientCore, _engine);
    std::shared_ptr<SoundComponent> sound = std::make_shared<SoundComponent>(_clientCore, _engine);
    std::shared_ptr<SpriteComponent> vu_level_input = std::make_shared<SpriteComponent>(_clientCore, _engine);
    std::shared_ptr<SpriteComponent> level_vu_meter_left_input = std::make_shared<SpriteComponent>(_clientCore, _engine);
    std::shared_ptr<SpriteComponent> level_vu_meter_right_input = std::make_shared<SpriteComponent>(_clientCore, _engine);
    std::shared_ptr<SpriteComponent> vu_level_output = std::make_shared<SpriteComponent>(_clientCore, _engine);
    std::shared_ptr<SpriteComponent> level_vu_meter_left_output = std::make_shared<SpriteComponent>(_clientCore, _engine);
    std::shared_ptr<SpriteComponent> level_vu_meter_right_output = std::make_shared<SpriteComponent>(_clientCore, _engine);
    std::shared_ptr<SpriteComponent> output_fader_button = std::make_shared<SpriteComponent>(_clientCore, _engine);

    text->setText("");


    button_reverb->addActionTarget(text);
    button_reverb->addActionTarget(text_button_reverb);
    //button_reverb->addActionTarget(input_volume);
    //button_reverb->addActionTarget(port_input);
    button_reverb->addActionTarget(sound);
    std::function<void()> handleClick = std::bind(&ButtonComponent::setSoundCallback, button_reverb);
    button_reverb->setCallback(handleClick);
    text_button_reverb->setText("Reverb Off");
    text_button_reverb->setAttribute("text reverb");
    text_button_reverb->setPosition(sf::Vector2f(275, 190));

    //input_volume->setPosition(sf::Vector2f(150, 380));
    port_input->setPosition(sf::Vector2f(150, 475));

    /*input_volume->addActionTarget(port_input);
    port_input->addActionTarget(input_volume);

    input_volume->setAttribute("input volume");
    input_volume->_textEntry = "100";
    input_volume->setText();*/

    port_input->setAttribute("port");
    port_input->_textEntry = "4242";
    port_input->setText();
    text->setAttribute("text add serv");

    sf::Texture texture;
    texture.loadFromFile("assets/vumeter.jpg");
    vu_level_input->setTexture(texture);
    vu_level_input->setPosition(sf::Vector2f(0, 0));
    vu_level_input->setSize(sf::Vector2f(42, 407));
    vu_level_input->setRect(sf::IntRect(0, 0, 84, 814));

    sf::Texture texture_vu_meter_left;
    texture_vu_meter_left.loadFromFile("assets/black.jpg");
    level_vu_meter_left_input->setTexture(texture_vu_meter_left);
    level_vu_meter_left_input->setAttribute("level vu meter left");
    level_vu_meter_left_input->setPosition(sf::Vector2f(0, 0));
    level_vu_meter_left_input->setSize(sf::Vector2f(22, 407));
    level_vu_meter_left_input->setRect(sf::IntRect(0, 0, 84, 84));
    level_vu_meter_left_input->setOpacity(200);

    sf::Texture texture_vu_meter_right;
    texture_vu_meter_right.loadFromFile("assets/black.jpg");
    level_vu_meter_right_input->setTexture(texture_vu_meter_right);
    level_vu_meter_right_input->setAttribute("level vu meter right");
    level_vu_meter_right_input->setPosition(sf::Vector2f(22, 0));
    level_vu_meter_right_input->setSize(sf::Vector2f(22, 200));
    level_vu_meter_right_input->setRect(sf::IntRect(0, 0, 84, 84));
    level_vu_meter_right_input->setOpacity(200);

    sf::Texture texture_vu_meter;
    texture_vu_meter.loadFromFile("assets/vumeter.jpg");
    vu_level_output->setTexture(texture_vu_meter);
    vu_level_output->setPosition(sf::Vector2f(750, 0));
    vu_level_output->setSize(sf::Vector2f(42, 407));
    vu_level_output->setRect(sf::IntRect(0, 0, 84, 814));

    sf::Texture texture_vu_meter_left_output;
    texture_vu_meter_left_output.loadFromFile("assets/black.jpg");
    level_vu_meter_left_output->setTexture(texture_vu_meter_left_output);
    level_vu_meter_left_output->setAttribute("level vu meter left output");
    level_vu_meter_left_output->setPosition(sf::Vector2f(750, 0));
    level_vu_meter_left_output->setSize(sf::Vector2f(22, 407));
    level_vu_meter_left_output->setRect(sf::IntRect(0, 0, 84, 84));
    level_vu_meter_left_output->setOpacity(200);

    sf::Texture texture_vu_meter_right_output;
    texture_vu_meter_right_output.loadFromFile("assets/black.jpg");
    level_vu_meter_right_output->setTexture(texture_vu_meter_right_output);
    level_vu_meter_right_output->setAttribute("level vu meter right output");
    level_vu_meter_right_output->setPosition(sf::Vector2f(772, 0));
    level_vu_meter_right_output->setSize(sf::Vector2f(22, 407));
    level_vu_meter_right_output->setRect(sf::IntRect(0, 0, 84, 84));
    level_vu_meter_right_output->setOpacity(200);

    sf::Texture texture_output_fader_button;
    texture_output_fader_button.loadFromFile("assets/fader_button.png");
    output_fader_button->setTexture(texture_output_fader_button);
    output_fader_button->setAttribute("output fader button");
    output_fader_button->setPosition(sf::Vector2f(730, 365));
    output_fader_button->setSize(sf::Vector2f(84, 84));
    output_fader_button->setRect(sf::IntRect(0, 0, 84, 84));
    output_fader_button->setOpacity(200);


    //addComponent(text);
    addComponent(button_reverb);
    addComponent(text_button_reverb);
    //addComponent(input_volume);
    //addComponent(port_input);
//    addComponent(sound);
    addComponent(vu_level_input);
    addComponent(level_vu_meter_left_input);
    addComponent(level_vu_meter_right_input);
    addComponent(vu_level_output);
    addComponent(level_vu_meter_left_output);
    addComponent(level_vu_meter_right_output);
    addComponent(output_fader_button);
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
    auto *out = _engine->outputBuffer;

    float vol_l_input = 0;
    float vol_r_input = 0;

    float vol_l_output = 0;
    float vol_r_output = 0;

    if (in == nullptr)
        return;
    for (unsigned long i = 0; i < 1024 * 2; i += 2) {
        vol_l_input = max(vol_l_input, std::abs(in[i]));
        vol_r_input = max(vol_r_input, std::abs(in[i+1]));
        vol_l_output = max(vol_l_output, std::abs(out[i]));
        vol_r_output = max(vol_r_output, std::abs(out[i+1]));
    }

    int vol_l_percent_input = 0;
    int vol_r_percent_input = 0;

    int vol_l_percent_output = 0;
    int vol_r_percent_output = 0;

    for (int i = 0; i < 100; i++) {
        float barProportion = i / (float)100;
        if (barProportion <= vol_l_input && barProportion <= vol_r_input) {
            vol_l_percent_input++;
            vol_r_percent_input++;
        } else if (barProportion <= vol_l_input) {
            vol_l_percent_input++;
        } else if (barProportion <= vol_r_input) {
            vol_r_percent_input++;
        }

        if (barProportion <= vol_l_output && barProportion <= vol_r_output) {
            vol_l_percent_output++;
            vol_r_percent_output++;
        } else if (barProportion <= vol_l_output) {
            vol_l_percent_output++;
        } else if (barProportion <= vol_r_output) {
            vol_r_percent_output++;
        }
    }

    for (auto &component : _components) {
        if (component->getAttribute() == "text left") {
            auto text = std::dynamic_pointer_cast<TextComponent>(component);
            text->setText("Stereo left : " + std::to_string(vol_l_percent_output) + "%");
        } else if (component->getAttribute() == "text right") {
            auto text = std::dynamic_pointer_cast<TextComponent>(component);
            text->setText("Stereo right : " + std::to_string(vol_r_percent_output) + "%");
        }
    }

    for (auto &component : _components) {
        if (component->getAttribute() == "level vu meter left") {
            auto sprite = std::dynamic_pointer_cast<SpriteComponent>(component);
            sprite->setSize(sf::Vector2f(22, 407 * ((float)abs(vol_l_percent_input - 100) / 100.f)));
        } else if (component->getAttribute() == "level vu meter right") {
            auto sprite = std::dynamic_pointer_cast<SpriteComponent>(component);
            sprite->setSize(sf::Vector2f(22, 407 * ((float)abs(vol_r_percent_input - 100) / 100.f)));
        }
    }

    for (auto &component : _components) {
        if (component->getAttribute() == "level vu meter left output") {
            auto sprite = std::dynamic_pointer_cast<SpriteComponent>(component);
            sprite->setSize(sf::Vector2f(22, 407 * ((float)abs(vol_l_percent_output - 100) / 100.f)));
        } else if (component->getAttribute() == "level vu meter right output") {
            auto sprite = std::dynamic_pointer_cast<SpriteComponent>(component);
            sprite->setSize(sf::Vector2f(22, 407 * ((float)abs(vol_r_percent_output - 100) / 100.f)));
        }
    }
}
