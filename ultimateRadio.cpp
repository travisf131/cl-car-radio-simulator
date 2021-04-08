#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PioneerWorld.h"
#include <conio.h>
#include <new>

#pragma warning(disable: 4996);

PioneerCarRadio* createRadio(std::string cmdArg);

int main(int argc, char* argv[])
{
	PioneerCarRadio * pRadio = NULL;

	std::string cmdArg = std::string(argv[1]);
	try
	{
		pRadio = createRadio(cmdArg);
	}
	catch (const char * e)
	{
		printf("%s", e);
		return 0;
	}

	char ch = ' ';
	while (true)
	{
		// display current radio
		pRadio->ShowCurrentSettings();
		ch = getch();
		pRadio->KeyPressHandler(ch);

		// exit chosen radio
		if (ch == 'x')
		{
			delete pRadio;

			// create new radio options
			while (true) 
			{
				char ch2 = ' ';
				ch2 = getch();

				if (ch2 == 'c')
				{
					pRadio = createRadio("-car");
					break;
				}
				else if (ch2 == 'a')
				{
					pRadio = createRadio("-am");
					break;
				}
				else if (ch2 == 'w')
				{
					pRadio = createRadio("-world");
					break;
				}
				else if (ch2 == 'x')
				{
					return 0;  // end program
				}
			}
		}
	}
	return 0;
}

PioneerCarRadio* createRadio(std::string cmdArg)
{
	if (cmdArg == "-car")
	{
		try
		{
			PioneerCarRadio* newRadio;
			newRadio = new PioneerCarRadio;
			return newRadio;
		}
		catch (std::bad_alloc& ba)
		{
			printf("bad_alloc caught: %s", ba.what());
		}
	}
	else if (cmdArg == "-am")
	{
		try
		{
			PioneerAM* newRadio;
			newRadio = new PioneerAM;
			return newRadio;
		}
		catch (std::bad_alloc& ba)
		{
			printf("bad_alloc caught: %s", ba.what());
		}
	}
	else if (cmdArg == "-world")
	{
		try
		{
			PioneerWorld* newRadio;
			newRadio = new PioneerWorld;
			return newRadio;
		}
		catch (std::bad_alloc& ba)
		{
			printf("bad_alloc caught: %s", ba.what());
		}
	}
	else
	{
		throw "Invalid command line argument. Please indicate a valid radio to create.";
	}
}