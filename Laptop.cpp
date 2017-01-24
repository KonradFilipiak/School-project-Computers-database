#include "Laptop.h"

Laptop::Laptop(int newID, std::string newName, std::string newProcessorType, double newProcessorClock, double newWeight)
{
	id = newID;
	name = newName;
	processorType = newProcessorType;
	processorClock = newProcessorClock;
	weight = newWeight;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Laptop::PrintData(std::ostream &stream) const
{
	stream << "Laptop info:\n";

	IComputer::PrintData(stream);

	stream << "\tWeight: " << weight << std::endl << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Laptop::PrintDataToFile(std::ostream &stream) const
{
	IComputer::PrintDataToFile(stream);

	stream << weight;
}