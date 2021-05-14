/*!---------------------------------------------------------------------------------------------------------------------
\file   Spawner.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the Spawner implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "Spawner.h"
#include "TraceUtils.h"
#include <iostream>
#include <algorithm>
#include <rttr/registration.h>
#include "Engine.h"
#include <rttr/registration.h>
#include "GameStats.h"
#include "Utilities/Serialization.h"

//----------------------------------------------------------------------------------------------------------------------
// Private Structures:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Private Consts:
//----------------------------------------------------------------------------------------------------------------------
namespace
{
	const float warning_time = 3.0f;
}

//----------------------------------------------------------------------------------------------------------------------
// Private Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Private Function Declarations:
//----------------------------------------------------------------------------------------------------------------------
template<typename T>
bool binary_search_time(T const &T1, T const &T2);

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

	rttr::registration::class_<Spawner::WaveData>("WaveData")
		.property("spawnTime", &Spawner::WaveData::_spawnTime)
		.property("spwanDataList", &Spawner::WaveData::_spwanDataList)
		;

	rttr::registration::class_<SpawnFile>("SpawnFile")
		.property("spwanDataLists", &SpawnFile::_spwanDataList)
		.property("waveLists", &SpawnFile::_waveList)
		.property("waveWaitingLists", &SpawnFile::_waveWaitingList)
		;
}

/*!---------------------------------------------------------------------------------------------------------------------
\brief
    constructor

\param id
    Entity's id
----------------------------------------------------------------------------------------------------------------------*/
Spawner::Spawner() :
	SystemBase("Spawner")
{
	std::string message;
	message = "Create Spawner";

	TraceDepth(higher);
	TraceMessage(message.c_str(), Verbose);
	TraceDepth(lower);
}

int Spawner::Init()
{
	_entitySys = (EntitySystem*)GetSystem("EntitySystem");
	assert(_entitySys);
	_waveWaitngListEnd = 0;
	return 0;
}

int Spawner::Update(float dt)
{
	assert(_timerList.size() == _spwanDataLists.size() && 
		   _timerList.size() == _factoryList.size()	   &&
		   _timerList.size() == _waveLists.size()		 );

	auto tIt = _timerList.begin();
	auto sIt = _spwanDataLists.begin();
	auto fIt = _factoryList.begin();
	auto wIt = _waveLists.begin();
	auto wwIt = _waveWarningList.begin();
	GameStats* gameStat = (GameStats*)GetSystem("GameStats");




	while (tIt != _timerList.end())
	{
		auto timer = (**tIt);
		auto &dataList = *sIt;
		auto &waveList = *wIt;
		auto &waveWarningList = *wwIt;
		auto factory = *fIt;

		while (!dataList.empty() && dataList.back()._spawnTime < timer)
		{
			auto data = dataList.back();
			factory->CreateEntity(data._type, data._x, data._y);
			dataList.pop_back();
		}

		while (!waveList.empty() && waveList.back()._spawnTime < timer)
		{
			
			auto waveData = waveList.back();
			auto dataIt = waveData._spwanDataList.begin();
			while (dataIt != waveData._spwanDataList.end())
			{
				factory->CreateEntity(dataIt->_type, dataIt->_x, dataIt->_y);
				++dataIt;
				gameStat->IncrementNumEnemies();
			}
			waveList.pop_back();
			//gameStat->IncrementWaveCount();
			gameStat->SetWaveActive(false);
		}

		while (!waveWarningList.empty() && waveWarningList.back()._spawnTime < timer + warning_time)
		{

			auto waveData = waveWarningList.back();
			auto dataIt = waveData._spwanDataList.begin();
			while (dataIt != waveData._spwanDataList.end())
			{
				factory->CreateWarningSign(dataIt->_x, dataIt->_y);
				++dataIt;
			}
			waveWarningList.pop_back();
			//gameStat->IncrementWaveCount();
		}

		++wwIt;
		++tIt;
		++sIt;
		++fIt;
		++wIt;

		if (!waveList.empty())
		{
			gameStat->SetWaveActive(true);
		}
	}

	return 0;
}

