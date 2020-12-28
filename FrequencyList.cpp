#include <iostream>
#include "frequency_list.h"

FrequencyList::FrequencyList() {
	this->count = 0;
	this->prev = NULL;
	this->next = NULL;
}

FrequencyList::FrequencyList(int count) {
	this->count = count;
	this->prev = NULL;
	this->next = NULL;
}

FrequencyList::FrequencyList(int count, FrequencyList *prev, FrequencyList *next) {
	this->count = count;
	this->prev = prev;
	this->next = next;
}

FrequencyList::~FrequencyList() {
	delete(this->prev);
	delete(this->next);
	this->nodelist.clear();
}

void FrequencyList::InsertNode(int node) {
	this->nodelist[node] = 1; // being called for the first time
}

void FrequencyList::LookUpNode(int node, int freq) {
	this->nodelist[node] = freq;
}

void FrequencyList::DeleteNode(int node) {
	if( IsPresent(node) ) // check if node exists
	this->nodelist.erase(node);
} // else no action

void FrequencyList::PrintNodeList() {
	for(unordered_map<int, int>::const_iterator itr = this->nodelist.begin(); itr != this->nodelist.end(); itr++)
	{
		cout<<itr->first<<" "<<itr->second<<"\n"; //Print full list
	}
}

int FrequencyList::GetNode() {
	return this->nodelist.begin()->first;
}

bool FrequencyList::IsPresent(int node) {
	unordered_map<int, int>::const_iterator itr = this->nodelist.find(node);
	if(itr != this->nodelist.end()) // end means not present
		return true;
	return false;
}

int FrequencyList::GetCount() {
	return this->count;
}

void FrequencyList::SetPrevious(FrequencyList* prev) {
	this->prev = prev;
}

void FrequencyList::SetNext(FrequencyList* next) {
	this->next = next;
}

FrequencyList* FrequencyList::GetPrevious() {
	return this->prev;
}

FrequencyList* FrequencyList::GetNext() {
	return this->next;
}

bool FrequencyList::IsEmpty() {
	if(this->nodelist.empty())
		return true;
	else
		return false;
}
