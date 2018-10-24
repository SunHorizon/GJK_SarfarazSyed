#include <iostream>
#include "GameManager.h"
#include "MMath.h"
#include "GJKAlgorithm.h"


///#include <SDL.h>
using namespace MATH;

int main(int argc, char* args[]) { /// Standard C-style entry point, you need to use it



	//Vec3 A1(0, 0, 0), A2(0, 4, 0), A3(4, 0, 0);
	////Vec3 B1(0, 0, 0), B2(0, 4, 0), B3(4, 0, 0);
	//Vec3 B1(4.5, 4.0, 0), B2(1.5, 4, 0), B3(4, 2, 0);
	//std::vector<Vec3> shapeA;
	//shapeA.push_back(A1);
	//shapeA.push_back(A2);
	//shapeA.push_back(A3);
	//std::vector<Vec3> shapeB;
	//shapeB.push_back(B1);
	//shapeB.push_back(B2);
	//shapeB.push_back(B3);

	//GJKAlgorithm collide;

	//if (collide.Collided(shapeA, shapeB) == true) {

	//	printf("YEAAAAAAAAAAAAAA it works");
	//}
	//else {
	//	printf("nooooooo");
	//}

	GameManager *ptr = new GameManager();
	bool status  = ptr->OnCreate();
	if (status == true) {
		ptr->Run();
	

	} else if (status == false) {
		/// You should have learned about stderr (std::cerr) in Operating Systems 
		std::cerr << "Fatal error occured. Cannot start this program" << std::endl;
	}


	

	delete ptr;
	return 0;

}