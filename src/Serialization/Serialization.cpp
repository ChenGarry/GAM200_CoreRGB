/*!---------------------------------------------------------------------------------------------------------------------
\file   Serialization.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the Serialization implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include "Serialization.h"
#include "FromJson.h"
#include "ToJson.h"
#include <iostream>
#include <fstream>
#include "rapidjson/reader.h"
#include <rapidjson/filereadstream.h>
#include "rapidjson/document.h"
#include <rapidjson/prettywriter.h>
#include <cstdio>
#include <rttr/registration>

// system include
#include "../TraceUtils.h"
#include "../InfoQueue.h"
#include "../Input.h"
#include "../FrameRateController.h"
#include "../GameStateManager.h"
#include "../CollisionSystem.h"
#include "../MeshSystem.h"
#include "../ShaderSystem.h"
#include "../SoundSystem.h"
#include "../MovementSystem.h"
#include "../BehaviorSystem.h"

//----------------------------------------------------------------------------------------------------------------------
// Private Consts:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Private Structures:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
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
using namespace rapidjson;

RTTR_REGISTRATION
{
	rttr::registration::class_<stringWraper>("stringWraper")
	.property("str", &stringWraper::str)
	;
	rttr::registration::class_<VectorStirng>("VectorStirng")
	.property("_strs", &VectorStirng::GetStrings, &VectorStirng::SetStrings)
	;
}

void Serialization::Load(rttr::instance obj)
{
	assert(_documentIndex < _document.Size());
	Deserialize(_document[_documentIndex++], obj);
}

void Serialization::startLoad(std::string fileName)
{
	_fileName = fileName;
	FILE *saveFile;
	errno_t err;

	err = fopen_s(&saveFile, _fileName.c_str(), "rb");
	assert(err == 0);

	FileReadStream is(saveFile, _readBuffer, sizeof(_readBuffer));
	fclose(saveFile);

	bool error;
	error = _document.Parse(_readBuffer).HasParseError();
	assert(!error);
	error = _document.IsArray();
	assert(error);
	_documentIndex = 0;
}

void Serialization::endLoad()
{
}

void Serialization::Save(rttr::instance obj)
{
	io::to_json(_writer, obj);
}

void Serialization::startSave(std::string fileName)
{
	_fileName = fileName;
	_writer.StartArray();
}

void Serialization::endSave()
{
	_writer.EndArray();
	std::ofstream saveFile;
	saveFile.open(_fileName, std::ios::out);
	saveFile << _sb.GetString();
	saveFile.close();
}

rttr::instance Serialization::Deserialize(Value& json_object, rttr::instance obj)
{
	io::from_json(json_object, obj);
	return obj;
}

std::string Serialization::Serialize(rttr::instance obj)
{
	return NULL;
}

void LoadLevel(std::string fileName)
{
    PhysicsSystem *physics = dynamic_cast<PhysicsSystem*>(GetSystem("PhysicsSystem"));
    TransformSystem *transform = dynamic_cast<TransformSystem*>(GetSystem("TransformSystem"));
    MovementSystem *movement = dynamic_cast<MovementSystem*>(GetSystem("MovementSystem"));
    Window* window = dynamic_cast<Window*>(GetSystem("Window"));
    Graphics* graphics = dynamic_cast<Graphics*>(GetSystem("Graphics"));
    SoundSystem* sound = dynamic_cast<SoundSystem*>(GetSystem("SoundSystem"));
    BehaviorSystem* behavior = dynamic_cast<BehaviorSystem*>(GetSystem("BehaviorSystem"));
    CollisionSystem* collision = dynamic_cast<CollisionSystem*>(GetSystem("CollisionSystem"));
}

void SaveLevel(std::string fileName)
{
}