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
  char *s; /// The guess string of the individual
  int fitness; /// The fitness (how well adapted) from the individuos
} individual; /// The representation of the individual

/**
 * @brief fitness Calculates the fitness (hamilton distance from target text) of the individual, and store the fitness on the fit address variable
 * @param s The string we want to check
 * @param fit A pointer to where we want the fitneess to be stored at
 */
void fitness(const char *s, const char *d, int *fit);

/**
 * @brief create_popultion Create the population, based on the parameter defined on consts.h
 * @return A pointer to an initilized population (which is nothing more than an individual array)
 */
individual* create_population(size_t dest_len);

/**
 * @brief calc_fitness Calculate the fitness of the population
 * @param pop The population to calculate the fitness
 * @param d The destination string
 */
void calc_fitness(individual *pop, const char *d);

/**
 * @brief xover_and_mutate Based on the parameters on consts.h, execute the cross over and mutation of the population
 * @param pop The population to cross and mutate
 * @param dest_len The size of the destination string
 */
void xover_and_mutate(individual *pop, size_t dest_len);

void destroy_population(individual *pop);

#endif /* GA_H_ */
