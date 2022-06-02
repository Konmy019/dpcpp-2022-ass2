#pragma once

#include "Patient.h"
#include "AlertLevel.h"


class HospitalAlertSystemFacade : public AlertLevelBase
{
public:
	HospitalAlertSystemFacade();
	virtual ~HospitalAlertSystemFacade();

	virtual void sendAlertForPatient(Patient* p) override;
};

