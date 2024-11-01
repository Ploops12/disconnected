/*******************************************************************************************
*
*   raylib gamejam template
*
*   Template originally created with raylib 4.5-dev, last time updated with raylib 5.0
*
*   Template licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"

#if defined(PLATFORM_WEB)
    #define CUSTOM_MODAL_DIALOGS            // Force custom modal dialogs usage
    #include <emscripten/emscripten.h>      // Emscripten library - LLVM to JavaScript compiler
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
// Simple log system to avoid printf() calls if required
// NOTE: Avoiding those calls, also avoids const strings memory usage
#define SUPPORT_LOG_INFO
#if defined(SUPPORT_LOG_INFO)
    #define LOG(...) printf(__VA_ARGS__)
#else
    #define LOG(...)
#endif

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
typedef enum {
    SCREEN_LOGO = 0,
    SCREEN_TITLE,
    SCREEN_GAMEPLAY,
    SCREEN_ENDING
} GameScreen;

// TODO: Define your custom data types here

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
static const int screenWidth = 800;
static const int screenHeight = 450;

static RenderTexture2D target = { 0 };  // Render texture to render our game

// TODO: Define global variables here, recommended to make them static

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
static void UpdateDrawFrame(void);      // Update and Draw one frame

#include "View.h"
#include "Machine.h"
#include "TalkBox.h"

Machine machine(screenWidth, screenHeight);
View<Machine> view(&machine);

TalkBox talkbox{700, 150, "This is a test message", true};
View<TalkBox> talk_view(&talkbox);

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
#if !defined(_DEBUG)
    SetTraceLogLevel(LOG_NONE);         // Disable raylib trace log messages
#endif

    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "raylib gamejam template");
    // TODO: Load resources / Initialize variables at this point

	machine.addPanel(3, 8);
	machine.addPanel(2, 2);
	machine.addCordCircuit();
	machine.addCordCircuit();
	machine.addCordCircuit();
//	machine.move(0,0);

    // Render texture to draw full screen, enables screen scaling
    // NOTE: If screen is scaled, mouse input should be scaled proportionally
    target = LoadRenderTexture(screenWidth, screenHeight);
    SetTextureFilter(target.texture, TEXTURE_FILTER_BILINEAR);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);     // Set our game frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button
    {
        UpdateDrawFrame();
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadRenderTexture(target);
    // TODO: Unload all loaded resources at this point

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

#include <iostream>

bool jackGrabState{false};
PhoneJack* grabbedJack{nullptr};

//--------------------------------------------------------------------------------------------
// Module functions definition
//--------------------------------------------------------------------------------------------
// Update and draw frame
void UpdateDrawFrame(void)
{
    // Update
	if (jackGrabState) {
		grabbedJack->move(GetMouseX(), GetMouseY());
		if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
			Port port = machine.getPortClicked(GetMouseX(), GetMouseY());
			Extension* ext = machine.getExtension(port);
			jackGrabState = false;

			if (ext) {
				if (!ext->getJack() && ext->intersect(GetMouseX(), GetMouseY())) {
					grabbedJack->setPort(port);
					ext->insert(grabbedJack);
					grabbedJack->move(ext->getPortCenter().x, ext->getPortCenter().y);
				} else {
					grabbedJack->disconnect();
					grabbedJack->setGrab(false);
				}
			} else {
				if (grabbedJack->getPort().portNum != -1) {
					Extension* ext2 = machine.getExtension(grabbedJack->getPort());
					ext2->disconnect();
				}
				grabbedJack->disconnect();
				grabbedJack->setGrab(false);
			}
		}
	} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		talkbox.visible = false;
		Control clicked = machine.getControlClicked(GetMouseX(), GetMouseY());
		ControlPtr control = machine.getControl(clicked);
		if (control.ptr) {
			if (control.type == ControlType::JACK1 || control.type == ControlType::JACK2) {
				jackGrabState = true;
				grabbedJack = (PhoneJack*)control.ptr;
				grabbedJack->setGrab(true);
			} else {
				SwitchState state;
				CircuitSwitch* switchPtr = (CircuitSwitch*)control.ptr;
				switch(control.type) {
					case ControlType::SW1_T:
						state = SwitchState::TOP;
						break;
					case ControlType::SW1_M:
						state = SwitchState::MIDDLE;
						break;
					case ControlType::SW1_B:
						state = SwitchState::BOTTOM;
						break;
					case ControlType::SW2_T:
						state = SwitchState::TOP;
						break;
					case ControlType::SW2_M:
						state = SwitchState::MIDDLE;
						break;
					case ControlType::SW2_B:
						state = SwitchState::BOTTOM;
						break;
				}

				switchPtr->state = state;
			}
		}
	}

    // Draw
    BeginTextureMode(target);
        ClearBackground(BLACK);
		view.draw();
		if (talkbox.visible) {
			talk_view.draw();
		}
    EndTextureMode();

    // Render to screen (main framebuffer)
    BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw render texture to screen, scaled if required
        DrawTexturePro(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height }, (Rectangle){ 0, 0, (float)target.texture.width, (float)target.texture.height }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    EndDrawing();
    //----------------------------------------------------------------------------------  
}
