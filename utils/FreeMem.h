#ifndef FREEMEM_H
#define FREEMEM_H
#include <stdlib.h>

struct elem
{ /* Definition of a structure that is FREEMEM_CELL bytes  in size.) */
	struct elem *next;
	char dummy[MBED_CONF_APP_FREEMEM_CELL - 2];
};
inline int FreeMem(void)
{
	int counter;
	struct elem *head, *current, *nextone;
	current = head = (struct elem *)malloc(sizeof(struct elem));
	if (head == NULL)
		return 0; /*No memory available.*/
	counter = 0;
	// __disable_irq();
	do
	{
		counter++;
		current->next = (struct elem *)malloc(sizeof(struct elem));
		current = current->next;
	} while (current != NULL);
	/* Now counter holds the number of type elem
	structures we were able to allocate. We
	must free them all before returning. */
	current = head;
	do
	{
		nextone = current->next;
		free(current);
		current = nextone;
	} while (nextone != NULL);
	// __enable_irq();

	return counter * MBED_CONF_APP_FREEMEM_CELL;
}
#endif // FREEMEM_H
