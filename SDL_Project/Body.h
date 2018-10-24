#ifndef BODY_H
#define BODY_H
#include "Vector.h"
#include "SDL.h"
#include <SDL_image.h>
using namespace MATH; 

class Body {
public:
	Vec3 P1, P2, P3;
	Vec3 pos;
	Vec3 vel;
	double mass;
	double radius;
	double rotationalInertia;
	double angle, angularVel, angularAcc;
	const float pi = 3.14159265;
	Vec3 Force;
	Vec3 ThrustForce;
	Vec3 accel;
	double torque;


	void UpdateAngle(const double deltaTime);
	Vec3 RotateVector(double angle, Vec3 force_);
	Body(double mass_, double rotationalInertia_);
	void ApplyTorque(double torque);
	void ApplyForce(Vec3 force);
	~Body();
	void Update(const double deltaTime);
private:
	SDL_Surface *bodyImage;
	
public:
	//Body(char* imageName ,float mass_, float radius_, Vec3 pos_, Vec3 vel_, Vec3 accel_);
	Body(Vec3 P1_, Vec3 P2_, Vec3 P3_, float mass_, double rotationalInertia_);
	/// Just a little helper function
	SDL_Surface* getImage();
};


#endif
