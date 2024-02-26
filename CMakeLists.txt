cmake_minimum_required(VERSION 3.25.1)
project(Showtime)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)

FetchContent_Declare(
        portaudio
        URL http://files.portaudio.com/archives/pa_stable_v190700_20210406.tgz
)

FetchContent_Declare(
        SFML
        URL https://www.sfml-dev.org/files/SFML-2.5.1-sources.zip
)

FetchContent_GetProperties(portaudio)
if(NOT portaudio_POPULATED)
    FetchContent_Populate(portaudio)
    add_subdirectory(${portaudio_SOURCE_DIR} ${portaudio_BINARY_DIR})
endif()

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Showtime main.cpp
        AudioEngine.cpp
        AudioEngine.hpp
        ClientCore.hpp
        ClientCore.cpp
        Scenes/IScene.hpp
        Scenes/AScene.hpp
        Scenes/AScene.cpp
        Scenes/Menu/MenuScene.hpp
        Scenes/Menu/MenuScene.cpp
        Components/IComponent.hpp
        Components/AComponent.hpp
        Components/AComponent.cpp
        Components/Text/TextComponent.hpp
        Components/Text/TextComponent.cpp
        Components/Sprite/SpriteComponent.hpp
        Components/Sprite/SpriteComponent.cpp
        Components/Sound/SoundComponent.hpp
        Components/Sound/SoundComponent.cpp
        Components/Music/MusicComponent.hpp
        Components/Music/MusicComponent.cpp
        Components/Input/InputComponent.hpp
        Components/Input/InputComponent.cpp
        Components/Button/ButtonComponent.hpp
        Components/Button/ButtonComponent.cpp
        Network/Networking.cpp
        Network/Networking.hpp)

message(STATUS "portaudio_SOURCE_DIR: ${portaudio_SOURCE_DIR}")

target_include_directories(Showtime PRIVATE ${portaudio_SOURCE_DIR}/include)
target_link_libraries(Showtime PRIVATE portaudio rt asound jack pthread sfml-audio sfml-system sfml-window sfml-graphics)