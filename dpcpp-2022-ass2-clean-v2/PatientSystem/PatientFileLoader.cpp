#include "PatientFileLoader.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

#include "Patient.h"
#include "Vitals.h" 

using namespace std;

std::vector<Patient*> PatientFileLoader::loadPatientFile(const std::string& file)
{
	vector<Patient*> patients{};
    
    std::ifstream inFile(file);
    if (inFile.is_open()) {
        // TODO: load your file here
        while (inFile.peek() != -1) {
            Patient* patient = new Patient{ }; //instantiate a new Patient 
            inFile >> *patient; // load the patient from the stream
            patients.push_back(patient); // add the patient to the vector
        }
    }
    return patients;
}
