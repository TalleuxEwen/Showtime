/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#pragma once

#include "Scenes/IScene.hpp"
#include "AudioEngine.hpp"
#include <chrono>
#include <map>
#include <memory>
#include <sys/time.h>
#include <thread>

class ClientCore
{
  public:

    /**
     * @brief ClientCore, constructor of ClientCore
     */
    explicit ClientCore(std::shared_ptr<AudioEngine> audioEngine);

    /**
     * @brief ~ClientCore, destructor of ClientCore
     */
    ~ClientCore() = default;


    /**
     * @brief run, run the client
     */
    void run();

    /**
     * @brief getSocket, get the socket
     *
     * @return std::shared_ptr<ClientSocket>
     */
    std::shared_ptr<IScene> getSceneByName(const std::string &name);

    /**
     * @brief setCurrentScene, set the current scene
     *
     * @param name
     */
    void setCurrentScene(const std::string &name);

    /**
     * @brief getCurrentScene, get the current scene
     *
     * @return std::shared_ptr<IScene>
     */
    std::shared_ptr<IScene> getCurrentScene() const;


  private:
    sf::RenderWindow _window;
    std::map<std::string, std::shared_ptr<IScene>> _scenes;
    std::shared_ptr<IScene> _currentScene;
    std::shared_ptr<AudioEngine> _audioEngine;
};
