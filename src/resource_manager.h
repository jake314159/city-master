#include <stdbool.h>

int getBalance();
void changeBalance(int value);
void setBalance(int value);
bool canAfford(int value);

void addHospitalToCount();
int getNumberOfHospitals();
void setHospitalCount(int value);

int getNumberOfPolice();
void addPoliceToCount();
float populationPerPolice();
void setNumberOfPolice(int newValue);

int getNumberOfSchools();
float populationPerSchool();
void addSchoolToCount();
void setNumberOfSchools(int value);

int getPopulation();
void setPopulation(int pop);

void setWasteDisposalCapacity(int wdc);
bool enoughWasteDisposal();
float wasteDisposalUtilisation();


