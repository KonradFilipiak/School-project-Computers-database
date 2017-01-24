#include "Desktop.h"

Desktop::Desktop(int newID, std::string newName, std::string newProcessorType, double newProcessorClock, double newHeight, double newWidth, double newLength)
{
	id = newID;
	name = newName;
	processorType = newProcessorType;
	processorClock = newProcessorClock;
	height = newHeight;
	width = newWidth;
	length = newLength;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Desktop::PrintData(std::ostream &stream) const
{
	stream << "Desktop info:\n";

	IComputer::PrintData(stream);

	stream << "\tHeight: " << height << std::endl;
	stream << "\tWidth: " << width << std::endl;
	stream << "\tLength: " << length << std::endl << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Desktop::PrintDataToFile(std::ostream &stream) const
{
	IComputer::PrintDataToFile(stream);

	stream << height << " " << width << " " << length;
}