#include "AdjacencyMatrixGraph.h"

void AdjacencyMatrixGraph::initializeMatrix()
{
	int n = vertex_List.size();
	adjacency_Matrix = new double*[n];
	for (int i = 0; i < n; i++)
	{
		adjacency_Matrix[i] = new double[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			adjacency_Matrix[i][j] = 0;
		}
	}
	matrix_Size = n;
}

void AdjacencyMatrixGraph::updateMatrix()
{
	int n = vertex_List.size();
	double **newMatrix = new double*[n];
	for (int i = 0; i < n; i++)
	{
		newMatrix[i] = new double[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			newMatrix[i][j] = 0;
		}
	}
	if (matrix_Size > 0)
	{
		for (int i = 0; i < matrix_Size; i++)
		{
			for (int j = 0; j < matrix_Size; j++)
			{
				newMatrix[i][j] = adjacency_Matrix[i][j];
			}
		}
		for (int i = 0; i < matrix_Size; i++)
		{
			delete adjacency_Matrix[i];
		}
		delete[] adjacency_Matrix;
	}
		adjacency_Matrix = newMatrix;
		matrix_Size = n;
}

FlightPath AdjacencyMatrixGraph::ShortestPath(int src)
{
	FlightPath fp;
	FlightElement fe;
	std::stack<FlightElement> modifyPQ;
	std::priority_queue<FlightElement, std::vector<FlightElement>, LeftRight> pq;
	fp.airports = vertex_List;
	fp.cost.resize(matrix_Size);
	fp.flight_Path.resize(matrix_Size);
	for (int i = 0; i < matrix_Size; i++)
	{
		if (i == src) fp.cost[i] = 0;
		else fp.cost[i] = INT_MAX;
	}
	for (int i = 0; i < matrix_Size; i++)
	{
		fe.airport = fp.airports[i];
		fe.cost = fp.cost[i];
		pq.push(fe);
	}
	while (!pq.empty())
	{
		fe = pq.top();
		pq.pop();
		int feRow = findAirport(fe.airport);
		for (int i = 0; i < matrix_Size; i++)
		{
			if (adjacency_Matrix[feRow][i] != 0.0)
			{
				double discoverWeight = adjacency_Matrix[feRow][i];
				if (fe.cost + discoverWeight < fp.cost[i])
				{
					fp.flight_Path[i] = fe.airport;
					fp.cost[i] = fe.cost + discoverWeight;
					FlightElement e;
					e.cost = fp.cost[i];
					e.airport = fp.airports[i];
					while (pq.top().airport != e.airport)
					{
						modifyPQ.push(pq.top());
						pq.pop();
					}
					pq.pop();
					pq.push(e);
					while (!modifyPQ.empty())
					{
						pq.push(modifyPQ.top());
						modifyPQ.pop();
					}
				}
			}
		}
	}
	return fp;
}

void AdjacencyMatrixGraph::displayPath(std::string x)
{
	for (int i = 0; i < x.length(); i++)
	{
		if (i % 3 == 0 && i != 0)
		{
			std::cout << " --> ";
		}
		std::cout << x[i];
	}
	std::cout << std::endl;
}

AdjacencyMatrixGraph::AdjacencyMatrixGraph(Airport A)
{
	vertex_List.push_back(A);
	initializeMatrix();
}

AdjacencyMatrixGraph::AdjacencyMatrixGraph()
{
	matrix_Size = 0;
}

bool AdjacencyMatrixGraph::directional_Connect(int A, int B, double weight)
{
	int n = vertex_List.size();
	if (((A >= n) || (A < 0)) || ((B >= n) || (B < 0)))							// A or B does not exists in our graph
	{
		return false;
	}
	adjacency_Matrix[A][B] = weight;											// set up as rows are outgoing, columns are incoming.
	return true;																// return a succesful connect.
}

bool AdjacencyMatrixGraph::disconnect(int A, int B)
{
	int n = vertex_List.size();
	if (((A >= n) || (A < 0)) || ((B >= n) || (B < 0)))							// A or B does not exists in our graph
	{
		return false;
	}
	if (adjacency_Matrix[A][B] == 0)
	{
		std::cout << "No path exists\n";
	}
	else 
	{
		std::cout << "path was sucessfully disconnected\n";
		adjacency_Matrix[A][B] = 0;
	}

	return true;																// return a successful disconnect
}

int AdjacencyMatrixGraph::findAirport(Airport A)
{
	for (int i = 0; i < vertex_List.size(); i++)
	{
		if (vertex_List[i] == A)
		{
			return i;
		}
	}
	return -1;	
}

int AdjacencyMatrixGraph::addAirport(Airport A)
{
	vertex_List.push_back(A);
	updateMatrix();
	return vertex_List.size() - 1;				// returns the index of the added airport
}

int AdjacencyMatrixGraph::getMatrixSize()
{
	return matrix_Size;
}

