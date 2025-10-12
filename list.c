/* 
 * list.c --- 
 * 
 * Author: Insecticide
 * Created: 10-11-2025
 * Version: 1.0
 * 
 * Description: The list.c module that implements the list of cars
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "list.h"

static car_t *front = NULL;

int32_t lput(car_t *cp) {
	if (cp == NULL) {
		return 1;
	}
	cp->next = front;
	front = cp;

	return 0;
}

car_t *lget() {
	if (front == NULL) {
		return NULL;
	}
	car_t *temp = front;
	front = front->next;
	temp->next = NULL;
	return temp;
}

void lapply(void (*fn)(car_t *cp)) {
	car_t *address;
	for (address = front; address != NULL; address = address->next) {
		fn(address);
	}
}

car_t *lremove(char *platep) {
	car_t *temp = front;
	car_t *prev = NULL;
	for (temp = front; temp != NULL; temp = temp->next) {
		if (strcmp(temp->plate, platep) == 0) {
			if (temp == front) {
				front = temp->next;
				return temp;
			}
			prev->next = temp->next;
			return temp;
		}
		prev = temp;
	}
	return NULL;
}

