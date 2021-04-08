/************************************************************************************************
 * FILE: AmFmRadio.cpp
 * PURPOSE: This file contains the definitions for the class methods belonging to the AmFmRadio
 *			class.
 *
 ************************************************************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "AmFmRadio.h"


 /*****************************************************************************************************
  *  Name    : AmFmRadio -- CONSTRUCTOR
  *  Purpose : instantiates an AmFmRadio object with the option of initializing it to be on or off
  *  Inputs  : a bool that initializes the object with the power either on (true) or off (false)
  *  Outputs : NONE
  *  Returns : NONE
  *
  *****************************************************************************************************/
AmFmRadio::AmFmRadio(bool powerStatus)
{
	for (int i = 0; i < TOTAL_BUTTONS; ++i)
	{
		buttons[i].AMFreq = buttonsCopy[i].AMFreq = AM_MIN;
	}
	for (int j = 0; j < TOTAL_BUTTONS; ++j)
	{
		buttons[j].FMFreq = buttonsCopy[j].FMFreq = FM_MIN;
	}


	currentStation = AM_MIN;
	savedFreqs.AMFreq = (int)currentStation;
	savedFreqs.FMFreq = FM_MIN;
	strcpy_s(currentBand, BAND_LEN, "AM");
	strcpy_s(currentBandCopy, BAND_LEN, "AM");
	volume = NO_VOLUME;
	savedVolume = volume;
	on = powerStatus;
	displayOutput = false;
}



/*****************************************************************************************************
 *  Name    : AmFmRadio -- CONSTRUCTOR
 *  Purpose : instantiates an AmFmRadio object with the option of initializing it to be on or off, as
 *			  well as initializing the setting for the preset radio buttons
 *  Inputs  : bool powerStatus -- initializes radio power to true (on), false (off)
 *			  Freqs initialFreqPresets[] -- array of structs of type Freq that contain the presets for
 *											all of the buttons
 *  Outputs : NONE
 *  Returns : NONE
 *
 *****************************************************************************************************/

AmFmRadio::AmFmRadio(Freqs initialFreqPresets[TOTAL_BUTTONS], bool powerStatus)
{
	for (int i = 0; i < TOTAL_BUTTONS; ++i)
	{
		// validate incoming frequencies; if invalid, set to defaults
		if (initialFreqPresets[i].AMFreq >= AM_MIN && initialFreqPresets[i].AMFreq <= AM_MAX)
		{
			buttons[i].AMFreq = buttonsCopy[i].AMFreq = initialFreqPresets[i].AMFreq;
		}
		else
		{
			buttons[i].AMFreq = buttonsCopy[i].AMFreq = AM_MIN;
		}

	}
	for (int j = 0; j < TOTAL_BUTTONS; ++j)
	{
		// validate incoming frequencies; if invalid, set to defaults
		if (initialFreqPresets[j].FMFreq >= FM_MIN && initialFreqPresets[j].FMFreq <= FM_MAX)
		{
			buttons[j].FMFreq = buttonsCopy[j].FMFreq = initialFreqPresets[j].FMFreq;
		}
		else
		{
			buttons[j].FMFreq = buttonsCopy[j].FMFreq = FM_MIN;
		}
	}

	currentStation = AM_MIN;
	savedFreqs.AMFreq = (int)currentStation;
	savedFreqs.FMFreq = FM_MIN;
	strcpy_s(currentBand, BAND_LEN, "AM");
	strcpy_s(currentBandCopy, BAND_LEN, "AM");
	volume = NO_VOLUME;
	savedVolume = volume;
	on = powerStatus;
	displayOutput = false;
}



/*****************************************************************************************************
 *  Name    : PowerToggle
 *  Purpose : toggles the power of the radio between on and off
 *  Inputs  : NONE
 *  Outputs : NONE
 *  Returns : NONE
 *
 *****************************************************************************************************/

void AmFmRadio::PowerToggle(void)
{
	if (on == false)
	{
		on = true;
		volume = savedVolume;
	}
	else
	{
		on = false;
		volume = NO_VOLUME;
	}
}



