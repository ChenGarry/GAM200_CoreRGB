#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   EntityManager.h
\author Garry Chen
\par    DP email: garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the EntityManager interface file.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include <unordered_map>
#include <vector>
#include <string>
#include "SystemBase.h"

//----------------------------------------------------------------------------------------------------------------------
// Forward References:
//----------------------------------------------------------------------------------------------------------------------
class Entity;

//----------------------------------------------------------------------------------------------------------------------
// Public Consts:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Structures:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/*!
    \class EntityManager
    \brief
        The EntityManager class is a container for components

        Operations include:

        - Constructors (Load Resources)
        - Initiate the factory
        - Create component from a prototype
        - Shutdown the factory
        - Destructor (Unload Resources)

*///--------------------------------------------------------------------------------------------------------------------
class EntityManager
{
  public:
      // id used to set world id, it can exist multiple world at the same screen
    EntityManager(unsigned id);
	
     // create an entity using type name, all component will be create accordingly 
    void CreateEntity(const std::string &typeName);

	  std::vector<Entity>::iterator DeleteEntity(std::vector<Entity>::iterator it);
     // delet the entity with given id
    void DeleteEntity(unsigned entityId);

     // delet all dirty entity
    void DeleteDirtyEntity();

     // get a pointer to the entity with given id
    Entity* GetEntity(unsigned entityId);

	  //unsigned int GetEntityID(std::string name);

     // get the world id of this manager
    unsigned GetWorldId();

    static unsigned _nextEntityId; //!< the id which will be given to next created entity

	  std::vector<Entity> GetEntityList();

  private:
    const unsigned _worldId;         //!< world id of this manager
    std::vector<Entity> _entityList; //!< vector which holds all the entity 

};

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

#endif