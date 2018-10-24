#include "Assignment4.h"
#include "Body.h"
#include <SDL.h>
#include "GameManager.h"
#include <cmath>
#include <time.h>
#include <cstdlib> 
#include "GJKAlgorithm.h"
#include <iostream>


Assignment4::Assignment4(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	elapsedTime = 0.0f;
	frameCount = 0L;
	keyCheck = false;
	closeWindow = false;
	for (int i = 0; i < NUM_BODIES; i++) {
		bodies[0] = nullptr;
	}

}

Assignment4::~Assignment4(){
}

bool Assignment4::OnCreate() {
	int w, h;
	SDL_Init(SDL_INIT_EVERYTHING);
	Renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_GetWindowSize(window,&w,&h);
	
	projectionMatrix = MMath::viewportNDC(w,h) * MMath::orthographic(0, 7, -0.5, 7, 0.0f, 1.0f) ;
	
	bodies[0] = new Body(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 4.0f, 0.0f), Vec3(4.0f, 0.0f, 0.0f), 1, 50);
	bodies[1] = new Body(Vec3(1.5f, 2.0f, 0.0f), Vec3(1.5f, 4.0f, 0.0f), Vec3(4.0f, 2.0f, 0.0f), 1, 50);



	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i] == nullptr) {
			return false;
		}
	}
	return true;
}

void Assignment4::OnDestroy() {
	IMG_Quit();
	for (int i = 0; i < NUM_BODIES; i++) {
		if (bodies[i]) {
			delete bodies[i];
			bodies[i] = nullptr;
		}
	}
}

void Assignment4::Update(const float Time) {

	
	if (CheckKeyPress == true) {
		elapsedTime += Time;
		if (elapsedTime < 2) {
			bodies[1]->ApplyTorque(1);
			bodies[1]->UpdateAngle(Time);
			bodies[1]->ApplyForce(Vec3(1, 1, 0));
			bodies[1]->Update(Time);
		}
		else {
			bodies[1]->ApplyTorque(1);
			bodies[1]->UpdateAngle(Time);
			bodies[1]->ApplyForce(Vec3(-2, -2, 0));
			bodies[1]->Update(Time);
		}
	}

	if (collide.checkCollision(*bodies[0], *bodies[1]) == true) {
		printf("collision detected \n");
	}
	else {
		printf("no collision \n");
	}


}
 void Assignment4::KeyPress() {
	 SDL_Event event;
	 while (SDL_PollEvent(&event) != 0)
	 {
		 if (event.type == SDL_QUIT) {	 
			 closeWindow = true;
		 }
		 //User presses a key
		 if (event.type == SDL_KEYDOWN)
		 {
			 //Select surfaces based on key press
			 switch (event.key.keysym.sym)
			 {
			 case SDLK_UP:
				 CheckKeyPress = true;
				 break;
			 default:
				 CheckKeyPress = false;
				 break;
			 }
		 }
	 }
}
 bool Assignment4::GetCloseWindow() {
	 return closeWindow;
}
void Assignment4::Render() {

		//Create the Renderer with the window.
		

		//Set the draw color...
		SDL_SetRenderDrawColor(Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

		//Clear the screen.
		SDL_RenderClear(Renderer);

		//Setting the actual draw color.
		SDL_SetRenderDrawColor(Renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);

		for (int i = 0; i < NUM_BODIES; i++) {
			Vec3 screenCoordsP1 = projectionMatrix  * bodies[i]->P1;
			Vec3 screenCoordsP2 = projectionMatrix  * bodies[i]->P2;
			Vec3 screenCoordsP3 = projectionMatrix  * bodies[i]->P3;

			SDL_RenderDrawLine(Renderer, screenCoordsP1.x, screenCoordsP1.y, screenCoordsP2.x, screenCoordsP2.y);
			SDL_RenderDrawLine(Renderer, screenCoordsP2.x, screenCoordsP2.y, screenCoordsP3.x, screenCoordsP3.y);
			SDL_RenderDrawLine(Renderer, screenCoordsP3.x, screenCoordsP3.y, screenCoordsP1.x, screenCoordsP1.y);
		
		}

		
		//Update the Renderer.
		SDL_RenderPresent(Renderer);
		//SDL_UpdateWindowSurface(window);
}