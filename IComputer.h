#pragma once

#include <string>
#include "IListItem.h"

enum COMPUTER_TYPE {
	CT_LAPTOP,
	CT_DESKTOP
};

class IComputer : public IListItem {

public:
	virtual ~IComputer() {}

	virtual COMPUTER_TYPE ComputerType() const = 0;

	virtual void PrintData(std::ostream &stream = std::cout) const;
	virtual void PrintDataToFile(std::ostream &stream) const;

	void ID(int newID) { id = newID; }
	void ProcessorClock(double newProcessorClock) { processorClock = newProcessorClock; }
	void ProcessorType(std::string newProcessorType) { processorType = newProcessorType; }
	void Name(std::string newName) { name = newName; }

	int ID() const { return id; }
	double ProcessorClock() const { return processorClock; }
	std::string ProcessorType() const { return processorType; }
	std::string Name() const { return name; }

protected:
	int id;
	double processorClock;
	std::string processorType;
	std::string name;
};