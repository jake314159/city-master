#include "resource_manager.h"


int reqired_power = 0;
int power_avalible = 1000;

int money = 100000; //,000s

int hospitals = 0; //number of hospitals

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

int getNumberOfHospitals()
{
    return hospitals;
}