/*****************************************************************************************************
 *  Name    : IsRadioOn
 *  Purpose : gets/returns the current power status of the radio
 *  Inputs  : NONE
 *  Outputs : NONE
 *  Returns : a bool that represents on or off
 *
 *****************************************************************************************************/

bool AmFmRadio::IsRadioOn(void)
{
	return on;
}



/*****************************************************************************************************
 *  Name    : SetVolume
 *  Purpose : allows the user to adjust the volume of the radio object and sets the volume attribute
 *  Inputs  : NONE
 *  Outputs : a message asking the user to enter a new volume level
 *  Returns : an int that is the number the user entered
 *
 *****************************************************************************************************/

int AmFmRadio::SetVolume(void)
{
	if (on) {
		char buf[20] = "";

		printf("\nEnter the volume level (0 - 100). ");
		fgets(buf, sizeof buf, stdin);

		return SetVolume(atoi(buf));
	}

}



/*****************************************************************************************************
 *  Name    : SetVolume - OVERLOADED
 *  Purpose : allows the user to adjust the volume of the radio object and sets the volume attribute;
 *			  also can set the objects volume by passing in a valur
 *  Inputs  : int vol -- a number representing the desired volume
 *  Outputs : NONE
 *  Returns : an int that represents status codes
 *
 *****************************************************************************************************/

int AmFmRadio::SetVolume(int vol) {

	volume = savedVolume = vol;

	if (volume < 0) //if user enters volume less than 0, volume = 0
	{
		volume = savedVolume = 0;
		return 0;
	}

	else if (volume > 100) //if user enters volume greater than 100, volume = 100
	{
		volume = savedVolume = 100;
		return 2;
	}
	return 1;
}



/*****************************************************************************************************
 *  Name    : ToggleBand
 *  Purpose : toggles the radio between AM and FM
 *  Inputs  : NONE
 *  Outputs : NONE
 *  Returns : NONE
 *
 *****************************************************************************************************/

void AmFmRadio::ToggleBand(void)
{
	if (strcmp(currentBand, "AM") == 0)
	{
		strcpy_s(currentBand, BAND_LEN, "FM");

		// set the current station to the last FM frequency saved
		SetCurrentStation(savedFreqs.FMFreq);
	}
	else
	{
		strcpy_s(currentBand, BAND_LEN, "AM");

		// set the current station to the last FM frequency saved
		SetCurrentStation(savedFreqs.AMFreq);
	}
}



/*****************************************************************************************************
 *  Name    : SetButton
 *  Purpose : sets a specified buttons frequency to the current station
 *  Inputs  : int buttonNum -- the button number
 *  Outputs : NONE
 *  Returns : an int that represents status codes; 0 = error, 1 = success
 *
 *****************************************************************************************************/

int AmFmRadio::SetButton(int buttonNum)
{
	if ((buttonNum >= 0) && (buttonNum <= 4))
	{
		if (strcmp("AM", currentBand) == 0)
		{
			buttons[buttonNum].AMFreq = (int)currentStation;
		}
		else
		{
			buttons[buttonNum].FMFreq = currentStation;
		}
		return 1;

	}
	return 0;
}



/*****************************************************************************************************
 *  Name    : SelectButtonStation
 *  Purpose : changes the current station to one of the stations saved in the preset buttons
 *  Inputs  : int buttonNum -- the chosen button
 *  Outputs : NONE
 *  Returns : an int that represents status codes; 0 = error, 1 = success
 *
 *****************************************************************************************************/

int AmFmRadio::SelectButtonStation(int buttonNum)
{
	if ((buttonNum >= 0) && (buttonNum <= TOTAL_BUTTONS - 1))
	{
		if (strcmp("AM", currentBand) == 0)
		{
			SetCurrentStation(buttons[buttonNum].AMFreq);
		}
		else
		{
			SetCurrentStation(buttons[buttonNum].FMFreq);
		}

		return 1;
	}
	return 0;
}



