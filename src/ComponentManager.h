#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   ComponentManager.h
\author Garry Chen
\par    DP email: garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the ComponentManager interface file.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include <unordered_map>
#include <vector>
#include <string>
#include <typeinfo> 
#include "Component.h"
#include "Entity.h"
#include "EntityManager.h"

//----------------------------------------------------------------------------------------------------------------------
// Forward References:
//----------------------------------------------------------------------------------------------------------------------
typedef EntityManager* EntityManagerPtr;

//----------------------------------------------------------------------------------------------------------------------
// Public Consts:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Structures:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
/*!
    \class ComponentManager
    \brief
        The ComponentManager class is a container + manager + factory for components

        Operations include:

        - Constructors (Load Resources)
        - Initiate the factory
        - Create component from a prototype
        - Shutdown the factory
        - Destructor (Unload Resources)

*///--------------------------------------------------------------------------------------------------------------------
template<typename T>
class ComponentManager
{
  public: 
      // create manager and store its type
    ComponentManager(Component::CompType type);

     // store a component archetype by name
    void AddComponentArchetype(const std::string &entityArcheType, const T &componentArcheType);

     // pass a component to the manager to store and set the parent to entity. 
    void AddComponent(Entity &entity, const T &component);

     // Create a component using type name and and set the parent to entity.
    void AddComponent(Entity &entity, const std::string &entityArcheType);

     // Create a component copy from entity2 and  set the parent to entity1. 
    void AddComponent(Entity &entity1, const Entity &entity2);

	  void AddComponent(unsigned int parentID, const std::string &entityArcheType);

	  void AddComponent(unsigned int parentID, const T &component);

     //  Delete the component whose parent is entity
    void deleteComponent(Entity &entity);

	  void deleteComponent(unsigned int parentID);

	  void deleteArchetypes();

	  unsigned GetParentId(unsigned index);

     // Get the entity's component
    T* GetComponent(Entity &entity);

     //  Get the entity's component using entity id
    T* GetComponent(unsigned entityId);

     //  Get the component using vector index
    T* operator[](unsigned index);
	  T* operator[](size_t index);
     //  Get the component arche type of the given name
    T& GetArcheType(std::string typeName);

     // Get the reference of the component vector
    std::vector<T>* GetComponentList();

	  void GetArchetypeComponentList(std::vector<T>* vector);


     // Get the manager type
    Component::CompType Type();

  private:
    Component::CompType _type;
    std::vector<T> _componentList;
    std::vector<unsigned> _componentToEntity;
    std::unordered_map<unsigned, unsigned> _entityToComponent;
    std::unordered_map<std::string, T> _componenetArcheTypeList;
};

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------
#include "ComponentManager.cpp"

#endif
