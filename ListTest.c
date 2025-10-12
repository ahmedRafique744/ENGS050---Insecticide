/* 
 * ListTest.c --- 
 * 
 * Author: Insecticide
 * Created: 10-12-2025
 * Version: 1.0
 * 
 * Description: The following contains comprehensive testing of our list.c file
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "list.h"


void printcar(car_t *cp) {
  printf("Plate: %s, Price: %.2f, Year: %d\n", cp->plate, cp->price, cp->year);
}

car_t *make_car(char *plate, double price, int year) {
  car_t *cp = (car_t*)malloc(sizeof(car_t));
  if (cp == NULL) {
    return NULL;
  }
  strcpy(cp->plate, plate);
  cp->price = price;
  cp->year = year;
  cp->next = NULL;
  return cp;
}

int main(void) {
  car_t *c1 = make_car("c1", 100.0, 2001);
  car_t *c2 = make_car("c2", 200.0, 2002);
  car_t *c3 = make_car("c3", 300.0, 2003);
  car_t *removed_car;

  printf("Testing lput\n");
  lput(c1);
  printf("put c1 into empty list\n");
  lput(c2);
  printf("put c2 into non-empty list\n");
  lput(c3);
  printf("put c3 into non-empty list\n");
  
  printf("\nTesting lapply\n");
  printf("List state:\n");
  lapply(printcar);

  printf("\nTesting lget\n");
  removed_car = lget();
  printf("get car: ");
  printcar(removed_car);

  removed_car = lget();
  printf("get car: ");
  printcar(removed_car);

  printf("List state after two gets:\n");
  lapply(printcar);

  removed_car = lget();
  printf("get car: ");
  printcar(removed_car);

  printf("List state after final get:\n");
  lapply(printcar);
  
  removed_car = lget();
  if (removed_car == NULL) {
    printf("get from empty list: success (NULL)\n");
  }

  free(c1);
  free(c2);
  free(c3);

  printf("\nTesting lremove\n");
  car_t *r1 = make_car("r1", 10.0, 2011);
  car_t *r2 = make_car("r2", 20.0, 2012);
  car_t *r3 = make_car("r3", 30.0, 2013);
  car_t *r4 = make_car("r4", 40.0, 2014);

  lput(r1);
  lput(r2);
  lput(r3);
  lput(r4);

  printf("Initial list for remove tests:\n");
  lapply(printcar);

  removed_car = lremove("r10");
  if (removed_car == NULL) {
    printf("\nremove non-existent plate 'r10': success (NULL)\n");
  }

  printf("\nRemoving from middle ('r2')...\n");
  removed_car = lremove("r2");
  if (removed_car != NULL) {
    printcar(removed_car);
    free(removed_car);
  }
  lapply(printcar);

  printf("\nRemoving from beginning ('r4')...\n");
  removed_car = lremove("r4");
  if (removed_car != NULL) {
    printcar(removed_car);
    free(removed_car);
  }
  lapply(printcar);

  printf("\nRemoving from end ('r1')...\n");
  removed_car = lremove("r1");
  if (removed_car != NULL) {
    printcar(removed_car);
    free(removed_car);
  }
  lapply(printcar);

  printf("\nRemoving last element ('r3')...\n");
  removed_car = lremove("r3");
  if (removed_car != NULL) {
    printcar(removed_car);
    free(removed_car);
  }
  
  printf("List state after all removes:\n");
  lapply(printcar);

  printf("\nRemoving from empty list...\n");
  removed_car = lremove("r1");
  if (removed_car == NULL) {
    printf("remove from empty list: success (NULL)\n");
  }
  
  exit(0);
}
