#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <GL/glew.h>
#include <vector>
#include <memory>

#include "Input/InputManager.h"

using std::vector;
using std::unique_ptr;

class Scene;

class Game
{
public:
	Game();
	virtual ~Game();
	
	void init(int screenWidth, int screenHeight);
	void load();
	void handleInputs();
	void update(float dt);
	void render();
	void clean();

	void changeScene(unique_ptr<Scene>);
	void pushScene(unique_ptr<Scene>);
	void popScene();

	bool isRunning;
	int windowWidth, windowHeight;

private:

	InputManager inputManager;
	vector<unique_ptr<Scene>> gameScenes;
};

#endif // GAME_H