int Spawner::Shutdown()
{
	return 0;
}

unsigned Spawner::AddScene(std::string sceneName, Factory* factory, float *timer)
{
	assert(timer);
	unsigned id = _timerList.size();
	_timerList.push_back(timer);
	_factoryList.push_back(factory);
	_spwanDataLists.emplace_back();
	_waveLists.emplace_back();
	_waveWarningList.emplace_back();
	_waveWaitingLists.emplace_back();
	_idMap.emplace(sceneName, id);

	return id;
}

void Spawner::AddSpawn(unsigned id, const SpawnData &data)
{
	assert(id < _spwanDataLists.size());
	auto &DataList = _spwanDataLists[id];

	auto where = std::lower_bound(std::begin(DataList), std::end(DataList), data, binary_search_time<SpawnData>);
	DataList.insert(where, data);
}

void Spawner::AddSpawn(Factory::EntityType type, float x, float y, float time)
{
	AddSpawn(0, SpawnData(type , x, y, time));
}


void Spawner::AddSpawn(const std::vector<SpawnData> &dataList)
{
	for(int i = 0; i < dataList.size(); ++i)
		AddSpawn(0, dataList[i]);
}

void Spawner::AddWave(unsigned id, const WaveData &data)
{
	assert(id < _waveLists.size());
	auto &DataList = _waveLists[id];

	auto where = std::lower_bound(std::begin(DataList), std::end(DataList), data, binary_search_time<WaveData>);
	DataList.insert(where, data);
}


void Spawner::AddWaitingWave(unsigned id, const WaveData &data)
{
	assert(id < _waveLists.size());
	auto &WaitingList = _waveWaitingLists[id];
	auto &WaitingWarnigList = _waveWarningList[id];

	WaitingList.insert(WaitingList.begin() + _waveWaitngListEnd, data);	
	
	++_waveWaitngListEnd;
}

void Spawner::SpawnNextWave(unsigned id, float waitTime)
{
	SpawntWave(id, waitTime, --_waveWaitngListEnd);
}

void Spawner::SpawntWave(unsigned id, float waitTime, unsigned index)
{
	if (id >= _waveLists.size())return;
	if (_waveLists.empty()) return;
	float time = *_timerList[id];
	auto &DataList = _waveLists[id];
	auto &WaitingList = _waveWaitingLists[id];
	auto &WarningList = _waveWarningList[id];
	// Use WaitingList from vector end to begin
	if (index >= WaitingList.size()) return;
	WaitingList[index]._spawnTime = time + waitTime;

	auto where = std::lower_bound(std::begin(DataList), std::end(DataList), WaitingList[index], binary_search_time<WaveData>);
	DataList.insert(where, WaitingList[index]);

	where = std::lower_bound(std::begin(WarningList), std::end(WarningList), WaitingList[index], binary_search_time<WaveData>);
	WarningList.insert(where, WaitingList[index]);
}

void Spawner::Load(unsigned id, const std::string fileName)
{
	assert(id < _spwanDataLists.size());
	SpawnFile sf;
	Serialization s;
	s.startLoad(fileName);
	s.Load(sf);
	_spwanDataLists[id] = sf._spwanDataList;
	_waveLists[id] = sf._waveList;
	_waveWarningList[id] = sf._waveList;
	_waveWaitingLists[id] = sf._waveWaitingList;
	s.endLoad();
	_waveWaitngListEnd = _waveWaitingLists[id].size();
}

void Spawner::Save(unsigned id, const std::string fileName)
{
	assert(id < _spwanDataLists.size());
	SpawnFile sf;
	Serialization s;
	sf._spwanDataList = _spwanDataLists[id];
	sf._waveList = _waveLists[id];
	sf._waveWaitingList = _waveWaitingLists[id];

	s.startSave(fileName);
	s.Save(sf);
	s.endSave();
}

//----------------------------------------------------------------------------------------------------------------------
// Private Functions:
//----------------------------------------------------------------------------------------------------------------------

template<typename T>
bool binary_search_time(T const &T1, T const &T2)
{
	return T1._spawnTime > T2._spawnTime;
}