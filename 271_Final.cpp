#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;


struct ParkingInfo
{
	string date;
	string timeInHour;
	string timeInMin;
	string timeOutHour;
	string timeOutMin;
	string make;
	string model;
	string licensePlate;
};

struct TheftInfo
{
	string date;
	string timeHour;
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
	cout << "What file is the theft information held in? ";
	cin >> file;
	in.open(file);
	while (!in)
	{
		cout << "File not found, try again:  ";
		cin >> file;
		in.open(file);
	}
	while (!in.eof())
	{
		getline(in, th.date, ',');
		getline(in, th.timeHour, ':');
		getline(in, th.timeMin, '\n');
		thefts.push_back(th);
	}
	/*for (int i = 0; i < thefts.size(); i++)
	{
		cout << thefts[i].date << ' ' << thefts[i].timeHour << ':' << thefts[i].timeMin << endl;
	} */
	in.clear();
	in.close();


	cout << "What file is the parking information held in? ";
	cin >> file;
	in.open(file);
	while (!in)
	{
		cout << "File not found, try again:  ";
		cin >> file;
		in.open(file);
	}
	while (!in.eof())
	{
		getline(in, par.date, ',');
		getline(in, par.timeInHour, ':');
		getline(in, par.timeInMin, ',');
		getline(in, par.timeOutHour, ':');
		getline(in, par.timeOutMin, ',');
		getline(in, par.make, ',');
		getline(in, par.model, ',');
		getline(in, par.licensePlate, '\n');
		cars.push_back(par);
	}
	/*for (int i = 0; i < cars.size()-1; i++) // cars.size() -1 because the last one is in there twice for some reason
	{
		cout << cars[i].date << ' ' << cars[i].timeInHour << ':' << cars[i].timeInMin << ' ' << cars[i].timeOutHour << ':' << cars[i].timeOutMin << ' ' 
		<< cars[i].make << ' ' << cars[i].model << ' ' << cars[i].licensePlate << endl;
	}*/
	in.clear();
	in.close();
	cout << '\n';
	for (int q = 1; q < cars.size() - 1; q++)
	{
		if (SuspectCheck(thefts, cars[q].date, cars[q].timeInHour, cars[q].timeInMin, cars[q].timeOutHour, cars[q].timeOutMin) == true)
		{
			cout << "Information for suspect car:" << endl;
			cout << cars[q].date << "  Time in: " << cars[q].timeInHour << ':' << cars[q].timeInMin << "  Time out: " << cars[q].timeOutHour << ':' << cars[q].timeOutMin << "  "
				<< cars[q].make << ' ' << cars[q].model << ' ' << cars[q].licensePlate << '\n' << endl;
		}
	}

}

bool SuspectCheck(vector<TheftInfo> thief, string d, string tih, string tim, string toh, string tom)
{
	float th, tm, tihi, timi, tohi, tomi;
	
	for (int i = 0; i < thief.size(); i++)
	{
		tm = stof(thief[i].timeMin)/60;
		th = stof(thief[i].timeHour) + tm;
		timi = stof(tim)/60;
		tomi = stof(tom)/60;
		tihi = stof(tih) + timi;
		tohi = stof(toh) + tomi;
		
		if (d == thief[i].date && tihi < th && tohi > th)
			return true;
	}
	return false;
}