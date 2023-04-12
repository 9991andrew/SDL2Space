#include "Explosion.h"


Explosion::Explosion(Spritesheet* spritesheet, int x, int y, float animationspeed): 
	GameObject(x,y), 
	spritesheet(spritesheet), 
	currentframe(0), 
	totalframes(spritesheet->gettotalframes()), 
	animationspeed(animationspeed), 
	animationtimer(0.0f) {
}

Explosion::~Explosion() {}

void Explosion::update(float deltatime) {
	animationtimer += deltatime;
	if (animationtimer >= animationspeed) {
		currentframe++;
		animationtimer = 0.0f;
	}
}

void Explosion::draw(SDL_Renderer* renderer) {
	if (currentframe < totalframes) {
		spritesheet->draw(renderer,x, y, currentframe);
	}
}

bool Explosion::isAnimationFinished() const {
	return currentframe >= totalframes;
}