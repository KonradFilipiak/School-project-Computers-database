#pragma once

#include "IComputer.h"

class Desktop : public IComputer {

public:
	Desktop(int newID, std::string newName, std::string newProcessorType, double newProcessorClock, double newHeight, double newWidth, double newLength);

	COMPUTER_TYPE ComputerType() const { return COMPUTER_TYPE::CT_DESKTOP; }

	void PrintData(std::ostream &stream = std::cout) const;
	void PrintDataToFile(std::ostream &stream) const;

	void Length(double newLength) { length = newLength; }
	void Width(double newWidth) { width = newWidth; }
	void Height(double newWHeight) { height = newWHeight; }

	double Length() const { return length; }
	double Width() const { return width; }
	double Height() const { return height; }

private:
	double length;
	double width;
	double height;
};