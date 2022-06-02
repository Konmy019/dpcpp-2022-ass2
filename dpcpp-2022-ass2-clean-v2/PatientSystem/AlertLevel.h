#pragma once
#include "PatientAlertLevels.h"
class Patient;

class AlertLevelBase
{
public:
	virtual void sendAlertForPatient(Patient* p) = 0;
};

class CAlertLevel
{
public:
	virtual void calAlertLevel(Patient& patient) = 0;

};

class CBoneitis_Vitals : public CAlertLevel
{
public:
	CBoneitis_Vitals(int respiratoryRate);
	virtual void calAlertLevel(Patient& patient) override;
protected:
	int _respiratoryRate;
};

class CGreyscale_Vitals : public CAlertLevel
{
public:
	CGreyscale_Vitals(int age, int heartRate);
	virtual void calAlertLevel(Patient& patient) override;

protected:
	int _age;
	int _heartRate;
};

class CSimianFlu_Vitals : public CAlertLevel
{
public:
	CSimianFlu_Vitals(int bloodPressureRate);
	virtual void calAlertLevel(Patient& patient) override;

protected:
	int _bloodPressureRate;
};
