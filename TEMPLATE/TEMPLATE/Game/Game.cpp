#include "../Engine/Game.h"
#include "../Engine/Scene.h"

Game::Game() : isRunning(false),
windowWidth(0),
windowHeight(0) {
}

Game::~Game() {
}

void Game::init(int screenWidth, int screenHeight) {
    windowWidth = screenWidth;
    windowHeight = screenHeight;
    inputManager.init(screenWidth, screenHeight);
    isRunning = true;
}

void Game::load() {
    // Game state
    //changeState(std::make_unique<Scene_005_Tessellation>());
}

void Game::handleInputs() {
    inputManager.prepareForUpdate();
    isRunning = inputManager.pollInputs();
    inputManager.update();
    const InputState& inputState = inputManager.getState();
    gameScenes.back()->handleEvent(inputState);
}

void Game::update(float dt) {
    gameScenes.back()->update(dt);
}

void Game::render() {
    gameScenes.back()->draw();
}

void Game::clean() {
    inputManager.clear();
    Assets::clear();
}

void Game::changeScene(unique_ptr<Scene> state) {
    // cleanup the current state
    if (!gameScenes.empty()) {
        gameScenes.back()->clean();
        gameScenes.pop_back();
    }

    // store and load the new state
    state->setGame(this);
    gameScenes.push_back(std::move(state));
    gameScenes.back()->load();
}

void Game::pushScene(unique_ptr<Scene> state) {
    // pause current state
    if (!gameScenes.empty()) {
        gameScenes.back()->pause();
    }

    // store and init the new state
    gameScenes.push_back(std::move(state));
    gameScenes.back()->load();
}

void Game::popScene() {
    // cleanup the current state
    if (!gameScenes.empty()) {
        gameScenes.back()->clean();
        gameScenes.pop_back();
    }

    // resume previous state
    if (!gameScenes.empty()) {
        gameScenes.back()->resume();
    }
}