/*!---------------------------------------------------------------------------------------------------------------------
\file   ComponentManager.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the ComponentManager implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "ComponentManager.h"

//----------------------------------------------------------------------------------------------------------------------
// Private Structures:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

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
template <typename T>
ComponentManager<T>::ComponentManager(Component::CompType type) : _type(type)
{
}

// store a component archetype by name
template<typename T>
void ComponentManager<T>::AddComponentArchetype(const std::string &entityArcheType, const T &componentArcheType)
{
	_componenetArcheTypeList.emplace(entityArcheType, T(componentArcheType));
}

// pass a component to the manager to store and set the parent to entity. 
template<typename T>
void ComponentManager<T>::AddComponent(Entity &entity, const T &component)
{
	_componentList.push_back(component);
	_componentToEntity.push_back(entity.GetId());
	_entityToComponent[entity.GetId()] = static_cast<unsigned>(_componentList.size() - 1);
}

// Create a component using type name and and set the parent to entity.
template<typename T>
void ComponentManager<T>::AddComponent(Entity &entity, const std::string &entityArcheType)
{
	AddComponent(entity, _componenetArcheTypeList[entityArcheType]);
}

// Create a component copy from entity2 and  set the parent to entity1. 
template<typename T>
void ComponentManager<T>::AddComponent(Entity &entity1, const Entity &entity2)
{
	AddComponent(GetComponent(entity2));
}

template<typename T>
void ComponentManager<T>::AddComponent(unsigned int parentID, const std::string &entityArcheType)
{
	AddComponent(parentID, _componenetArcheTypeList[entityArcheType]);
}

template<typename T>
void ComponentManager<T>::AddComponent(unsigned int parentID, const T &component)
{
	_componentList.push_back(component);
	_componentToEntity.push_back(parentID);
	_entityToComponent[parentID] = static_cast<unsigned>(_componentList.size() - 1);
}

//  Delete the component whose parent is entity
template<typename T>
void ComponentManager<T>::deleteComponent(Entity &entity)
{
	unsigned index = _entityToComponent[entity.GetId()];
	bool isNotLast = (_componentList.size() != index + 1);
	if (isNotLast)
	{
		_componentList[index] = _componentList.back();
		_componentToEntity[index] = _componentToEntity.back();
	}

	_componentList.pop_back();
	_componentToEntity.pop_back();
	_entityToComponent.erase(entity.GetId());
	if (isNotLast)
		_entityToComponent[_componentToEntity[index]] = index;
}

template<typename T>
void ComponentManager<T>::deleteComponent(unsigned int parentID)
{
	auto constIt = _entityToComponent.find(parentID);
	if (constIt == _entityToComponent.end())
		return;

	unsigned index = constIt->second;
	bool isNotLast = (_componentList.size() != index + 1);
	if (isNotLast)
	{
		_componentList[index] = _componentList.back();
		_componentToEntity[index] = _componentToEntity.back();
	}

	_componentList.pop_back();
	_componentToEntity.pop_back();
	_entityToComponent.erase(parentID);
	if (isNotLast)
		_entityToComponent[_componentToEntity[index]] = index;
}

template<typename T>
void ComponentManager<T>::deleteArchetypes()
{
	_componenetArcheTypeList.clear();
}

template<typename T>
unsigned ComponentManager<T>::GetParentId(unsigned index)
{
	return _componentToEntity[index];
}

// Get the entity's component
template<typename T>
T* ComponentManager<T>::GetComponent(Entity &entity)
{
	return &_componentList[_entityToComponent[entity.GetId()]];
}

//  Get the entity's component using entity id
template<typename T>
T* ComponentManager<T>::GetComponent(unsigned entityId)
{
	std::unordered_map<unsigned, unsigned>::const_iterator constIt = _entityToComponent.find(entityId);
	if (constIt != _entityToComponent.end())
		return &_componentList[constIt->second];
	return NULL;
}

//  Get the component using vector index
template<typename T>
T* ComponentManager<T>::operator[](unsigned index)
{
	if (index < _componentList.size())
		return &_componentList[index];
	return NULL;
}

template<typename T>
T * ComponentManager<T>::operator[](size_t index)
{
	if (index < _componentList.size())
		return &_componentList[index];
	return NULL;
}

//  Get the component arche type of the given name
template<typename T>
T& ComponentManager<T>::GetArcheType(std::string typeName)
{
	return _componenetArcheTypeList[typeName];
}

// Get the reference of the component vector
template<typename T>
std::vector<T>* ComponentManager<T>::GetComponentList()
{
	return &_componentList;
}

template<typename T>
void ComponentManager<T>::GetArchetypeComponentList(std::vector<T>* vector)
{

	for (auto it = _componenetArcheTypeList.begin(); it != _componenetArcheTypeList.end(); ++it) 
	{
		vector->push_back(it->second);
	}

}

// Get the manager type
template<typename T>
Component::CompType ComponentManager<T>::Type()
{
	return _type;
}