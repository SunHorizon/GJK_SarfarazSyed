#ifndef Assignment4_H
#define Assignment4_H
#include <SDL_image.h>
#include "MMath.h"
#include "Scene.h"
#include <cmath>
#include <SDL.h>
#include "Collider.h"
#include "GJKAlgorithm.h"
#include <vector>


using namespace MATH;
#define NUM_BODIES 2
class Assignment4 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	class Body* bodies[NUM_BODIES];
	Vec3 direction;
	Vec3 direction2;
	Vec3 gForce;
	float dis;
	float dis2;
	float fg1;
	float fg2;
	float elapsedTime;
	unsigned long frameCount;
	bool keyCheck;
	bool checkC;
	SDL_Renderer* Renderer;
	GJKAlgorithm collide;
	std::vector<Vec3> ShapeA;
	std::vector<Vec3> ShapeB;
	bool CheckKeyPress;
public:
	Assignment4(SDL_Window* sdlWindow);
	~Assignment4();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void KeyPress();
	bool closeWindow;
	bool GetCloseWindow();
};

#endif

