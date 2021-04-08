#ifndef _PIONEERAM_H
#define _PIONEERAM_H

#include "PioneerCarRadio.h";
#include <string>

class PioneerAM : public PioneerCarRadio
{
public:
	// constructor
	PioneerAM(void) : PioneerCarRadio(false)
	{
		SetName("Pioneer XS440-AM");

		// make sure radio is always set to AM by default
		if (strcmp(GetCurrentBand(), "FM") == 0)
		{
			ToggleBand();
		}
	}

	virtual void ToggleBand(void)
	{
		// toggle band only has the effect of initializing to AM, but cannot change to FM
		if (strcmp(GetCurrentBand(), "FM") == 0)
		{
			ToggleBand();
		}
	}

	virtual void ShowCurrentSettings(void)
	{
		system("CLS");
		if (IsRadioOn())
		{
			printf("%s", GetName().c_str());
			printf("\nRadio is on");
			printf("\nVolume: %d", GetVolume());
			printf("\nCurrent Station:  %d %s", (int)GetCurrentStation(), GetCurrentBand());

			// display AM preset buttons
			Freqs* buttonPresets = GetButtons();
			printf("\nAM Buttons:\n");
			for (int i = 0; i < TOTAL_BUTTONS; ++i)
			{
				printf("%d: %d,  ", i + 1, buttonPresets->AMFreq);
				++buttonPresets;
			}
			printf("\n");
		}
		else
		{
			printf("%s", GetName().c_str());
			printf("\nRadio is off\n");
		}
	}

	virtual ~PioneerAM(void)
	{
		if (GetName() == "Pioneer XS440-AM")
		{
			printf("\nDestroying %s Radio", GetName().c_str());
		}
	}
};
#endif