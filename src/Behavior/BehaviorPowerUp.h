#ifndef BEHAVIOR_POWER_UP_H
#define BEHAVIOR_POWER_UP_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   BehaviorPowerUp.h
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the BehaviorPowerUp interface file.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "Behavior.h"

//----------------------------------------------------------------------------------------------------------------------
// Forward References:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Consts:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Structures:
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*!
	\class BehaviorPowerUp
	\brief
		The BehaviorPowerUp class initializes, updates, and shutsdown the shooting behavior

		Operations include:

		- Constructor
		- Destructor
		- OnInit
		- OnUpdate
		- OnExit

*///--------------------------------------------------------------------------------------------------------------------
class BehaviorPowerUp : public Behavior
{
public:
	typedef enum
	{
		POWERUP_INVALID = -1,
		POWERUP_NORMAL,
		POWERUP_DEAD,
		POWERUP_SPAWN,

	}PowerUpStates;

	BehaviorPowerUp(unsigned parentID);	//Constructor
	BehaviorPowerUp();
	~BehaviorPowerUp();					//Destructor

	void SetLifeTime(float time);

	void OnInit();				//Initializes the behavior system
	void OnUpdate(float dt);	//Updates the behaviors
	void OnExit();				//Shutsdown the behavior system
	void OnCollide(BehaviorType other);

private:
	float _lifeTime;
};

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

#endif