/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** R-type
*/

#include "ClientCore.hpp"
#include "Scenes/Menu/MenuScene.hpp"

/**
 * @brief Construct a new Client Core:: Client Core object
 *
 */
ClientCore::ClientCore(std::shared_ptr<AudioEngine> audioEngine) : _audioEngine(std::move(audioEngine))
{
    _scenes["menu"] = std::make_unique<MenuScene>(this, _audioEngine);
    _currentScene = _scenes["menu"];
}

/**
 * @brief run, run the client
 *
 */
void ClientCore::run()
{
    _window.create(sf::VideoMode(800, 600), "R-Type");
    sf::Event event{};

    _window.setFramerateLimit(120);

    while (_window.isOpen()) {
        _window.clear();
        _currentScene->handleEvent(event, _window);
        _currentScene->update();
        _currentScene->display(_window);
        _window.display();
    }
}

/**
 * @brief getSceneByName, get the scene by name
 *
 * @param name
 * @return std::shared_ptr<IScene>
 */
std::shared_ptr<IScene> ClientCore::getSceneByName(const std::string &name)
{
    return _scenes[name];
}

/**
 * @brief setCurrentScene, set the current scene
 *
 * @param name
 */
void ClientCore::setCurrentScene(const std::string &name)
{
    _currentScene->continueScene = false;
    _currentScene->pauseScene();
    _currentScene = getSceneByName(name);
    _currentScene->continueScene = true;
    _currentScene->resumeScene();
}

/**
 * @brief getCurrentScene, get the current scene
 *
 * @return std::shared_ptr<IScene>
 */
std::shared_ptr<IScene> ClientCore::getCurrentScene() const
{
    return _currentScene;
}
