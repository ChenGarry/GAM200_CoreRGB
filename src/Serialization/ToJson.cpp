/*!---------------------------------------------------------------------------------------------------------------------
\file   FromJson.cpp
\author Garry Chen
\par    DP email:	garry.c\@digipen.edu
\par    Course: 	GAM200
\par    Team: 		Improv Spark
\par    Project: 	CoreRGB
\par    Copyright © 2019 DigiPen (USA) Corporation.

\brief
  This is the FromJson implenmentation file.
----------------------------------------------------------------------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------------------------
// Include Files:
//----------------------------------------------------------------------------------------------------------------------
#include <cstdio>
#include <string>
#include <vector>
#include <array>
#include <iostream>

#define RAPIDJSON_HAS_STDSTRING 1
#include <rapidjson/prettywriter.h> // for stringify JSON
#include <rapidjson/document.h>     // rapidjson's DOM-style API
#include <rttr/type>

using namespace rapidjson;
using namespace rttr;

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
namespace
{
void to_json_recursively(const instance& obj, PrettyWriter<StringBuffer>& writer);
bool write_variant(const variant& var, PrettyWriter<StringBuffer>& writer);

//----------------------------------------------------------------------------------------------------------------------
// Private Function:
//----------------------------------------------------------------------------------------------------------------------
bool write_atomic_types_to_json(const type& t, const variant& var, PrettyWriter<StringBuffer>& writer)
{
    if (t.is_arithmetic())
    {
        if (t == type::get<bool>())
            writer.Bool(var.to_bool());
        else if (t == type::get<char>())
            writer.Bool(var.to_bool());
        else if (t == type::get<int8_t>())
            writer.Int(var.to_int8());
        else if (t == type::get<int16_t>())
            writer.Int(var.to_int16());
        else if (t == type::get<int32_t>())
            writer.Int(var.to_int32());
        else if (t == type::get<int64_t>())
            writer.Int64(var.to_int64());
        else if (t == type::get<uint8_t>())
            writer.Uint(var.to_uint8());
        else if (t == type::get<uint16_t>())
            writer.Uint(var.to_uint16());
        else if (t == type::get<uint32_t>())
            writer.Uint(var.to_uint32());
        else if (t == type::get<uint64_t>())
            writer.Uint64(var.to_uint64());
        else if (t == type::get<float>())
            writer.Double(var.to_double());
        else if (t == type::get<double>())
            writer.Double(var.to_double());

        return true;
    }
    else if (t.is_enumeration())
    {
        bool ok = false;
        auto result = var.to_string(&ok);
        if (ok)
        {
            writer.String(var.to_string());
        }
        else
        {
            ok = false;
            auto value = var.to_uint64(&ok);
            if (ok)
                writer.Uint64(value);
            else
                writer.Null();
        }

        return true;
    }
    else if (t == type::get<std::string>())
    {
        writer.String(var.to_string());
        return true;
    }

    return false;
}

static void write_array(const variant_sequential_view& view, PrettyWriter<StringBuffer>& writer)
{
    writer.StartArray(); 
    for (const auto& item : view)
    {
        if (item.is_sequential_container())
        {
            write_array(item.create_sequential_view(), writer);
        }
        else
        {
            variant wrapped_var = item.extract_wrapped_value();
            type value_type = wrapped_var.get_type();
            if (value_type.is_arithmetic() || value_type == type::get<std::string>() || value_type.is_enumeration())
            {
                write_atomic_types_to_json(value_type, wrapped_var, writer);
            }
            else // object
            {
                to_json_recursively(wrapped_var, writer);
            }
        }
    }
    writer.EndArray();
}

static void write_associative_container(const variant_associative_view& view, PrettyWriter<StringBuffer>& writer)
{
    static const string_view key_name("key");
    static const string_view value_name("value");

    writer.StartArray();

    if (view.is_key_only_type())
    {
        for (auto& item : view)
        {
            write_variant(item.first, writer);
        }
    }
    else
    {
        for (auto& item : view)
        {
            writer.StartObject();
            writer.String(key_name.data(), static_cast<rapidjson::SizeType>(key_name.length()), false);

            write_variant(item.first, writer);

            writer.String(value_name.data(), static_cast<rapidjson::SizeType>(value_name.length()), false);

            write_variant(item.second, writer);

            writer.EndObject();
        }
    }

    writer.EndArray();
}

bool write_variant(const variant& var, PrettyWriter<StringBuffer>& writer)
{
    auto value_type = var.get_type();
    auto wrapped_type = value_type.is_wrapper() ? value_type.get_wrapped_type() : value_type;
    bool is_wrapper = wrapped_type != value_type;

    if (write_atomic_types_to_json(is_wrapper ? wrapped_type : value_type,
                                   is_wrapper ? var.extract_wrapped_value() : var, writer))
    {
    }
    else if (var.is_sequential_container())
    {
        write_array(var.create_sequential_view(), writer);
    }
    else if (var.is_associative_container())
    {
        write_associative_container(var.create_associative_view(), writer);
    }
    else
    {
        auto child_props = is_wrapper ? wrapped_type.get_properties() : value_type.get_properties();
        if (!child_props.empty())
        {
            to_json_recursively(var, writer);
        }
        else
        {
            bool ok = false;
            auto text = var.to_string(&ok);
            if (!ok)
            {
                writer.String(text);
                return false;
            }

            writer.String(text);
        }
    }

    return true;
}

void to_json_recursively(const instance& obj2, PrettyWriter<StringBuffer>& writer)
{
    writer.StartObject();
    instance obj = obj2.get_type().get_raw_type().is_wrapper() ? obj2.get_wrapped_instance() : obj2;

	writer.Key("type name");
	writer.String(obj.get_type().get_name().data());
    auto prop_list = obj.get_derived_type().get_properties();
    for (auto prop : prop_list)
    {
        if (prop.get_metadata("NO_SERIALIZE"))
            continue;

        variant prop_value = prop.get_value(obj);
        if (!prop_value)
            continue; // cannot serialize, because we cannot retrieve the value

        const auto name = prop.get_name();
        writer.String(name.data(), static_cast<rapidjson::SizeType>(name.length()), false);
        if (!write_variant(prop_value, writer))
        {
            std::cerr << "cannot serialize property: " << name << std::endl;
        }
    }

    writer.EndObject();
}

} // end namespace anonymous


//----------------------------------------------------------------------------------------------------------------------
// Public Functions:
//----------------------------------------------------------------------------------------------------------------------
namespace io
{

std::string to_json(const variant& var)
{
    StringBuffer sb;
    PrettyWriter<StringBuffer> writer(sb);
	
	writer.StartObject();
	writer.Key(var.get_type().get_name().data());
	write_variant(var, writer);
	writer.EndObject();
    return sb.GetString();
}

void to_json(rapidjson::PrettyWriter<StringBuffer> &writer, rttr::instance obj)
{
	to_json_recursively(obj, writer);
}
} // end namespace io
