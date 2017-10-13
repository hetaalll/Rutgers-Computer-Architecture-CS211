#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "mystery.h"

int a[200];

int main(int argc, char *argv[])
{
  int num, i, output;

  if(argc > 2 || argc < 2)
  {
    fprintf(stderr, "%s\n", "ERROR: Invalid Number of Arguments");
    exit(0);
  }


  if(isdigit((char)*argv[1]))
  {
    num = atoi(argv[1]);
  }
  else
  {
    fprintf(stderr, "%s\n", "ERROR: Not a Number");
    exit(0);
  }

  for(i = 0; i < 200; i++)
  {
    a[i] = -1;
  }

  if(num >= 47)
  {
    fprintf(stderr, "%s\n", "ERROR: Overflow");
    exit(0);
  }

  output = fibonacci(num);
  printf("Value: %d\n", output);

  return 0;
}

int add(int x, int y)
{
  return x + y;
} //end add

int fibonacci(int num)
{
  int fib;

  if(a[num] == -1)
  {
    if(num == 0)
    {
      a[num] = 0;
    }
    else if (num == 1)
    {
      a[num] = 1;
    }
    else
    {
      a[num] = add(fibonacci(num-2), fibonacci(num-1));
    }
  }

  fib = a[num];
  return fib;

} //end dothething
