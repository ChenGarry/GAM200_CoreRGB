#ifndef BEHAVIOR_LASER_H
#define BEHAVIOR_LASER_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   BehaviorLaser.h
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the BehaviorLaser interface file.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "Behavior.h"
#include <Eigen/Dense>

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
class BehaviorLaser : public Behavior
{
public:
	typedef enum
	{
		SHOOT_INVALID = -1,
		SHOOT_NORMAL,
		SHOOT_COLLIDE,
		SHOOT_DEAD,
		SHOOT_RESTART,

	}LaserStates;

	BehaviorLaser(unsigned parentID);	//Constructor
	BehaviorLaser();
	~BehaviorLaser();					//Destructor

	void SetLifeTime(float time);
	void SetShooterId(unsigned shooterId);
	Eigen::Vector3f GetDirection();
	void SetDirection(Eigen::Vector3f direction);

	void OnInit();				//Initializes the behavior system
	void OnUpdate(float dt);	//Updates the behaviors
	void OnExit();				//Shutsdown the behavior system
	void OnCollide(BehaviorType other);

private:
	unsigned _shooterId;
	float _lifeTime;
	Eigen::Vector3f _direction;

	void UpdateLaser(float dt);
};

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

#endif