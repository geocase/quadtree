#include <iostream>
#include <SDL2/SDL.h>

#include "input.h"

void cInput::Update() {
	this->UpdateMouse();
	this->WindowEvents();
}


void cInput::UpdateMouse() {
	SDL_PumpEvents();
	SDL_GetMouseState(&this->mouseX, &this->mouseY);

}

void cInput::WindowEvents() {
	SDL_Event e;
	while(SDL_PollEvent(&e) != 0) {
		if(e.type == SDL_QUIT) {
			this->windowExit = true;	
		}
	}
}
