/*
 * ga.h
 *
 *  Created on: 11/12/2018
 *      Author: minterciso
 */

#ifndef GA_H_
#define GA_H_

#include "consts.h"

typedef struct {
  char s[FINAL_LENGTH];
  int fitness;
} individual;

void fitness(const char *s, int *fit);
void create_popultion(individual *pop);
void calc_fitness(individual *pop);
void xover_and_mutate(individual *pop);


#endif /* GA_H_ */
