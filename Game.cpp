#include "Game.h"
#include "SDL.h"
#include "Graphics.h"
#include "Player.h"
#include "Input.h"

namespace {
	const int FPS = 60;
}

int Game::tileSize = 32;

Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_ShowCursor(SDL_DISABLE);
	eventLoop();
}

Game::~Game() {
	SDL_Quit();
}

void Game::eventLoop() {
	bool running = true;
	Graphics graphics;
	Input input;
	SDL_Event event;

	player_.reset(new Player(graphics, 480, 320));
	int last_update_time = SDL_GetTicks();
	while (running) {
		const int start_time_ms = SDL_GetTicks();
		input.beginNewFrame();
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				input.keyDownEvent(event); 
				break;
			case SDL_KEYUP:
				input.keyUpEvent(event);
			default:
				break;
			}
		}
		if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)) {
			running = false;
		}

		if (input.isKeyHeld(SDL_SCANCODE_LEFT) && input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
			player_->stopMoving();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_LEFT)) {
			player_->startMovingLeft();
		}
		else if (input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
			player_->startMovingRight();
		}
		else player_->stopMoving();

		const int current_time_ms = SDL_GetTicks();
		update(current_time_ms - last_update_time);
		last_update_time = current_time_ms;
		draw(graphics);
		const int ms_per_frame = 1000/*ms*/ / FPS;
		const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
		if (elapsed_time_ms < ms_per_frame) {
			SDL_Delay(ms_per_frame - elapsed_time_ms);
		}
	}
}

void Game::update(int elapsed_time_ms) {
	player_->update(elapsed_time_ms);
}

void Game::draw(Graphics &graphics) {
	graphics.clear();
	player_->draw(graphics);
	graphics.flip();
}

int main(int argc, char **argv) {
	Game();
	return 0;
}
