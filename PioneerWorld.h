#ifndef _PIONEERWORLD_H
#define _PIONEERWORLD_H

#include "PioneerAM.h";
#include <string>

#define PIONEERWORLD_AM_MIN 531
#define PIONEERWORLD_AM_MAX 1602
#define SCAN_INCREMENT 9

class PioneerWorld : public PioneerAM
{
public:
	// constructor
	PioneerWorld(void) : PioneerAM()
	{
		SetName("Pioneer XS440-WRLD");
		SetCurrentStation(531);

		// set AM default presets to 531 instead of 530
		for (int i = 0; i < TOTAL_BUTTONS; ++i)
		{
			SetButton(i);
		}
	}

	virtual void ScanUp(void)
	{
		if (GetCurrentStation() == PIONEERWORLD_AM_MAX)
		{
			SetCurrentStation(PIONEERWORLD_AM_MIN);
		}
		else
		{
			SetCurrentStation(GetCurrentStation() + SCAN_INCREMENT);
		}
	}

	virtual void ScanDown(void)
	{
		if (GetCurrentStation() == PIONEERWORLD_AM_MIN)
		{
			SetCurrentStation(PIONEERWORLD_AM_MAX);
		}
		else
		{
			SetCurrentStation(GetCurrentStation() - SCAN_INCREMENT);
		}
	}

	virtual ~PioneerWorld(void)
	{
		if (GetName() == "Pioneer XS440-WRLD")
		{
			printf("\nDestroying %s Radio", GetName().c_str());
		}
	}
};
#endif