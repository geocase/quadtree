#ifndef INPUT_H
#define INPUT_H

class cInput;

class cInput {
public:
	int32_t mouseX, mouseY;
	bool windowExit = false;
	

	void Update();
	void UpdateMouse();
	void WindowEvents();
};

#endif
