#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <getopt.h>

#include "consts.h"
#include "ga.h"
#include "utils.h"
#include "gnuplot.h"
#include "../config.h"

const char *program_name;

/**
 * @brief print_pop Helper function to print the population on the fout parameter
 * @param pop A pointer to an already initialized population
 * @param amount The amount of individuals we need to print
 * @param fout The file output to print the population, unless there's an error
 * @param dest_len The size of the string inside each individual
 */
void print_pop(individual *pop, int amount, FILE* fout, size_t dest_len){
  int i,j;
  int real_amount = amount;
  if(pop == NULL){
      fprintf(stderr,"Unable to print population, as population is NULL!");
      return;
    }
  if(real_amount == -1) // If the amount parameter is -1, print at max POP_SIZE
      real_amount = POP_SIZE;
  for(i=0;i<real_amount;i++){
      fprintf(fout,"Individual %02d:",i);
      for(j=0;j<dest_len;j++)
          fprintf(fout,"%c",pop[i].s[j]);
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

/**
 * @brief print_usage Prints a simple usage information
 * @param stream Where to output the usage information
 * @param exit_code The code to exit the program with
 */
void print_usage(FILE *stream, int exit_code){
  fprintf(stream, "Usage: %s options\n", program_name);
  fprintf(stream, "    -h\t--help\t\t\tDisplay this help message.\n");
  fprintf(stream, "    -d\t--destination \"string\"\tString to try to evolve into.\n");
  fprintf(stream, "    -o\t--output filename\tOutput of fitness trough time.\n");
  fprintf(stream, "    -s\t--stop\t\t\tStop when finding the string.\n");
  fprintf(stream, "    -p\t--plot filename\t\tPlot a file using gnuplot pipes, and save on filename (only .png).\n");
  exit(exit_code);
}

int main(int argc, char *argv[]){
  individual *pop; // An array with the complete population
  const char *dest = NULL;
  size_t dest_len = 0;
  int g, stop_g=-1;
  double time_start = 0;
  // getopt variables
  int next_option;
  const char* const short_options ="hd:o:sp:";
  const struct option long_options[] = {
    {"help", 0, NULL, 'h' },
    {"destination",0,NULL,'d'},
    {"output",1, NULL, 'o'},
    {"stop",0, NULL, 's'},
    {"plot",0,NULL,'p'},
    {NULL,0,NULL,0}
  };
  const char *fitness_output = NULL;
  const char *gnuplot_fname = NULL;
  FILE *data_fp = NULL;
  int stop = 0;

  program_name = argv[0];
  // Parse options
  do{
      next_option = getopt_long(argc, argv, short_options, long_options, NULL);
      switch(next_option){
        case 'h': print_usage(stdout,EXIT_SUCCESS);
        case 'd': dest=optarg; break;
        case 'o': fitness_output = optarg; break;
        case '?': print_usage(stderr, EXIT_FAILURE);
        case 's': stop=1; break;
        case 'p': {
#ifndef HAVE_GNUPLOT
            fprintf(stderr, "You asked to plot on %s, however 'gnuplot' is not installed! Won't plot!\n",optarg);
#else
            gnuplot_fname = optarg;
#endif
            break;
          }
        case -1: break;
        default: abort();
        }
    }while(next_option != -1);
  if(fitness_output == NULL){
      fprintf(stderr, "Output file is mandatory!\n");
      print_usage(stderr, EXIT_FAILURE);
    }
  if(dest==NULL)
    dest="Hello World from a motherf****ing perspective!\0"; //Default
  dest_len = strlen(dest);

  // Open up the CVS log file
  if((data_fp=fopen(fitness_output, "w"))==NULL){
      perror("Unable to open file!");
      return EXIT_SUCCESS;
    }
  fprintf(data_fp, "generation,fitness");

  // Now we really start
  time_start = cpuSecond();
  fprintf(stdout, "[*] Starting %s...\n",argv[0]);
  fflush(stdout);
  fprintf(stdout,"[*] Creating population...");
  fflush(stdout);
  if((pop = create_population(dest_len))==NULL)
    return errno;
  fprintf(stdout,"[OK]\n");
  fprintf(stdout,"[*] Evolving...");
  fflush(stdout);
  individual * best = NULL;
  for(g=0;g<GA_RUNS;g++){
      calc_fitness(pop, dest);
      qsort(pop,POP_SIZE,sizeof(individual),cmppop);
      best = &pop[0];
      fprintf(data_fp,"%d,%d\n",g,best->fitness);
      if(best->fitness==0){
          if(stop_g == -1)
            stop_g = g;
          if(stop==1)
            break;
        }
      if(g!=GA_RUNS)
          xover_and_mutate(pop, dest_len);
    }
  fprintf(stdout,"[OK]\n");
  fprintf(stdout,"[*] Best found: '%s' [%d]\n",best->s, best->fitness);
  if(best->fitness == 0)
      fprintf(stdout,"[*] Found correct sentence in %d generations!\n",stop_g);
  fflush(stdout);
  //free(pop);
  destroy_population(pop);
  fclose(data_fp);
  fprintf(stdout,"[*] Done, took %f seconds!\n", cpuSecond() - time_start);
  if(gnuplot_fname!=NULL){
    fprintf(stdout, "[*] Plotting evolution to '%s'\n", gnuplot_fname);
    plot(fitness_output, gnuplot_fname);
    }
  return EXIT_SUCCESS;
}
