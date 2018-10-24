#include "GJKAlgorithm.h"



GJKAlgorithm::GJKAlgorithm()
{

}

bool GJKAlgorithm::checkCollision(Body shapeA_, Body shapeB_) {

	

	std::vector<Vec3> shapeA;
	std::vector<Vec3> shapeB;

	shapeA.push_back(shapeA_.P1);
	shapeA.push_back(shapeA_.P2);
	shapeA.push_back(shapeA_.P3);

	shapeB.push_back(shapeB_.P1);
	shapeB.push_back(shapeB_.P2);
	shapeB.push_back(shapeB_.P3);

	std::vector<Vec3> Points;

	Vec3 CenterA(0, 0, 0);
	Vec3 CenterB(0, 0, 0);
	std::vector<Vec3> center;

	// getting the center point for a tringle;
	for (auto shapeA : shapeA) {
		CenterA += shapeA;
	}
	CenterA /= shapeA.size();

	// getting the center point for a tringle;
	for (auto shapeB : shapeB) {
		CenterB += shapeB;
	}
	CenterB /= shapeB.size();

	// Getting the first direction
	// get the center points of the shapes
	d = CenterB - CenterA;
	Vec3 s = SearchPoint(shapeA, shapeB, d);
	Points.push_back(s);
	d = -1 * s;

	Vec3 A;

	// start the loop
	while (true) {
		// adding the new point
		A = SearchPoint(shapeA, shapeB, d);
		// checking if the point added contains the origin
		if (VMath::dot(A, d) <= 0) {
			// if the point was not past the origin then it does not conatin the origin
			return false;
		}
		else {
			Points.push_back(A);
			// checks if the points contain the origin in the given direction
			if (CheckSimplex(Points, d) == true) {
				// if true it contains the origin
				return true;
			}
			else {
				// get the new direction
				d = getDirection();
			}
		}
	}

}


bool GJKAlgorithm::checkCollision(std::vector<Vec3> shapeA, std::vector<Vec3> shapeB) {

	std::vector<Vec3> Points;

	Vec3 CenterA(0, 0, 0);
	Vec3 CenterB(0, 0, 0);
	std::vector<Vec3> center;

	// getting the center point for a tringle;
	for (auto shapeA : shapeA) {
		CenterA += shapeA;
	}
	CenterA /= shapeA.size();

	// getting the center point for a tringle;
	for (auto shapeB : shapeB) {
		CenterB += shapeB;
	}
	CenterB /= shapeB.size();

	// Getting the first direction
	// get the center points of the shapes
	d = CenterB - CenterA;
	Vec3 s = SearchPoint(shapeA, shapeB, d);
	Points.push_back(s);
	d = -1 * s;
	
	Vec3 A;

	// start the loop
	while (true) {
		// adding the new point
		A = SearchPoint(shapeA, shapeB, d);
 		// checking if the point added contains the origin
		if (VMath::dot(A, d) <= 0) {
			// if the point was not past the origin then it does not conatin the origin
			return false;
		}
		else {
			Points.push_back(A);
			// checks if the points contain the origin in the given direction
			if (CheckSimplex(Points, d) == true) {
				// if true it contains the origin
				return true;
			}
			else {
				// get the new direction
				d = getDirection();
			}
		}
	}

}


bool GJKAlgorithm::CheckSimplex(std::vector<Vec3> Points, Vec3 d_) {

	//// getting the old point
	//Vec3 oldPoint = Points[Points.size() - 2];
	//// getting the new point
	//Vec3 NewPoint = Points[Points.size() -1];

	Vec3 a = Points[Points.size() - 1];
	Vec3 ao = Vec3(0, 0, 0) - a;

	// checking if there are 3 points
	if (Points.size() == 3) {
		// checking for 3 points
		// getting b and c
		Vec3 b = Points[Points.size() - 2];
		Vec3 c = Points[Points.size() - 3];

		Vec3 ab = b - a;
		Vec3 ac = c - a;

		// getting the normals
		Vec3 abPreb = (VMath::cross(VMath::cross(ac, ab), ab));
		Vec3 aCPreb = (VMath::cross(VMath::cross(ab, ac), ac));


		if (VMath::dot(abPreb, ao) > 0) {
			// removing c
			Points.erase(Points.begin());
			setDirection(abPreb);
		}
		else {
			if (VMath::dot(aCPreb, ao) > 0) {
				Points.erase(Points.begin() + 1);
				setDirection(aCPreb);
			}
			else {
				return true;
			}
		}
	}
	else {
		Vec3 b = Points[Points.size() - 2];
		Vec3 ab = b - a;
		Vec3 abPrep = (VMath::cross(VMath::cross(ab, ao), ab));
		setDirection(abPrep);

	}
	return false;
	/*if (VMath::dot(oldPoint - NewPoint, Vec3(0, 0, 0) - NewPoint) > 0) {
		setDirection(VMath::cross(VMath::cross(oldPoint - NewPoint, ao), oldPoint - NewPoint));
	}
	else {
		setDirection(Vec3(0, 0, 0) - NewPoint);
	}
*/
}


// setting the new direction
void GJKAlgorithm::setDirection(Vec3 d) {
	NewDirection = d;
}

//  getting  the new direction
Vec3 GJKAlgorithm::getDirection() {
	return NewDirection;
}


// searching for the furthest point in a given direction
Vec3 GJKAlgorithm::SearchPoint(std::vector<Vec3> shapeA, std::vector<Vec3> shapeB, Vec3 direction) {

	
	Vec3 P1;
	Vec3 P2;
	Vec3 P3;

	//// get the furthest point in a given direction
	//for (int i = 0; i < shapeA.size(); i++) {
	//	float check = VMath::dot(shapeA[i], direction);
	//	for (int j = i; j < shapeA.size(); j++) {
	//		float checktest = VMath::dot(shapeA[j], direction);
	//		if (check >= VMath::dot(shapeA[j], direction)) {
	//			P1 = shapeA[i];
	//			testing++;
	//			//break;
	//		}
	//	}
	//}


	if (VMath::dot(shapeA[0], direction) > VMath::dot(shapeA[1], direction) && VMath::dot(shapeA[0], direction) > VMath::dot(shapeA[2], direction)) {
		P1 = shapeA[0];
	}
	else if (VMath::dot(shapeA[1], direction) > VMath::dot(shapeA[2], direction)) {
		P1 = shapeA[1];
	}
	else {
		P1 = shapeA[2];
	}


	Vec3 NeDirection = -1 * direction;

	//// get the furthest point in the oppsite direction
	//for (int i = 0; i < shapeB.size(); i++) {
	//	float check = VMath::dot(shapeB[i], NeDirection);
	//	for (int j = i + 1; j < shapeB.size(); j++) {
	//		float checktest = VMath::dot(shapeB[j], NeDirection);
	//		if (check <= VMath::dot(shapeB[j], NeDirection)) {
	//			P2 = shapeB[i];
	//			//break;
	//		}
	//	}
	//}


	if (VMath::dot(shapeB[0], direction) < VMath::dot(shapeB[1], direction) && VMath::dot(shapeB[0], direction) < VMath::dot(shapeB[2], direction)) {
		P2 = shapeB[0];
	}
	else if (VMath::dot(shapeB[1], direction) < VMath::dot(shapeB[2], direction)) {
		P2 = shapeB[1];
	}
	else {
		P2 = shapeB[2];
	}

	// get the point in minkowski difference
	P3 = P1 - P2;

	return P3;

}





































GJKAlgorithm::~GJKAlgorithm()
{
}
