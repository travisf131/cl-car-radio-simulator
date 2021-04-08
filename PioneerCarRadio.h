/************************************************************************************************
 * FILE:    PioneerCarRadio.h
 * PURPOSE: The PioneerCarRadio class is C++ class which is a child class of its parent, the
 *			AmFmRadio class. It therefore has all of the basic functionality of the AmFmRadio
 *			in general, with a few modifications.
 * 
 *			The Pioneer radio has a new interface that doesn't rely on a menu display. Instead,
 *			it shows all of the radio settings, and the user can interact with the radio by using
 *			different keypresses which trigger different actions on the radio. This makes the Pioneer
 *			radio feel more like an actual radio interface. The display also hides the settings display
 *			when the radio is turned off.
 * 
 *			It maintains the functionality of having the ability to toggle the power, change volume,
 *		    scan the frequency up or down, select and set preset buttons, and exit the program.
 *
 ************************************************************************************************/
#ifndef _PIONEERCARRADIO_H
#define _PIONEERCARRADIO_H

#include "AmFmRadio.h";
#include <string>

class PioneerCarRadio : public AmFmRadio
{
private:
	std::string name;

public:
	// constructor
	PioneerCarRadio(bool powerStatus = false);

	// mutator and accessor for new name attribute
	void SetName(std::string nameVal);
	std::string GetName(void);

	// display and keypress methods
	virtual void ShowCurrentSettings(void); // overridden display function
	void KeyPressHandler(char buttonChoice);

	virtual ~PioneerCarRadio(void);
};
#endif