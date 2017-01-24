#pragma once

#include <string>
#include <time.h>
#include "List.h"

class Manager {
public:

	Manager();
	~Manager();

	void LoadList();
	void ShowMenu();
	void AddComputer();
	void RemoveComputer();
	void ModifyComputer();
	void PrintComputers();
	void Sort();
	void PrintList();

private:
	std::fstream file;

	List* computerList;

	//variables to get the time and show it in the proper format
	struct tm* newtime;
	time_t aclock;
	char timeInString[22];

	void CreateReport();

	void SortByID() const {	int(IComputer::*ptr)(void) const = &IComputer::ID;	computerList->SortList(ptr); }
	void SortByProcessorClock() const { double(IComputer::*ptr)(void) const = &IComputer::ProcessorClock;	computerList->SortList(ptr); }
	void SortByProcessorType() const { std::string(IComputer::*ptr)(void) const = &IComputer::ProcessorType;	computerList->SortList(ptr); }
	void SortByName() const { std::string(IComputer::*ptr)(void) const = &IComputer::Name;	computerList->SortList(ptr); };

	void PrintComputersWithGivenID() const;
	void PrintComputersWithGivenProcessorClock() const;
	void PrintComputersWithGivenProcessorType() const;
	void PrintComputersWithGivenName() const;
};
