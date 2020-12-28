#ifndef FREQUENCYLIST_H
#define FREQUENCYLIST_H

#include <unordered_map>

using namespace std;

class FrequencyList {
	private:
		int count;
		unordered_map <int, int> nodelist;
		FrequencyList *prev;
		FrequencyList *next;
	public:
		FrequencyList();
		FrequencyList(int count);
		FrequencyList(int count, FrequencyList *prev, FrequencyList *next);
		~FrequencyList();
		void InsertNode(int node);
		void LookUpNode(int node);
		void DeleteNode(int node);
		bool IsPresent(int node);
		void PrintNodeList();
		int GetNode();
		int GetCount();
		void SetPrevious(FrequencyList *prev);
		void SetNext(FrequencyList *next);
		FrequencyList *GetPrevious();
		FrequencyList *GetNext();
		bool IsEmpty();
};

#endif

