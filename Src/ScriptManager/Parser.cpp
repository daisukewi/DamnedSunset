/**
@file Parser.cpp

Contiene la implementación de la clase CParser que será la encargada
de servir de interfaz de comunicación entre el parser de lua
y C++.

@author Alberto Plaza
@date Marzo, 2012
*/
#include "Parser.h"
#include "Server.h"

#include "Map\MapParser.h"

#pragma warning( disable: 4251 )
#include <luabind\luabind.hpp>

namespace ScriptManager
{

	CParser::CParser()
	{
		
		
	} // CParser

	//--------------------------------------------------------

	CParser::~CParser()
	{

		
	} // ~CParser

	//--------------------------------------------------------

	void CParser::beginEntity()
	{
		
		
	} // beginEntity

	//--------------------------------------------------------

	void CParser::registerClass()
	{
		luabind::module(CServer::getSingletonPtr()->getLuaState())
		[
			luabind::class_<CParser>("Parser")
				.def(luabind::constructor<>())
				.def("beginEntity", (void (CParser::*) (const char*)) &CParser::beginEntity)
				.def("newAttrib", (void (CParser::*) (const char*, const char*)) &CParser::newAttrib)
				.def("endEntity", &CParser::endEntity)
		];

	} // registerClass

	//--------------------------------------------------------

	void CParser::beginEntity(const char *name)
	{
		Map::CMapParser::getSingletonPtr()->beginEntity(std::string(name));
		
	} // beginEntity

	//--------------------------------------------------------

	void CParser::newAttrib(const char *name, const char *value)
	{
		if ((strcmp(name, "type") == 0))
			Map::CMapParser::getSingletonPtr()->newAttribType(std::string(value));
		else
			Map::CMapParser::getSingletonPtr()->newAttrib(std::string(name), std::string(value));
		
	} // newAttrib

	//--------------------------------------------------------

	void CParser::endEntity()
	{
		Map::CMapParser::getSingletonPtr()->endEntity();
		
	} // endEntity

	//--------------------------------------------------------

} // namespace ScriptManager