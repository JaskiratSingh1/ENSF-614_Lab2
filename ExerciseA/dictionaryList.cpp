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

Datum& DictionaryList::cursor_datum()
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
    for (Node *p = headM; p !=0; p = p->nextM)
    {
        if(keyA == p->keyM)
        {
            cursorM = p;
            return;
        }
    }
    cursorM = 0;
}


void DictionaryList::destroy()
{
  Node *p = headM;
  while (p != 0) {
    Node *next = p->nextM;
    delete p;
    p = next;
  }
  headM = 0;
  cursorM = 0;
  sizeM = 0;
  
}


void DictionaryList::copy(const DictionaryList& source)
{
  if (source.headM == nullptr) { // source list is empty.
        headM = nullptr;
        cursorM = nullptr;
        sizeM = 0;
        return; 
    }

    headM = new Node(source.headM->keyM, source.headM->datumM, nullptr); // create the first node in the new list.
    Node* currSource = source.headM->nextM; // pointer to the next node in the source list.
    Node* currNode = headM; // pointer to the next node in the new list.

    // copy each node.
    while (currSource != nullptr) {
        currNode->nextM = new Node(currSource->keyM, currSource->datumM, nullptr);
        currNode = currNode->nextM;
        currSource = currSource->nextM;
    }

    sizeM = source.sizeM;

    // find the corresponding cursor in the new list.
    if (source.cursorM != nullptr) {
        currSource = source.headM;
        currNode = headM;

        // traverse both lists together to find the cursor position.
        while (currSource != source.cursorM) {
            currSource = currSource->nextM;
            currNode = currNode->nextM;
        }
        // set the cursor of this list to the corresponding node.
        cursorM = currNode;
    } else 
        cursorM = nullptr;
    
}
// subscript operator
const Mystring& DictionaryList::operator[](int index) const
{
    if (index < 0 || index >= sizeM)
    {
        cerr << "out of bounds\n";
        exit(1);
    }
    Node* current = headM;
    for (int i = 0; i < index; ++i)
    {
        current = current->nextM;
    }
    return current->datumM;
}

// insertion operator
ostream& operator<<(ostream& os, const DictionaryList& dl)
{
    Node* current = dl.headM;
    while (current != 0)
    {
        os << current->keyM << "  " << current->datumM << endl;
        current = current->nextM;
    }
    return os;
}

