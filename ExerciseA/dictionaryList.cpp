// lookuptable.cpp

// ENSF 614 - Lab 2 - Exercise A
 
// Completed by:

#include <assert.h>
#include <iostream>
#include <stdlib.h>
#include "dictionaryList.h"
#include "mystring_B.h"

using namespace std;

Node::Node(const Key& keyA, const Datum& datumA, Node *nextA)
  : keyM(keyA), datumM(datumA), nextM(nextA)
{
}

DictionaryList::DictionaryList()
  : sizeM(0), headM(0), cursorM(0)
{
}

DictionaryList::DictionaryList(const DictionaryList& source)
{
  copy(source);
}

DictionaryList& DictionaryList::operator =(const DictionaryList& rhs)
{
  if (this != &rhs) {
    destroy();
    copy(rhs);
  }
  return *this;
}

DictionaryList::~DictionaryList()
{
  destroy();
}

int DictionaryList::size() const
{
  return sizeM;
}

int DictionaryList::cursor_ok() const
{
  return cursorM != 0;
}

const Key& DictionaryList::cursor_key() const
{
  assert(cursor_ok());
  return cursorM->keyM;
}

const Datum& DictionaryList::cursor_datum() const
{
  assert(cursor_ok());
  return cursorM->datumM;
}

void DictionaryList::insert(const int& keyA, const Mystring& datumA)
{
  // Add new node at head?                                                                                  
  if (headM == 0 || keyA < headM->keyM) {
    headM = new Node(keyA, datumA, headM);
    sizeM++;
  }
	
  // Overwrite datum at head?                                                                               
  else if (keyA == headM->keyM)
    headM->datumM = datumA;
	
  // Have to search ...                                                                                     
  else {
      
    //POINT ONE
		
    // if key is found in list, just overwrite data;                                                        
    for (Node *p = headM; p !=0; p = p->nextM)
		{
			if(keyA == p->keyM)
			{
				p->datumM = datumA;
				return;
			}
		}
		
    //OK, find place to insert new node ...                                                                 
    Node *p = headM ->nextM;
    Node *prev = headM;
		
    while(p !=0 && keyA >p->keyM)
		{
			prev = p;
			p = p->nextM;
		}
		
    prev->nextM = new Node(keyA, datumA, p);
    sizeM++;
  }
  cursorM = NULL;
	
}

void DictionaryList::remove(const int& keyA)
{
    if (headM == 0 || keyA < headM -> keyM)
        return;
    
    Node *doomed_node = 0;
    
    if (keyA == headM-> keyM) {
        doomed_node = headM;
        headM = headM->nextM;
        
        // POINT TWO
    }
    else {
        Node *before = headM;
        Node *maybe_doomed = headM->nextM;
        while(maybe_doomed != 0 && keyA > maybe_doomed-> keyM) {
            before = maybe_doomed;
            maybe_doomed = maybe_doomed->nextM;
        }
        
        if (maybe_doomed != 0 && maybe_doomed->keyM == keyA) {
            doomed_node = maybe_doomed;
            before->nextM = maybe_doomed->nextM;
        }
        
        
    } 
    if(doomed_node == cursorM)
        cursorM = 0;
    
    delete doomed_node;           // Does nothing if doomed_node == 0.
    sizeM--;
}

void DictionaryList::go_to_first()
{
    cursorM = headM;
}

void DictionaryList::step_fwd()
{
    assert(cursor_ok());
    cursorM = cursorM->nextM;
}

void DictionaryList::make_empty()
{
    destroy();
    sizeM = 0;
    cursorM = 0;
}


// The following function are supposed to be completed by the stuents, as part
// of the exercise B part II. the given fucntion are in fact place-holders for
// find, destroy and copy, in order to allow successful linking when you're
// testing insert and remove. Replace them with the definitions that work.

void DictionaryList::find(const Key& keyA)
{
    // Set cursor to head
    cursorM = headM;
    // Loop until reaching the end
    while(cursorM != nullptr){
        // Check if current node's key matches keyA
        if(cursorM->keyM == keyA) {
            return;
        }
        //Increment node
        cursorM = cursorM->nextM;
    }
    //Unable to find key in list, set cursor to null
    cursorM = nullptr;
}

// Deallocate all nodes, set headM to zero.
void DictionaryList::destroy()
{
    // Loop until all nodes are destroyed
    while(headM != nullptr){
        //Set cursor to head
        cursorM = headM;
        //Set head to next node
        headM = headM->nextM;
        //Delete cursor node
        delete cursorM;
    }
    // set cursor and head to null
    headM = cursorM = nullptr;
}

// Establishes *this as a copy of source.  Cursor of *this will
// point to the twin of whatever the source's cursor points to.
void DictionaryList::copy(const DictionaryList& source)
{
    //If making a copy of an empty list
    if(source.headM == nullptr) {
        headM = cursorM = nullptr;
        sizeM = 0;
        return;
    }
    
    // Copy head first
    headM = new Node(source.headM->keyM, source.headM->datumM, nullptr);
    // Set up two Node pointers
    Node* currentSourceNode = source.headM->nextM;
    Node* newNode = headM;
    
    // Loop until reaching end of source
    while(currentSourceNode != nullptr) {
        // Create new node and set to nextM
        newNode->nextM = new Node(currentSourceNode->keyM, currentSourceNode->datumM, nullptr);
        // Increment current node
        currentSourceNode = currentSourceNode->nextM;
        // Increment previous node
        newNode = newNode->nextM;
    }
    // Copying now complete
    // Update size
    sizeM = source.sizeM;
    
    // Set cursor to point to the twin of source's cursor
    if(source.cursorM == nullptr) {
        cursorM = nullptr;
    } else {
        //Reset both cursors
        cursorM = headM;
        currentSourceNode = source.headM;
        //Loop till end of list instead of until value matches to avoid potential infinite loop
        while(currentSourceNode != nullptr) {
            if(source.cursorM == currentSourceNode) {
                //Exit function when cursorM is pointing to the correct node
                return;
            }
            cursorM = cursorM->nextM;
            currentSourceNode = currentSourceNode->nextM;
        }
    }
}
