#include "resource_manager.h"

int reqired_power = 0;
int power_avalible = 1000;

int money = 100000; //,000s

int hospitals = 0; //number of hospitals
int police = 0; //Number of police stations
int schools = 0;

int population = 0;
int number_of_shops = 0;

int getBalance()
{
    return money;
}

int changeBalance(int value)
{
    money += value;
}

bool canAfford(int value)
{
    return value <= money;
}

int addHospitalToCount()
{
    hospitals++;
}

int getNumberOfPolice()
{
    return police;
}

float populationPerPolice()
{
    return (float)getPopulation()/(float)police;
}

int addPoliceToCount()
{
    police++;
}

int getNumberOfHospitals()
{
    return hospitals;
}

int getPopulation()
{
    return population;
}

void setPopulation(int pop)
{
    population = pop;
}

int getNumberOfSchools()
{
    return schools;
}

float populationPerSchool()
{
    return (float)getPopulation()/(float)schools;
}

int addSchoolToCount()
{
    schools++;
}
