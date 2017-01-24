#pragma once

#include "IComputer.h"

class Laptop : public IComputer {

public:
	Laptop(int newID, std::string newName, std::string newProcessorType, double newProcessorClock, double newWeight);

	COMPUTER_TYPE ComputerType() const { return COMPUTER_TYPE::CT_LAPTOP; }

	void PrintData(std::ostream &stream = std::cout) const;
	void PrintDataToFile(std::ostream &stream) const;

	void Weight(double newWeight) { weight = newWeight; }
	double Weight() const { return weight; }

private:
	double weight;
};
