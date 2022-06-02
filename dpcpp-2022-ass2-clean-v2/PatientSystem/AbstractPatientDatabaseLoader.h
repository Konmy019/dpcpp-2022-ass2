#pragma once

#include <vector>
#include "PatientFileLoader.h"

// forward declare the Patient class
class Patient;

class AbstractPatientDatabaseLoader {
public:
	// initialise the database connection
	virtual void initialiseConnection() = 0;
	virtual void loadPatients(std::vector<Patient*>& patientIn) = 0;
	virtual void closeConnection() = 0;
};

class CompositeDataLoader : public AbstractPatientDatabaseLoader
{
public:
	void addLoaders(AbstractPatientDatabaseLoader* loaders)
	{
		_loaders.push_back(loaders);
	}

	virtual void initialiseConnection() override
	{
		
	}

	virtual void loadPatients(std::vector<Patient*>& patientIn) override
	{
		for (auto comp : _loaders) {
			comp->loadPatients(patientIn);
		}
	}

	virtual void closeConnection() override
	{
	
	}

protected:
	std::vector<AbstractPatientDatabaseLoader*> _loaders;
};

class FileLoader : public AbstractPatientDatabaseLoader
{
public:
	virtual void initialiseConnection() override
	{}

	virtual void loadPatients(std::vector<Patient*>& patientIn) override
	{
		std::vector<Patient*> patientsList = _adaptee->loadPatientFile("patients.txt");
		for (auto* p : patientsList) {
			patientIn.push_back(p);
		}
	}

	virtual void closeConnection() override
	{}

protected:
	PatientFileLoader* _adaptee;
};