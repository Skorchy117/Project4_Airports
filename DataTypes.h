#pragma once
#include <string>

struct Airport {
	std::string airport_Code;
	std::string airport_Name;
public:
	bool operator==(const Airport A) const
	{
		if (airport_Code == A.airport_Code)
		{
			return true;
		}
		else return false;
	}
	bool operator !=(const Airport A) const
	{
		if (airport_Code != A.airport_Code)
		{
			return true;
		}
		else return false;
	}
};

struct FlightPath {
	std::vector<Airport> airports;
	std::vector<double> cost;
	std::vector<Airport> flight_Path;
};

struct FlightElement {
	Airport airport;
	double cost;
};