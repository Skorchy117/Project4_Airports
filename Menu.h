#pragma once
#include "AdjacencyMatrixGraph.h"
#include <fstream>
#include <cctype>

class Menu {
private:
	AdjacencyMatrixGraph airport_Graph;
protected:
	void display_Airports();
	bool airportFound(int);
	void display_Graph();
	void airport_Information(int);
	void cheapest_Flight(int, int);
	void delete_Flight(int, int);
	void add_Flight(int, int, double);
	void cheapest_RoundTrip(int, int);
	void visit_All_Airport(int);
	void add_Airport(Airport);
public:
	Menu();
	void displayMenu();
};