/*****************************************************************************************************
 *  Name    : ShowCurrentSettings
 *  Purpose : displays all of the main attributes of the AmFmRadio object.
 *  Inputs  : NONE
 *  Outputs : - a message about whether the radio is on or off
 *			  - the current frequency
 *	          - the current volume
 *			  - the current station
 *			  - AM button settings
 *			  - FM button settings
 *  Returns : NONE
 *
 *****************************************************************************************************/

void AmFmRadio::ShowCurrentSettings(void)
{

	if (on == true)
	{
		printf("\n\nRadio is on. \n");
	}
	else
	{
		printf("\n\nRadio is off. \n");
	}

	printf("\nFrequency: %s\n", currentBand);
	printf("Volume: %d\n", volume);

	// eliminate decimal from AM reading
	if (strcmp(currentBand, "AM") == 0)
	{
		printf("Current Station: %d %s\n", (int)currentStation, currentBand);
	}
	else
	{
		printf("Current Station: %.1f %s\n", currentStation, currentBand);
	}

	printf("AM Button Settings: ");
	for (int i = 0; i < TOTAL_BUTTONS; ++i)
	{
		printf("%d) %6d ", i + 1, buttons[i].AMFreq);
	}

	printf("\nFM Button Settings: ");
	for (int j = 0; j < TOTAL_BUTTONS; ++j)
	{
		printf("%d) %6.1f ", j + 1, buttons[j].FMFreq);
	}
}



/*****************************************************************************************************
 *  Name    : ScanUp
 *  Purpose : increases the radio frequency (by .2 if FM and by 10 if AM)
 *  Inputs  : NONE
 *  Outputs : displays the new current station after the station has moved up, only if displayOutput
 *			  is true
 *  Returns : NONE
 *
 *****************************************************************************************************/

void AmFmRadio::ScanUp(void)
{
	if (strcmp("AM", currentBand) == 0)
	{
		//if current_station is 1700, then currentStation becomes 530
		if (currentStation == AM_MAX)
		{
			SetCurrentStation(AM_MIN);
		}
		else
		{
			SetCurrentStation(currentStation + 10);
		}
	}
	else
	{
		// if the current_station is greater than 109.7 the current_station becomes 87.9
		// (greater than accounts for the potential problem of floating point inaccuracy 
		// and equality comparisons)
		if (currentStation > FM_MAX)
		{
			SetCurrentStation(FM_MIN);
		}
		else
		{
			SetCurrentStation(currentStation + .2);
		}
	}

	// display current station if display is set to true
	if (displayOutput)
	{
		if (strcmp(currentBand, "AM") == 0)
		{
			printf("\nCurrent station: %d %s\n", (int)currentStation, currentBand);
		}
		else
		{
			printf("\nCurrent station: %.1f %s\n", currentStation, currentBand);
		}
	}
}



/*****************************************************************************************************
 *  Name    : ScanDown
 *  Purpose : decreases the radio frequency (by .2 if FM and by 10 if AM)
 *  Inputs  : NONE
 *  Outputs : displays the new current station after the station has moved only, only if displayOutput
 *			  is true
 *  Returns : NONE
 *
 *****************************************************************************************************/

void AmFmRadio::ScanDown(void)
{
	if (strcmp("AM", currentBand) == 0)
	{
		//if current_station is 530, the current_station becomes 1700
		if (currentStation == AM_MIN)
		{
			SetCurrentStation(AM_MAX);
		}
		else
		{
			SetCurrentStation(currentStation - 10);
		}
	}
	else
	{
		// if the current_station is less than 87.9 the current_station becomes 107.9
		// (less than accounts for the potential problem of floating point inaccuracy 
		// and equality comparisons)
		if (currentStation < FM_MIN)
		{
			SetCurrentStation(FM_MAX);
		}
		else
		{
			SetCurrentStation(currentStation - .2);
		}
	}

	// display current station if display is set to true
	if (displayOutput)
	{
		if (strcmp(currentBand, "AM") == 0)
		{
			printf("\nCurrent station: %d %s\n", (int)currentStation, currentBand);
		}
		else
		{
			printf("\nCurrent station: %.1f %s\n", currentStation, currentBand);
		}
	}
}