void AdjacencyMatrixGraph::printGraph()
{
	for (int i = 0; i < matrix_Size + 1; i++)
	{
		std::cout << std::setw(9) << std::setfill(' ') << std::left;
		if (i == 0)
		{
			std::cout << "";
		}
		else std::cout << vertex_List[i-1].airport_Code;
	}
	std::cout << std::endl << std::endl;
	for (int i = 0; i < matrix_Size; i++)
	{
		std::cout << vertex_List[i].airport_Code;
		for (int j = 0; j < matrix_Size; j++)
		{
			std::cout << std::setw(9) << std::setfill(' ') << std::right;
			std::cout << adjacency_Matrix[i][j];
		}
		std::cout << std::endl << std::endl;
	}
}

void AdjacencyMatrixGraph::displayAirportInformation(int A)
{

	std::cout << vertex_List[A].airport_Name << " Airport information:\n\n";
	std::cout << "Out-Going Flights:\n";
	std::cout << "Location" << std::setw(25) << std::setfill(' ') << "Cost\n";
	std::cout << std::setw(35) << std::setfill('-') << "\n";
	for (int i = 0; i < matrix_Size; i++)
	{
		if (adjacency_Matrix[A][i] != 0)
		{
			std::cout << std::setw(28) << std::setfill(' ');
			std::cout << std::left << vertex_List[i].airport_Name << std::right << "$" << adjacency_Matrix[A][i] << std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << "Incoming Flights:\n";
	std::cout << "Location" << std::setw(25) << std::setfill(' ') << "Cost\n";
	std::cout << std::setw(35) << std::setfill('-') << "\n";
	for (int i = 0; i < matrix_Size; i++)
	{
		if (adjacency_Matrix[i][A] != 0)
		{
			std::cout << std::setw(28) << std::setfill(' ');
			std::cout << std::left << vertex_List[i].airport_Name << std::right << "$" << adjacency_Matrix[i][A] << std::endl;
		}
	}
	std::cout << std::endl;
}

double AdjacencyMatrixGraph::cheapestFlight(int A, int B)
{
	FlightPath cheapestPath = ShortestPath(A);
	std::string path;
	int i = B;
	path = vertex_List[B].airport_Code;
	while (cheapestPath.flight_Path[i].airport_Code != "")
	{
		path = cheapestPath.flight_Path[i].airport_Code + path;
		i = findAirport(cheapestPath.flight_Path[i]);
	}
	std::cout << "Flight Plan from " << vertex_List[A].airport_Code << " to " << vertex_List[B].airport_Code << ":\n";
	displayPath(path);
	std::cout << "Total Cost: $" << cheapestPath.cost[B] << std::endl << std::endl;
	return cheapestPath.cost[B];							// if we want to return a value
}

double AdjacencyMatrixGraph::cheapestRoundTrip(int A, int B)
{
	FlightPath one_Way = ShortestPath(A);
	FlightPath second_Way = ShortestPath(B);
	std::string first_Path;
	std::string second_Path;
	first_Path = vertex_List[B].airport_Code;
	second_Path = vertex_List[A].airport_Code;
	int i = B;
	while (one_Way.flight_Path[i].airport_Code != "")
	{
		first_Path = one_Way.flight_Path[i].airport_Code + first_Path;
		i = findAirport(one_Way.flight_Path[i]);
	}
	i = A;
	while (second_Way.flight_Path[i].airport_Code != "")
	{
		second_Path = second_Way.flight_Path[i].airport_Code + second_Path;
		i = findAirport(second_Way.flight_Path[i]);
	}
	std::cout << "Roundtrip Flight Plan from " << vertex_List[A].airport_Code << " to " << vertex_List[B].airport_Code << ":\n";
	displayPath(first_Path);
	displayPath(second_Path);
	std::cout << "Total Cost: $" << one_Way.cost[B] + second_Way.cost[A] << std::endl << std::endl;
	return one_Way.cost[B] + second_Way.cost[A];		// if we want to return a value
}

double ** AdjacencyMatrixGraph::getGraph()
{
	return adjacency_Matrix;
}

std::vector<Airport> AdjacencyMatrixGraph::getAirports()
{
	return vertex_List;
}

std::vector<Airport> AdjacencyMatrixGraph::BFS(int A)
{
	int n = vertex_List.size();
	std::queue<Airport> traversal;
	std::vector<Airport> BreadthFirst;
	bool *visted = new bool[n];
	for (int i = 0; i < n; i++)
	{
		visted[i] = false;
	}
	traversal.push(vertex_List[A]);
	visted[A] = true;
	while (!traversal.empty())
	{
		for (int i = 0; i < n; i++)
		{
			if (adjacency_Matrix[A][i] != 0)
			{
				if (visted[i] == false)
				{
					traversal.push(vertex_List[i]);
					visted[i] = true;
				}
			}
		}
		BreadthFirst.push_back(traversal.front());
		traversal.pop();
		if (!traversal.empty())
		{
			A = findAirport(traversal.front());
		}
	}
	delete[] visted;
	return BreadthFirst;
}
