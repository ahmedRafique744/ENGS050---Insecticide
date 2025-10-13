/* 
 * queueTest.c --- 
 * 
 * Author: Insecticide
 * Created: 10-12-2025
 * Version: 1.0
 * 
 * Description: This file tests the queue.c module and queue.h interface.
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

typedef struct car {
    char plate[10];
    double price;
    int year;
} car_t;

void print_car(void *cp) {
    car_t *car = (car_t *)cp;
    printf("%s: $%.2f, %d\n", car->plate, car->price, car->year);
}

bool match_plate(void *cp, const void *keyp) {
    car_t *car = (car_t *)cp;
    const char *key = (const char *)keyp;
    return (strcmp(car->plate, key) == 0);
}

int main(void) {
    printf("Queue Module Test\n");
		
    queue_t *qp = qopen();
    if (!qp) {
        printf("qopen failed\n");
        exit(EXIT_FAILURE);
    }

    car_t *c1 = malloc(sizeof(car_t));
    car_t *c2 = malloc(sizeof(car_t));
    car_t *c3 = malloc(sizeof(car_t));
    strcpy(c1->plate, "ABC123"); c1->price = 12000.00; c1->year = 2010;
    strcpy(c2->plate, "XYZ789"); c2->price = 8000.00;  c2->year = 2012;
    strcpy(c3->plate, "LMN456"); c3->price = 10000.00; c3->year = 2011;

    qput(qp, c1);
    qput(qp, c2);
    qput(qp, c3);

    printf("After qput:\n");
    qapply(qp, print_car);

    car_t *found = qsearch(qp, match_plate, "XYZ789");
    if (found != NULL)
        printf("\nFound: %s ($%.2f)\n", found->plate, found->price);
    else
        printf("\nSearch failed\n");

    car_t *removed = qremove(qp, match_plate, "ABC123");
    if (removed != NULL) {
        printf("\nRemoved: %s\n", removed->plate);
        free(removed);
    }

    printf("\nAfter qremove:\n");
    qapply(qp, print_car);

    car_t *first = qget(qp);
    if (first != NULL) {
        printf("\nqget removed: %s\n", first->plate);
        free(first);
    }

    printf("\nAfter qget:\n");
    qapply(qp, print_car);
		qapply(qp, free);
		qclose(qp);
    printf("\nQueue closed successfully.\n");
		
		c1 = NULL;
		c2 = NULL;
		c3 = NULL;
		
    return 0;
}

