#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#include "nCr.h"

int main(int argc, char *argv[])
{

  int i;
  struct timeval
    start, end;

  int power;
  double t = 0;
  char* arg = argv[1];


  if(argc > 2 || argc < 2)
  {
    fprintf(stderr, "%s\n", "ERROR: Invalid number of arguments");
    exit(0);
  }

  if (argv[1][0] == '-' && argv[1][1] == 'h')
  {
  		printf("Usage: formula <positive integer>\n");
      exit(0);
  }

  for(i = 0; i < strlen(arg); i++)
  {
    if(!isdigit(arg[i]))
    {
      fprintf(stderr, "%s\n", "ERROR: Not a number");
      exit(0);
    }
  }

  if(isdigit((char)*argv[1]))
  {
    power = atoi(argv[1]);
  }
  else
  {
    fprintf(stderr, "%s\n", "ERROR: Not a Number");
    exit(0);
  }

  if(power < 0)
  {
    fprintf(stderr, "%s\n", "ERROR: Power should be an integer greater than or equal to 0");
    exit(0);
  }


  int n = power;
  int r = 0;
  int num;

  num = 0.0;

    gettimeofday(&start, NULL);


    printf("(1 + x)^%d = ", power);

    for(; r <= power; r++)
    {
      num = nCr(n,r);

      if(power == 0)
      {
          printf("%d\n", 1);
          break;
      }

      if(num < 0)
      {
        fprintf(stderr, "%s\n", "ERROR: Overflow");
        exit(0);
      }
      else if(r == 0)
      {
        printf("%d + ", num ); //first
      }
      else
      {
        if(r != n)
        {
          printf("%d*x^%d + ", num, r );
        }
        else
        {
          printf("%d*x^%d ", num, r ); //last
        }
      }
    } //forloop

  gettimeofday(&end, NULL);

  t = (double)(end.tv_usec - start.tv_usec)/1000000 + (double)(end.tv_sec - start.tv_sec);

  printf("\nTime Required: %.0f microseconds\n", t*1000000);


  return 0;
}
