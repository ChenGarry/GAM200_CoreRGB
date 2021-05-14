#ifndef BEHAVIOR_SHOOT_STRAIGHT_H
#define BEHAVIOR_SHOOT_STRAIGHT_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   BehaviorShootStraight.h
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the BehaviorShootStraight interface file.
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
	\class BehaviorShootStraight
	\brief
		The BehaviorShootStraight class initializes, updates, and shutsdown the shooting behavior

		Operations include:

		- Constructor
		- Destructor
		- OnInit
		- OnUpdate
		- OnExit

*///--------------------------------------------------------------------------------------------------------------------
class BehaviorShootStraight : public Behavior
{
public:
	typedef enum
	{
		SHOOT_INVALID = -1,
		SHOOT_IDLE,
		SHOOT_SHOOTING,
		SHOOT_COOLDOWN,
		SHOOT_DEAD,

	}ShootStraightStates;

	BehaviorShootStraight();	//Constructor
	BehaviorShootStraight(unsigned parentID);
	~BehaviorShootStraight();	//Destructor

	void OnInit();				//Initializes the behavior system
	void OnUpdate(float dt);	//Updates the behaviors
	void OnExit();				//Shutsdown the behavior system
	void OnCollide(BehaviorType other) {};

private:
	float _cooldown;
	float _timer;
	bool _isShooting;
	int _dir;
};

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

#endif