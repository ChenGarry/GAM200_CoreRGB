/*!---------------------------------------------------------------------------------------------------------------------
\file   Component.cpp
\author Jacob Randich, Garry Chen
\par    DP email:	j.randich\@digipen.edu  garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the Component implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "Component.h"
#include <rttr/registration.h>

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

// Garry Code Start
RTTR_REGISTRATION
{
	rttr::registration::class_<Component>("Component")
		.property("_type", &Component::Type, &Component::SetType)
		.property("_parentID", &Component::GetParentID, &Component::SetParentID)
		;
}

//----------------------------------------------------------------------------------------------------------------------
// Constructor
// Params: parent - GameObject that the component will belong too
//			type - Type of the component this is
// Returns:
// Constructs a new component and then adds it to the given parent object
//----------------------------------------------------------------------------------------------------------------------
Component::Component(CompType type) : 
	_type(type)
{
}

void Component::SetType(CompType type)
{
	_type = type;
}
// Garry Code End

//----------------------------------------------------------------------------------------------------------------------
// Type
// Params: 
// Returns: CompType - The type of the component.
// Returns the type of the component
//----------------------------------------------------------------------------------------------------------------------
Component::CompType Component::Type() const
{ 
	return _type; 
}


unsigned int Component::GetParentID()
{ 
	return _parentID;
}

void Component::SetParentID(unsigned int parentID)
{
	_parentID = parentID; 
}
//----------------------------------------------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------------------------------------------------

