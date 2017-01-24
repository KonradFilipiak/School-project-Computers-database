#include "IComputer.h"

void IComputer::PrintData(std::ostream &stream) const
{
	stream << "\tID number: " << ID() << std::endl;
	stream << "\tName: " << Name() << std::endl;
	stream << "\tProcessor type: " << ProcessorType() << std::endl;
	stream << "\tProcessor clock: " << ProcessorClock() << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void IComputer::PrintDataToFile(std::ostream &stream) const
{
	stream << ID() << " " << Name() << " " << ProcessorType() << " " << ProcessorClock() << " ";
}