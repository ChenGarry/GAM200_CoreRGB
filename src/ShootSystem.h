#ifndef SHOOT_SYSTEM_H
#define SHOOT_SYSTEM_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   ShootSystem.h
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the ShootSystem interface file.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include "SystemBase.h"
#include "EntitySystem.h"
#include "BehaviorSystem.h"
#include "Factory.h"

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
    \class Spawner
    \brief
        The Spawner class is responsible for spawning a entity with given type/time/position.

        Operations include:

        - Constructors (Load Resources)
        - Destructor (Unload Resources)

*///--------------------------------------------------------------------------------------------------------------------
class ShootSystem : public SystemBase
{
  public:
	enum ShootType
	{
		SHOOT_BASIC,
		SHOOT_SPREAD,
		SHOOT_LASER,
		SHOOT_COUNT
	};
	struct ShootData
	{
		unsigned _shooterId;
		ShootType _type;
		float _dir_x;
		float _dir_y;
		float _lifeTime;
		std::string _collisionGroup;
		Eigen::Vector4f color;
		ShootData() {};
		ShootData(unsigned shooterId, ShootType type, std::string collisionGroup, float dir_x = 0.0f, float dir_y = 0.0f,
				  float time = -1.0f) :
			_shooterId(shooterId), 
			_type(type), 
			_collisionGroup(collisionGroup), 
			_dir_x(dir_x), 
			_dir_y(dir_y), 
			_lifeTime(time){}
	};

	ShootSystem();

	int Init();
	int Update(float dt);
	int Shutdown();

	void Shoot(ShootData &data, std::string colGroup) const;

  private:
	EntitySystem *_entitySys;
	BehaviorSystem* _behaviorSys;
	Factory* _factory;

	void ShootBasic(ShootData &data, std::string colGroup) const;
	void ShootSpread(ShootData &data, std::string colGroup) const;
	void ShootLaser(ShootData &data) const;
};

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

#endif