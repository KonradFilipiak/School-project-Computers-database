#include "Manager.h"

int main()
{
	Manager manager;

	int usersChoice;

	do
	{
		manager.ShowMenu();

		// Reads the users choice
		while (scanf("%d", &usersChoice) == 0 || getchar() != '\n')
		{
			printf("Please try again: ");
			while (getchar() != '\n');
		}

		switch (usersChoice)	// 0 exits the program
		{
		case 1:
			manager.AddComputer();
			break;

		case 2:
			manager.RemoveComputer();
			break;

		case 3:
			manager.Sort();
			break;

		case 4:
			manager.ModifyComputer();
			break;

		case 5:
			manager.PrintComputers();
			break;

		case 6:
			manager.PrintList();
			break;

		default:
			std::cout << "There is no option with provided number.\n";
			break;
		}
	} while (usersChoice != 0);


	return 0;
}