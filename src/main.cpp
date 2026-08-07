/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include <iostream>
#include <string>

#include "Physics/CollisionManager.h"
#include "CameraController.h"






int main()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(800, 600, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	CollisionManager colManager = CollisionManager{};

	// TODO - Seperate this stuff into a seperate scene class
	AABB bodyTestAABB = { Rectangle{0, 0, 32, 32}, false };
	PhysicsBody* bodyTest = colManager.CreatePhysicsBody<PhysicsBody>(bodyTestAABB);
	bodyTest->m_velocity = {100, 100};


	AABB staticAABB = { Rectangle{0, 400, 800, 100}, true };
	PhysicsBody* staticBody = colManager.CreatePhysicsBody<PhysicsBody>(staticAABB);
	staticBody->m_usesGravity = false;
	
	CameraController camController = CameraController();

	PhysicsBody* _highlightedBody = nullptr;

	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{
		colManager.UpdatePhysicsWorld();

		if (IsKeyPressed(KEY_Q)) {
			for (int i = 0; i <= 20; i++) {
				PhysicsBody* body = colManager.CreatePhysicsBody<PhysicsBody>(AABB{Rectangle{0,0,32,32}, false});
				body->SetPositon({(float)GetRandomValue(0, 750), (float)GetRandomValue(0, 50)});

				body->m_physicsProperties.m_bouncy = (float)GetRandomValue(1, 99) / 100.0f;
				body->m_physicsProperties.m_mass = (float)GetRandomValue(1, 199) / 100.0f;
			}
		}

		if (IsKeyPressed(KEY_SPACE)) colManager.m_pausePhysics = !colManager.m_pausePhysics;
		
		PhysicsBody* _hoveredBody = colManager.GetBodyAtPoint(camController.m_camera.ScreenToWorldPosition(GetMousePosition()));

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			_highlightedBody = _hoveredBody;
			
		}
		

		camController.Update();

		// drawing
		BeginDrawing();

		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);

		BeginMode2D(camController.m_camera.m_camera2D);

			colManager.DrawColliders();

			if (_highlightedBody) {
				DebugDraw::DrawHighlight(_highlightedBody);
			}

			if (_hoveredBody) {
				DebugDraw::DrawHighlight(_hoveredBody);
			}

		EndMode2D();

		DrawFPS(0,0);

		DrawText( std::to_string(colManager.GetBodyCount()).c_str(), 0, 30, 20, GREEN);

		if (colManager.m_pausePhysics) {
			DrawText("SIMULATION PAUSED", (GetScreenWidth() * 0.5f) - 200, 0, 40, RED);
		}

		if (_highlightedBody) {
			DebugDraw::DrawDebugMenu(_highlightedBody);
		}

		
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}

	// cleanup

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
