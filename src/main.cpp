/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir
#include "CollisionManager.h"

#include <iostream>

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(800, 600, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	CollisionManager colManager = CollisionManager{};

	PhysicsBody* bodyTest = colManager.CreatePhysicsBody<PhysicsBody>(AABB{Rectangle{0,0,32,32}, false});	
	bodyTest->m_velocity = {100, 100};
	PhysicsBody* staticBody = colManager.CreatePhysicsBody<PhysicsBody>(AABB{Rectangle{0,400,800,100}, true});	
	staticBody->m_usesGravity = false;
	
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		colManager.UpdatePhysicsWorld();

		if (IsKeyPressed(KEY_SPACE)) {
			for (int i = 0; i <= 20; i++) {
				PhysicsBody* body = colManager.CreatePhysicsBody<PhysicsBody>(AABB{Rectangle{0,0,32,32}, false});
				body->SetPositon({(float)GetRandomValue(0, 750), (float)GetRandomValue(0, 50)});
			}
		}

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		colManager.DrawColliders();

		DrawFPS(0,0);

		DrawText( std::to_string(colManager.GetBodyCount()).c_str(), 0, 30, 20, GREEN);
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
