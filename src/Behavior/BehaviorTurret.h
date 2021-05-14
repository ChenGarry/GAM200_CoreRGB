#ifndef BEHAVIOR_TURRET_H
#define BEHAVIOR_TURRET_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   BehaviorTurret.h
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the BehaviorTurret interface file.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "Behavior.h"
#include <string>

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
class BehaviorTurret : public Behavior
{
public:
	typedef enum
	{
		SHOOT_INVALID = -1,
		SHOOT_IDLE,
		SHOOT_LEFT,
		SHOOT_RIGHT,
		SHOOT_IN_RANGE,
		SHOOT_DEAD,
		SHOOT_RESTART,

	}ShootStraightStates;

	 BehaviorTurret();	//Constructor
	 BehaviorTurret(unsigned parentID);
	~BehaviorTurret();	//Destructor

	BehaviorType GetProjectileType();
	void SetProjectileType(BehaviorType type);
	unsigned GetTargetID();
	void  SetTargetID(unsigned id);
	float GetMaxDetectionDistance();
	void  SetMaxDetectionDistance(float distance);

	void OnInit();				//Initializes the behavior system
	void OnUpdate(float dt);	//Updates the behaviors
	void OnExit();				//Shutsdown the behavior system
	void OnCollide(BehaviorType other);

private:
	BehaviorType _projectileType;
	unsigned _targetID;
	float _maxDetectionDistance;
};

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

#endif