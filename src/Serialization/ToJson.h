#ifndef TO_JSON_H
#define TO_JSON_H
/*!---------------------------------------------------------------------------------------------------------------------
\file   ToJson.h
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the ToJson interface file.
----------------------------------------------------------------------------------------------------------------------*/
#pragma once

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <rttr/type>
#include <rapidjson/prettywriter.h>
#include <rapidjson/document.h>

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
// Public Variables:
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------
namespace io
{

/*!
 * Serialize the given instance to a json encoded string.
 */
std::string to_json(const rttr::variant& var);

void to_json(rapidjson::PrettyWriter<rapidjson::StringBuffer> &writer, rttr::instance obj);

}

#endif