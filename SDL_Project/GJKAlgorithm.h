#ifndef GJKAlgorithm_H
#define GJKAlgorithm_H
#include "Body.h" 
#include <math.h> 
#include "VMath.h"
#include <vector>
#include "Body.h"

using namespace MATH;

class GJKAlgorithm
{
public:
	
	GJKAlgorithm();
	~GJKAlgorithm();


	std::vector<Vec3> Points;
	Vec3 d;
	Vec3 NewDirection;
	Vec3 SearchPoint(std::vector<Vec3> shapeA, std::vector<Vec3> shapeB, Vec3 direction);
	bool checkCollision(std::vector<Vec3> shapeA, std::vector<Vec3> shapeB);
	bool checkCollision(Body shapeA, Body shapeB);
	bool CheckSimplex(std::vector<Vec3> Points, Vec3 d);
	void setDirection(Vec3 d);
	Vec3 getDirection();

};
#endif
