/************************************************************************************************
 * FILE: PioneerCarRadio.cpp
 * PURPOSE: This file contains the definitions for the class methods belonging to the PioneerCarRadio
 *			class.
 *
 ************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PioneerCarRadio.h"


 /*****************************************************************************************************
   *  Name    : PioneerCarRadio -- CONSTRUCTOR
   *  Purpose : instantiates PionnerCarRadio object with the option of initializing it to be on or off.
   *			   The default setting, when instantiated without any parameters is to set the radio to be
   *			   off.
   *  Inputs  : a bool that initializes the object with the power either on (true) or off (false)
   *  Outputs : NONE
   *  Returns : NONE
   *
   *****************************************************************************************************/
PioneerCarRadio::PioneerCarRadio(bool powerStatus) : AmFmRadio(false) {

	if (powerStatus == true)
	{
		if (IsRadioOn() == false)
		{
			PowerToggle();
		}
	}
	else
	{
		if (IsRadioOn() == true)
		{
			PowerToggle();
		}
	}

	name = "Pioneer XS440";
}



/********************************************************************************
 *  Name    : ShowCurrentSettings
 *  Purpose : displays all of the main attributes of the PioneerCarRadio object.
 *  Inputs  : NONE
 *  Outputs : - the name of the radio
			  - a message about whether the radio is on or off
			  If ON:
 *			  - the current station (+ band)
 *	          - the current volume
 *			  - AM button settings
 *			  - FM button settings
 *  Returns : NONE
 *
 ********************************************************************************/
void PioneerCarRadio::ShowCurrentSettings(void)
{
	system("CLS");
	if (IsRadioOn())
	{
		printf("%s", name.c_str());
		printf("\nRadio is on");
		printf("\nVolume: %d", GetVolume());

		if (strcmp(GetCurrentBand(), "AM") == 0)
		{
			printf("\nCurrent Station:  %d %s", (int)GetCurrentStation(), GetCurrentBand());
		}
		else
		{
			printf("\nCurrent Station:  %.1f %s", GetCurrentStation(), GetCurrentBand());
		}


		// display preset buttons
		Freqs* buttonPresets = GetButtons();
		printf("\nAM Buttons:\n");
		for (int i = 0; i < TOTAL_BUTTONS; ++i)
		{
			printf("%d: %d,  ", i + 1, buttonPresets->AMFreq);
			++buttonPresets;
		}

		// display PM preset buttons
		buttonPresets = GetButtons();
		printf("\nFM Buttons:\n");
		for (int i = 0; i < TOTAL_BUTTONS; ++i)
		{
			printf("%d: %.1f,  ", i + 1, buttonPresets->FMFreq);
			++buttonPresets;
		}
		printf("\n");
	}
	else
	{
		printf("%s", name.c_str());
		printf("\nRadio is off\n");
	}
}



/*****************************************************************************************************
 *  Name    : KeyPressHandler
 *  Purpose : processes key presses that correspond to different radio functionality. Each valid
 *			  key press triggers an action on the radio by calling various class methods. Invalid
 *			  key presses are ignored and don't do anything.
 *  Inputs  : char buttonChoise -- the character that was pressed by the user
 *  Outputs : NONE
 *  Returns : NONE
 *
 *****************************************************************************************************/
void PioneerCarRadio::KeyPressHandler(char buttonChoice)
{
	if (buttonChoice == 'o')  // toggle on/off
	{
		PowerToggle();
	}

	if (IsRadioOn())
	{
		switch (buttonChoice)
		{
		case '+':
			SetVolume(GetVolume() + 1);
			break;
		case '_':
			SetVolume(GetVolume() - 1);
			break;
		case '=':
			ScanUp();
			break;
		case '-':
			ScanDown();
			break;
		case 'b':
			ToggleBand();
			break;
		case '1':
			SelectButtonStation(0);
			break;
		case '2':
			SelectButtonStation(1);
			break;
		case '3':
			SelectButtonStation(2);
			break;
		case '4':
			SelectButtonStation(3);
			break;
		case '5':
			SelectButtonStation(4);
			break;
		case '!':
			SetButton(0);
			break;
		case '@':
			SetButton(1);
			break;
		case '#':
			SetButton(2);
			break;
		case '$':
			SetButton(3);
			break;
		case '%':
			SetButton(4);
			break;
		}
	}
}



/*************************************************************************
 *  Name    : SetName
 *  Purpose : changes the name of the Pioneer radio
 *  Inputs  : std::string nameVal -- the desired new name of the radio
 *  Outputs : NONE
 *  Returns : NONE
 *
 ************************************************************************/
void PioneerCarRadio::SetName(std::string nameVal)
{
	name = nameVal;
}



/*****************************************************************************
 *  Name    : GetName
 *  Purpose : retrieves/returns the current name of the Pioneer radio
 *  Inputs  : NONE
 *  Outputs : NONE
 *  Returns : std::string -- the current name of the radio
 *
 *****************************************************************************/
std::string PioneerCarRadio::GetName(void)
{
	return name;
}



/************************************************************************
 *  Name    : PioneerCarRadio -- DESTRUCTOR
 *  Purpose : destroys the PioneerCarRadio object
 *  Inputs  : NONE
 *  Outputs : a message saying the PioneerCarRadio has been destroyed
 *  Returns : NONE
 *
 ***********************************************************************/
PioneerCarRadio::~PioneerCarRadio(void)
{
	if (name == "Pioneer XS440")
	{
		printf("\nDestroying %s Radio", name.c_str());
	}
}
