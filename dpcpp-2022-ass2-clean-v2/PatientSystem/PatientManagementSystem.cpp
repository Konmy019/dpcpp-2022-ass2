#include "PatientManagementSystem.h"

#include <iostream>
#include <map>
#include <tuple>

#include "Patient.h"
#include "PatientDatabaseLoader.h"
#include "PatientFileLoader.h"
#include "Vitals.h"

#include "GPNotificationSystemFacade.h"
#include "HospitalAlertSystemFacade.h"
#include "AbstractPatientDatabaseLoader.h"


using namespace std;


PatientManagementSystem::PatientManagementSystem() :
	_patientDatabaseLoader(std::make_unique<PatientDatabaseLoader>()),
	_patientFileLoader(std::make_unique<FileLoader>())
{
	_patientDatabaseLoader->initialiseConnection();
}

PatientManagementSystem::~PatientManagementSystem()
{
	_patientDatabaseLoader->closeConnection();
	// clear memory
	for (auto p : _patients) {
		delete p;
	} 
}

void PatientManagementSystem::init()
{
	auto d = new PatientDatabaseLoader();
	auto f = new FileLoader();
	auto df = new CompositeDataLoader();

	df->addLoaders(d);
	df->addLoaders(f);

	df->loadPatients(_patients);
	for (Patient* p : _patients) {
		_patientLookup[p->uid()] = p;
	}

	delete d;
	delete f;
	delete df;
}

void PatientManagementSystem::run()
{
	printWelcomeMessage();

	bool running = true;
	while (running) {
		printMainMenu();
		int option = 0;
		cin >> option;

		// handle basic errors
		if (cin.bad()) {
			cin.clear();
			cin.ignore();
			continue;
		}

		// switch based on the selected option
		switch (option) {
		case 1:
			printPatients();
			break;
		case 2:
			addVitalsRecord();
			break;
		case 3:
			running = false;
			break;
		}
	}
}

void PatientManagementSystem::addVitalsRecord()
{
	cout << "Patients" << endl;
	printPatients();
	cout << endl;
	cout << "Enter the patient ID to declare vitals for > ";
	
	string pid { "" };
	cin >> pid;
	if (_patientLookup.count(pid)) {
		float bodyTemperature;
		int bloodPressure;
		int heartRate;
		int respitoryRate;

		cout << "enter body temperature: ";
		cin >> bodyTemperature;
		cout << "enter blood pressure: ";
		cin >> bloodPressure;
		cout << "enter heart rate: ";
		cin >> heartRate;
		cout << "enter respitory rate: ";
		cin >> respitoryRate;

		Vitals* v = new Vitals(bodyTemperature, bloodPressure, heartRate, respitoryRate);
		_patientLookup[pid]->addVitals(v);
	}
	else {
		cout << "Patient not found" << endl;
	}
}

void PatientManagementSystem::printWelcomeMessage() const
{
	cout << "WELCOME TO HEALTHCO 3000" << endl;
	cout << "------------------------" << endl;
}

void PatientManagementSystem::printMainMenu() const
{
	cout << endl << "Select an option:" << endl;
	cout << "1. List patients" << endl;
	cout << "2. Add vitals record" << endl;
	cout << "3. Quit" << endl;
	cout << "> ";
}

void PatientManagementSystem::printPatients() const
{
	for (Patient* p : _patients) {
		std::cout << *p << std::endl;
	}
}
