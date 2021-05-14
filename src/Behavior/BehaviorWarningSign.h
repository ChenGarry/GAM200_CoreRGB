#ifndef BEHAVIOR_WARNING_SIGN_H
#define BEHAVIOR_WARNING_SIGN_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   BehaviorWarningSign.h
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the BehaviorWarningSign interface file.
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
class BehaviorWarningSign : public Behavior
{
public:
	typedef enum
	{
		WARNING_SIGN_INVALID = -1,
		WARNING_SIGN_WAITING,
		WARNING_SIGN_DEAD,

	}WarningSignStates;

	BehaviorWarningSign(unsigned parentID); //Constructor
	BehaviorWarningSign();					//Constructor
	~BehaviorWarningSign();					//Destructor

	void OnInit();				//Initializes the behavior system
	void OnUpdate(float dt);	//Updates the behaviors
	void OnExit();				//Shutsdown the behavior system
	void OnCollide(BehaviorType other);

private:
};

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

#endif