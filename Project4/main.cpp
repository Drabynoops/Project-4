#include "BSTMenu.h"

using namespace std;

int main()
{
	BSTMenu myMenu = BSTMenu();
	
	bool continueLoop = true;

	while (continueLoop)
	{
		myMenu.PrintMenu();
		continueLoop = myMenu.SelectMenuOption();
	}
}