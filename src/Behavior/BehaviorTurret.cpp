/*!---------------------------------------------------------------------------------------------------------------------
\file   BehaviorTurret.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the BehaviorTurret implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "BehaviorTurret.h"
#include "Input.h"
#include "SoundSystem.h"
#include "BehaviorHomingBullet.h"
#include "BehaviorStraightBullet.h"
#include "BehaviorSystem.h"
#include "TransformSystem.h"
#include "EntitySystem.h"
#include "Engine.h"
#include <string>
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
	float WeaponCooldown = 0.5f;
	float BulletSpeed = 0.05f;
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
BehaviorTurret::BehaviorTurret() :
	Behavior(BehaviorType::BEHAVIOR_TURRET)
{
	TraceDepth(higher);
	TraceMessage("BehaviorTurret Constructing", Debug);
	SetStateCurr(SHOOT_INVALID);
	SetStateNext(SHOOT_IDLE);
	TraceDepth(lower);
	_maxDetectionDistance = 0.5f;
}

BehaviorTurret::BehaviorTurret(unsigned parentID) :
	Behavior(BehaviorType::BEHAVIOR_TURRET, parentID)
{
	TraceDepth(higher);
	TraceMessage("BehaviorTurret Constructing", Debug);
	SetStateCurr(SHOOT_INVALID);
	SetStateNext(SHOOT_IDLE);
	_maxDetectionDistance = 0.5f;
	TraceDepth(lower);
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Destructor
----------------------------------------------------------------------------------------------------------------------*/
BehaviorTurret::~BehaviorTurret()
{
	TraceDepth(higher);
	TraceMessage("BehaviorTurret Destructing", Debug);
	TraceDepth(lower);
}

Behavior::BehaviorType BehaviorTurret::GetProjectileType()
{
	return _projectileType;
}

void BehaviorTurret::SetProjectileType(BehaviorType type)
{
	TraceDepth(higher);
	std::string message = "BehaviorTurret: Setting Projectile Type To " + BehaviorTypeAsString(type);
	TraceMessage(message.c_str(), Debug);
	_projectileType = type;
}

unsigned BehaviorTurret::GetTargetID()
{
	return _targetID;
}

void BehaviorTurret::SetTargetID(unsigned id)
{
	TraceDepth(higher);
	std::string message = "BehaviorTurret: Setting Target ID To ";
	message += id;
	TraceMessage(message.c_str(), Debug);
	_targetID = id;
	TraceDepth(lower);
}

float BehaviorTurret::GetMaxDetectionDistance()
{
	return _maxDetectionDistance;
}

