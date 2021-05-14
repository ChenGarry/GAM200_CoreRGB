/*!---------------------------------------------------------------------------------------------------------------------
\file   BehaviorLaser.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the BehaviorLaser implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "BehaviorLaser.h"
#include "Input.h"
#include "SoundSystem.h"
#include "CollisionSystem.h"
#include "ColliderRect.h"
#include "PhysicsSystem.h"
#include "TransformSystem.h"
#include "EntitySystem.h"
#include "Engine.h"
#include "GameStats.h"

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
namespace
{
#define PI 3.1415926f  
	float WeaponCooldown = 1.5f;
	float halflife = 0.33f;
	float duration = 2.1f;
}

//----------------------------------------------------------------------------------------------------------------------
// Private Function Declarations:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Constructor
----------------------------------------------------------------------------------------------------------------------*/
BehaviorLaser::BehaviorLaser(unsigned parentID) :
	Behavior(BehaviorType::BEHAVIOR_STRAIGHT_BULLET, parentID),
	_lifeTime(duration)
{
	TraceDepth(higher);
	TraceMessage("BehaviorLaser Constructing", Debug);
	SetStateCurr(SHOOT_INVALID);
	SetStateNext(SHOOT_NORMAL);
	TraceDepth(lower);
}

BehaviorLaser::BehaviorLaser() :
	Behavior(BehaviorType::BEHAVIOR_STRAIGHT_BULLET),
	_lifeTime(duration)
{
	TraceDepth(higher);
	TraceMessage("BehaviorLaser Constructing", Debug);
	SetStateCurr(SHOOT_INVALID);
	SetStateNext(SHOOT_NORMAL);
	TraceDepth(lower);
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Destructor
----------------------------------------------------------------------------------------------------------------------*/
BehaviorLaser::~BehaviorLaser()
{
	TraceDepth(higher);
	TraceMessage("BehaviorLaser Destructing", Debug);
	TraceDepth(lower);
}

void  BehaviorLaser::SetLifeTime(float time)
{
	_lifeTime = time;
}

void  BehaviorLaser::SetShooterId(unsigned shooterId)
{
	_shooterId = shooterId;
}

Eigen::Vector3f BehaviorLaser::GetDirection()
{
	return _direction;
}

void BehaviorLaser::SetDirection(Eigen::Vector3f direction)
{
	_direction = direction;
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Initializes the BehaviorSystemShootStraight

\return int
	Returns 0 if success, anything else if failure
----------------------------------------------------------------------------------------------------------------------*/
void BehaviorLaser::OnInit()
{
	if (GetStateCurr() == SHOOT_DEAD)
	{
		EntitySystem* es = (EntitySystem*)GetSystem("EntitySystem");
		es->SetDirty(GetParentID());
	}
	else if (GetStateCurr() == SHOOT_NORMAL)
	{
		Physics* myPhysics = ((PhysicsSystem*)GetSystem("PhysicsSystem"))->GetComponent(GetParentID());
	}
}

void BehaviorLaser::OnUpdate(float dt)
{
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
		SetStateNext(SHOOT_NORMAL);
		break;

	case SHOOT_NORMAL:
		BehaviorLaser::UpdateLaser(dt);
		break;

	case SHOOT_COLLIDE:
		break;

	case SHOOT_DEAD:
		break;
	}

	TraceDepth(lower);
}

void BehaviorLaser::OnExit()
{
	if (GetStateCurr() == SHOOT_INVALID)
	{
		SetTimer(_lifeTime);
	}
}

void BehaviorLaser::OnCollide(BehaviorType other)
{
}

//----------------------------------------------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------------------------------------------------
namespace
{

#define degreeToRad 0.0174533
}
void  BehaviorLaser::UpdateLaser(float dt)
{
	SetTimer(GetTimer() - dt);
	float cur_time = GetTimer();
	if (cur_time <= 0.0f)
	{
		SetStateNext(SHOOT_DEAD);
	}
	else
	{
		Transform* transform = ((TransformSystem*)GetSystem("TransformSystem"))->GetComponent(GetParentID());
		Transform* shooterTransform = ((TransformSystem*)GetSystem("TransformSystem"))->GetComponent(_shooterId);
		ColliderRect* collider = reinterpret_cast<ColliderRect*>(((CollisionSystem*)GetSystem("CollisionSystem"))
																					->GetComponent(GetParentID()));
		auto scale = transform->GetScale();

		if (cur_time <= _lifeTime * halflife * 0.5f)
		{

		}
		else if (cur_time <= _lifeTime * halflife)
		{
			scale.y() *= halflife * 1.5;
			transform->SetScale(scale);
		}
		else if (cur_time <= _lifeTime * halflife * 2)
		{
			scale.y() *= halflife * 2.5;
			collider->SetHeight(collider->GetHeight() * 0.9f);
			transform->SetScale(scale);
		}
		
		if (scale.y() < 0.1f)
		{
			cur_time = 0.0f;
		}


		float rotation = shooterTransform->GetRotation();
		float length = 10.0f;
		Eigen::Vector2f dir(cos(rotation*degreeToRad), sin(rotation*degreeToRad));
		dir.normalize();
		transform->SetRotation(rotation);

		auto translate = shooterTransform->GetTranslation();

		translate.x() += dir.x() * (length / 2 + 0.15f);
		translate.y() += dir.y() * (length / 2 + 0.15f);
		transform->SetTranslation(translate);

		
		if (dir.y() > 0.8f) // up 
		{
			collider->SetBH(scale.y(), scale.x());
		}
		else if(dir.y() < -0.8f) // down
		{
			collider->SetBH(scale.y(), -scale.x());
		}
		else if (dir.x() > 0.8f) // right
		{
			collider->SetBH(scale.x(), scale.y());
		}
		else // left
		{
			collider->SetBH(-scale.x(), scale.y());
		}
		
	}

}