#pragma once
#include "DataTypes.h"

class LeftRight {
public:
	bool operator()(const FlightElement& p, const FlightElement &q)
	{
		return p.cost > q.cost;
	}
};