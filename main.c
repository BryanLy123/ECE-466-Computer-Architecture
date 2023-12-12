//Author: Bryan Ly
//ECE 466 Homework 5
//DAXPY loop execution times

#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

//Gener
void daxpy_loop(int num, double var, double *x, double *y){
 // int i = 0;
  for (int i = 0; i < num ; i++){
    y[i] = var*x[i] + y[i];
  }
}

int main(void) {
  double var = 2.0;
  int num = 10000;

  struct timeval begin_time, end_time;

  double *x = (double*) malloc(num * sizeof(double));
  double *y = (double*) malloc(num * sizeof(double));

  //declaration of x and y
  for (int i = 0; i < num; i++){
    x[i] = i;
    y[i] = i;
  }

  //timing function to measure time before loop
  gettimeofday(&begin_time, NULL);
  daxpy_loop(num, var, x, y);
  gettimeofday(&end_time, NULL);
  
  //double time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
  printf("Execution time: %ld microseconds\n", (end_time.tv_sec - begin_time.tv_sec) * 1000000 + (end_time.tv_usec - begin_time.tv_usec));

  //unrolled loop
  for (int i = 0; i < num; i+=4){
    y[i] = var*x[i] + y[i];
    y[i+1] = var*x[i+1] + y[i+1];
    y[i+2] = var*x[i+2] + y[i+2];
    y[i+3] = var*x[i+3] + y[i+3];
  }
  
  //timing function to measure time after loop
  gettimeofday(&begin_time, NULL);
  daxpy_loop(num, var, x, y);
  gettimeofday(&end_time, NULL);

  //output for time after unrolling loop
  printf("Execution time after unrolling: %ld microseconds\n", (end_time.tv_sec - begin_time.tv_sec) * 1000000 + (end_time.tv_usec - begin_time.tv_usec));
  
  //deallocating arrays
  free(x);
  free(y);
  
  return 0;
}