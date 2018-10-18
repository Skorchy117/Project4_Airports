#include "Menu.h"

Menu::Menu()
{
	std::ifstream inFile;
	std::string value;
	Airport A;
	inFile.open("P4Airports.txt");
	while (!inFile.eof())
	{
		bool firstPass = true;
		getline(inFile, value);
		for (int i = 0; i < value.size(); i++)
		{
			if (isalpha(value[i]) && firstPass)
			{

				A.airport_Code = value.substr(i, 3);
				i += 2;
				firstPass = false;
			}
			else if (isalpha(value[i]) && !firstPass)
			{
				A.airport_Name = value.substr(i, value.size() - 1);
				break;
			}
		}
		airport_Graph.addAirport(A);
	}
	inFile.close();
	inFile.open("P4Flights.txt");
	while (!inFile.eof())
	{
		int airport_A, airport_B;
		double cost;
		inFile >> airport_A;
		inFile >> airport_B;
		inFile >> cost;
		airport_Graph.directional_Connect(airport_A, airport_B, cost);
	}
	inFile.close();
}

void Menu::displayMenu()
{
	int get_Matrix_Size = airport_Graph.getMatrixSize();
	char selection;	
	do {
		std::cout << "Please select one of the following options below:\n\n";
		std::cout << "1: Display Airport Information\n";
		std::cout << "2: Cheapest Flight from Airport A to Airport B\n";
		std::cout << "3: Add a flight from Airport A to Airport B\n";
		std::cout << "4: Delete a flight from Airport A to Airport B\n";
		std::cout << "5: Cheapest Round Trip Flight from Airport A to Airport B\n";
		std::cout << "6: Find a flight with fewest stops from Airport A to Airport B\n";
		std::cout << "7: Find all flights from Airport A to Airport B\n";
		std::cout << "8: Visit all Airports from a starting Airport\n";
		std::cout << "9: Add an Airport\n";
		std::cout << "Q: Exit\n\n";
		std::cout << "Option -> ";
		std::cin >> selection;
		if (isdigit(selection))
		{
			system("CLS");
			int selection_One = selection - 48;
			int airport_One, airport_Two;
			switch (selection_One)
			{
			case 0:
				display_Graph();
				break;
			case 1:
				display_Airports();
				std::cout << "Please select an airport to view its information -> ";
				std::cin >> airport_One;
				std::cout << std::endl;
				airport_Information(airport_One - 1);
				break;

			case 2:
				display_Airports();
				std::cout << "Please select an airport above as your starting location -> ";
				std::cin >> airport_One;
				std::cout << "Please select an airport above as your destination location -> ";
				std::cin >> airport_Two;
				std::cout << std::endl;
				cheapest_Flight(airport_One - 1, airport_Two - 1);
				break;

			case 3:
				double cost;
				display_Airports();
				std::cout << "Please select an airport above as your starting location -> ";
				std::cin >> airport_One;
				std::cout << "Please select an airport above as your destination location -> ";
				std::cin >> airport_Two;
				std::cout << "Please selection a cost -> ";
				std::cin >> cost;
				std::cout << std::endl;
				add_Flight(airport_One - 1, airport_Two - 1, cost);
				break;

			case 4:
				display_Airports();
				std::cout << "Please select an airport above as your starting location -> ";
				std::cin >> airport_One;
				std::cout << "Please select an airport above as your destination location -> ";
				std::cin >> airport_Two;
				std::cout << std::endl;
				delete_Flight(airport_One - 1, airport_Two - 1);
				break;
			case 5:
				display_Airports();
				std::cout << "Please select an airport above as your starting location -> ";
				std::cin >> airport_One;
				std::cout << "Please select an airport above as your destination location -> ";
				std::cin >> airport_Two;
				std::cout << std::endl;
				cheapest_RoundTrip(airport_One - 1, airport_Two - 1);
				break;

			case 6:
				std::cout << "The option you have selected is currently unavailable at this time\n";
				break;

			case 7:
				std::cout << "The option you have selected is currently unavailable at this time\n";
				break;

			case 8:
				display_Airports();
				std::cout << "Please select an airport to visit all airports -> ";
				std::cin >> airport_One;
				std::cout << std::endl;
				visit_All_Airport(airport_One - 1);
				break;

			case 9:
				Airport A;
				std::string code, name;
				std::cout << "Airport Code -> ";
				std::cin >> code;
				std::cout << "Airport Name -> ";
				std::cin.ignore();
				getline(std::cin, name);
				A.airport_Code = code;
				A.airport_Name = name;
				add_Airport(A);
				break;
			}
		}
		else
		{
			selection = toupper(selection);
		}
	} while (selection != 'Q');
	std::ofstream outFile;
	std::vector<Airport> airport_List = airport_Graph.getAirports();
	int n = airport_List.size();
	if (get_Matrix_Size != n)
	{
		double **matrix = airport_Graph.getGraph();
		outFile.open("ModifiedAirportList.txt");
		if (outFile.is_open())
		{
			for (int i = 0; i < n; i++)
			{
				std::string airport_Code = airport_List[i].airport_Code;
				std::string airport_Name = airport_List[i].airport_Name;
				outFile << i << "  " << airport_Code << "   " << airport_Name << std::endl;
			}
		}
		outFile.close();
		outFile.open("ModifiedAirportFlight.txt");
		if (outFile.is_open())
		{
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					if (matrix[i][j] != 0)
					{
						outFile << i << "  " << j << "  " << matrix[i][j] << std::endl;
					}
				}
			}
		}
		outFile.close();
	}
}

