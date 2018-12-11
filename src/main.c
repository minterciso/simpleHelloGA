#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "consts.h"
#include "ga.h"

void print_pop(individual *pop, int amount){
  int i,j;
  for(i=0;i<amount;i++){
      printf("Individual %02d:",i);
      for(j=0;j<FINAL_LENGTH;j++){
          printf("%c",pop[i].s[j]);
        }
      printf(" [%d]\n",pop[i].fitness);
    }
}

static int cmppop(const void *p1, const void *p2){
  individual *i1=(individual*)p1;
  individual *i2=(individual*)p2;
  return i1->fitness-i2->fitness;
}

int main(int argc, char *argv[]){
  individual *pop;
  int g;
  if((pop=(individual*)malloc(sizeof(individual)*POP_SIZE))==NULL){
      perror("Unable to allocate!");
      return -1;
    }
  memset(pop,'\0',sizeof(individual)*POP_SIZE);
  create_popultion(pop);
  printf("Done creating...\n");
  individual * best = NULL;
  for(g=0;g<GA_RUNS;g++){
      calc_fitness(pop);
      qsort(pop,POP_SIZE,sizeof(individual),cmppop);
      best = &pop[0];
      if(best->fitness==0){
          printf("String found is '%s'. Found in %d generations.\n",best->s,g+1);
          break;
        }
      printf("Best so far: %s [%d]\n",best->s, best->fitness);
      if(g!=GA_RUNS){
          xover_and_mutate(pop);
        }
      else{
          printf("After %d runs, we still were unable to find the string...\n",GA_RUNS);
        }
    }
  free(pop);
  return EXIT_SUCCESS;
}
