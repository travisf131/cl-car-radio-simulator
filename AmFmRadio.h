/************************************************************************************************
 * FILE:    AmFmRadio.h
 * PURPOSE: The AmFmRadio class is a C++ class designed to model a car radio with both AM and FM
 *			frequency bands. The radio model displays a menu interface that gives the user the
 *			ability to toggle the power, change its volume, scan up or scan down the frequency
 *			on both frequency bands, and exit the program.
 * 
 *			It also comes with 5 channel preset buttons for both the AM and FM
 *	 		bands, any of which the user can either select (to change the current channel) or set
 *			(to change the preset channel stored on that button).
 *
 ************************************************************************************************/

#ifndef _AMFMRADIO_H
#define _AMFMRADIO_H

#define TOTAL_BUTTONS 5
#define BAND_LEN 3
#define FM_MIN 87.9
#define FM_MAX 107.9
#define AM_MIN 530
#define AM_MAX 1700
#define NO_VOLUME 0 

struct Freqs
{
	int AMFreq;
	double FMFreq;
};

class AmFmRadio
{
private:
	Freqs	buttons[TOTAL_BUTTONS];
	Freqs	buttonsCopy[TOTAL_BUTTONS];
	Freqs   savedFreqs;
	double	currentStation;
	char	currentBand[BAND_LEN];
	char    currentBandCopy[BAND_LEN];
	int		volume;
	int     savedVolume;
	bool	on;
	bool    displayOutput;

public:

	// constructors
	AmFmRadio(bool powerStatus = false);
	AmFmRadio(struct Freqs initialFreqPresets[TOTAL_BUTTONS], bool powerStatus = false);

	// mutators
	void PowerToggle(void);
	virtual void ToggleBand(void);
	int SetButton(int buttonNum);
	int SelectButtonStation(int buttonNum);
	int SetVolume(void);
	int SetVolume(int vol);
	int SetCurrentStation(double newStation);
	void SetDisplayOutput(void);
	virtual void ScanUp(void);
	virtual void ScanDown(void);

	// accessors	
	bool IsRadioOn(void);
	Freqs* GetButtons(void);
	double GetCurrentStation(void);
	char* GetCurrentBand(void);
	int	GetVolume(void);
	bool GetDisplayOutput(void);

	// display methods
	virtual void ShowCurrentSettings(void);

	// destructor 
	virtual ~AmFmRadio(void);

};
#endif
