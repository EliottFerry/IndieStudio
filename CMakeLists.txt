CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
PROJECT(BOMBERMAN)

# Dependencies
SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/)
FIND_PACKAGE(raylib REQUIRED)
FIND_PACKAGE(Filesystem REQUIRED)

# Set C++ standard of project
SET(CMAKE_CXX_STANDARD_17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add include directories
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src/)

# Set output directory
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../)

# Add project sources (.cpp and .hpp)
SET(BOMBERMAN_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ChangePath.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ChangePath.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/encapsulation/Window.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/encapsulation/Window.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/encapsulation/ManageButtons.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/encapsulation/ManageButtons.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/encapsulation/Event.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/encapsulation/Event.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Core.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/Core.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/Parsing.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parsing/Parsing.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/SceneManager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/SceneManager.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/AScene.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/AScene.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/IScene.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/ECS.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/ECS.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/PositionComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/PositionComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/ModelComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/ModelComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/Model2DComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/Model2DComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/TwoDComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/TwoDComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/CameraComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/CameraComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/ExplosionComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/ExplosionComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/TextComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/TextComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/Score.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/Score.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/Audio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/Audio.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/ButtonComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/ButtonComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/ShaderComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/BoxComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/BoxComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/ButtonComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/ShaderComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/ShaderComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/Champion.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/Champion.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/BombComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/BombComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/BreakableWall.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/BreakableWall.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/BombermanAI.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/BombermanAI.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/Player.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/Player.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/PowerUpComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/PowerUpComponent.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/PowerUps/BombUp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/PowerUps/BombUp.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/PowerUps/ExploUp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/PowerUps/ExploUp.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/PowerUps/SpeedUp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/PowerUps/SpeedUp.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/PowerUps/StrenghtUp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/ECS/Components/PowerUps/StrenghtUp.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/mainMenu/Menu.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/initScene/initScene.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/initScene/initScene.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/mainMenu/Menu.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/inGame/Game.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/inGame/Game.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/loadingMenu/Loading.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/loadingMenu/Loading.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/newGame/CreateNewGame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/newGame/CreateNewGame.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/loadSave/LoadSave.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/loadSave/LoadSave.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/createSave/CreateSave.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/createSave/CreateSave.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/pauseMenu/Pause.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/pauseMenu/Pause.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/optionsMenu/Options.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/optionsMenu/Options.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/finishGame/FinishGame.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/finishGame/FinishGame.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/creditScene/Credit.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/creditScene/Credit.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/equalityScene/Equality.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scenes/equalityScene/Equality.hpp
)

SOURCE_GROUP("\\" FILES ${BOMBERMAN_SRC})

# Generate executable
ADD_EXECUTABLE(bomberman ${BOMBERMAN_SRC})
TARGET_LINK_LIBRARIES(bomberman raylib)
# Copy assets to build directory
ADD_CUSTOM_COMMAND(TARGET bomberman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/Assets/ $<TARGET_FILE_DIR:bomberman>/Assets/)
ADD_CUSTOM_COMMAND(TARGET bomberman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/config_files/ $<TARGET_FILE_DIR:bomberman>/config_files/)
ADD_CUSTOM_COMMAND(TARGET bomberman POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/saved/ $<TARGET_FILE_DIR:bomberman>/saved/)