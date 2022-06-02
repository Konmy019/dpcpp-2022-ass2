#include "Patient.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <map>
#include <list>

#include "Vitals.h"
#include "AlertLevel.h"
#include "PatientManagementSystem.h"
#include "HospitalAlertSystemFacade.h"
#include "GPNotificationSystemFacade.h"

using namespace std;

const std::string Diagnosis::SIMIAN_FLU = "SimianFlu";
const std::string Diagnosis::GREYSCALE = "Greyscale";
const std::string Diagnosis::BONEITIS = "Boneitis";

Patient::Patient()
{ }

Patient::Patient(CAlertLevel* AlertLevel) :
	_vAlertLevel(AlertLevel)
{ }

Patient::Patient(const std::string& firstName, const std::string& lastName, std::tm birthday) :
	Person(firstName, lastName, birthday),
	_alertLevel(AlertLevel::Green)
{ }

Patient::~Patient()
{
	for (auto v : _vitals)
	{
		delete v;
	}
	delete _vAlertLevel;

	for (auto o : _alertLevelBase)
	{
		delete o;
	}
}

int Patient::age() const
{
	// an inaccurate age estimate but fine for assignment purposes
	return 2022 - (1900 + _birthday.tm_year);
}

std::string Patient::uid() const
{
	std::stringstream ss;
	ss << (char)std::tolower(_lastName.at(0))
		<< (char)std::tolower(_firstName.at(0))
		<< std::setfill('0') << std::setw(2) << (_birthday.tm_mon + 1)
		<< _birthday.tm_year;
	return ss.str();
}

std::string Patient::humanReadableID() const
{
	return "" + _lastName + ", " + _firstName + " (" + uid() + ")";
}

std::ostream& operator<<(std::ostream& os, const Patient& p)
{
	os << p.uid() << "|" << p._lastName << "," << p._firstName << "|" << std::put_time(&p._birthday, "%d-%m-%Y") << "|" << p.primaryDiagnosis();

	os << "|";
	for (int i = 0; i < p.vitals().size(); ++i) {
		auto v = p.vitals()[i];
		os << *v;
		if (i != p.vitals().size() - 1) {
			os << ";";
		}
	}
	return os;
}

std::istream& operator>>(std::istream& is, Patient& p)
{
	string line;
	getline(is, line);
	stringstream ss(line); 

	string strid;
	getline(ss, strid, '|');
	getline(ss, p._lastName, ',');
	getline(ss, p._firstName, '|');

	string strdob;
	getline(ss, strdob, '|');
	tm t{ };
	istringstream iss(strdob);
	iss >> get_time(&t, "%d-%m-%Y");
	p._birthday = t;

	string primaryDiagnosis;
	getline(ss, primaryDiagnosis, '|');
	p.addDiagnosis(primaryDiagnosis);

	while (!ss.eof()) 
	{
		string strvitalLines;
		getline(ss, strvitalLines, ';');

		if (strvitalLines != "") {
			stringstream vl(strvitalLines);
			string btString;
			getline(vl, btString, ',');
			float bt = stoi(btString);
			string bpString;
			getline(vl, bpString, ',');
			int bp = stoi(bpString);
			string hrString;
			getline(vl, hrString, ',');
			int hr = stoi(hrString);
			string rrString;
			getline(vl, rrString, ',');
			int rr = stoi(rrString);
			const Vitals* vital = new Vitals(bt, bp, hr, rr);
			p.addVitals(vital);
		}
	}

	return is;
}


void Patient::addDiagnosis(const std::string& diagnosis)
{
	_diagnosis.push_back(diagnosis);
}

const std::string& Patient::primaryDiagnosis() const
{
	return _diagnosis.front();
}

void Patient::addVitals(const Vitals* v)
{
	_vitals.push_back(v);

	// TODO: calculate alert levels
	if (this->primaryDiagnosis() == "Boneitis")
	{
		_vAlertLevel = new CBoneitis_Vitals(v->RR());
	}
	else if (this->primaryDiagnosis() == "Greyscale")
	{
		auto age = this->age();
		_vAlertLevel = new CGreyscale_Vitals(age, v->HR());
	}
	else if (this->primaryDiagnosis() == "SimianFlu") 
	{
		_vAlertLevel = new CSimianFlu_Vitals(v->BP());
	}

	// calc alter level
	_vAlertLevel->calAlertLevel(*this);
}

const std::vector<const Vitals*> Patient::vitals() const
{
	return _vitals;
}

void Patient::setAlertLevel(AlertLevel level)
{
	_alertLevel = level;
	if (_alertLevel > AlertLevel::Green) {
		cout << "Patient: " << humanReadableID() << "has an alert level: ";
		switch (_alertLevel) {
		case AlertLevel::Yellow:
			cout << "Yellow";
			break;
		case AlertLevel::Orange:
			cout << "Orange";
			break;
		case AlertLevel::Red:
			cout << "Red";
			break;
		}
		cout << endl;
	}

	this->addAlertLevelObserver(new HospitalAlertSystemFacade);
	this->addAlertLevelObserver(new GPNotificationSystemFacade);
	setNotification(level);
	this->_alertLevelBase.clear();
}

void Patient::addAlertLevelObserver(AlertLevelBase* alObserver)
{
	_alertLevelBase.push_back(alObserver);
}

void Patient::setNotification(AlertLevel alertLevel)
{
	for (AlertLevelBase* alertObserver : _alertLevelBase) {
		alertObserver->sendAlertForPatient(this);
	}
}