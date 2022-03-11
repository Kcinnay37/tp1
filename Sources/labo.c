#include"labo.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

void PushBack(Queue* q, void* data)
{
	if (q->head == NULL && q->tail == NULL)
	{
		Node* newNode = malloc(sizeof(Node));//allocate(sizeof(Node));

		newNode->next = NULL;
		newNode->prev = NULL;
		newNode->data = data;

		q->tail = newNode;
		q->head = newNode;
		q->nombreNode++;

		return;
	}
	else
	{
		Node* newNode = malloc(sizeof(Node));//allocate(sizeof(Node));
		newNode->next = NULL;
		newNode->prev = q->tail;
		newNode->data = data;

		q->tail->next = newNode;
		q->tail = newNode;
		q->nombreNode++;

		return;
	}
}

void PushHead(Queue* q, void* data)
{
	if (q->head == NULL && q->tail == NULL)
	{
		PushBack(q, data);
		
		return;
	}
	else
	{
		Node* newNode = malloc(sizeof(Node));//allocate(sizeof(Node));
		newNode->next = q->head;
		newNode->prev = NULL;
		newNode->data = data;

		q->head->prev = newNode;
		q->head = newNode;
		q->nombreNode++;

		return;
	}
}

void PushNodePosition(Queue* q, Node* n, void* data)
{
	if (q->head == NULL && q->tail == NULL)
	{
		PushBack(q, data);
		return;
	}
	else if (n == q->head || n == NULL)
	{
		if (n == q->head)
		{
			PushHead(q, data);
		}
		else if (n == NULL)
		{
			PushBack(q, data);
		}
		return;
	}
	else
	{
		Node* newNode = malloc(sizeof(Node));//allocate(sizeof(Node));
		newNode->next = n;
		newNode->prev = n->prev;
		newNode->data = data;

		newNode->prev->next = newNode;
		newNode->next->prev = newNode;

		q->nombreNode++;
		return;
	}

}

void PushAsPriority(Queue* q, void* data)
{
	if (q->head == NULL && q->tail == NULL)
	{
		PushBack(q, data);
		return;
	}
	else
	{
		Node* currNode = q->head;
		Items* newItems = data;

		while (currNode != NULL)
		{
			Items* currItems = currNode->data;

			if (currItems->prixVente > newItems->prixVente)
			{
				break;
			}

			currNode = currNode->next;
		}

		PushNodePosition(q, currNode, data);
		return;
	}
}

void PushRandomItems(Queue* q, Queue* items, int number)
{
	srand(time(0));
	for (int i = 0; i < number; i++)
	{
		int randNumber = rand() % TakeNumberItemsFile();
		PushBack(q, FindItemsByPosition(items, randNumber));
	}
}

void PushRandomItemsWithout(Queue* q, Queue* items, int number, int index)
{
	srand(time(0));
	int randNumber = 0;
	for (int i = 0; i < number; i++)
	{
		while (1)
		{
			randNumber = rand() % TakeNumberItemsFile();
			if (randNumber != index)
			{
				break;
			}
		}
		PushBack(q, FindItemsByPosition(items, randNumber));
	}
}

void deleteNode(Queue* q, Node* node)
{
	if (q->head == NULL && q->tail == NULL || node == NULL)
	{
		return;
	}
	else if (q->head == node || q->tail == node)
	{
		if (q->head == node && q->tail == node)
		{
			node->next = NULL;
			node->prev = NULL;
			memset(node, 0, sizeof(node));

			q->head = NULL;
			q->tail = NULL;
			q->nombreNode = 0;
			return;
		}
		else if (q->head == node)
		{
			q->head = node->next;
			q->head->prev = NULL;
			q->nombreNode--;

			node->next = NULL;
			node->prev = NULL;
			memset(node, 0, sizeof(Node));
			return;
		}
		else if (q->tail == node)
		{
			q->tail = node->prev;
			q->tail->next = NULL;
			q->nombreNode--;

			node->next = NULL;
			node->prev = NULL;
			memset(node, 0, sizeof(Node));
			return;
		}
	}
	else
	{
		node->next->prev = node->prev;
		node->prev->next = node->next;
		
		node->next = NULL;
		node->prev = NULL;
		memset(node, 0, sizeof(Node));
		q->nombreNode--;
		return;
	}
}

