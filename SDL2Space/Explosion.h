#pragma once
#include "GameObject.h"
#include "Spritesheet.h"
#include <SDL.h>
class Explosion : public GameObject{
public:
	Explosion(std::shared_ptr<Spritesheet> spritesheet, int x, int y, float animationspeed);
	~Explosion();
	void update(float deltaTime) override;
	void draw(SDL_Renderer* renderer);
	bool isAnimationFinished() const;
private:
	std::shared_ptr<Spritesheet> spritesheet;
	int currentframe;
	int totalframes;
	float animationspeed;
	float animationtimer;
};

