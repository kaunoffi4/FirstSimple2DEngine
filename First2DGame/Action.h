#pragma once

#include "Entity.h"

#include <string>

class Action
{

	std::string m_name = "NONE"; // "jump", "left" "shoot" etc
	std::string m_type = "NONE"; // "start" or "end"

public:
	
	Action();
	Action(const std::string& name, const std::string& type);

	const std::string& name() const;
	const std::string& type() const;
	std::string toString() const;
};