#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "InputState.h"


class InputManager
{
public:
	InputManager();
	virtual ~InputManager();

	void init(int screenWidth, int screenHeight);

	void clear();

	void prepareForUpdate();
	void update();

	bool pollInputs();

	const InputState& getState() const;

	bool getIsCursorDisplayed() const { return isCursorDisplayed; }
	void setMouseCursor(bool isCursorDisplayedP);
	void setMouseRelativeMode(bool isMouseRelativeOnP);

private:
	float filter1D(int input);
	// Vector2 filter2D(int inputX, int inputY);

	InputState inputState;

	bool isCursorDisplayed;

	int windowWidth;
	int windowHeight;
};

#endif // INPUTMANAGER_H
