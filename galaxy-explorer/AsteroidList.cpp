#include <galaxy-explorer/AsteroidList.hpp>


AsteroidListItem::AsteroidListItem() {
	this->next = nullptr;
	this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
	this->next = nullptr;
	this->data = new Asteroid(a);
}

AsteroidListItem::~AsteroidListItem() {
    //do nothing
}

AsteroidList::AsteroidList()
{
    //do nothing
}

AsteroidList::AsteroidList(const AsteroidList& src)
{
    const AsteroidListItem* ptr = src.begin();
    AsteroidListItem* last = NULL;
    AsteroidListItem* nptr = NULL;
    head.setNext(NULL);
    //create new AsteroidListItem objects and copy them from src
    while(ptr != NULL) {
        nptr = new AsteroidListItem(ptr->getData());
        if(last == NULL) head.setNext(nptr);
        else last->setNext(nptr);
        ptr = ptr->getNext();
        last = nptr;
    }
    last = nullptr;
    delete last;
    nptr = nullptr;
    delete nptr;
    ptr = nullptr;
    delete ptr;
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the destructor (because you should put all your constructors together).
}

AsteroidList::~AsteroidList() {
    AsteroidListItem* ptr;
    //free dynamic memory allocated with AsteroidList
    while(head.getNext() != NULL) {
        ptr = head.getNext();
        head.setNext(ptr->getNext());
        ptr = nullptr;
        delete ptr;
    }
	// The functions in this class are listed in a suggested order of implementation,
	// except for this one and the copy constructor (because you should put all your constructors together).
}

void AsteroidList::pushFront(Asteroid e) {  
    //create a new AsteroidListItem and put it at the front of the list 
    AsteroidListItem* nptr = new AsteroidListItem(e);
    nptr->setNext(begin());
    head.setNext(nptr);
    nptr = nullptr;
    delete nptr;
}

Asteroid& AsteroidList::front() {
    return (head.getNext()->getData());
	//return *(Asteroid*)nullptr;
}

const Asteroid& AsteroidList::front() const {
    return (head.getNext()->getData());
	//return *(const Asteroid*)nullptr;
}

bool AsteroidList::isEmpty() const {
    //if the head is empty, return true
    if(head.getNext() == NULL)
	return true;
    else 
        return false;
}

int AsteroidList::size() const {
    int count = 0;
    const AsteroidListItem* tptr = head.getNext();
    //increment count every next item 
    while(tptr != NULL) {
        count++;
        tptr = tptr->getNext();
    }
	return count;
}

AsteroidListItem* AsteroidList::beforeBegin() {
    //return the address of head
	return &head;
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
	return &head;
}

AsteroidListItem* AsteroidList::begin() {
    //return the first item in the list 
	return head.getNext();
}

const AsteroidListItem* AsteroidList::begin() const {
	return head.getNext();
}

AsteroidListItem* AsteroidList::beforeEnd() {
    //if list is empty, return beforeBegin
    if(isEmpty())
        return (beforeBegin());
    AsteroidListItem* tptr = head.getNext();
    //traverse the list and return the current tptr when its next is pointing to NULL
    while(tptr->getNext() != NULL) {
        tptr = tptr->getNext();
    }
	return tptr;
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
    if(isEmpty())
        return (beforeBegin());
    const AsteroidListItem* tptr = head.getNext();
    //traverse the list and return the current tptr when its next is pointing to NULL
    while(tptr->getNext() != NULL) {
        tptr = tptr->getNext();
    }
	return tptr;
}

AsteroidListItem* AsteroidList::end() {
    //return null for the position after the last asteroid 
	return nullptr;
}

const AsteroidListItem* AsteroidList::end() const {
	return nullptr;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    //create a new pointer and insert where prev next points and have the new pointer point to the temp pointer which points to what prev pointer pointed to originally
    AsteroidListItem* nptr = new AsteroidListItem(e);
    AsteroidListItem* tptr = prev->getNext();
    prev->setNext(nptr);
    nptr->setNext(tptr);
    tptr = nullptr;
    delete tptr;
    return nptr;
} 

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, const AsteroidList& others) {
    //insert an AsteroidList after prev 
    const AsteroidListItem* nptr = others.begin();
    while(nptr != NULL) {
        //insert each Asteroid sequentially using insertAfter
        prev = this->insertAfter(prev, nptr->getData());
        nptr = nptr->getNext();
    }
    delete nptr;
    nptr = nullptr;
    return prev;
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    //erase the asteroid item right after prev 
    if(prev->getNext() != NULL) {
        AsteroidListItem* nptr = prev->getNext();
        AsteroidListItem* tptr = nptr->getNext();
        delete nptr;
        nptr = nullptr;
        prev->setNext(tptr); 
        delete tptr;
        tptr = nullptr;
    }
    return prev;
}

void AsteroidList::clear() {
    AsteroidListItem* ptr;
    //free dynamic memory allocated with AsteroidList
    while(head.getNext() != NULL) {
        ptr = head.getNext();
        head.setNext(ptr->getNext());
        delete ptr;
        ptr = nullptr;
    }
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    //if the two lists are equal, return itself
    if(this == &src)
        return (*this);
    //clear the list 
    this->clear();
    //insert src to the empty list
    this->insertAfter(this->beforeBegin(), src);
    return (*this);
        
}
