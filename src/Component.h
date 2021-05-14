#ifndef COMPONENT_H
#define COMPONENT_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   Component.h
\author Jacob Randich, Garry Chen
\par    DP email: 	j.randich\@digipen.edu  garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the Component interface file.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Forward References:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Consts:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Structures:
//----------------------------------------------------------------------------------------------------------------------
class Component
{
public:

	enum CompType
	{
		//COM_ANIMATION,
		COM_PHYSICS,
		COM_TRANSFORM,
		COM_SPRITE,
		COM_BEHAVIOR,
		COM_COLLIDER,
		COM_EMMITER,
		COM_AUTOSHOOTDATA,
		COM_COUNT
	};
	Component(CompType type);

     // get the type of current component
	void SetType(CompType type);
	CompType Type() const;
	unsigned int GetParentID();
	void SetParentID(unsigned int parentID);

     // no parent id store in the component, parent id list will be store in the component manager

private:
	unsigned int _parentID;
	CompType _type; //!< Type of the component
};
//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

#endif
