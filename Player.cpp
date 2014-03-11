#include "Player.h"
#include "Animated_Sprite.h"
#include "Graphics.h"
#include "Game.h"
#include <cmath>
#include <algorithm>

namespace {
	const float WalkingAcceleration = 0.0012f;
	const float MaxSpeed = 0.325f;
	const float SlowdownFactor = 0.8f;
}

Player::Player(Graphics &graphics, int x, int y) {
	x_ = x;
	y_ = y;
	velocity_x_ = 0.0f;
	acceleration_x_ = 0.0f;
	sprite_.reset(new AnimatedSprite(graphics, "content/MyChar.bmp", 
		Game::tileSize * 0, Game::tileSize * 0, Game::tileSize, Game::tileSize, 15, 3));
}

void Player::update(int elapsed_time_ms) {
	sprite_->update(elapsed_time_ms);
	x_ += round(velocity_x_ * elapsed_time_ms);
	velocity_x_ += acceleration_x_ * elapsed_time_ms;
	if (acceleration_x_ < 0.0f) {
		velocity_x_ = std::max(velocity_x_, -MaxSpeed);
	}
	else if (acceleration_x_ > 0.0f) {
		velocity_x_ = std::min(velocity_x_, MaxSpeed);
	}
	else {
		velocity_x_ *= SlowdownFactor;
	}
}

void Player::draw(Graphics& graphics) {
	sprite_->draw(graphics, x_, y_);
}

void Player::startMovingLeft() {
	acceleration_x_ = -WalkingAcceleration;
}

void Player::startMovingRight() {
	acceleration_x_ = WalkingAcceleration;

}
void Player::stopMoving() {
	acceleration_x_ = 0.0f;
}