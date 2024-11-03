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

#include <vector>

#include "View.h"
#include "Machine.h"
#include "TalkBox.h"
#include "Tutorial.h"

static TutorialState tutState{TutorialState::START_1};
static Machine machine(screenWidth, screenHeight);
static std::vector<int> unlitPorts;

static void lightNextPort() {
	Port port{0, *unlitPorts.begin()};
	Extension* ext = machine.getExtension(port);
	ext->setLight(true);
	unlitPorts.erase(unlitPorts.begin());
}

static void lightPort(int portNum) {
	Port port{0, portNum};
	Extension* ext = machine.getExtension(port);
	ext->setLight(true);
}

static void unlightPort(int portNum) {
	Port port{0, portNum};
	Extension* ext = machine.getExtension(port);
	ext->setLight(false);
}

static void SetTalkBox(TutorialState tutState) {
	Message msg = tutorialMessages[tutState];
	SetTalkBox(msg.speaker, msg.text);
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
#if !defined(_DEBUG)
    SetTraceLogLevel(LOG_DEBUG);         // Disable raylib trace log messages
#endif

    // Initialization
    //--------------------------------------------------------------------------------------
	// Non-repeating, random initialization of the unlitPorts vector
	std::vector<int> initNums{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};
	int initNumsStartSize = initNums.size();
	while (unlitPorts.size() < initNumsStartSize) {
		int index{0};
		int select = GetRandomValue(0, initNums.size());
		for (auto it = initNums.begin(); it != initNums.end();) {
			if (index == select) {
				unlitPorts.push_back(*it);
				it = initNums.erase(it);
			} else {
				++it;
			}
			++index;
		}
	}

    InitWindow(screenWidth, screenHeight, "raylib gamejam template");
    // TODO: Load resources / Initialize variables at this point
	ResizeTalkBox(700, 70);
	SetTalkBox(tutState);

	machine.addPanel(3, 10);
	machine.addCordCircuit();
	machine.shift(0, -38);

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

static PhoneJack* grabbedJack{nullptr};

//--------------------------------------------------------------------------------------------
// Module functions definition
//--------------------------------------------------------------------------------------------

static void jackMoveAndPlug() {
	grabbedJack->move(GetMouseX(), GetMouseY());
	if (!IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		Port port = machine.getPortClicked(GetMouseX(), GetMouseY());
		Extension* ext = machine.getExtension(port);

		if (ext) {
			// Check if extension already is full
			if (!ext->getJack()) {
				grabbedJack->connect(ext);
			} else {
				grabbedJack->disconnect();
			}
		} else {
			grabbedJack->disconnect();
		}

		grabbedJack = nullptr;
	}
}

static void HandleControls(ControlType type = ControlType::NONE) {
	if (!grabbedJack) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Control clicked = machine.getControlClicked(GetMouseX(), GetMouseY());
			ControlPtr control = machine.getControl(clicked);
			if (control.ptr) {
				if (type == control.type || type == ControlType::NONE) {
					if (control.type == ControlType::JACK1 || control.type == ControlType::JACK2) {
						if (type == control.type || type == ControlType::NONE) {
							grabbedJack = (PhoneJack*)control.ptr;
							grabbedJack->grab();
						}
					} else if (control.type == ControlType::SW1 || control.type == ControlType::SW2) {
						CircuitSwitch* switchPtr = (CircuitSwitch*)control.ptr;
						SwitchSection section = switchPtr->getSection(GetMouseX(), GetMouseY());
						if (section.valid) {
							switchPtr->state = section.state;
						}
					}
				}
			}
		}
	} else {
		jackMoveAndPlug();
	}
}

static void NextTutorialMessage() {
	tutState = (TutorialState)(((int)tutState) + 1);
	SetTalkBox(tutState);
}

static void NextTutorialMessageWait() {
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		NextTutorialMessage();
	}
}

bool isRed(PhoneJack* jack) {
	return jack->color == 1;
}

