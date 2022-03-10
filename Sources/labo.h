#include <stdint.h>
#include <assert.h>

#define HEAP_SIZE 1024 * 1024
extern uint8_t* heap;
extern size_t heap_top;

static void* allocate(size_t size) {
	size_t old_top = heap_top;
	heap_top += size;
	assert(heap_top <= HEAP_SIZE);
	return &heap[old_top];
}

typedef struct Items Items;

struct Items
{
	char* name;
	int prixVente;
};

typedef struct Node Node;

struct Node
{
	Node* prev;
	void* data;
	Node* next;
};

typedef struct Queue Queue;

struct Queue
{
	Node* head;
	Node* tail;
	int nombreNode;
};

void PushBack(Queue* q, void* data);

void PushAsPriority(Queue* q, void* data);

void PushHead(Queue* q, void* data);

void PushNodePosition(Queue* q, Node* n, void* data);

void PushRandomItems(Queue* q);

void deleteNode(Queue* q, Node* node);

Node PopByName(Queue* q, char* name);

void SortByPrixVente(Queue* q);

Items* FindItemsByPosition(Queue* q, int position);

Items* FindItemsByName(Queue* q, char* name);

int TakeNumberItems(Queue* q);

void PrintInventory(Queue* q);

void DeleteQueueMemory(Queue* q);