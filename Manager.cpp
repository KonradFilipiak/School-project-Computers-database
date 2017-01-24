#include "Manager.h"
#include "Desktop.h"
#include "Laptop.h"

Manager::Manager()
{
	computerList = new List();
	LoadList();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Manager::~Manager()
{
	file.open("Computers.txt", std::ios::out);

	computerList->SaveToFile(file);

	file.close();

	CreateReport();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Manager::LoadList()
{
	file.open("Computers.txt", std::ios::in);

	if (!file.good())
	{
		std::cout << "Could not open a file \"Computers.txt\".\n\n";
	}
	else
	{
		char tmp;	//Used to check whether given row in the file contains data of a laptop or a desktop

		std::string processorType, name;
		int ID;
		double processorClock, height, width, length, weight;

		while (!file.eof())
		{
			file >> ID;
			file >> name;
			file >> processorType;
			file >> processorClock;
			file >> weight;

			tmp = file.get();

			if (tmp == '\n')	// We know it is a laptop
			{
				computerList->AddTail(new Laptop(ID, name, processorType, processorClock, weight));
			}
			else if (tmp == ' ')	// We know it is a desktop
			{
				height = weight;
				file >> width;
				file >> length;

				computerList->AddTail(new Desktop(ID, name, processorType, processorClock, height, width, length));
			}
		}

		file.close();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Manager::ShowMenu()
{
	std::cout << "\n0) Exit. \n";
	std::cout << "1) Add a computer. \n";
	std::cout << "2) Remove a computer with given ID. \n";
	std::cout << "3) Sort the list by... \n";
	std::cout << "4) Modify a computer. \n";
	std::cout << "5) Print computers with given... \n";
	std::cout << "6) Print all of the computers. \n";
	std::cout << "Please select option: ";
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Manager::AddComputer()
{
	char usersChoice;		// We use to know if user wants a laptop or a desktop

	int ID;
	double processorClock;
	double weight;
	double height;
	double width;
	double length;
	std::string processorType;
	std::string name;

	std::cout << "Are you adding a laptop or a desktop? [L/D]: ";
	while (scanf("%c", &usersChoice) == 0 || (usersChoice != 'L' && usersChoice != 'D' && usersChoice != 'l' && usersChoice != 'd') || getchar() != '\n')
	{
		printf("Please try again: ");
		while (getchar() != '\n');
	}

	int(IComputer::*ptr)(void) const = &IComputer::ID;	//To check if computer with given ID exits. We do not want 2 computers with the same ID
	std::cout << "ID: ";
	while (scanf("%d", &ID) == 0 || computerList->FindItem(ptr, ID, static_cast<IComputer*>(computerList->Head())) || ID <= 0 || getchar() != '\n')
	{
		printf("Please try again(a computer with given ID might exist): ");
		while (getchar() != '\n');
	}

	std::cout << "Name: ";
	getline(std::cin, name);

	std::cout << "Processor type: ";
	getline(std::cin, processorType);

	std::cout << "Processor clock: ";
	while (scanf("%lf", &processorClock) == 0 || processorClock <= 0 || getchar() != '\n')
	{
		printf("Please try again: ");
		while (getchar() != '\n');
	}

	// If adding a laptop
	if (usersChoice == 'L' || usersChoice == 'l')
	{
		std::cout << "Weight: ";
		while (scanf("%lf", &weight) == 0 || weight <= 0 || getchar() != '\n')
		{
			printf("Please try again: ");
			while (getchar() != '\n');
		}

		computerList->AddTail(new Laptop(ID, name, processorType, processorClock, weight));
	}
	else	// If adding a desktop
	{
		std::cout << "Height: ";
		while (scanf("%lf", &height) == 0 || height <= 0 || getchar() != '\n')
		{
			printf("Please try again: ");
			while (getchar() != '\n');
		}

		std::cout << "Width: ";
		while (scanf("%lf", &width) == 0 || width <= 0 || getchar() != '\n')
		{
			printf("Please try again: ");
			while (getchar() != '\n');
		}

		std::cout << "Length: ";
		while (scanf("%lf", &length) == 0 || length <= 0 || getchar() != '\n')
		{
			printf("Please try again: ");
			while (getchar() != '\n');
		}

		computerList->AddTail(new Desktop(ID, name, processorType, processorClock, height, width, length));
	}

	std::cout << "A computer has been added.\n\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Manager::RemoveComputer()
{
	int ID;

	std::cout << "ID number of the computer: ";
	while (scanf("%d", &ID) == 0 || getchar() != '\n')
	{
		printf("Please try again: ");
		while (getchar() != '\n');
	}

	int(IComputer::*ptr)(void) const = &IComputer::ID;

	if (!(computerList->RemoveItem(ptr, ID)))
		std::cout << "Computer with given ID number does not exist.\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Manager::ModifyComputer()
{
	int ID;
	IComputer* computer = NULL;

	std::cout << "ID number of the computer: ";
	while (scanf("%d", &ID) == 0 || getchar() != '\n')
	{
		printf("Please try again: ");
		while (getchar() != '\n');
	}

	int(IComputer::*ptr)(void) const = &IComputer::ID;	//To check if computer with given ID exits. We do not want 2 computers with the same ID
	if (!(computer = static_cast<IComputer*>(computerList->FindItem(ptr, ID, static_cast<IComputer*>(computerList->Head())))))
		std::cout << "Computer with given ID does not exist.\n\n";
	else
	{
		COMPUTER_TYPE computerType;

		double processorClock;
		double weight;
		double height;
		double width;
		double length;
		std::string processorType;
		std::string name;

		std::cout << "Enter new values or \'0\' if you do not want any changes.\n";

		// ID
		std::cout << "\tID: ";
		while (scanf("%d", &ID) == 0 || computerList->FindItem(ptr, ID, static_cast<IComputer*>(computerList->Head())) || ID <= 0 || getchar() != '\n')
		{
			printf("Please try again(a computer with given ID might exist): ");
			while (getchar() != '\n');
		}
		if (ID != 0)
			computer->ID(ID);

		// name
		std::cout << "\tName: ";
		getline(std::cin, name);
		if (name != "0")
			computer->Name(name);

		// processor type
		std::cout << "\tProcessor type: ";
		getline(std::cin, processorType);
		if (processorType != "0")
			computer->ProcessorType(processorType);

		// processor clock
		std::cout << "\tProcessor clock: ";
		while (scanf("%lf", &processorClock) == 0 || processorClock < 0 || getchar() != '\n')
		{
			printf("Please try again: ");
			while (getchar() != '\n');
		}
		if (processorClock != 0)
			computer->ProcessorClock(processorClock);

		// checking if it is a laptop or a desktop
		computerType = computer->ComputerType();

		switch (computerType)
		{
		case CT_LAPTOP:			// we know it is a laptop

			// weight
			std::cout << "\tWeight: ";
			while (scanf("%lf", &weight) == 0 || weight < 0 || getchar() != '\n')
			{
				printf("Please try again: ");
				while (getchar() != '\n');
			}
			if (weight != 0)
				static_cast<Laptop*>(computer)->Weight(weight);

			break;
		case CT_DESKTOP:			//we know it is a desktop

			//height
			std::cout << "\tHeight: ";
			while (scanf("%lf", &height) == 0 || height < 0 || getchar() != '\n')
			{
				printf("Please try again: ");
				while (getchar() != '\n');
			}
			if (height != 0)
				static_cast<Desktop*>(computer)->Height(height);

			// width
			std::cout << "\tWidth: ";
			while (scanf("%lf", &width) == 0 || width < 0 || getchar() != '\n')
			{
				printf("Please try again: ");
				while (getchar() != '\n');
			}
			if (width != 0)
				static_cast<Desktop*>(computer)->Width(width);

			// lenght
			std::cout << "\tLength: ";
			while (scanf("%lf", &length) == 0 || length < 0 || getchar() != '\n')
			{
				printf("Please try again: ");
				while (getchar() != '\n');
			}
			if (length != 0)
				static_cast<Desktop*>(computer)->Length(length);

			break;
		default:
			std::cout << "\nSomething went wrong. The list contains a computer of undefine type. Program will exit and the changes will not be saved.\n";
			std::cout << "Please select ENTER...";
			std::cin.get();

			exit(1);
			break;
		}

		std::cout << "\nThe data has been changed.\n\n";

	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Manager::PrintComputers()
{
	int usersChoice;
	const int numberOfOptions = 4;

	std::cout << "0) Cancel.\n";
	std::cout << "1) ID number.\n";
	std::cout << "2) Processor clock.\n";
	std::cout << "3) Processor type.\n";
	std::cout << "4) Name.\n";

	std::cout << "Print computers with given...  ";

	while (scanf("%d", &usersChoice) == 0 || getchar() != '\n' || usersChoice < 0 || usersChoice > numberOfOptions)
	{
		printf("Please try again: ");
		while (getchar() != '\n');
	}

	switch (usersChoice)
	{
		case 1:	//ID
			PrintComputersWithGivenID();
			break;

		case 2:	//Processor clock
			PrintComputersWithGivenProcessorClock();
			break;

		case 3:	//Processor type
			PrintComputersWithGivenProcessorType();
			break;

		case 4:	//Name
			PrintComputersWithGivenName();
			break;

		default:
			std::cout << "Canceled.\n";
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Manager::Sort()
{
	int usersChoice;
	const int numberOfOptions = 4;

	std::cout << "0) Cancel.\n";
	std::cout << "1) ID number.\n";
	std::cout << "2) Processor clock.\n";
	std::cout << "3) Processor type.\n";
	std::cout << "4) Name.\n";

	std::cout << "Sort the list by...  ";

	while (scanf("%d", &usersChoice) == 0 || getchar() != '\n' || usersChoice < 0 || usersChoice > numberOfOptions)
	{
		printf("Please try again: ");
		while (getchar() != '\n');
	}

	switch (usersChoice)
	{
		case 1:	//ID
			SortByID();
			break;

		case 2:	//Processor clock
			SortByProcessorClock();
			break;

		case 3:	//Processor type
			SortByProcessorType();
			break;

		case 4:	//Name
			SortByName();
			break;
	}

	usersChoice != 0 ? std::cout << "The list has been sorted.\n" : std::cout << "Sorting canceled.\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Manager::PrintList()
{
	std::cout << "The list of all computers:\n";
	computerList->PrintList();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Manager::CreateReport()
{
	file.open("Report.txt", std::ios::out);

	// Gets the time in proper format
	time(&aclock);
	newtime = localtime(&aclock);
	strftime(timeInString, 22, "%d/%m/%Yr. %H:%M:%S", newtime);

	// Header
	file << "Database of computers (last update: " << timeInString << "):";
	file << "\n------------------------------------------------------------------------------------------\n";

	// List of computers
	computerList->PrintList(file);

	// Footer
	file << "------------------------------------------------------------------------------------------\n";
	file << "\tAuthor: Konrad Filipiak";

	file.close();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Manager::PrintComputersWithGivenID() const
{
	int id;

	std::cout << "ID: ";
	while (scanf("%d", &id) == 0 || getchar() != '\n')
	{
		printf("Please try again: ");
		while (getchar() != '\n');
	}

	int(IComputer::*ptr)(void) const = &IComputer::ID;

	if (!(computerList->PrintItem(ptr, id)))
		std::cout << "Computers with given id do not exist.\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Manager::PrintComputersWithGivenProcessorClock() const
{
	double processorClock;

	std::cout << "Processor clock: ";
	while (scanf("%lf", &processorClock) == 0 || getchar() != '\n')
	{
		printf("Please try again: ");
		while (getchar() != '\n');
	}

	double(IComputer::*ptr)(void) const = &IComputer::ProcessorClock;

	if (!(computerList->PrintItem(ptr, processorClock)))
		std::cout << "Computers with given processor clock do not exist.\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Manager::PrintComputersWithGivenProcessorType() const
{
	std::string processorType;

	std::cout << "Processor type: ";
	getline(std::cin, processorType);

	std::string(IComputer::*ptr)(void) const = &IComputer::ProcessorType;

	if (!(computerList->PrintItem(ptr, processorType)))
		std::cout << "Computers with given processor type do not exist.\n";
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Manager::PrintComputersWithGivenName() const
{
	std::string name;

	std::cout << "Computer's name: ";
	getline(std::cin, name);

	std::string(IComputer::*ptr)(void) const = &IComputer::Name;

	if (!(computerList->PrintItem(ptr, name)))
		std::cout << "Computer with given name does not exist.\n";
}