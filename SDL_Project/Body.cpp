#include "Body.h" 


Body:: Body(Vec3 P1_, Vec3 P2_, Vec3 P3_, float mass_, double rotationalInertia_) {

	P1 = P1_;
	P2 = P2_;
	P3 = P3_;
	mass = mass_;
	rotationalInertia = rotationalInertia_;
}


// set the mass, rotationalInertia_ and all the rest to 0 
Body::Body(double mass_, double rotationalInertia_) {
	mass = mass_;
	rotationalInertia = rotationalInertia_;
	radius = 0;
	pos = 0;
	vel = 0;
	accel = 0;
	angle = 0;
	angularVel = 0;
	angularAcc = 0;
	torque = 0;
}
// Apply angularAcc using torque / rotationalInertia.
void Body::ApplyTorque(double torque_) {

	angularAcc = torque_ / rotationalInertia;
	torque = torque_;
}

// rotates the force thrust vector.
Vec3 Body::RotateVector(double angle, Vec3 force_)
{
	// rotates the vector
	double x2, y2;
	double tempx, tempy;
	Vec3 tempForce;
	x2 = force_.x * cos(angle);
	y2 = force_.y * sin(angle);
	tempx = round(x2 - y2);
	x2 = force_.x * sin(angle);
	y2 = force_.y * cos(angle);
	tempy = round(x2 + y2);
	tempForce.x = tempx;
	tempForce.y = tempy;

	return tempForce;

}
// Apply force
void Body::ApplyForce(Vec3 force) {

	// applies the rotate vector
	Force = RotateVector(angle, force);
	accel = Force / mass;

}

Body::~Body() {} /// There is really nothing to do here - yet!

void Body::UpdateAngle(const double deltaTime) {

	// update the orientation angle
	angle += (angularVel * deltaTime) + ((0.5)*angularAcc)* (deltaTime * deltaTime);

	// get the anuglar velociy
	angularVel += angularAcc * deltaTime;
}

void Body::Update(const double deltaTime) {

	// update the position
	P1.x = P1.x + vel.x * deltaTime + (accel.x / 2) * (deltaTime * deltaTime);
	P2.x = P2.x + vel.x * deltaTime + (accel.x / 2) * (deltaTime * deltaTime);
	P3.x = P3.x + vel.x * deltaTime + (accel.x / 2) * (deltaTime * deltaTime);

	P1.y = P1.y + vel.y * deltaTime + (accel.y / 2) * (deltaTime * deltaTime);
	P2.y = P2.y + vel.y * deltaTime + (accel.y / 2) * (deltaTime * deltaTime);
	P3.y = P3.y + vel.y * deltaTime + (accel.y / 2) * (deltaTime * deltaTime);

	// get the velovity
	vel += accel * deltaTime;

}


SDL_Surface* Body::getImage() {
	return bodyImage;
}