// Update and draw frame
void UpdateDrawFrame(void)
{
    // Update
	switch(tutState) {
		case TutorialState::START_1:
		case TutorialState::START_2:
			NextTutorialMessageWait();
			break;
		case TutorialState::LIGHT:
			NextTutorialMessageWait();
			lightPort(11);
			break;
		case TutorialState::CONNECT_1:
			{
				HandleControls(ControlType::JACK1);
				Port port{0, 11};
				Extension* ext = machine.getExtension(port);
				if (ext->getJack()) {
					if (!isRed(ext->getJack())) {
						NextTutorialMessage();
					}
				}
			}
			break;
		case TutorialState::SWITCH_TOP:
			{
				HandleControls(ControlType::SW1);
				Port port{0, 11};
				Extension* ext = machine.getExtension(port);
				if (ext->getJack()) {
					Control control{0, ControlType::SW1};
					ControlPtr ctrlPtr = machine.getControl(control);
					CircuitSwitch* switchPtr = (CircuitSwitch*)ctrlPtr.ptr;

					if (switchPtr->state == SwitchState::TOP) {
						NextTutorialMessage();
					}
				}
			}
			break;
		case TutorialState::CALLER_1:
		case TutorialState::RESPONSE_1:
		case TutorialState::LOOKUP_1:
		case TutorialState::LOOKUP_2:
		case TutorialState::LOOKUP_3:
			NextTutorialMessageWait();
			break;
		case TutorialState::CONNECT_2:
			{
				HandleControls(ControlType::JACK2);
				Port port{0, 23};
				Extension* ext = machine.getExtension(port);
				if (ext->getJack()) {
					if (isRed(ext->getJack())) {
						NextTutorialMessage();
					}
				}
			}
			break;
		case TutorialState::SWITCH_BTM:
			{
				HandleControls(ControlType::SW2);
				Port port{0, 23};
				Extension* ext = machine.getExtension(port);
				if (ext->getJack()) {
					Control control{0, ControlType::SW2};
					ControlPtr ctrlPtr = machine.getControl(control);
					CircuitSwitch* switchPtr = (CircuitSwitch*)ctrlPtr.ptr;

					if (switchPtr->state == SwitchState::BOTTOM) {
						NextTutorialMessage();
					}
				}
			}
			break;
		case TutorialState::RINGING:
		case TutorialState::RESPONSE_2:
			NextTutorialMessageWait();
			break;
		case TutorialState::PICKUP_1:
			{
				lightPort(23);
				HandleControls(ControlType::SW2);
				Port port{0, 23};
				Extension* ext = machine.getExtension(port);
				if (ext->getJack()) {
					Control control{0, ControlType::SW2};
					ControlPtr ctrlPtr = machine.getControl(control);
					CircuitSwitch* switchPtr = (CircuitSwitch*)ctrlPtr.ptr;

					if (switchPtr->state == SwitchState::TOP) {
						NextTutorialMessage();
					}
				}
			}
			break;
		case TutorialState::PICKUP_2:
		case TutorialState::CALLER_2:
			NextTutorialMessageWait();
			break;
		case TutorialState::SWITCH_MID:
			{
				HandleControls(ControlType::SW1);
				HandleControls(ControlType::SW2);
				Port port{0, 11};
				Extension* ext = machine.getExtension(port);
				if (ext->getJack()) {
					Control sw1{0, ControlType::SW1};
					ControlPtr sw1Ptr = machine.getControl(sw1);
					CircuitSwitch* switch1Ptr = (CircuitSwitch*)sw1Ptr.ptr;

					Control sw2{0, ControlType::SW2};
					ControlPtr sw2Ptr = machine.getControl(sw2);
					CircuitSwitch* switch2Ptr = (CircuitSwitch*)sw2Ptr.ptr;

					if (switch1Ptr->state == SwitchState::MIDDLE && switch2Ptr->state == SwitchState::MIDDLE) {
						NextTutorialMessage();
					}
				}
			}
			break;
		case TutorialState::WAITING_1:
		case TutorialState::WAITING_2:
		case TutorialState::WAITING_3:
		case TutorialState::WAITING_4:
		case TutorialState::WAITING_5:
			NextTutorialMessageWait();
			break;
		case TutorialState::WAITING_6:
			unlightPort(11);
			unlightPort(23);
			NextTutorialMessageWait();
			break;
		case TutorialState::DISCONNECT:
			{
				HandleControls(ControlType::JACK1);
				HandleControls(ControlType::JACK2);
				Port port1{0, 11};
				Port port2{0, 23};
				Extension* ext1 = machine.getExtension(port1);
				Extension* ext2 = machine.getExtension(port2);
				if (!ext1->getJack() && !ext2->getJack()) {
					NextTutorialMessage();
				}
			}
			break;
		case TutorialState::FINISH_1:
		case TutorialState::FINISH_2:
		case TutorialState::FINISH_3:
		case TutorialState::FINISH_4:
		case TutorialState::FINISH_5:
			NextTutorialMessageWait();
			break;
		case TutorialState::FINISH_6:
			NextTutorialMessageWait();
			machine.addCordCircuit();
			machine.addCordCircuit();
			machine.addCordCircuit();
			break;
		case TutorialState::END:
			break;
		case TutorialState::GAME_OVER:
			SetTalkBox(TutorialState::GAME_OVER);
			break;
	}

    // Draw
    BeginTextureMode(target);
        ClearBackground(BLACK);
		machine.draw();
		DrawTalkBox();
    EndTextureMode();

    // Render to screen (main framebuffer)
    BeginDrawing();
        ClearBackground(RAYWHITE);
        // Draw render texture to screen, scaled if required
        DrawTexturePro(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, -(float)target.texture.height }, (Rectangle){ 0, 0, (float)target.texture.width, (float)target.texture.height }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    EndDrawing();
    //----------------------------------------------------------------------------------  
}
