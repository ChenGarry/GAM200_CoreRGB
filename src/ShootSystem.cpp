/*!---------------------------------------------------------------------------------------------------------------------
\file   ShootSystem.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the ShootSystem implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "ShootSystem.h"
#include "TraceUtils.h"
#include <iostream>
#include "Engine.h"
#include <rttr/registration.h>
#include "BehaviorStraightBullet.h"
#include "BehaviorLaser.h"
#include "Transform.h"
#include "TransformSystem.h"
#include <random>

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
RTTR_REGISTRATION
{
	rttr::registration::class_<Spawner::SpawnData>("SpawnData")
		.property("type", &Spawner::SpawnData::_type)
		.property("x", &Spawner::SpawnData::_x)
		.property("y", &Spawner::SpawnData::_y)
		.property("spawnTime", &Spawner::SpawnData::_spawnTime)
		;
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
    constructor

\param id
    Entity's id
----------------------------------------------------------------------------------------------------------------------*/
ShootSystem::ShootSystem() :
	SystemBase("ShootSystem")
{
	std::string message;
	message = "Create ShootSystem";

	TraceDepth(higher);
	TraceMessage(message.c_str(), Verbose);
	TraceDepth(lower);
}

int ShootSystem::Init()
{
	_entitySys = (EntitySystem*)GetSystem("EntitySystem");
	_behaviorSys = (BehaviorSystem*)GetSystem("BehaviorSystem");
	_factory = (Factory*)GetSystem("Factory");

	assert(_entitySys);
	assert(_behaviorSys);
	assert(_factory);
	return 0;
}

int ShootSystem::Update(float dt)
{
	return 0;
}

int ShootSystem::Shutdown()
{
	return 0;
}

void ShootSystem::Shoot(ShootData &data, std::string colGroup) const
{
	switch (data._type)
	{
	case SHOOT_BASIC:
		ShootBasic(data, colGroup);
		break;
	case SHOOT_SPREAD:
		ShootSpread(data, colGroup);
		break;
	case SHOOT_LASER:
		ShootLaser(data);
		break;
	default:
		break;
	}
}

//----------------------------------------------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------------------------------------------------
#define degreeToRad 0.0174533
#define radTodegree 57.2958
void ShootSystem::ShootBasic(ShootData &data, std::string colGroup) const
{
	Transform* shooterTrans = ((TransformSystem*)GetSystem("TransformSystem"))->GetComponent(data._shooterId);
	Eigen::Vector3f pos = shooterTrans->GetTranslation();

	int bulletID = _factory->CreateStraightBullet(pos.x(), pos.y(), data._collisionGroup, data.color);
	BehaviorStraightBullet* bulletBehavior = (BehaviorStraightBullet*)(_behaviorSys->GetComponent(bulletID));
	Eigen::Vector2f dir(data._dir_x, data._dir_y);
	float theta = 0;
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	dir = Eigen::Rotation2Df(-0.5 * theta * degreeToRad).toRotationMatrix()*dir;
	dir = Eigen::Rotation2Df(theta * degreeToRad * r).toRotationMatrix()*dir;

	bulletBehavior->SetDirection({ dir.x(), dir.y(), 0});
	bulletBehavior->SetLifeTime(data._lifeTime);
	Transform* transform = ((TransformSystem*)GetSystem("TransformSystem"))->GetComponent(bulletID);

	transform->SetRotationV(dir);
}


void ShootSystem::ShootSpread(ShootData &data, std::string colGroup) const
{
	Eigen::Vector2f dir(data._dir_x, data._dir_y);
	float theta = 15;
	dir = Eigen::Rotation2Df(-3 * theta * degreeToRad).toRotationMatrix()*dir;
	TransformSystem* transSys = (TransformSystem*)GetSystem("TransformSystem");

	Transform* shooterTrans = ((TransformSystem*)GetSystem("TransformSystem"))->GetComponent(data._shooterId);
	Eigen::Vector3f pos = shooterTrans->GetTranslation();

	for (int i = 0; i < 5; ++i)
	{
		int bulletID = _factory->CreateStraightBullet(pos.x(), pos.y(), data._collisionGroup, data.color);
		BehaviorStraightBullet* bulletBehavior = (BehaviorStraightBullet*)(_behaviorSys->GetComponent(bulletID));
		Transform* transform = transSys->GetComponent(bulletID);

		dir = Eigen::Rotation2Df(theta * degreeToRad).toRotationMatrix()*dir;
		dir.normalize();
		bulletBehavior->SetDirection({ dir.x(), dir.y(), 0.0f });
		bulletBehavior->SetDeathTimer(0.5f/*data._lifeTime*/);
		/*float rotate = atan2(dir.y(), dir.x());
		transform->SetRotation(rotate*radTodegree);*/
		transform->SetRotationV(dir);
	}
}

void ShootSystem::ShootLaser(ShootData &data) const
{
	Transform* shooterTrans = ((TransformSystem*)GetSystem("TransformSystem"))->GetComponent(data._shooterId);
	Eigen::Vector3f pos = shooterTrans->GetTranslation();
	float length = 10.0f;
	int bulletID = _factory->CreateLaser(pos.x(), pos.y(), length, 0.4f, data._shooterId);
	BehaviorLaser* laserBehavior = (BehaviorLaser*)(_behaviorSys->GetComponent(bulletID));
	Transform* transform = ((TransformSystem*)GetSystem("TransformSystem"))->GetComponent(bulletID);
	 
	Eigen::Vector2f dir(data._dir_x, data._dir_y);
	dir.normalize();
	transform->SetRotationV(dir);

	auto translate = shooterTrans->GetTranslation();

	translate.x() += dir.x() * (length / 2 + 0.12f);
	translate.y() += dir.y() * (length / 2 + 0.12f);
	transform->SetTranslation(translate);

	//laserBehavior->SetLifeTime(data._lifeTime);
}

