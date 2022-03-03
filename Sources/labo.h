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

void pushBack(Node* n, void* data);

Node* popByName(Node* n, char* name);

void sortByPrixVente(Node* n);

Items* findItemsByPosition(Node* n, int position);

Items* findItemsByName(Node* n, char* name);

int takeNumberItems(Node* n);