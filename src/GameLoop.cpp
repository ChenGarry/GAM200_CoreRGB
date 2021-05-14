/*!---------------------------------------------------------------------------------------------------------------------
\file   GameLoop.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the GameLoop implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "Game.h"
#include "GameStats.h"
#include "GameStateManager.h"
#include "Input.h"
#include "Factory.h"
#include "Engine.h"
#include "EntitySystem.h"
#include "SoundSystem.h"
#include "BehaviorSystem.h"
#include "BehaviorMenu.h"
#include "BehaviorButton.h"
#include "Buttons.h"
#include "FrameRateController.h"
#include <iostream>

//----------------------------------------------------------------------------------------------------------------------
// Private Structures:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------
bool windowMode = true;
bool start = false;
bool gameOver = false;
bool wasPaused = false;
float splashTime = 0;
unsigned splashID1;
unsigned splashID2 = 0;
unsigned splashID3 = 0;
unsigned splashNum = 1;
unsigned controlsID;
unsigned creditsID;
unsigned creditsID1;
unsigned creditsID2;
unsigned creditsID3;
unsigned creditsID4;
unsigned whiteID;
unsigned blackID;
bool showingCredits = false;
bool showingControls = false;
bool restarting = false;
float creditsTime = 0;
float volume = 0.7f;
BehaviorMenu* menu;
BehaviorMenu* quitMenu;
Factory* fac;
GameStats* stats;
Input* inputSys;
SoundSystem* soundSys;
BehaviorSystem* behavSys;
EntitySystem* entSys;
SpriteSystem* spriteSys;
TransformSystem* transSys;

//----------------------------------------------------------------------------------------------------------------------
// Private Consts:
//----------------------------------------------------------------------------------------------------------------------
#define _ENABLE_EXTENDED_ALIGNED_STORAGE

//----------------------------------------------------------------------------------------------------------------------
// Private Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Private Function Declarations:
//----------------------------------------------------------------------------------------------------------------------
void CreateMenu();
bool SkipKeyPressed();
void CreateQuitMenu();
void StopControls();
void CreateGameOver();
void CreateGameOverQuitMenu();

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

// Load the resources associated with the Stub game state.
void GameStateGARRYLoad()
{
}

// Initialize the memory associated with the Stub game state.
void GameStateGARRYInit()
{
	gameOver = false;
	wasPaused = false;
	splashTime = 0;
	splashID1;
	splashID2 = 0;
	splashID3 = 0;
	splashNum = 1;
	showingCredits = false;
	showingControls = false;
	creditsTime = 0;
	volume = 0.5f;

	entSys = (EntitySystem*)GetSystem("EntitySystem");
	behavSys = (BehaviorSystem*)GetSystem("BehaviorSystem");
	soundSys = (SoundSystem*)GetSystem("SoundSystem");
	spriteSys = (SpriteSystem*)GetSystem("SpriteSystem");
	inputSys = (Input*)GetSystem("Input");
	stats = (GameStats*)GetSystem("GameStats");
	fac = (Factory*)GetSystem("Factory");
	transSys = (TransformSystem*)GetSystem("TransformSystem");

	if (!start && !restarting)
	{
		whiteID = fac->CreateWhite();
		splashID1 = fac->CreateSplashScreen1();
	}
	else
	{
		GameInit();
		stats->SetGameRunning(true);
	}
	
	soundSys->SetMasterVolume(1.0f * volume);
}

// Update the Stub game state.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameStateGARRYUpdate(float dt)
{
	if (start)
	{
		if (stats->GetGameOver())
		{
			if (!gameOver)
			{
				CreateGameOver();
				gameOver = true;
			}
		}
		else if (!stats->IsPaused())
		{
			if (wasPaused)
			{
				menu->DestructMenu();
				soundSys->SetMasterVolume(1.0f * volume);
				wasPaused = false;
			}
			GameUpdate(dt);
		}
		else
		{

			if (!wasPaused)
			{
				CreateMenu();
				wasPaused = true;
			}
			else if (showingCredits)
			{
				creditsTime += GetFrameDt();
				if (creditsTime > 8)
				{
					Transform* trans = transSys->GetComponent(creditsID4);
					trans->SetTranslation({ -12, -12, 1.0f });
					entSys->SetDirty(creditsID4);
					showingCredits = false;
					CreateMenu();
				}
				else if (creditsTime > 6)
				{
					if (creditsID != creditsID4)
					{
						entSys->SetDirty(creditsID3);
						creditsID4 = fac->CreateCreditsScreen4();
						creditsID = creditsID4;
					}
				}
				else if (creditsTime > 4)
				{
					if (creditsID != creditsID3)
					{
						entSys->SetDirty(creditsID2);
						creditsID3 = fac->CreateCreditsScreen3();
						creditsID = creditsID3;
					}
				}
				else if (creditsTime > 2)
				{
					if (creditsID != creditsID2)
					{
						entSys->SetDirty(creditsID);
						creditsID2 = fac->CreateCreditsScreen2();
						creditsID = creditsID2;
					}
				}
			}
			soundSys->SetMasterVolume(0.2f * volume);
		}
	}
	else
	{
		if (splashTime > 6 || SkipKeyPressed())
		{
			switch (splashNum)
			{
			case 1:
				entSys->SetDirty(whiteID);
				entSys->SetDirty(splashID1);
				break;
			case 2:
				entSys->SetDirty(blackID);
				entSys->SetDirty(splashID2);
				break;
			case 3:
				entSys->SetDirty(whiteID);
				entSys->SetDirty(splashID3);
				break;
			default:
				break;
			}

			
			GameInit(); 
			stats->SetGameRunning(true);
			stats->TogglePause();
			soundSys->PlayMusic("musSong", "MusicChannel", true);
			start = true;
		}
		else
		{
			if (splashTime > 4)
			{
				if (splashID3 == 0)
				{
					entSys->SetDirty(splashID2);
					entSys->SetDirty(blackID);
					whiteID = fac->CreateWhite();
					splashID3 = fac->CreateSplashScreen3();
					++splashNum;
				}
			}
			else if (splashTime > 2)
			{
				if (splashID2 == 0)
				{
					entSys->SetDirty(whiteID);
					entSys->SetDirty(splashID1);

					blackID = fac->CreateBlack();
					splashID2 = fac->CreateSplashScreen2();
					++splashNum;
				}
			}

			splashTime += dt;
		}
	}

	if (inputSys->isTriggered(inputSys->KeyF11))
	{
		GLFWmonitor *monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode *mode = glfwGetVideoMode(monitor);
		

		switch (windowMode)
		{
		case true:
		{
			glfwSetWindowMonitor(glfwGetCurrentContext(), nullptr, 0, 0, 800, 800, 60);
			windowMode = false;
		}
		break;
		case false:
		{
			glfwSetWindowMonitor(glfwGetCurrentContext(), monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
			windowMode = true;
		}
		break;
		}
	}

}

// Shutdown any memory associated with the Stub game state.
void GameStateGARRYShutdown()
{
	GameShutdown();
}

// Unload the resources associated with the Stub game state.
void GameStateGARRYUnload()
{
}

void Window()
{
	glfwSetWindowMonitor(glfwGetCurrentContext(), nullptr, 0, 0, 800, 800, 60);
	windowMode = false;
}

void Fullscreen()
{
	GLFWmonitor *monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode *mode = glfwGetVideoMode(monitor);
	glfwSetWindowMonitor(glfwGetCurrentContext(), monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
	windowMode = true;
}

void BackToMenu()
{
	menu->DestructMenu();
	if (gameOver)
		CreateGameOver();
	else
		CreateMenu();
}

void CreateGameOver()
{
	Factory* fac = (Factory*)GetSystem("Factory");
	BehaviorSystem* behavSys = (BehaviorSystem*)GetSystem("BehaviorSystem");
	unsigned menuID = fac->CreateMenu();

	unsigned ID1 = fac->CreateButtonRestart(0, -0.5);
	unsigned ID2 = fac->CreateButtonExit(0, -0.8);

	menu = (BehaviorMenu*)behavSys->GetComponent(menuID);
	BehaviorButton* _1 = (BehaviorButton*)behavSys->GetComponent(ID1); 
	ButtonExit* _2 = (ButtonExit*)behavSys->GetComponent(ID2);
	_2->SetExecute(CreateGameOverQuitMenu);

	_1->SetUpButton(ID2);
	_1->SetDownButton(ID2);
	_2->SetUpButton(ID1);
	_2->SetDownButton(ID1);

	_1->SetMenu(menuID);
	_2->SetMenu(menuID);
	menu->SetDefault(ID1);
	menu->AddButton(_1);
	menu->AddButton(_2);
}

void CreateOptions()
{
	menu->DestructMenu();

	Factory* fac = (Factory*)GetSystem("Factory");
	BehaviorSystem* behavSys = (BehaviorSystem*)GetSystem("BehaviorSystem");
	unsigned menuID = fac->CreateMenu();

	unsigned ID1 = fac->CreateButtonMute(0, 0.7);
	unsigned ID2 = fac->CreateButtonFullscreen(0, 0.0);
	unsigned ID3 = fac->CreateButtonBack(0, -0.7);

	menu = (BehaviorMenu*)behavSys->GetComponent(menuID);
	BehaviorButton* _1 = (BehaviorButton*)behavSys->GetComponent(ID1);
	BehaviorButton* _2 = (BehaviorButton*)behavSys->GetComponent(ID2);
	ButtonBack* _3 = (ButtonBack*)behavSys->GetComponent(ID3);
	_3->SetExecute(BackToMenu);

	_1->SetUpButton(ID3);
	_1->SetDownButton(ID2);
	_2->SetUpButton(ID1);
	_2->SetDownButton(ID3);
	_3->SetUpButton(ID2);
	_3->SetDownButton(ID1);

	_1->SetMenu(menuID);
	_2->SetMenu(menuID);
	_3->SetMenu(menuID);
	menu->SetDefault(ID1);
	menu->AddButton(_1);
	menu->AddButton(_2);
	menu->AddButton(_3);
}

void StartCredits()
{
	menu->DestructMenu();
	creditsID = fac->CreateCreditsScreen1();
	showingCredits = true;
	creditsTime = 0;
}

void StopControls()
{
	menu->DestructMenu();
	entSys->SetDirty(controlsID);
	CreateMenu();
}

void StartControls()
{
	menu->DestructMenu();
	controlsID = fac->CreateControlsScreen(0, 0);
	unsigned menuID = fac->CreateMenu();
	unsigned ID1 = fac->CreateButtonBack(0, -0.85);

	menu = (BehaviorMenu*)behavSys->GetComponent(menuID);
	ButtonBack* _1 = (ButtonBack*)behavSys->GetComponent(ID1);
	_1->SetExecute(StopControls);

	_1->SetMenu(menuID);
	menu->SetDefault(ID1);
	menu->AddButton(_1);
}

void Mute()
{
	volume = 0.0f;
}

void UnMute()
{
	volume = 0.7f;
}

//----------------------------------------------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------------------------------------------------

bool SkipKeyPressed()
{
	return inputSys->isTriggered(inputSys->KeyEnter) 
		|| inputSys->isTriggered(inputSys->KeySpace) 
		|| inputSys->isTriggered(inputSys->KeyEsc);
}

void CreateMenu()
{
	if (showingControls)
	{
		entSys->SetDirty(controlsID);
		showingControls = false;
	}

	unsigned menuID = fac->CreateMenu();
	unsigned ID1;

	if(Game::GameIsStart())
		ID1 = fac->CreateButtonResume(0, 0.8);
	else
	{
		ID1 = fac->CreateButtonStart(0, 0.8);
		//createPauseVer = true;
	}

	unsigned ID2 = fac->CreateButtonOptions(0, 0.4);
	unsigned ID3 = fac->CreateButtonControls(0, 0.0);
	unsigned ID4 = fac->CreateButtonCredits(0, -0.4);
	unsigned ID5 = fac->CreateButtonExit(0, -0.8);

	menu = (BehaviorMenu*)behavSys->GetComponent(menuID);
	BehaviorButton* _1 = (BehaviorButton*)behavSys->GetComponent(ID1);
	BehaviorButton* _2 = (BehaviorButton*)behavSys->GetComponent(ID2);
	BehaviorButton* _3 = (BehaviorButton*)behavSys->GetComponent(ID3);
	BehaviorButton* _4 = (BehaviorButton*)behavSys->GetComponent(ID4);
	ButtonExit* _5 = (ButtonExit*)behavSys->GetComponent(ID5);
	_5->SetExecute(CreateQuitMenu);

	_1->SetUpButton(ID5);
	_1->SetDownButton(ID2);
	_2->SetUpButton(ID1);
	_2->SetDownButton(ID3);
	_3->SetUpButton(ID2);
	_3->SetDownButton(ID4);
	_4->SetUpButton(ID3);
	_4->SetDownButton(ID5);
	_5->SetUpButton(ID4);
	_5->SetDownButton(ID1);

	_1->SetMenu(menuID);
	_2->SetMenu(menuID);
	_3->SetMenu(menuID);
	_4->SetMenu(menuID);
	_5->SetMenu(menuID);
	menu->SetDefault(ID1);
	menu->AddButton(_1);
	menu->AddButton(_2);
	menu->AddButton(_3);
	menu->AddButton(_4);
	menu->AddButton(_5);
}

void CreateQuitMenu()
{
	unsigned quitID = fac->CreateMenu();
	unsigned ID1 = fac->CreateButtonYes(0.3, 0);
	unsigned ID2 = fac->CreateButtonNo(-0.3, 0);

	quitMenu = (BehaviorMenu*)behavSys->GetComponent(quitID);
	BehaviorButton* _1 = (BehaviorButton*)behavSys->GetComponent(ID1);
	ButtonNo* _2 = (ButtonNo*)behavSys->GetComponent(ID2);
	_2->SetExecute(CreateMenu);

	_1->SetLeftButton(ID2);
	_1->SetRightButton(ID2);
	_2->SetLeftButton(ID1);
	_2->SetRightButton(ID1);

	_1->SetMenu(quitID);
	_2->SetMenu(quitID);
	quitMenu->SetDefault(ID2);
	quitMenu->AddButton(_1);
	quitMenu->AddButton(_2);
}

void CreateGameOverQuitMenu()
{
	unsigned quitID = fac->CreateMenu();
	unsigned ID1 = fac->CreateButtonYes(0.3, 0);
	unsigned ID2 = fac->CreateButtonNo(-0.3, 0);

	quitMenu = (BehaviorMenu*)behavSys->GetComponent(quitID);
	BehaviorButton* _1 = (BehaviorButton*)behavSys->GetComponent(ID1);
	ButtonNo* _2 = (ButtonNo*)behavSys->GetComponent(ID2);
	_2->SetExecute(CreateGameOver);

	_1->SetLeftButton(ID2);
	_1->SetRightButton(ID2);
	_2->SetLeftButton(ID1);
	_2->SetRightButton(ID1);

	_1->SetMenu(quitID);
	_2->SetMenu(quitID);
	quitMenu->SetDefault(ID2);
	quitMenu->AddButton(_1);
	quitMenu->AddButton(_2);
}