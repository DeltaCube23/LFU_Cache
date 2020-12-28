#ifndef LFU_H
#define LFU_H

#include "frequency_list.h"

class LFU {
	private:
		unordered_map<int, FrequencyList*> NodeFrequencyListMap;
		unordered_map<int, FrequencyList*> CountFrequencyListMap;
		FrequencyList *head;
	public:
		LFU();
		~LFU();
		void Set(int value);
		void Retrieve(int value);
		void Evict();
		bool NodePresent(int node);
		bool FrequencyNodePresent(int count);
		bool IsNodeEmpty(FrequencyList *frequencyList);
		void PrintLfu();
};

#endif
