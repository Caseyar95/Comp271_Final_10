#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


struct ParkingInfo		// struct for car parking information
{
	string date;
	string timeInHour;
	string timeInMin;		// Had to make them all strings so getline would work
	string timeOutHour;		// and had to split hour and minutes to get rid of colon
	string timeOutMin;
	string make;
	string model;
	string licensePlate;
};

struct TheftInfo		// struct for theft occurance information
{
	string date;
	string timeHour;	// same here
	string timeMin;
};

bool SuspectCheck(vector<TheftInfo> thief, string d, string tih, string tim, string toh, string tom);

void main()
{
	vector<TheftInfo> thefts; vector<ParkingInfo> cars;
	TheftInfo th;
	ParkingInfo par;
	string file;
	ifstream in;
	cout << "What file is the theft information held in? ";		//opening theft file
	cin >> file;
	in.open(file);
	while (!in)
	{
		cout << "File not found, try again:  ";
		cin >> file;
		in.open(file);
	}
	while (!in.eof())
	{							// putting theft file information into TheftInfo object
		getline(in, th.date, ',');
		getline(in, th.timeHour, ':');
		getline(in, th.timeMin, '\n');
		thefts.push_back(th);				// push back into vector
	}

	/*for (int i = 0; i < thefts.size(); i++)	// test if vector was filled
	{
		cout << thefts[i].date << ' ' << thefts[i].timeHour << ':' << thefts[i].timeMin << endl;
	} */

	in.clear();
	in.close();


	cout << "What file is the parking information held in? ";	//opening parking information
	cin >> file;
	in.open(file);
	while (!in)
	{
		cout << "File not found, try again:  ";
		cin >> file;
		in.open(file);
	}
	while (!in.eof())
	{								// reading it into the parking stuct object
		getline(in, par.date, ',');
		getline(in, par.timeInHour, ':');
		getline(in, par.timeInMin, ',');
		getline(in, par.timeOutHour, ':');
		getline(in, par.timeOutMin, ',');
		getline(in, par.make, ',');
		getline(in, par.model, ',');
		getline(in, par.licensePlate, '\n');
		cars.push_back(par);					// push back into vector
	}

	/*for (int i = 0; i < cars.size()-1; i++) // cars.size() -1 because the last one is in there twice for some reason
	{
		cout << cars[i].date << ' ' << cars[i].timeInHour << ':' << cars[i].timeInMin << ' ' << cars[i].timeOutHour << ':' << cars[i].timeOutMin << ' ' 
		<< cars[i].make << ' ' << cars[i].model << ' ' << cars[i].licensePlate << endl;
	}*/

	in.clear();
	in.close();
	cout << '\n';
	//ofstream out;
	//out.open("SuspectCars.txt");
	for (int q = 1; q < cars.size() - 1; q++)  // car.size() - 1 because the last is a repeat for some reason
	{											// started q at 1 since the first row is header information in the excel doc
		if (SuspectCheck(thefts, cars[q].date, cars[q].timeInHour, cars[q].timeInMin, cars[q].timeOutHour, cars[q].timeOutMin) == true) //calling to check if vehicle is suspect
		{
			cout << "Information for suspect car:" << endl;
			cout << cars[q].date << "  Time in: " << cars[q].timeInHour << ':' << cars[q].timeInMin << "  Time out: " << cars[q].timeOutHour << ':' << cars[q].timeOutMin << "  "
				<< cars[q].make << ' ' << cars[q].model << ' ' << cars[q].licensePlate << '\n' << endl;
				
			// optional output to file "SuspectCars.txt"
			/*out << "Information for suspect car:" << endl;
			out << cars[q].date << "  Time in: " << cars[q].timeInHour << ':' << cars[q].timeInMin << "  Time out: " << cars[q].timeOutHour << ':' << cars[q].timeOutMin << "  "
				<< cars[q].make << ' ' << cars[q].model << ' ' << cars[q].licensePlate << '\n' << endl;*/ 
		}
	}
	//out.clear();
	//out.close();
}

bool SuspectCheck(vector<TheftInfo> thief, string d, string tih, string tim, string toh, string tom)
{
	float th, tm, tihi, timi, tohi, tomi;
	
	for (int i = 0; i < thief.size(); i++)
	{
		tm = stof(thief[i].timeMin)/60;			//converting string info to floats and minutes to percentages of an hour
		th = stof(thief[i].timeHour) + tm;		// and adding to hour for ease of comparison
		timi = stof(tim)/60;
		tomi = stof(tom)/60;
		tihi = stof(tih) + timi;
		tohi = stof(toh) + tomi;
		
		if (d == thief[i].date && tihi < th && tohi > th)  // if dates are equal and time of a theft is between parked time
			return true;
	}
	return false;
}
