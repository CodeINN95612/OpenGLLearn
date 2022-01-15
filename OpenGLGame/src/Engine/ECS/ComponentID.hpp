#pragma once

//std
#include <bitset>

namespace GL::ECS
{
	using ComponentID = int16_t;
	constexpr const ComponentID MaxComponents = 32;

	//This represents how an entity manages to see if it has a component easily
	//if it has 1,2,3 bits as true, then it has those components 0b111...(MaxComponents bits)
	using ComponentSignature = std::bitset<MaxComponents>;
}
