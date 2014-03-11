#include "Sprite.h"
#include "Graphics.h"

Sprite::Sprite(Graphics &graphics, const std::string& file_path, int source_x, int source_y, int width, int height) {
	sprite_sheet_ = graphics.loadTexture(file_path);
	source_rect_.x = source_x;
	source_rect_.y = source_y;
	source_rect_.w = width;
	source_rect_.h = height;
}

Sprite::~Sprite() {
	SDL_DestroyTexture(sprite_sheet_);
}

void Sprite::draw(Graphics& graphics, int x, int y) {
	SDL_Rect destination_rectangle;
	destination_rectangle.x = x;
	destination_rectangle.y = y;
	graphics.renderTexture(sprite_sheet_, destination_rectangle.x, destination_rectangle.y, &source_rect_);
}