/*!---------------------------------------------------------------------------------------------------------------------
\file   EntityManager.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the EntityManager implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "EntityManager.h"
#include "Entity.h"
#include "ComponentManager.h"
#include "TraceUtils.h"
#include <iterator>
#include <iostream>
#include "ParticleSystem.h"
#include "CollisionSystem.h"
#include "MeshSystem.h"
#include "ShaderSystem.h"
#include "SoundSystem.h"
#include "MovementSystem.h"
#include "BehaviorSystem.h"
#include "SpriteSystem.h"
#include "AutoShootSystem.h"

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

/*!---------------------------------------------------------------------------------------------------------------------
\brief
    constructor

\param id
    Entity's id
----------------------------------------------------------------------------------------------------------------------*/
EntityManager::EntityManager(unsigned id): 
    _worldId(id)
{
	std::string message;
	message = "Create EntityManager #";
	message += std::to_string(_worldId);

	TraceDepth(higher);
	TraceMessage(message.c_str(), Verbose);
	TraceDepth(lower);
}

void EntityManager::CreateEntity(const std::string &typeName)
{
    _entityList.emplace_back();
}

std::vector<Entity>::iterator EntityManager::DeleteEntity(std::vector<Entity>::iterator it)
{
	if (it + 1 != _entityList.end())
	{
		*it = _entityList.back();
		_entityList.pop_back();
		return it;
	}
	else
	{
		_entityList.pop_back();
		return _entityList.end();
	}
}

void EntityManager::DeleteEntity(unsigned entityId)
{
	size_t index;
	size_t size = _entityList.size();
	for (size_t i = 0; i <= size; i++)
	{
		if (_entityList[i].GetId() == entityId)
		{
			index = i;
			if (i == size - 1)
			{
				_entityList.pop_back();
				return;
			}

			_entityList[i] = _entityList[size - 1];
			_entityList.pop_back();

			std::string message;
			message = "Delete Entity #";
			message += std::to_string(entityId);

			TraceDepth(higher);
			TraceMessage(message.c_str(), Debug);
			TraceDepth(lower);
			return;
		}
	}
}

void EntityManager::DeleteDirtyEntity()
{
	BehaviorSystem* bs = (BehaviorSystem*)GetSystem("BehaviorSystem");
	PhysicsSystem* ps = (PhysicsSystem*)GetSystem("PhysicsSystem");
	TransformSystem* ts = (TransformSystem*)GetSystem("TransformSystem");
	SpriteSystem* ss = (SpriteSystem*)GetSystem("SpriteSystem");
	CollisionSystem* cs = (CollisionSystem*)GetSystem("CollisionSystem");
	AutoShootSystem* as = (AutoShootSystem*)GetSystem("AutoShootSystem");
	ParticleSystem* particleSys = (ParticleSystem*)GetSystem("ParticleSystem");
	size_t size = _entityList.size();

    std::vector<Entity>::iterator it = _entityList.begin();
	for(; it != _entityList.end(); )
    {
		if (it->IsDirty())
		{
			std::string message;
			message = "Delete Entity #";

			TraceDepth(higher);
			TraceMessage(message.c_str(), Debug);
			TraceDepth(lower);

			bs->DeleteComponent(it->GetId());
			ps->DeleteComponent(it->GetId());
			ts->DeleteComponent(it->GetId());
			ss->DeleteSprite(it->GetId(), Sprite::SP_NORMAL);
			ss->DeleteSprite(it->GetId(), Sprite::SP_DEBUG);
			cs->DeleteComponent(it->GetId());
			as->DeleteComponent(it->GetId());
			particleSys->DeleteComponent(it->GetId());
			it = DeleteEntity(it);
		}
		else
			++it;
    }
}

Entity* EntityManager::GetEntity(unsigned entityId)
{
    std::vector<Entity>::iterator it = _entityList.begin();
    for(;it != _entityList.end(); ++it)
    {
        if(it->GetId() == entityId)
            return &(*it);
    }
    return NULL;
}

unsigned EntityManager::GetWorldId()
{
    return _worldId;
}

std::vector<Entity> EntityManager::GetEntityList()
{
	return _entityList;
}