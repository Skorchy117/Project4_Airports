#pragma once
#include <vector>
#include <stack>
#include <map>
#include <queue>
#include <iostream>
#include <iomanip>
#include "DataTypes.h"
#include "Comparator.h"

class AdjacencyMatrixGraph {
private:
	std::vector<Airport> vertex_List;
	double **adjacency_Matrix;
	int matrix_Size;
protected:
	void initializeMatrix();
	void updateMatrix();
	FlightPath ShortestPath(int);
	void displayPath(std::string);
public:
	AdjacencyMatrixGraph(Airport);
	AdjacencyMatrixGraph();
	// returns a bool to see if we got a successful or unsucessful connection/disconnection
	bool directional_Connect(int , int ,double );
	bool disconnect(int, int);
	int findAirport(Airport);
	// returns the number of airports after creating a new airport
	int addAirport(Airport);
	int getMatrixSize();
	void printGraph();
	void displayAirportInformation(int);
	double cheapestFlight(int, int);
	double cheapestRoundTrip(int, int);
	double ** getGraph();
	std::vector<Airport> getAirports();
	std::vector<Airport> BFS(int A);
};