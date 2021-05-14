#ifndef GAME_LOOP_H
#define GAME_LOOP_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   GameLoop.h
\author Garry Chen
\par    DP email: garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the GameLoop interface file.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Private Consts:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Private Structures:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Private Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Private Function Declarations:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

// Load the resources associated with the Stub game state.
void GameStateGARRYLoad();

// Initialize the memory associated with the Stub game state.
void GameStateGARRYInit();

// Update the Stub game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateGARRYUpdate(float dt);

// Shutdown any memory associated with the Stub game state.
void GameStateGARRYShutdown();

// Unload the resources associated with the Stub game state.
void GameStateGARRYUnload();

void Fullscreen();
void Window();

void Mute();
void UnMute();

void StartControls();
void BackToMenu();
void StartCredits();

void CreateOptions();
void BackToMenu();

//----------------------------------------------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------------------------------------------------

#endif

