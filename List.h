#pragma once

#include "IComputer.h"

class List
{
public:
	List() : head(NULL), tail(NULL) {}
	~List()
	{
		while (head)
			RemoveHead();
	}

	void AddHead(IListItem* newHead);
	void AddTail(IListItem* newTail);

	void RemoveHead();
	void RemoveTail();

	void PrintList(std::ostream &stream = std::cout) const;

	void SaveToFile(std::fstream &file) const;

	template <class TClass, typename TVar> void SortList(TVar(TClass::*ptr)(void) const)
	{
		//Only temporary class, used as guards in quicksort algorithm
		class TMP : public IListItem { void PrintData(std::ostream &stream = std::cout) const {} void PrintDataToFile(std::ostream &stream) const {} };

		IListItem* tmp1 = new TMP();	//guards
		IListItem* tmp2 = new TMP();

		if (head && head->next)
		{
			AddHead(tmp1);
			AddTail(tmp2);

			SplitList(ptr, static_cast<TClass*>(head), static_cast<TClass*>(tail));
		
			RemoveHead();
			RemoveTail();
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	// Returns a pointer to a IListItem, which 'TVar(TClass::*ptr)(void)' getter has a value of 'TVar value'
	template <class TClass, typename TVar> IListItem* FindItem(TVar(TClass::*ptr)(void) const, TVar value, TClass* tmp) const
	{

		for (tmp; tmp != NULL; tmp = static_cast<TClass*>(tmp->next))
		{
			try
			{
				if ((tmp->*ptr)() == value)
					return tmp;
					
			}
			catch (...)	//In case TClass* does not contain (*ptr) method
			{
				continue;
			}
		}

		return NULL;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <class TClass, typename TVar> bool RemoveItem(TVar(TClass::*ptr)(void) const, TVar value)
	{
		bool ret = false;

		if (!head)
			return ret;

		TClass* tmp = static_cast<TClass*>(head);
		TClass* toDelete = NULL;

		while ((toDelete = static_cast<TClass*>(FindItem(ptr, value, static_cast<TClass*>(tmp)))) != NULL)
		{
			tmp = static_cast<TClass*>(toDelete->next);

			if (toDelete == static_cast<TClass*>(head))
				RemoveHead();
			else if (toDelete == static_cast<TClass*>(tail))
				RemoveTail();
			else
			{
				toDelete->prev->next = toDelete->next;
				toDelete->next->prev = toDelete->prev;
				delete toDelete;
			}

			ret = true;
		}
		
		return ret;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <class TClass, typename TVar> bool PrintItem(TVar(TClass::*ptr)(void) const, TVar value) const
	{
		bool ret = false;

		if (!head)
			return ret;

		TClass* tmp = static_cast<TClass*>(head);
		TClass* toPrint = NULL;

		while ((toPrint = static_cast<TClass*>(FindItem(ptr, value, static_cast<TClass*>(tmp)))) != NULL)
		{
			tmp = static_cast<TClass*>(toPrint->next);

			toPrint->PrintData();

			ret = true;
		}

		return ret;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

	template <class TClass, typename TVar> bool DoesExist(TVar(TClass::*ptr)(void) const, TVar value) const
	{
		if (!head)
			return false;

		TClass* tmp = static_cast<TClass*>((head));

		if (FindItem((ptr), ID, tmp))
			return true;

		return false;
	}

	IListItem* Head() const { return head; }
	IListItem* Tail() const { return tail; }

	////////////////////////////////////////////////////////////////////////////////////////////////////

private:

	IListItem* head;
	IListItem* tail;

	// For sorting with quicksort algorithm
	template <class TClass, typename TVar> void SplitList(TVar(TClass::*ptr)(void) const, TClass* left, TClass* right)
	{
		TClass *pivot, *smallerList, *biggerList;

		pivot = static_cast<TClass*>(left->next);
		smallerList = static_cast<TClass*>(pivot->next);

		if (smallerList != right)
		{
			do
			{
				biggerList = smallerList;
				smallerList = static_cast<TClass*>(smallerList->next);

				if ((biggerList->*ptr)() < (pivot->*ptr)())
				{
					biggerList->prev->next = biggerList->next;
					biggerList->next->prev = biggerList->prev;

					biggerList->next = pivot;
					biggerList->prev = pivot->prev;
					pivot->prev = biggerList;
					biggerList->prev->next = biggerList;
				}
			} while (smallerList != right);

			if (left->next != pivot) SplitList(ptr, left, pivot);
			if (pivot->next != right) SplitList(ptr, pivot, right);
		}
	}
};
