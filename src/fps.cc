#include <iostream>
#include <SDL2/SDL.h>

#include "fps.h"

void cFPS::StartFPSCounter() {
	this->fpsStartTime = SDL_GetTicks();
}

void cFPS::StartFrame() {
	this->frameStart = SDL_GetTicks();
	this->frames++;
}

void cFPS::EndFrame() {
	this->frameEnd = SDL_GetTicks();
}

double cFPS::GetFrameRate() {
	this->frameRate = this->frames / (double)((this->frameEnd - this->fpsStartTime) / 1000);
	return this->frameRate;
}

double cFPS::GetFrameTime() {
	return (double)(this->frameEnd - this->frameStart) / 1000;
}

uint64_t cFPS::GetFrames() {
	return this->frames;
}
