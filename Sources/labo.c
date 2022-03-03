#include"labo.h"

void pushBack(Node* n, void* data)
{
	if (n->data == NULL)
	{
		n->next = NULL;
		n->prev = NULL;
		n->data = data;

		return;
	}

	if (n->prev == NULL)
	{
		Node* newNode = allocate(sizeof(Node));
		
		n->prev = newNode;
		n->next = newNode;

		newNode->prev = n;
		newNode->next = NULL;
		newNode->data = data;

		return;
	}

	Node* newNode = allocate(sizeof(Node));
	n->prev->next = newNode;
	newNode->prev = n->prev;
	n->prev = newNode;
	newNode->next = NULL;
	newNode->data = data;
}

Node popByName(Node* n, char* name)
{
	if (n == NULL || n->data == NULL)
	{
		Node temp = { 0 };
		return temp;
	}
	else if(n->next == NULL)
	{
		Items* currentItems = n->data;
		if (*currentItems->name == *name)
		{
			Node temp = *n;
			n->next = NULL;
			n->prev = NULL;
			n->data = NULL;
			return temp;
		}
		else
		{
			Node temp = { 0 };
			return temp;
		}
	}
	
	Node* currentNode = n;

	while (currentNode != NULL)
	{
		Items* currentItems = currentNode->data;

		if (*currentItems->name == *name)
		{
			Node temp = *currentNode;

			if (currentNode->prev != NULL)
			{
				currentNode->prev->next = currentNode->next;
			}


			memset(currentNode, 0, sizeof(Node));
			return temp;
		}

		currentNode = currentNode->next;
	}
	Node temp = { 0 };
	return temp;
}

void sortByPrixVente(Node* n)
{

}

Items* findItemsByPosition(Node* n, int position)
{

}

Items* findItemsByName(Node* n, char* name)
{

}

int takeNumberItems(Node* n)
{

}