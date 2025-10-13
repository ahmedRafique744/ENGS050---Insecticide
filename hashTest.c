/* 
 * hashTest.c --- 
 * 
 * Author: Insecticide
 * Created: 10-13-2025
 * Version: 1.0
 * 
 * Description: The following tests our hash.c file
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"

typedef struct car {
  char plate[10];
  double price;
  int year;
} car_t;

void print_car(void *ep) {
  car_t *car = (car_t*)ep;
  printf("%s: $%.2f, %d\n", car->plate, car->price, car->year);
}

bool match_plate(void *ep, const void *keyp) {
  car_t *car = (car_t*)ep;
  const char *key = (const char*)keyp;
  return (strcmp(car->plate, key) == 0);
}

int main(void) {
  printf("Hash Table Module Test\n");

  hashtable_t *htp = hopen(10);
  if (!htp) {
    printf("hopen failed\n");
    exit(EXIT_FAILURE);
  }

  car_t *c1 = malloc(sizeof(car_t));
  car_t *c2 = malloc(sizeof(car_t));
  car_t *c3 = malloc(sizeof(car_t));
  strcpy(c1->plate, "ABC123"); c1->price = 12000.00; c1->year = 2010;
  strcpy(c2->plate, "XYZ789"); c2->price = 8000.00;  c2->year = 2012;
  strcpy(c3->plate, "LMN456"); c3->price = 10000.00; c3->year = 2011;

  hput(htp, c1, c1->plate, strlen(c1->plate));
  hput(htp, c2, c2->plate, strlen(c2->plate));
  hput(htp, c3, c3->plate, strlen(c3->plate));

  printf("\nAfter hput:\n");
  happly(htp, print_car);

  car_t *found = hsearch(htp, match_plate, "XYZ789", strlen("XYZ789"));
  if (found != NULL) {
    printf("\nFound: %s ($%.2f)\n", found->plate, found->price);
  } else {
    printf("\nSearch failed for existing car\n");
  }

  found = hsearch(htp, match_plate, "BOGUS", strlen("BOGUS"));
  if (found == NULL) {
    printf("\nSuccessfully did not find non-existent car\n");
  } else {
    printf("\nSearch failed, found a car that doesn't exist\n");
  }

  car_t *removed = hremove(htp, match_plate, "ABC123", strlen("ABC123"));
  if (removed != NULL) {
    printf("\nRemoved: %s\n", removed->plate);
    free(removed);
  }

  printf("\nAfter hremove:\n");
  happly(htp, print_car);

  happly(htp, free);
  hclose(htp);
  printf("\nHash table closed successfully.\n");

  c1 = NULL;
  c2 = NULL;
  c3 = NULL;

  return 0;
}