void BehaviorTurret::SetMaxDetectionDistance(float distance)
{
	TraceDepth(higher);
	std::string message = "BehaviorTurret: Setting Max Detection Distance To " + std::to_string(distance);
	TraceMessage(message.c_str(), Debug);
	_maxDetectionDistance = distance;
	TraceDepth(lower);
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Initializes the BehaviorSystemShootStraight

\return int
	Returns 0 if success, anything else if failure
----------------------------------------------------------------------------------------------------------------------*/
void BehaviorTurret::OnInit()
{
	TraceDepth(higher);
	TraceMessage("BehaviorTurret: CurrState OnInit", Debug);
	
	if (GetStateCurr() == SHOOT_IDLE)
	{
		SetTimer(2.0f);
	}
	if (GetStateCurr() == SHOOT_DEAD)
	{
		GameStats* gameStat = (GameStats*)GetSystem("GameStats");
		EntitySystem *entitySys = (EntitySystem*)GetSystem("EntitySystem");
		entitySys->SetDirty(GetParentID());
		gameStat->DecrementNumEnemies();
		gameStat->IncrementScore();
		
	}
	
	TraceDepth(lower);
}

void BehaviorTurret::OnUpdate(float dt)
{
	TraceDepth(higher);
	TraceMessage("BehaviorTurret: CurrState OnUpdate", Debug);

	SoundSystem *soundSys = (SoundSystem*) GetSystem("SoundSystem");
	BehaviorSystem *behaviorSys = (BehaviorSystem*)GetSystem("BehaviorSystem");
	TransformSystem *transformSys = (TransformSystem*)GetSystem("TransformSystem");
	EntitySystem *entitySys = (EntitySystem*)GetSystem("EntitySystem");
	Transform	*myTransform = transformSys->GetComponent(GetParentID());
	Transform *targetTransform = transformSys->GetComponent(_targetID);
	Eigen::Vector3f	myTranslation = myTransform->GetTranslation();
	Eigen::Vector3f targetTranslation = targetTransform->GetTranslation();
	Eigen::Vector3f direction = targetTranslation - myTranslation;
	PhysicsSystem *physicsSys = (PhysicsSystem*)GetSystem("PhysicsSystem");
	Physics	*myPhysics = physicsSys->GetComponent(GetParentID());

	float d = direction.squaredNorm();

	GameStats* gs = (GameStats*)GetSystem("GameStats");

	if (gs->GetGameOver())
	{
		SetStateNext(SHOOT_DEAD);
	}


	switch (GetStateCurr())
	{
	case SHOOT_INVALID:
		SetStateNext(SHOOT_IDLE);
		break;

	case SHOOT_IDLE:
		if (d < _maxDetectionDistance * _maxDetectionDistance)
		{
			SetStateNext(SHOOT_IN_RANGE);
		}
		else
		{
			SetTimer(1.0f);
			SetStateNext(SHOOT_LEFT);
		}

		break;
	case SHOOT_IN_RANGE:
		int id;
		switch (_projectileType)
		{
			case BEHAVIOR_STRAIGHT_BULLET:
				id = entitySys->CreateEntity("StraightBullet", myTranslation.x(), myTranslation.y());
				((BehaviorHomingBullet*)behaviorSys->GetComponent(id))->SetDirection(direction);
				break;

			case BEHAVIOR_HOMING_BULLET:
				id = entitySys->CreateEntity("HomingBullet", myTranslation.x(), myTranslation.y());
				((BehaviorStraightBullet*)behaviorSys->GetComponent(id))->SetDirection(direction);
				break;
		}
		
		myTransform->SetRotationV({ direction[0], direction[1] });
		if (direction.squaredNorm() > _maxDetectionDistance * _maxDetectionDistance)
		{
			SetStateNext(SHOOT_IDLE);
		}
		SetStateNext(SHOOT_COOLDOWN);
		break;

	case SHOOT_COOLDOWN:
		DecrementTimer(dt);
		if (GetTimer() <= 0.0f)
		{
			SetStateNext(SHOOT_IDLE);
		}
		break;

	case SHOOT_LEFT:
		SetTimer(GetTimer() - dt);
		myTransform->SetRotation(myTransform->GetRotation() + 2.5f);
		if (GetTimer() <= 0.0f)
		{
			SetTimer(2.0f);
			SetStateNext(SHOOT_RIGHT);
		}
		if (d < _maxDetectionDistance * _maxDetectionDistance)
		{
			SetStateNext(SHOOT_IN_RANGE);
		}
		break;

	case SHOOT_RIGHT:
		SetTimer(GetTimer() - dt);
		myTransform->SetRotation(myTransform->GetRotation() - 2.5f);
		if (GetTimer() <= 0.0f)
		{
			SetTimer(2.0f);
			SetStateNext(SHOOT_LEFT);
		}
		if (d < _maxDetectionDistance * _maxDetectionDistance)
		{
			SetStateNext(SHOOT_IN_RANGE);
		}
		break;

	case SHOOT_DEAD:
		SetStateNext(SHOOT_INVALID);
		break;
	}
	TraceDepth(lower);
}

void BehaviorTurret::OnExit()
{
	TraceDepth(higher);
	TraceMessage("BehaviorTurret: CurrState OnExit", Debug);
	TraceDepth(lower);
}

void BehaviorTurret::OnCollide(BehaviorType other)
{
	TraceDepth(higher);
	TraceMessage("BehaviorTurret: CurrState OnCollide", Debug);
	if (other == BehaviorType::BEHAVIOR_STRAIGHT_BULLET)
		SetStateNext(SHOOT_DEAD);
	TraceDepth(lower);
}

//----------------------------------------------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------------------------------------------------