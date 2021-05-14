#ifndef ENTITY_H
#define ENTITY_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   Entity.h
\author Garry Chen
\par    DP email: garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the Entity interface file.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include <unordered_map>
#include "Component.h"

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
    \class Entity
    \brief
        The Entity class is a container for components

        Operations include:

        - Constructors (Load Resources)
        - Initiate the factory
        - Create component from a prototype
        - Shutdown the factory
        - Destructor (Unload Resources)

*///--------------------------------------------------------------------------------------------------------------------
class Entity
{
  public:
      // Set an unique const entity id
    Entity();
    //Entity(unsigned id = 0);
    Entity(const Entity&);
    Entity& operator=(const Entity&);
    //void AddCompoment(Component::CompType type, unsigned index);

     // 
    unsigned GetId() const;

     // Set dity flag = true
    void SetDirty(bool isDirty = true);

     // Check if dirty flag is true
    bool IsDirty() const;

    //unsigned GetCompomentId(Component::CompType type);
    //std::unordered_map<Component::CompType, unsigned>& GetMap();
  private:
    unsigned _id; //!< id of the entity
    bool _isDirty;      //!< dirty flag use to destory the entity

    //std::unordered_map<Component::CompType, unsigned> _componenetMap;
};

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

#endif