Node PopByName(Queue* q, char* name)
{
	if (q->head == NULL && q->tail == NULL)
	{
		Node temp = { 0 };
		return temp;
	}
	else
	{
		Node* currNode = q->head;
		int sameName = 0;
		int index = 0;
		while (currNode != NULL)
		{
			Items* currItems = currNode->data;

			int tailleNom = 0;
			while (currItems->name[tailleNom] != 0)
			{
				if (currItems->name[tailleNom] == name[tailleNom])
				{
					sameName = 1;
				}
				else
				{
					sameName = 0;
					break;
				}
				tailleNom++;
			}

			if (sameName)
			{
				break;
			}

			currNode = currNode->next;
		}
		Node temp = {0};
		if (currNode != NULL)
		{
			temp = *currNode;
		}
		deleteNode(q, currNode);
		return temp;
	}
}

void SortByPrixVente(Queue* q)
{
	if (q->head == NULL && q->tail == NULL)
	{
		return;
	}
	else
	{
		Items** tablItems = malloc(sizeof(Items) * q->nombreNode);//allocate(sizeof(Items) * q->nombreNode);
		Node* currNode = q->head;

		int nombreItems = q->nombreNode;

		int a = 0;
		while (currNode != NULL)
		{
			tablItems[a] = currNode->data;
			currNode = currNode->next;
			a++;
		}

		while (q->head != NULL && q->tail != NULL)
		{
			deleteNode(q, q->head);
		}

		for (int i = 0; i < nombreItems; i++)
		{
			PushAsPriority(q, tablItems[i]);
		}

		memset(tablItems, 0, sizeof(Items) * q->nombreNode);
		return;
	}
	
	
}

Items* FindItemsByPosition(Queue* q, int position)
{
	if (position >= q->nombreNode)
	{
		return NULL;
	}
	else
	{
		Node* currNode = q->head;
		for (int i = 0; i < position; i++)
		{
			currNode = currNode->next;
		}

		Items* currItems = currNode->data;
		return currItems;
	}
}

Items* FindItemsByName(Queue* q, char* name)
{
	if (q->head == NULL && q->tail == NULL)
	{
		return NULL;
	}
	Node* currNode = q->head;
	Items* currItems = currNode->data;

	int sameName = 0;
	int index = 0;
	while (currNode != NULL)
	{
		int tailleNom = 0;
		while (currItems->name[tailleNom] != 0)
		{
			if (currItems->name[tailleNom] == name[tailleNom])
			{
				sameName = 1;
			}
			else
			{
				sameName = 0;
				break;
			}
			tailleNom++;
		}

		if (sameName)
		{
			return currItems;
		}
		currNode = currNode->next;
		if (currNode != NULL)
		{
			currItems = currNode->data;
		}
	}
	return NULL;
}

int TakeNumberItems(Queue* q)
{
	return q->nombreNode;
}

int TakeItemsIdexByName(Queue* q, char* name)
{
	if (q->head == NULL && q->tail == NULL)
	{
		return -1;
	}
	Node* currNode = q->head;
	Items* currItems = currNode->data;

	int sameName = 0;

	int index = 0;
	while (currNode != NULL)
	{
		int tailleNom = 0;
		while (currItems->name[tailleNom] != 0)
		{
			if (currItems->name[tailleNom] == name[tailleNom])
			{
				sameName = 1;
			}
			else
			{
				sameName = 0;
				break;
			}
			tailleNom++;
		}

		if (sameName)
		{
			return index;
		}
		currNode = currNode->next;
		if (currNode != NULL)
		{
			currItems = currNode->data;
			index++;
		}
	}
	return -1;
}

