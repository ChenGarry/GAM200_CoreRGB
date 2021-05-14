/*!---------------------------------------------------------------------------------------------------------------------
\file   BehaviorShootStraight.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the BehaviorShootStraight implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "BehaviorShootStraight.h"
#include "Input.h"
#include "SoundSystem.h"
#include "Engine.h"
#include "Factory.h"
#include "EntitySystem.h"
#include "Transform.h"
#include "BehaviorStraightBullet.h"

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
	const int right = 0;
	const int up = 1;
	const int left = 2;
	const int down = 3;	
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
BehaviorShootStraight::BehaviorShootStraight() :
	Behavior(BehaviorType::BEHAVIOR_SHOOT_STRAIGHT),
	_cooldown(0.05f),
	_timer(0.0f),
	_isShooting(false)
{
	SetStateCurr(SHOOT_INVALID);
	SetStateNext(SHOOT_IDLE);
}

BehaviorShootStraight::BehaviorShootStraight(unsigned parentID) :
	Behavior(BehaviorType::BEHAVIOR_SHOOT_STRAIGHT, parentID),
	_cooldown(0.05f),
	_timer(0.0f),
	_isShooting(false)
{
	SetStateCurr(SHOOT_INVALID);
	SetStateNext(SHOOT_IDLE);
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Destructor
----------------------------------------------------------------------------------------------------------------------*/
BehaviorShootStraight::~BehaviorShootStraight()
{

}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Initializes the BehaviorSystemShootStraight

\return int
	Returns 0 if success, anything else if failure
----------------------------------------------------------------------------------------------------------------------*/
void BehaviorShootStraight::OnInit()
{
}

void BehaviorShootStraight::OnUpdate(float dt)
{
	Input *input = (Input*) GetSystem("Input");
	SoundSystem *sound = (SoundSystem*) GetSystem("SoundSystem");

	switch (GetStateCurr())
	{
	case SHOOT_INVALID:
		SetStateNext(SHOOT_IDLE);

	case SHOOT_IDLE:
		{
			if (input->isPressed(input->aUP))
			{
				_dir = up;
				SetStateNext(SHOOT_SHOOTING);
			}
			else if (input->isTriggered(input->aDN))
			{
				_dir = down;
				SetStateNext(SHOOT_SHOOTING);
			}
			else if (input->isTriggered(input->aLF))
			{
				_dir = left;
				SetStateNext(SHOOT_SHOOTING);
			}
			else if (input->isTriggered(input->aRT))
			{
				_dir = right;
				SetStateNext(SHOOT_SHOOTING);
			}
		
		}		
		break;

	case SHOOT_SHOOTING:
		{
			EntitySystem* es = (EntitySystem*)GetSystem("EntitySystem");
			Transform* transCom = ((TransformSystem*)GetSystem("TransformSystem"))->GetComponent(GetParentID());
			Eigen::Vector3f pos = transCom->GetTranslation();
			int bulletID = es->CreateEntity("StraightBullet", pos.x(), pos.y());
			BehaviorStraightBullet* bulletBehavior = (BehaviorStraightBullet*)(((BehaviorSystem*)GetSystem("BehaviorSystem"))->GetComponent(bulletID));
			switch (_dir)
			{
			case up:
				bulletBehavior->SetDirection({ 0.0f, 1.0f, 0.0f });
				break;
			case down:
				bulletBehavior->SetDirection({ 0.0f, -1.0f, 0.0f });
				break;
			case left:
				bulletBehavior->SetDirection({ -1.0f, 0.0f, 0.0f });
				break;
			case right:
				bulletBehavior->SetDirection({ 1.0f, 0.0f, 0.0f });
				break;
			default:
				break;
			}
			_timer = _cooldown;
			SetStateNext(SHOOT_COOLDOWN);
		}
		break;

	case SHOOT_COOLDOWN:
		_timer -= dt;
		if (_timer <= 0.0f)
		{
			SetStateNext(SHOOT_IDLE);
		}
		break;

	case SHOOT_DEAD:
		break;
	}
}

void BehaviorShootStraight::OnExit()
{
}

//----------------------------------------------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------------------------------------------------