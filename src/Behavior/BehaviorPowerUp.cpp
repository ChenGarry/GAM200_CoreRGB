/*!---------------------------------------------------------------------------------------------------------------------
\file   BehaviorPowerUp.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the BehaviorPowerUp implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "BehaviorPowerUp.h"
#include "SoundSystem.h"
#include "CollisionSystem.h"
#include "ColliderRect.h"
#include "PhysicsSystem.h"
#include "TransformSystem.h"
#include "EntitySystem.h"
#include "Engine.h"
#include "TraceSystem.h"
#include "GameStats.h"
#include "Particle.h"
#include "ParticleSystem.h"

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
	float duration = 3.0f;
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

BehaviorPowerUp::BehaviorPowerUp(unsigned parentID) :
	Behavior(BehaviorType::BEHAVIOR_POWERUP, parentID),
	_lifeTime(duration)
{
	TraceDepth(higher);
	TraceMessage("BehaviorPowerUp Constructing", Debug);
	SetStateCurr(POWERUP_INVALID);
	SetStateNext(POWERUP_SPAWN);
	TraceDepth(lower);
}

BehaviorPowerUp::BehaviorPowerUp() :
	Behavior(BehaviorType::BEHAVIOR_STRAIGHT_BULLET),
	_lifeTime(duration)
{
	TraceDepth(higher);
	TraceMessage("BehaviorPowerUp Constructing", Debug);
	SetStateCurr(POWERUP_INVALID);
	SetStateNext(POWERUP_SPAWN);
	TraceDepth(lower);
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Destructor
----------------------------------------------------------------------------------------------------------------------*/
BehaviorPowerUp::~BehaviorPowerUp()
{
	TraceDepth(higher);
	TraceMessage("BehaviorPowerUp Destructing", Debug);
	TraceDepth(lower);
}



void  BehaviorPowerUp::SetLifeTime(float time)
{
	_lifeTime = time;
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Initializes the BehaviorSystemShootStraight

\return int
	Returns 0 if success, anything else if failure
----------------------------------------------------------------------------------------------------------------------*/
void BehaviorPowerUp::OnInit()
{
	if (GetStateCurr() == POWERUP_DEAD)
	{
		EntitySystem* es = (EntitySystem*)GetSystem("EntitySystem");
		es->SetDirty(GetParentID());
	}
}

void BehaviorPowerUp::OnUpdate(float dt)
{
	GameStats* gs = (GameStats*)GetSystem("GameStats");
	ParticleSystem* pS = (ParticleSystem*)GetSystem("ParticleSystem");
	EntitySystem* eS = (EntitySystem*)GetSystem("EntitySystem");
	Particle* particle;

	if (gs->GetGameOver())
	{
		SetStateNext(POWERUP_DEAD);
	}
	switch (GetStateCurr())
	{
	case POWERUP_INVALID:
		SetStateNext(POWERUP_NORMAL);
		break;

	case POWERUP_NORMAL:
		break;

	case POWERUP_DEAD:
		break;

	case POWERUP_SPAWN:
		SetStateNext(POWERUP_NORMAL);
		break;
	}

	TraceDepth(lower);
}

void BehaviorPowerUp::OnExit()
{
	if (GetStateCurr() == POWERUP_INVALID)
	{
		SetTimer(_lifeTime);
	}
}

void BehaviorPowerUp::OnCollide(BehaviorType other)
{
	switch (other)
	{
	case BehaviorType::BEHAVIOR_PLAYER:
		SetStateNext(POWERUP_DEAD);
		break;
	case BehaviorType::BEHAVIOR_BOMB:
	case BehaviorType::BEHAVIOR_ENEMY:
	case BehaviorType::BEHAVIOR_ENEMY_CHARGE:
	case BehaviorType::BEHAVIOR_ENEMY_FOLLOW:
	case BehaviorType::BEHAVIOR_ENEMY_SQUARE:
	case BehaviorType::BEHAVIOR_ENEMY_SQUARE_INVERSE:
	case BehaviorType::BEHAVIOR_TURRET:
	case BehaviorType::BEHAVIOR_ENEMY_STAR:
	default:
		break;
	}
}

//----------------------------------------------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------------------------------------------------