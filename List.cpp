#include "List.h"

void List::AddHead(IListItem* newHead)
{
	if (head)
	{
		head->prev = newHead;
		newHead->next = head;
		head = newHead;
	}
	else
	{
		head = tail = newHead;
	}
	head->prev = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void List::AddTail(IListItem* newTail)
{
	if (head)
	{
		tail->next = newTail;
		newTail->prev = tail;
		tail = newTail;
	}
	else
	{
		head = tail = newTail;
	}
	tail->next = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void List::RemoveHead()
{
	if (head)
	{
		if (head == tail)
		{
			delete head;
			head = tail = NULL;
		}
		else
		{
			head = head->next;
			delete head->prev;
			head->prev = NULL;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void List::RemoveTail()
{
	if (head)
	{
		if (head == tail)
		{
			delete head;
			head = tail = NULL;
		}
		else
		{
			tail = tail->prev;
			delete tail->next;
			tail->next = NULL;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void List::PrintList(std::ostream &stream) const
{
	if (head)
	{
		for (IListItem* tmp = head; tmp != NULL; tmp = tmp->next)
		{
			tmp->PrintData(stream);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void List::SaveToFile(std::fstream &file) const
{
	if (head)
	{
		for (IListItem* tmp = head; tmp != tail; tmp = tmp->next)
		{
			tmp->PrintDataToFile(file);

			file << std::endl;
		}

		//The tail is not in the loop not to create an empty line at the end
		tail->PrintDataToFile(file);

	}
}