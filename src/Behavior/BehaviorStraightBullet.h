#ifndef BEHAVIOR_STRAIGHT_BULLET_H
#define BEHAVIOR_STRAIGHT_BULLET_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   BehaviorStraightBullet.h
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the BehaviorStraightBullet interface file.
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
class BehaviorStraightBullet : public Behavior
{
public:
	typedef enum
	{
		SHOOT_INVALID = -1,
		SHOOT_MOVING,
		SHOOT_DEAD,

	}ShootStraightStates;

	BehaviorStraightBullet(unsigned parentID);	//Constructor
	BehaviorStraightBullet();
	~BehaviorStraightBullet();					//Destructor

	float GetSpeed();
	void  SetSpeed(float speed);
	void  SetLifeTime(float time);
	float GetDeathTimer();
	void  SetDeathTimer(float time);
	Eigen::Vector3f GetDirection();
	void						SetDirection(Eigen::Vector3f direction);

	void OnInit();				//Initializes the behavior system
	void OnUpdate(float dt);	//Updates the behaviors
	void OnExit();				//Shutsdown the behavior system
	void OnCollide(BehaviorType other);

private:
	float _speed;
	float _lifeTime;
	Eigen::Vector3f _direction;
};

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

#endif