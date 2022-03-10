#include"labo.h"
#include<stdlib.h>

void PushBack(Queue* q, void* data)
{
	if (q->head == NULL && q->tail == NULL)
	{
		Node* newNode = malloc(sizeof(Node));//allocate(sizeof(Node));

		int bob;

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

void PushRandomItems(Queue* q)
{

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
		while (currNode != NULL)
		{
			Items* currItems = currNode->data;

			if (currItems->name == name)
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
	Node* currNode = q->head;
	Items* currItems = currNode->data;

	while (currNode != NULL)
	{
		if (currItems->name == name)
		{
			return currItems;
		}
		currNode = currNode->next;
		currItems = currNode->data;
	}
	return NULL;
}

int TakeNumberItems(Queue* q)
{
	return q->nombreNode;
}

void PrintInventory(Queue* q)
{
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