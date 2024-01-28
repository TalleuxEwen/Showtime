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
    std::shared_ptr<SpriteComponent> reverb_level = std::make_shared<SpriteComponent>(_clientCore, _engine);
    std::shared_ptr<SpriteComponent> reverb_decay = std::make_shared<SpriteComponent>(_clientCore, _engine);
    std::shared_ptr<SpriteComponent> reverb_reverberation = std::make_shared<SpriteComponent>(_clientCore, _engine);
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
    std::shared_ptr<TextComponent> text_input = std::make_shared<TextComponent>(_clientCore, _engine);
    std::shared_ptr<TextComponent> text_output = std::make_shared<TextComponent>(_clientCore, _engine);
    std::shared_ptr<SpriteComponent> gain_button = std::make_shared<SpriteComponent>(_clientCore, _engine);
    std::shared_ptr<TextComponent> text_gain = std::make_shared<TextComponent>(_clientCore, _engine);
    std::shared_ptr<SpriteComponent> pan_button = std::make_shared<SpriteComponent>(_clientCore, _engine);
    std::shared_ptr<TextComponent> text_pan = std::make_shared<TextComponent>(_clientCore, _engine);

    text->setText("");

    text_input->setText("Input");
    text_input->setAttribute("text input");
    text_input->setPosition(sf::Vector2f(10, 450));

    text_output->setText("Output");
    text_output->setAttribute("text output");
    text_output->setPosition(sf::Vector2f(700, 450));


    button_reverb->addActionTarget(text);
    button_reverb->addActionTarget(text_button_reverb);
    //button_reverb->addActionTarget(input_volume);
    //button_reverb->addActionTarget(port_input);
    button_reverb->addActionTarget(sound);
    std::function<void()> handleClick = std::bind(&ButtonComponent::setSoundCallback, button_reverb);
    button_reverb->setCallback(handleClick);
    button_reverb->setSize(sf::Vector2f(0.3, 0.3));
    button_reverb->setPosition(sf::Vector2f(300, 200));
    text_button_reverb->setText("Reverb Off");
    text_button_reverb->setAttribute("text reverb");
    text_button_reverb->setPosition(sf::Vector2f(330, 225));

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

    sf::Texture texture_gain_button;
    texture_gain_button.loadFromFile("assets/turnable_button.png");
    gain_button->setTexture(texture_gain_button);
    gain_button->setAttribute("gain button");
    gain_button->setPosition(sf::Vector2f(550, 350));
    gain_button->setSize(sf::Vector2f(84, 84));
    gain_button->setRect(sf::IntRect(0, 0, 84, 84));
    gain_button->setOrigin(42, 42);
    gain_button->setRotation(-90);

    text_gain->setText("Gain");
    text_gain->setAttribute("text gain");
    text_gain->setPosition(sf::Vector2f(525, 425));

    sf::Texture texture_pan_button;
    texture_pan_button.loadFromFile("assets/turnable_button.png");
    pan_button->setTexture(texture_pan_button);
    pan_button->setAttribute("pan button");
    pan_button->setPosition(sf::Vector2f(250, 350));
    pan_button->setSize(sf::Vector2f(84, 84));
    pan_button->setRect(sf::IntRect(0, 0, 84, 84));
    pan_button->setOrigin(42, 42);
    pan_button->setRotation(0);

    text_pan->setText("Pan");
    text_pan->setAttribute("text pan");
    text_pan->setPosition(sf::Vector2f(225, 425));

    sf::Texture texture_reverb_level;
    texture_reverb_level.loadFromFile("assets/turnable_button.png");
    reverb_level->setTexture(texture_reverb_level);
    reverb_level->setAttribute("reverb level");
    reverb_level->setPosition(sf::Vector2f(400, 100));
    reverb_level->setSize(sf::Vector2f(84, 84));
    reverb_level->setRect(sf::IntRect(0, 0, 84, 84));
    reverb_level->setOrigin(42, 42);
    reverb_level->setRotation(-90);

    sf::Texture texture_reverb_decay;
    texture_reverb_decay.loadFromFile("assets/turnable_button.png");
    reverb_decay->setTexture(texture_reverb_decay);
    reverb_decay->setAttribute("reverb decay");
    reverb_decay->setPosition(sf::Vector2f(300, 150));
    reverb_decay->setSize(sf::Vector2f(84, 84));
    reverb_decay->setRect(sf::IntRect(0, 0, 84, 84));
    reverb_decay->setOrigin(42, 42);
    reverb_decay->setRotation(-90);

    sf::Texture texture_reverb_reverberation;
    texture_reverb_reverberation.loadFromFile("assets/turnable_button.png");
    reverb_reverberation->setTexture(texture_reverb_reverberation);
    reverb_reverberation->setAttribute("reverb reverberation");
    reverb_reverberation->setPosition(sf::Vector2f(500, 150));
    reverb_reverberation->setSize(sf::Vector2f(84, 84));
    reverb_reverberation->setRect(sf::IntRect(0, 0, 84, 84));
    reverb_reverberation->setOrigin(42, 42);
    reverb_reverberation->setRotation(_engine->reverberation * 1.8f - 90.f);

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
    addComponent(text_input);
    addComponent(text_output);
    addComponent(gain_button);
    addComponent(text_gain);
    addComponent(pan_button);
    addComponent(text_pan);
    addComponent(reverb_level);
    addComponent(reverb_decay);
    addComponent(reverb_reverberation);
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
