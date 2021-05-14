/*!---------------------------------------------------------------------------------------------------------------------
\file   BehaviorWarningSign.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the BehaviorWarningSign implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include "BehaviorWarningSign.h"
#include "Input.h"
#include "SoundSystem.h"
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
BehaviorWarningSign::BehaviorWarningSign() :
	Behavior(BehaviorType::BEHAVIOR_WALL)
{
	TraceDepth(higher);
	TraceMessage("BehaviorWarningSign Constructing", Debug);
	SetStateCurr(WARNING_SIGN_INVALID);
	SetStateNext(WARNING_SIGN_WAITING);
	TraceDepth(lower);
}

BehaviorWarningSign::BehaviorWarningSign(unsigned parentID) :
	Behavior(BehaviorType::BEHAVIOR_WALL, parentID)
{
	TraceDepth(higher);
	TraceMessage("BehaviorWarningSign Constructing", Debug);
	SetStateCurr(WARNING_SIGN_INVALID);
	SetStateNext(WARNING_SIGN_WAITING);
	TraceDepth(lower);
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Destructor
----------------------------------------------------------------------------------------------------------------------*/
BehaviorWarningSign::~BehaviorWarningSign()
{
	TraceDepth(higher);
	TraceMessage("BehaviorWall Destructing", Debug);
	TraceDepth(lower);
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
	Initializes the BehaviorSystemShootStraight

\return int
	Returns 0 if success, anything else if failure
----------------------------------------------------------------------------------------------------------------------*/
void BehaviorWarningSign::OnInit()
{
	if (GetStateCurr() == WARNING_SIGN_DEAD)
	{
		EntitySystem* es = (EntitySystem*)GetSystem("EntitySystem");
		es->SetDirty(GetParentID());
	}
}

void BehaviorWarningSign::OnUpdate(float dt)
{
	SetTimer(GetTimer() - dt);
	if (GetTimer() <= 0.0f)
	{
		SetStateNext(WARNING_SIGN_DEAD);
	}
}

void BehaviorWarningSign::OnExit()
{
}

void BehaviorWarningSign::OnCollide(BehaviorType other)
{

}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------