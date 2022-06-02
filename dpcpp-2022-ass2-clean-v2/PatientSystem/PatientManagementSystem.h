#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>


// forward declare several classes
class AbstractPatientDatabaseLoader;
class FileLoader;
class PatientDatabaseLoader;
class HospitalAlertSystemFacade;
class GPNotificationSystemFacade;
class Patient;
class AlertLevelBase;
class PatientFileLoader;


class PatientManagementSystem
{
public:

	PatientManagementSystem();
	~PatientManagementSystem();

	// initialise the patient records
	void init();
	void run();

	// ask the user for a patient and vitals and add those vitals to the patient
	void addVitalsRecord();

	void printWelcomeMessage() const;
	void printMainMenu() const;
	void printPatients() const;

protected:
	std::vector<Patient*> _patients;
	std::map<std::string, Patient*> _patientLookup;	
	std::unique_ptr<AbstractPatientDatabaseLoader> _patientFileLoader;
	std::unique_ptr<AbstractPatientDatabaseLoader> _patientDatabaseLoader;
};

