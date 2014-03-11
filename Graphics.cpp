#include "Graphics.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

namespace {
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
}

Graphics::Graphics() {
	window_ = SDL_CreateWindow("Cave Story", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window_ == nullptr) {
		throw std::runtime_error("SDL_CreateWindow");
	}
	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
	if (renderer_ == nullptr) {
		throw std::runtime_error("SDL_CreateRenderer");
	}
}

Graphics::~Graphics() {
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

SDL_Texture* Graphics::loadTexture(const std::string &file) {
	SDL_Surface *surface = SDL_LoadBMP(file.c_str());
	if (surface == nullptr) {
		throw std::runtime_error("SDL_LoadBMP");
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface);
	if (texture == nullptr) {
		throw std::runtime_error("SDL_CreateTextureFromSurface");
	}
	SDL_FreeSurface(surface);
	return texture;
}

void Graphics::renderTexture(SDL_Texture *tex, SDL_Rect dst, SDL_Rect *clip) const {
	SDL_RenderCopy(renderer_, tex, clip, &dst);
}

void Graphics::renderTexture(SDL_Texture *tex, int x, int y, SDL_Rect *clip) const {
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	if (clip != nullptr) {
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	renderTexture(tex, dst, clip);
}

void Graphics::flip() const {
	SDL_RenderPresent(renderer_);
}

void Graphics::clear() const {
	SDL_RenderClear(renderer_);
}