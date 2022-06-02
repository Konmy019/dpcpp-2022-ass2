#pragma once
#include "Person.h"

#include <memory>
#include <vector>
#include <list>

#include "PatientAlertLevels.h"
#include "AlertLevel.h"
#include "PatientManagementSystem.h"

// forward declare classes
class Vitals;

class Diagnosis {
public:
	static const std::string SIMIAN_FLU;
	static const std::string GREYSCALE;
	static const std::string BONEITIS;
};

class Patient : public Person {
public:
	Patient();

	Patient(CAlertLevel* AlertLevel);

	Patient(const std::string& firstName, const std::string& lastName, std::tm birthday);

	virtual ~Patient();
	// return a calculated age for the patient
	// this calculation is not accurate, but is suitable for assignment purposes
	int age() const;

	// return a "unique" ID generated for the patient
	// this id is generated purely from patient details, and as such may have collisions
	std::string uid() const;
	
	// returns a "nice" ID for humans to interpret: lastname, firstname (UID)
	std::string humanReadableID() const;

	// patients have diagnoses of a disease
	// Note: the initial design consider multiple diagnoses added using addDiagnosis.
	// This was refactored to only consider the primary (i.e. the first) diagnosis.
	void addDiagnosis(const std::string& diagnosis);
	const std::string& primaryDiagnosis() const;

	void addVitals(const Vitals* v);
	const std::vector<const Vitals*> vitals() const;

	// patients have an alert level (green, yellow, orange, red) calculated from their disease and and their last vitals
	void setAlertLevel(AlertLevel level);
	const AlertLevel alertLevel() const { return _alertLevel; }

	void addAlertLevelObserver(AlertLevelBase* alBase);
protected:
	std::vector<std::string> _diagnosis;
	std::vector<const Vitals*> _vitals;
	AlertLevel _alertLevel;

	friend std::ostream& operator<<(std::ostream& os, const Patient& p);
	friend std::istream& operator>>(std::istream& is, Patient& p);

	CAlertLevel* _vAlertLevel;
	std::list<AlertLevelBase*> _alertLevelBase;
	void setNotification(AlertLevel alertLevel);
	
	friend std::ostream& operator<<(std::ostream& os, const Patient& p);
	friend std::istream& operator>>(std::istream& is, Patient& p);
};

