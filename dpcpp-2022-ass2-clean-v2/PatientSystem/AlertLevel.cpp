#include "AlertLevel.h"
#include "Patient.h"

// CBoneitis_Vitals
CBoneitis_Vitals::CBoneitis_Vitals(int respiratoryRate) :
	_respiratoryRate(respiratoryRate)
{ }

void CBoneitis_Vitals::calAlertLevel(Patient& patient)
{
	if (_respiratoryRate > 40) {
		patient.setAlertLevel(AlertLevel::Red);
	}
	else if (_respiratoryRate > 30) {
		patient.setAlertLevel(AlertLevel::Orange);
	}
	else if (_respiratoryRate > 20) {
		patient.setAlertLevel(AlertLevel::Yellow);
	}
}

// CGreyscale_Vitals
CGreyscale_Vitals::CGreyscale_Vitals(int age, int heartRate) :
    _age(age),
    _heartRate(heartRate)
{ }

void CGreyscale_Vitals::calAlertLevel(Patient& patient)
{
    if (_age < 12) {
        if (_heartRate > 120) {
            patient.setAlertLevel(AlertLevel::Red);
        }
    }
    else {
        if (_heartRate > 100) {
            patient.setAlertLevel(AlertLevel::Red);
        }
    }
}

// CSimianFlu_Vitals
CSimianFlu_Vitals::CSimianFlu_Vitals(int bloodPressureRate) :
    _bloodPressureRate(bloodPressureRate)
{ }

void CSimianFlu_Vitals::calAlertLevel(Patient& patient)
{
    if (_bloodPressureRate > 140) {
        patient.setAlertLevel(AlertLevel::Red);
    }
    else if (_bloodPressureRate > 130) {
        patient.setAlertLevel(AlertLevel::Orange);
    }
    else if (_bloodPressureRate > 110) {
        patient.setAlertLevel(AlertLevel::Yellow);
    }
}