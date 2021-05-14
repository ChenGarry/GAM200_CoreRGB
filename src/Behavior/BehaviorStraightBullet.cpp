/*!---------------------------------------------------------------------------------------------------------------------
\file   BehaviorStraightBullet.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the BehaviorStraightBullet implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "BehaviorStraightBullet.h"
#include "Input.h"
#include "SoundSystem.h"
#include "PhysicsSystem.h"
#include "TransformSystem.h"
#include "EntitySystem.h"
#include "Engine.h"
#include "GameStats.h"
#include "ColliderBase.h"
#include "CollisionSystem.h"
//------------------------------------------------------------------------------
// Private Consts:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Structures:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Variables:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Private Variables:
//------------------------------------------------------------------------------
namespace
{
#define PI 3.1415926f  
	float WeaponCooldown = 0.5f;
	float BulletSpeed = 1.5f;


}
//------------------------------------------------------------------------------
// Private Function Declarations:
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Constructor
----------------------------------------------------------------------------------------------------------------------*/

BehaviorStraightBullet::BehaviorStraightBullet(unsigned parentID) :
	Behavior(BehaviorType::BEHAVIOR_STRAIGHT_BULLET, parentID)
{
	TraceDepth(higher);
	TraceMessage("BehaviorStraightBullet Constructing", Debug);
	SetStateCurr(SHOOT_INVALID);
	SetStateNext(SHOOT_MOVING);
	_speed = BulletSpeed;
	TraceDepth(lower);
}

BehaviorStraightBullet::BehaviorStraightBullet() :
	Behavior(BehaviorType::BEHAVIOR_STRAIGHT_BULLET)
{
	TraceDepth(higher);
	TraceMessage("BehaviorStraightBullet Constructing", Debug);
	SetStateCurr(SHOOT_INVALID);
	SetStateNext(SHOOT_MOVING);
	_speed = BulletSpeed;
	TraceDepth(lower);
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Destructor
----------------------------------------------------------------------------------------------------------------------*/
BehaviorStraightBullet::~BehaviorStraightBullet()
{
	TraceDepth(higher);
	TraceMessage("BehaviorStraightBullet Destructing", Debug);
	TraceDepth(lower);
}

float BehaviorStraightBullet::GetSpeed()
{
	return _speed;
}

void BehaviorStraightBullet::SetSpeed(float speed)
{
	TraceDepth(higher);
	std::string message = "BehaviorStraightBullet: Setting Speed To " + std::to_string(speed);
	TraceMessage(message.c_str(), Debug);
	_speed = speed;
	TraceDepth(lower);
}


void  BehaviorStraightBullet::SetLifeTime(float time)
{
	_lifeTime = time;
}

float BehaviorStraightBullet::GetDeathTimer()
{
	return GetTimer();
}

void BehaviorStraightBullet::SetDeathTimer(float time)
{
	TraceDepth(higher);
	std::string message = "BehaviorStraightBullet: Setting Death Timer To " + std::to_string(time) + "s";
	TraceMessage(message.c_str(), Debug);
	SetTimer(time);
	TraceDepth(lower);
}

Eigen::Vector3f BehaviorStraightBullet::GetDirection()
{
	return _direction;
}

void BehaviorStraightBullet::SetDirection(Eigen::Vector3f direction)
{
	TraceDepth(higher);
	std::string message = "BehaviorStraightBullet: Setting Direction To ";
	message += "<" + std::to_string(direction.x()) + ", " + std::to_string(direction.y()) + ", " + std::to_string(direction.z()) + ">";
	TraceMessage(message.c_str(), Debug);
	_direction = direction;
	TraceDepth(lower);
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Initializes the BehaviorSystemShootStraight

\return int
	Returns 0 if success, anything else if failure
----------------------------------------------------------------------------------------------------------------------*/
void BehaviorStraightBullet::OnInit()
{
	TraceDepth(higher);
	TraceMessage("BehaviorStraightBullet: CurrState OnInit", Debug);
	TraceDepth(lower);
	if (GetStateCurr() == SHOOT_DEAD)
	{
		EntitySystem* es = (EntitySystem*)GetSystem("EntitySystem");
		es->SetDirty(GetParentID());
	}
	if (GetStateCurr() == SHOOT_MOVING)
	{
		//SetTimer(0.8f);
		Physics* myPhysics = ((PhysicsSystem*)GetSystem("PhysicsSystem"))->GetComponent(GetParentID());
		myPhysics->SetVelocity(_speed * _direction);
	}
}

void BehaviorStraightBullet::OnUpdate(float dt)
{
	TraceDepth(higher);
	TraceMessage("BehaviorStraightBullet: CurrState OnUpdate", Debug);

	//SoundSystem *soundSys;
	PhysicsSystem *physicsSys;
	Physics *myPhysics;

	GameStats* gs = (GameStats*)GetSystem("GameStats");

	if (gs->GetGameOver())
	{
		SetStateNext(SHOOT_DEAD);
	}

	switch (GetStateCurr())
	{
	case SHOOT_INVALID:
		SetStateNext(SHOOT_MOVING);
		break;

	case SHOOT_MOVING:
		//(((TransformSystem*)GetSystem("TransformSystem"))->GetComponent(GetParentID()))->SetRotation(
		//	_direction.x() != 0.0f ? (_direction.x() == 1.0f ? 0 : 180.0f) : (_direction.y() == 1.0f ? 90.0f : -90.0f));
		SetTimer(GetTimer() - dt);
		if (GetTimer() <= 0.0f)
		{
			SetStateNext(SHOOT_DEAD);
		}
		break;

	case SHOOT_DEAD:
		//soundSys = (SoundSystem*)GetSystem("SoundSystem");
		//soundSys->PlaySoundEffect("Laser", "LaserChannel", false);
		//SetStateNext(SHOOT_INVALID);
		break;
	}

	TraceDepth(lower);
}

void BehaviorStraightBullet::OnExit()
{
	TraceDepth(higher);
	TraceMessage("BehaviorStraightBullet: CurrState OnExit", Debug);
	TraceDepth(lower);
}

void BehaviorStraightBullet::OnCollide(BehaviorType other)
{
	TraceDepth(higher);
	TraceMessage("BehaviorStraightBullet: CurrState OnCollide", Debug);
	if (other != BehaviorType::BEHAVIOR_PLAYER || other != BehaviorType::BEHAVIOR_STRAIGHT_BULLET)
	{
		SetStateNext(SHOOT_DEAD);
		auto collider = ((CollisionSystem*)GetSystem("CollisionSystem"))->GetComponent(GetParentID());
		collider->SetActive(false);
	}
	TraceDepth(lower);
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------