#pragma once

#include "Patient.h"
#include "AlertLevel.h"


class GPNotificationSystemFacade : public AlertLevelBase {
public:
	GPNotificationSystemFacade();
	virtual ~GPNotificationSystemFacade();

	virtual void sendAlertForPatient(Patient* p) override;
};

