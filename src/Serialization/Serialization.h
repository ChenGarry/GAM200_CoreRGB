#ifndef SERIALIZATION_H
#define SERIALIZATION_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   Serialization.h
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the Serialization interface file.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <rttr/type>
#include <rapidjson/prettywriter.h> // for stringify JSON
#include <rapidjson/document.h>     // rapidjson's DOM-style API

//----------------------------------------------------------------------------------------------------------------------
// Forward References:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Consts:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Structures:
//----------------------------------------------------------------------------------------------------------------------
struct stringWraper
{
	std::string str;
};

struct VectorStirng
{
	std::vector<stringWraper> _strs;
	void SetStrings(const std::vector<stringWraper>& strs)
	{
		for (int i = 0; i < strs.size(); ++i)
			_strs.push_back(strs[i]);
	}
	const std::vector<stringWraper>& GetStrings()
	{
		return _strs;
	}
};

class Serialization
{
public:
    struct FileMetaData
    {
        std::string dataName;
        std::vector<std::string> info;
    };

	Serialization() :_writer(_sb) { };

	void startLoad(std::string fileName);
    void Load(rttr::instance obj);
	void endLoad();

    void startSave(std::string fileName);
	void Save(rttr::instance obj);
	void endSave();

    void LoadLevel(std::string fileName);
    void SaveLevel(std::string fileName);

private:
	FILE* _pSaveFile;
	rapidjson::SizeType _documentIndex;
	char _readBuffer[65536];
	rapidjson::Document _document; // Default template parameter uses UTF8 and MemoryPoolAllocator.
	std::string _fileName;
	rapidjson::StringBuffer _sb;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> _writer;

     // Serialize function
    rttr::instance Deserialize(rapidjson::Value& json_object, rttr::instance obj);
    std::string Serialize(rttr::instance obj);
};

//----------------------------------------------------------------------------------------------------------------------
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------

// Initialize the game state manager.
// rttr::instance Load(std::string fileName);
// void Save(std::string fileName, rttr::instance obj);

#endif