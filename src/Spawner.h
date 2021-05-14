#ifndef SPAWNER_H
#define SPAWNER_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   Spawner.h
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the Spawner interface file.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include <vector>
#include <unordered_map>
#include <string>
#include "Factory.h"
#include "EntitySystem.h"

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
class Spawner : public SystemBase
{
  public:
	struct SpawnData 
	{
		Factory::EntityType _type;
		float _x;
		float _y;
		float _spawnTime;
		SpawnData() {};
		SpawnData(Factory::EntityType type, float x, float y, float time = 0) : 
			_type(type), 
			_x(x), 
			_y(y), 
			_spawnTime(time){}
	};

	struct WaveData
	{
		float _spawnTime;
		std::vector<SpawnData> _spwanDataList;
	};
      // 
	Spawner();

	int Init();
	int Update(float dt);
	int Shutdown();

	unsigned AddScene(std::string sceneName, Factory* factory, float *timer);
	void AddSpawn(Factory::EntityType type, float x, float y, float time = 0);
	void AddSpawn(unsigned id, const SpawnData &data);
	void AddSpawn(const std::vector<SpawnData> &dataList);
	void AddSpawn(unsigned id, std::string fileName, bool usingTimeBase = false);

	void AddWave(unsigned id, const WaveData &data);
	void AddWaitingWave(unsigned id, const WaveData &data);
	void SpawnNextWave(unsigned id, float waitTime);
	void SpawntWave(unsigned id, float waitTime, unsigned index);

	void Load(unsigned id, const std::string fileName);
	void Save(unsigned id, const std::string fileName);

  private:
	std::vector<float*> _timerList;						    //!< 
	std::vector<std::vector<SpawnData> > _spwanDataLists;	//!< 
	std::vector<std::vector<WaveData> >  _waveLists;		//!< 
	std::vector<std::vector<WaveData> > _waveWarningList;	//!< 
	std::vector<std::vector<WaveData> >  _waveWaitingLists;	//!< 
	std::vector<Factory*> _factoryList;
	std::unordered_map<std::string ,unsigned> _idMap;

	EntitySystem *_entitySys;
	unsigned _waveWaitngListEnd;
     // prevent using
	/*Spawner(const Spawner&);
	Spawner& operator=(const Spawner&);*/
};

struct SpawnFile
{
	std::vector<Spawner::SpawnData> _spwanDataList;		//!< 
	std::vector<Spawner::WaveData> _waveList;			//!< 
	std::vector<Spawner::WaveData> _waveWaitingList;	//!< 
};
//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

#endif