/*****************************************************************************************************
 *  Name    : SetDisplayOutput
 *  Purpose : toggles the displayOutput data-member between true and false
 *  Inputs  : NONE
 *  Outputs : NONE
 *  Returns : NONE
 *
 *****************************************************************************************************/

void AmFmRadio::SetDisplayOutput(void)
{
	if (displayOutput == false)
	{
		displayOutput = true;
	}
	else
	{
		displayOutput = false;
	}
}



/*****************************************************************************************************
 *  Name    : SetCurrentStation
 *  Purpose : changes the current station of the radio to any valid frequency
 *  Inputs  : double newStation -- the station to change to
 *  Outputs : NONE
 *  Returns : an int that represents status codes; 0 = error, 1 = success
 *
 *****************************************************************************************************/

int AmFmRadio::SetCurrentStation(double newStation)
{
	if (strcmp("AM", currentBand) == 0)
	{
		currentStation = (int)newStation;
		savedFreqs.AMFreq = (int)currentStation;
		return 1;
	}
	else
	{
		currentStation = newStation;
		savedFreqs.FMFreq = currentStation;
		return 1;
	}

	return 0;
}



/*****************************************************************************************************
 *  Name    : GetButtons
 *  Purpose : gets/returns the array of structs that contain the information about the preset buttons
 *  Inputs  : NONE
 *  Outputs : NONE
 *  Returns : a pointer to the first struct in the array of structs that holds the button info
 *
 *****************************************************************************************************/

Freqs* AmFmRadio::GetButtons(void)
{
	memcpy(buttonsCopy, buttons, sizeof(buttons));
	return buttonsCopy;
}



/*****************************************************************************************************
 *  Name    : GetCurrentStation
 *  Purpose : gets/returns the current radio station value
 *  Inputs  : NONE
 *  Outputs : NONE
 *  Returns : the current radio station
 *
 *****************************************************************************************************/

double AmFmRadio::GetCurrentStation(void)
{
	return currentStation;
}



/*****************************************************************************************************
 *  Name    : GetCurrentBand
 *  Purpose : gets/returns the current band status (i.e. AM or FM)
 *  Inputs  : NONE
 *  Outputs : NONE
 *  Returns : a copy of the currentBand attribute as a char pointer
 *
 *****************************************************************************************************/

char* AmFmRadio::GetCurrentBand(void)
{
	memcpy(currentBandCopy, currentBand, sizeof(currentBand));
	return currentBandCopy;
}



/*****************************************************************************************************
 *  Name    : GetVolume
 *  Purpose : gets/returns the current volume
 *  Inputs  : NONE
 *  Outputs : NONE
 *  Returns : the current volume
 *
 *****************************************************************************************************/

int	AmFmRadio::GetVolume(void)
{
	return volume;
}



/*****************************************************************************************************
 *  Name    : GetDisplayOutput
 *  Purpose : determines whether or not the AmFmRadio class's displayOutput attribute it set to true
 *			  or false
 *  Inputs  : NONE
 *  Outputs : NONE
 *  Returns : a bool that indicates whether the object is displaying outputs from within its methods
 *
 *****************************************************************************************************/

bool AmFmRadio::GetDisplayOutput(void)
{
	return displayOutput;
}



/*****************************************************************************************************
 *  Name    : AmFmRadio -- DESTRUCTOR
 *  Purpose : destroys the AmFmRadio object
 *  Inputs  : NONE
 *  Outputs : a message saying the object has been destroyed
 *  Returns : NONE
 *
 *****************************************************************************************************/

AmFmRadio::~AmFmRadio(void)
{
	if (displayOutput) {
		printf("Destroying AmFmRadio");
	}
}


