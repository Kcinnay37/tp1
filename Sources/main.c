#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "labo.h"

uint8_t* heap = NULL;
size_t heap_top = 0;

int main(void)
{
	Queue items = { 0 };
	Queue inventory = { 0 };

	TakeAllItemsFile(&items);

	PushBack(&inventory, FindItemsByName(&items, "Potion"));

	PushRandomItemsWithout(&inventory, &items, 10, TakeItemsIdexByName(&items, "Potion"));

	PrintInventory(&inventory);

	SortByPrixVente(&inventory);

	PopByName(&inventory, "Potion");

	PrintInventory(&inventory);

	DeleteItemsMemory(&items);
	DeleteQueueMemory(&items);
	DeleteQueueMemory(&inventory);

	return 0;
}
