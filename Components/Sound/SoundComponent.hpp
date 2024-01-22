/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "../AComponent.hpp"
#include <SFML/Audio.hpp>

class SoundComponent : public AComponent
{
  public:

    /**
     * @brief Construct a new Sound Component:: Sound Component object
     *
     * @param core
     * @param socket
     */
    SoundComponent(ClientCore *core, std::shared_ptr<AudioEngine> engine);

    /**
     * @brief Destroy the Sound Component:: Sound Component object
     *
     */
    ~SoundComponent() override = default;

    /**
     * @brief action, play the sound
     */
    void action() override;

    /**
     * @brief display, display the sound
     *
     * @param window
     */
    void display(sf::RenderWindow &window) override;

    /**
     * @brief setSound, set the sound
     *
     * @param path the path of the sound
     */
    void setSound(const std::string &path);

    /**
     * @brief stop, stop the sound
     */
    void stop();

    /**
     * @brief handleEvent, handle the event
     *
     * @param event
     * @param window
     */
    void handleEvent(const sf::Event &event, sf::RenderWindow &window) override;

  private:
    sf::SoundBuffer _buffer;
    sf::Sound _sound;
};
