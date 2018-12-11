#include "gnuplot.h"
#include <stdio.h>
#include <stdlib.h>

void plot(const char *data_fname, const char *output_fname)
{
  FILE *gnuplotPipe = NULL;
  if((gnuplotPipe=popen("gnuplot -persistent", "w"))==NULL){
      perror("Unable to open gnuplot pipe");
      return;
    }
  fprintf(gnuplotPipe, "set title \"Hello World evolution\"\n");
  fprintf(gnuplotPipe, "set xlabel \"Generations\"\n");
  fprintf(gnuplotPipe, "set ylabel \"Fitness\"\n");
  fprintf(gnuplotPipe, "set datafile separator \",\"\n");
  fprintf(gnuplotPipe, "set grid\n");
  fprintf(gnuplotPipe, "set term png\n");
  fprintf(gnuplotPipe, "set output '%s'\n", output_fname);
  fprintf(gnuplotPipe, "plot '%s' using 2 with lines title 'f'\n", data_fname);
  fprintf(gnuplotPipe, "set term x11\n");
  fprintf(gnuplotPipe, "quit\n");
  fflush(gnuplotPipe);
  pclose(gnuplotPipe);
}
