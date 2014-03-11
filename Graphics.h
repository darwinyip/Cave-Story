#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include <string>
#include <iostream>
#include <stdexcept>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;
struct SDL_Rect;

struct Graphics {
	Graphics();
	~Graphics();
	SDL_Texture* loadTexture(const std::string &file);
	void renderTexture(SDL_Texture *tex, SDL_Rect dst, SDL_Rect *clip = nullptr) const;
	void renderTexture(SDL_Texture *tex, int x, int y, SDL_Rect *clip = nullptr) const;
	void flip() const;
	void clear() const;

private:
	SDL_Window *window_;
	SDL_Renderer *renderer_;
};

#endif //GRAPHICS_H_