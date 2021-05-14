/*!---------------------------------------------------------------------------------------------------------------------
\file   Entity.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the Entity implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "Entity.h"
#include "EntityManager.h"
#include "TraceUtils.h"
#include <unordered_map>
#include <iostream>
#include <rttr/registration.h>

//----------------------------------------------------------------------------------------------------------------------
// Private Structures:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------
unsigned EntityManager::_nextEntityId;

//----------------------------------------------------------------------------------------------------------------------
// Private Consts:
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
RTTR_REGISTRATION
{
	rttr::registration::class_<Entity>("Entity")
		.property_readonly("_id", &Entity::GetId)
		.property("_isDirty", &Entity::IsDirty, &Entity::SetDirty)
		;
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
    constructor

\param id
    Entity's id
----------------------------------------------------------------------------------------------------------------------*/
Entity::Entity() :
    _id(EntityManager::_nextEntityId++),
    _isDirty(false)
{
	std::string message;
	message = "Create Entity #";
	message += std::to_string(_id);

	TraceDepth(higher);
	TraceMessage(message.c_str(), Verbose);
	TraceDepth(lower);
}

Entity::Entity(const Entity &rhs) :
    _id(rhs.GetId()),
    _isDirty(rhs.IsDirty())
{
	std::string message;
	message = "Copy Entity #";
	message += std::to_string(_id);

	TraceDepth(higher);
	TraceMessage(message.c_str(), Verbose);
	TraceDepth(lower);
}

Entity& Entity::operator=(const Entity &rhs)
{
	this->_id = rhs._id;
    this->_isDirty = rhs._isDirty;
    return *this;
}

unsigned Entity::GetId() const
{
    return _id;
}


void Entity::SetDirty(bool isDirty)
{
    _isDirty = isDirty;
}

bool Entity::IsDirty() const
{
    return _isDirty;
}