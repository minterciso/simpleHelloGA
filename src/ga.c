/*
 * ga.c
 *
 *  Created on: 11/12/2018
 *      Author: minterciso
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ga.h"

void fitness(const char *s, int *fit){
  int i;
  const char *d = FINAL_STRING;
  *fit = 0;
  for(i=0;i<FINAL_LENGTH;i++){
      *fit += abs(s[i]-d[i]);
    }
}

individual* create_popultion(void){
  int i,j;
  int min=MIN_CHAR;
  int max=MAX_CHAR;
  char *tmp_string;
  individual *pop = NULL;

  srand(time(NULL));
  if((pop=(individual*)malloc(sizeof(individual)*POP_SIZE))==NULL){
      perror("Unable to allocate memory for population");
      return NULL;
    }
  memset(pop,'\0',sizeof(individual)*POP_SIZE);
  if((tmp_string=(char*)malloc(sizeof(char)*FINAL_LENGTH))==NULL){
      perror("Unable to allocate temporary string");
      free(pop);
      return NULL;
    }
  for(i=0;i<POP_SIZE;i++){
      pop[i].fitness=99999;
      memset(tmp_string,'\0',FINAL_LENGTH);
      for(j=0;j<FINAL_LENGTH-1;j++){
          tmp_string[j] = (char)(rand()%(max-min+1)+min);
        }
      snprintf(pop[i].s, FINAL_LENGTH, "%s",tmp_string);
    }
  free(tmp_string);
  return pop;
}

void calc_fitness(individual *pop){
  int i;
  for(i=0;i<POP_SIZE;i++){
      fitness(pop[i].s, &pop[i].fitness);
    }
}

void xover_and_mutate(individual *pop){
  int i,j;
  int min=MIN_CHAR;
  int max=MAX_CHAR;

  // Kill low performance individuals
  for(i=KEEP_POP;i<POP_SIZE;i++){
      pop[i].fitness=9999;
      memset(pop[i].s,'\0',FINAL_LENGTH);
    }
  for(i=KEEP_POP;i<POP_SIZE;i+=2){
      //select 2 random ids
      int id1=rand()%KEEP_POP;
      int id2=id1;
      while(id2==id1){
          id2 = rand()%KEEP_POP;
        }
      //select single point xover
      int xp = rand()%FINAL_LENGTH;
      individual *p1 = &pop[id1];
      individual *p2 = &pop[id2];
      individual *s1 = &pop[i];
      individual *s2 = &pop[i+1];
      // There may be a bug here with the memcpy(), we may be copying more than needed, check this!
      memcpy(s1->s, p1->s, xp);
      memcpy(s1->s + xp, p2->s + xp, (FINAL_LENGTH-xp));
      memcpy(s2->s, p2->s, xp);
      memcpy(s2->s + xp, p1->s +xp, (FINAL_LENGTH-xp));
      // mutate
      for(j=0;j<FINAL_LENGTH;j++){
          //s1
          float rnd = (float)rand()/(float)(RAND_MAX);
          if(rnd < PROB_M){
              s1->s[j] = (char)(rand()%(max-min+1)+min);
            }
          //s2
          rnd = (float)rand()/(float)(RAND_MAX);
          if(rnd < PROB_M){
              s2->s[j] = (char)(rand()%(max-min+1)+min);
            }
        }
    }
}
