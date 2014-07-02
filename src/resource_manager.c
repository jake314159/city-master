#include "resource_manager.h"

int reqired_power = 0;
int power_avalible = 1000;

int money = 100000; //,000s

int hospitals = 0; //number of hospitals
int police = 0; //Number of police stations
int schools = 0;

int population = 0;
int number_of_shops = 0;

int waste_disposal_capacity = 0;

int getBalance()
{
    return money;
}

void changeBalance(int value)
{
    money += value;
}

bool canAfford(int value)
{
    return value <= money;
}

void addHospitalToCount()
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

void addPoliceToCount()
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

void addSchoolToCount()
{
    schools++;
}

void setWasteDisposalCapacity(int wdc)
{
    waste_disposal_capacity = wdc;
}

bool enoughWasteDisposal()
{
    float amount_of_waste = population*(1.f/500.f) + schools*0.5f + police*0.5f + (float)hospitals;
    return amount_of_waste <= waste_disposal_capacity;
}

float wasteDisposalUtilisation()
{
    float amount_of_waste = population*(1.f/500.f) + schools*0.5f + police*0.5f + (float)hospitals;
    return 1.f-(amount_of_waste)/((float)waste_disposal_capacity);
}
