#include <iostream>
#include <SDL2/SDL.h>

#include "sector.h"
#include "window.h"

cWindow::cWindow() {
	this->sdlwin = SDL_CreateWindow(this->winTitle.c_str(),
	                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
	                                this->winx, this->winy,
	                                SDL_WINDOW_SHOWN);
	
	this->sdlren = SDL_CreateRenderer(this->sdlwin, -1, SDL_RENDERER_SOFTWARE);
	if(!(this->sdlren && this->sdlwin)) {
		std::cout << "SDL_ERROR" << std::endl << SDL_GetError() << std::endl;
	}
}

void cWindow::DrawLine(uint32_t ax, uint32_t ay, uint32_t bx, uint32_t by, sColor_t c) {
	SDL_SetRenderDrawColor(this->sdlren, c.r, c.g, c.b, c.a);
	
	SDL_RenderDrawLine(this->sdlren, ax, ay, bx, by);
}

void cWindow::DrawLine(double ax, double ay, double bx, double by, sColor_t c) {
	SDL_SetRenderDrawColor(this->sdlren, c.r, c.g, c.b, c.a);
	
	SDL_RenderDrawLine(this->sdlren, (int)ax, (int)ay, (int)bx, (int)by);
}

void cWindow::DrawPixel(int x, int y, sColor_t c) {
	SDL_SetRenderDrawColor(this->sdlren, c.r, c.g, c.b, c.a);
	SDL_RenderDrawPoint(this->sdlren, x, y);
}

void cWindow::DrawPolygon(cPolygon *p, sColor_t col) {
	cVertex tempA;
	cVertex tempB;
	for(uint32_t i = 0; i < p->faceCount; i++) {
		tempA = *(p->faces.at(i).a);
		tempB = *(p->faces.at(i).b);
		this->DrawLine(tempA.position.x, tempA.position.y, tempB.position.x, tempB.position.y, col);
	}
}

void cWindow::Update() {
	SDL_RenderPresent(this->sdlren);
	SDL_SetRenderDrawColor(this->sdlren, 0, 0, 0, 255);
	SDL_RenderClear(this->sdlren);
}
