#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "nCr.h"


extern int Factorial(int n)
{
  if(n > 12)
  {
    fprintf(stderr, "%s\n", "ERROR: Integer overflow");
    exit(0);
  }

  if(n == 0 || n == 1)
  {
    return 1;
  }
  else
  {
    return (n * Factorial(n - 1));
  }

} //end factorial


extern int nCr(int n, int r)
{
  if(n > 12)
  {
    fprintf(stderr, "%s\n", "Integer overflow");
    exit(0);
  }

  if(n < r)
  {
    printf("%s\n", "ERROR: n < r");
    exit(0);
  }

  int ncr = 0;

  ncr = Factorial(n) / (Factorial(r) * Factorial(n-r));

  return ncr;
}