void Menu::display_Airports()
{
	std::vector<Airport> airport_List = airport_Graph.getAirports();
	std::cout << "Available Airports: \n\n";
	for (int i = 0; i < airport_List.size(); i++)
	{
		std::cout << i + 1 << ": " << airport_List[i].airport_Code << " " << airport_List[i].airport_Name << std::endl;
	}
	std::cout << std::endl;
}

bool Menu::airportFound(int i)
{
	if (i < 0 || i >= airport_Graph.getMatrixSize())
	{
		return false;
	}
	return true;
}

void Menu::display_Graph()
{
	airport_Graph.printGraph();
}

void Menu::airport_Information(int i)
{
	bool airportValid = airportFound(i);
	while (!airportValid)
	{
		std::cout << "You have inputted an incorrect airport, please try again\n";
		display_Airports();
		std::cout << "Airport: ";
		std::cin >> i;
		i -= 1;
		airportValid = airportFound(i);
	}
	airport_Graph.displayAirportInformation(i);
}

void Menu::cheapest_Flight(int i, int j)
{
	bool airport_One_Valid = airportFound(i);
	bool airport_Two_Valid = airportFound(j);
	while (!airport_One_Valid || !airport_Two_Valid)
	{
		std::cout << "You have inputted an incorrect airport, please try again\n";
		display_Airports();
		std::cout << "From: ";
		std::cin >> i;
		std::cout << "To: ";
		std::cin >> j;
		i -= 1;
		j -= 1;
		airport_One_Valid = airportFound(i);
		airport_Two_Valid = airportFound(j);
	}
	airport_Graph.cheapestFlight(i, j);
}

void Menu::delete_Flight(int i, int j)
{
	bool valid = airport_Graph.disconnect(i, j);
	while (!valid)
	{
		std::cout << "You have inputted an incorrect airport, please try again\n";
		display_Airports();
		std::cout << "From: ";
		std::cin >> i;
		std::cout << "To: ";
		std::cin >> j;
		i -= 1;
		j -= 1;
		valid = airport_Graph.disconnect(i, j);
	}
}

void Menu::add_Flight(int i, int j, double cost)
{
	bool airport_One_Valid = airportFound(i);
	bool airport_Two_Valid = airportFound(j);
	while (!airport_One_Valid || !airport_Two_Valid)
	{
		std::cout << "You have inputted an incorrect airport, please try again\n";
		display_Airports();
		std::cout << "From: ";
		std::cin >> i;
		std::cout << "To: ";
		std::cin >> j;
		i -= 1;
		j -= 1;
		airport_One_Valid = airportFound(i);
		airport_Two_Valid = airportFound(j);
	}
	airport_Graph.directional_Connect(i, j, cost);
}

void Menu::cheapest_RoundTrip(int i, int j)
{
	bool airport_One_Valid = airportFound(i);
	bool airport_Two_Valid = airportFound(j);
	while (!airport_One_Valid || !airport_Two_Valid)
	{
		std::cout << "You have inputted an incorrect airport, please try again\n";
		display_Airports();
		std::cout << "From: ";
		std::cin >> i;
		std::cout << "To: ";
		std::cin >> j;
		i -= 1;
		j -= 1;
		airport_One_Valid = airportFound(i);
		airport_Two_Valid = airportFound(j);
	}
	airport_Graph.cheapestRoundTrip(i, j);
}

void Menu::visit_All_Airport(int i)
{
	bool airportValid = airportFound(i);
	while (!airportValid)
	{
		std::cout << "You have inputted an incorrect airport, please try again\n";
		display_Airports();
		std::cout << "Airport: ";
		std::cin >> i;
		i -= 1;
		airportValid = airportFound(i);
	}
	std::vector<Airport> BFS_List = airport_Graph.BFS(i);
	std::cout << "Airport BFS list from " << BFS_List[0].airport_Code << " as starting point:\n\n";
	for (int i = 0; i < BFS_List.size(); i++)
	{
		std::cout << BFS_List[i].airport_Code << " ";
	}
	std::cout << std::endl << std::endl;
	
}
void Menu::add_Airport(Airport A)
{
	airport_Graph.addAirport(A);
}
