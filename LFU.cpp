#include <iostream>
#include "lfu.h"

// CountFrequencyListMap points the frequency variable to it's node in the frequency list
// NodeFrequencyListMap points a cache variable to it's parent frequency in the frequency list 

LFU::LFU() {
	this->head = new FrequencyList(0, NULL, NULL);
	this->CountFrequencyListMap[0] = this->head;
}

LFU::~LFU() {
	delete(this->head);
	this->CountFrequencyListMap.clear();
	this->NodeFrequencyListMap.clear();
}

// Add item to Cache
void LFU::Set(int value) {
	if(NodePresent(value)) {
		Retrieve(value);
	}
	else {
		int freq = 1;
		
		if(FrequencyNodePresent(freq)) {
			FrequencyList *currentlist = this->CountFrequencyListMap.find(freq)->second;
			
			currentlist->InsertNode(value);
			this->NodeFrequencyListMap[value] = currentlist;
		} else {
			FrequencyList *newnode = new FrequencyList(freq);
			this->CountFrequencyListMap[freq] = newnode;
			//adjust new node pointers
			newnode->SetPrevious(this->head);
			newnode->SetNext(this->head->GetNext());
			//update new node
			newnode->InsertNode(value);
			//adjust neighbour pointers
			this->head->SetNext(newnode);
			if(newnode->GetNext() != NULL)
				newnode->GetNext()->SetPrevious(newnode);
				
			this->NodeFrequencyListMap[value] = newnode;
		}
	}
}

// Retrieve value present in cache
void LFU::Retrieve(int value) {
	FrequencyList *currentlist = this->NodeFrequencyListMap.find(value)->second;
	int freq = currentlist->GetCount();
	
	currentlist->DeleteNode(value);
	freq += 1;
	if(FrequencyNodePresent(freq)) {
		FrequencyList *freqlist = this->CountFrequencyListMap.find(freq)->second;
		
		freqlist->LookUpNode(value, freq);
		this->NodeFrequencyListMap[value] = freqlist;
	} else {
		FrequencyList *newnode = new FrequencyList(freq);
		this->CountFrequencyListMap[freq] = newnode;
		//adjust new node pointers
		newnode->SetPrevious(currentlist);
		newnode->SetNext(currentlist->GetNext());
		//update new node
		newnode->LookUpNode(value, freq);
		//adjust neighbour pointers
		currentlist->SetNext(newnode);
		if(newnode->GetNext() != NULL)
			newnode->GetNext()->SetPrevious(newnode);
		
		this->NodeFrequencyListMap[value] = newnode;
	}
	// if that frequency node is empty after deletion
	if(IsNodeEmpty(currentlist))
	{
		if(currentlist->GetNext() != NULL)
			currentlist->GetNext()->SetPrevious(currentlist->GetPrevious());
        
        currentlist->GetPrevious()->SetNext(currentlist->GetNext());
        
        this->CountFrequencyListMap.erase(currentlist->GetCount());
        free(currentlist);
	}
}

// Remove lfu node present in cache	
void LFU::Evict() {
	FrequencyList *newnode = this->head->GetNext(); //Get the lowest frequency next to 0
	int value = newnode->GetNode(); //Get any 1 node
	newnode->DeleteNode(value);
	
	// if that frequency node becomes empty after deletion
	if(IsNodeEmpty(newnode))
	{
		if(newnode->GetNext() != NULL)
			newnode->GetNext()->SetPrevious(newnode->GetPrevious());
        
        newnode->GetPrevious()->SetNext(newnode->GetNext());
        
        this->CountFrequencyListMap.erase(newnode->GetCount());
        free(newnode);
	}
	
}

bool LFU::NodePresent(int node) {
	unordered_map<int, FrequencyList*>::const_iterator itr = this->NodeFrequencyListMap.find(node);
	if(itr != this->NodeFrequencyListMap.end())
		return true;
	return false;
}

bool LFU::FrequencyNodePresent(int count) {
	unordered_map<int, FrequencyList*>::const_iterator itr = this->CountFrequencyListMap.find(count);
	if(itr != this->CountFrequencyListMap.end())
		return true;
	return false;
}

bool LFU::IsNodeEmpty(FrequencyList *frequencyList) {
	return frequencyList->IsEmpty();
}
		
void LFU::PrintLfu() {
	FrequencyList *node = this->head;
	while(node != NULL)
	{
		node->PrintNodeList();
		node = node->GetNext();
	}
}

int main() {
	// a basic sample test case
	LFU *lfu = new LFU();
    lfu->Set(1);
    lfu->Set(1);
    lfu->Set(2);
    lfu->Retrieve(2);
    lfu->Set(3);
    lfu->Evict();
    lfu->Set(1);
    lfu->Set(4);
    lfu->PrintLfu();
    return 0;
}
