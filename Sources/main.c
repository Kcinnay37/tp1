#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "labo.h"

uint8_t* heap = NULL;
size_t heap_top = 0;

int main(void)
{
	Queue q = {0};

	Items items1 = { "patate", 55};
	Items items2 = { "couteau", 300};
	Items items3 = { "armure", 1000};
	Items items4 = { "hache", 400};

	PushBack(&q, &items1);
	PushBack(&q, &items2);
	PushBack(&q, &items3);
	PushBack(&q, &items4);

	SortByPrixVente(&q);

	//PopByName(&q, "couteau");

	PrintInventory(&q);

	return 0;
}
