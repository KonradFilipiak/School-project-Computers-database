#pragma once

#include <iostream>
#include <fstream>

class IListItem
{
public:
	friend class List;

	IListItem() : next(NULL), prev(NULL) {}
	virtual ~IListItem() {}

	virtual void PrintData(std::ostream &stream = std::cout) const = 0;
	virtual void PrintDataToFile(std::ostream &stream) const = 0;

	void Next(IListItem* newNext) { next = newNext; };
	void Prev(IListItem* newPrev) { prev = newPrev; };
	IListItem* Next() const { return next; }
	IListItem* Prev() const { return prev; }

protected:
	IListItem* next;
	IListItem* prev;
};