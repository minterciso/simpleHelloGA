#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "consts.h"
#include "ga.h"
#include "utils.h"

/**
 * @brief print_pop Helper function to print the population on the fout parameter
 * @param pop A pointer to an already initialized population
 * @param amount The amount of individuals we need to print
 * @param fout The file output to print the population, unless there's an error
 */
void print_pop(individual *pop, int amount, FILE* fout){
  int i,j;
  int real_amount = amount;
  if(pop == NULL){
      fprintf(stderr,"Unable to print population, as population is NULL!");
      return;
    }
  if(real_amount == -1){ // If the amount parameter is -1, print at max POP_SIZE
      real_amount = POP_SIZE;
    }
  for(i=0;i<amount;i++){
      fprintf(fout,"Individual %02d:",i);
      for(j=0;j<FINAL_LENGTH;j++){
          fprintf(fout,"%c",pop[i].s[j]);
        }
      fprintf(fout, " [%d]\n",pop[i].fitness);
    }
}

/**
 * @brief cmppop Returns the fitness difference. Used on the qsort() method
 * @param p1 The 1st individual to compare
 * @param p2 The 2nd individual to compare to
 * @return The differente of fitness
 */
static int cmppop(const void *p1, const void *p2){
  individual *i1=(individual*)p1;
  individual *i2=(individual*)p2;
  return i1->fitness-i2->fitness;
}

int main(int argc, char *argv[]){
  individual *pop; // An array with the complete population
  int g;
  int time_start = cpuSecond();
  fprintf(stdout, "[*] Starting %s...\n",argv[0]);
  fflush(stdout);
  fprintf(stdout,"[*] Creating population...");
  fflush(stdout);
  if((pop = create_popultion())==NULL)
    return errno;
  fprintf(stdout,"[OK]\n");
  fprintf(stdout,"[*] Evolving...");
  fflush(stdout);
  individual * best = NULL;
  for(g=0;g<GA_RUNS;g++){
      calc_fitness(pop);
      qsort(pop,POP_SIZE,sizeof(individual),cmppop);
      best = &pop[0];
      if(best->fitness==0){
          break;
        }
      if(g!=GA_RUNS)
          xover_and_mutate(pop);
    }
  fprintf(stdout,"[OK]\n");
  fprintf(stdout,"[*] Best found: '%s' [%d]\n",best->s, best->fitness);
  if(best->fitness == 0)
      fprintf(stdout,"[*] Found correct sentence in %d generations!\n",g);
  fflush(stdout);
  free(pop);
  fprintf(stdout,"[*] Done, took %f seconds!\n", cpuSecond() - time_start);
  return EXIT_SUCCESS;
}
