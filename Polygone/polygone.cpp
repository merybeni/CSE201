#include <iostream>
#iostream "Polygone.hpp"

NodeList::NodeList(int d, NodeList* nxt)
{
	data = d;
	next = nxt;
}

NodeList::~NodeList()
{
	if (next != NULL) delete next;
}

PointList::PointList()
  // create an empty list
{ 
   first = NULL;
   last = NULL;
}

void PointList::append()
  // add a point to the list
{
  if (last == NULL) {
    first = new NodeList(d);
	last = first; // cuz on a plus que un seul element 
}
	else {
	last -> next = new NodeList(d); // on creer un element de type listode(d)
	last = last -> next;
}
}