void PrintInventory(Queue* q)
{
	if (q->head == NULL && q->tail == NULL)
	{
		return;
	}

	Node* currNode = q->head;
	
	int i = 0;
	while (currNode != NULL)
	{
		Items* currItems = currNode->data;
		printf("Items %d\n", i);
		printf("Name : %s\n", currItems->name);
		printf("Prix Vente : %d$\n\n", currItems->prixVente);
		
		currNode = currNode->next;
		i++;
	}
}

void DeleteQueueMemory(Queue* q)
{
	while (q->head != NULL && q->tail != NULL)
	{
		deleteNode(q, q->head);
	}
}

void DeleteItemMemory(Items* item)
{
	memset(item->name, 0, sizeof(char) * 30);
	memset(item, 0, sizeof(Items));
}

void DeleteItemsMemory(Queue* q)
{
	Node* currNode = q->head;
	while (currNode != NULL)
	{
		Items* currItems = currNode->data;
		DeleteItemMemory(currItems);
		currNode = currNode->next;
	}
}

void TakeAllItemsFile(Queue* items)
{
	int nbItems = TakeNumberItemsFile();
	for (int i = 0; i < nbItems; i++)
	{
		PushBack(items, TakeItemsFile(i));
	}
}

Items* TakeItemsFile(int line)
{
	FILE* file;
	file = fopen("C:\\Users\\yanni\\OneDrive\\Bureau\\TechProg\\tp1\\Deployment\\data.csv", "r");
	
	char currChar = 0;
	int nonNull = 0;
	rewind(file);
	for (int i = 0; i < line; i++)
	{
		while (currChar != '\n')
		{
			currChar = getc(file);
			if (currChar != EOF)
			{
				nonNull = 1;
			}
			if (currChar == EOF && nonNull == 0)
			{
				//Items temp = { 0 };
				return NULL;
			}
			nonNull = 0;
		}
		currChar = getc(file);
	}

	Items* newItems = malloc(sizeof(Items));
	newItems->name = malloc(sizeof(char) * 30);
	int a = 0;
	char prixChar[20] = { 0 };

	while (currChar != ',')
	{
		currChar = fgetc(file);
	}
	currChar = fgetc(file);
	currChar = fgetc(file);
	while (currChar != ',')
	{
		newItems->name[a] = currChar;
		currChar = fgetc(file);
		a++;
	}
	while (a != 30)
	{
		newItems->name[a] = 0;
		a++;
	}

	currChar = fgetc(file);
	while (currChar != ',')
	{
		currChar = fgetc(file);
	}
	currChar = fgetc(file);
	currChar = fgetc(file);
	a = 0;
	while (currChar != '\n' && currChar != EOF)
	{
		prixChar[a] = currChar;
		currChar = fgetc(file);
		a++;
	}

	newItems->prixVente = ConvertStringToInt(prixChar, a);

	fclose(file);

	return newItems;
}

int TakeNumberItemsFile()
{
	FILE* file;
	file = fopen("C:\\Users\\yanni\\OneDrive\\Bureau\\TechProg\\tp1\\Deployment\\data.csv", "r");

	char currChar = 0;
	int nombreLine = 0;
	int step = 0;

	rewind(file);
	while (currChar != EOF)
	{
		currChar = getc(file);
		if (step == 0 && currChar == EOF)
		{
			fclose(file);
			return nombreLine;
		}
		if (currChar == '\n')
		{
			nombreLine++;
		}
		step++;
	}
	nombreLine++;


	fclose(file);

	return nombreLine;
}

int ConvertStringToInt(char* text, int length)
{
	int exposant = 1;
	int nombreTotal = 0;
	for (int i = 0; i < length - 1; i++)
	{
		exposant *= 10;
	}
	for (int i = 0; i < length; i++)
	{
		int currNombre = (int)text[i] - 48;
		nombreTotal += currNombre * exposant;
		exposant /= 10;
	}

	return nombreTotal;
}