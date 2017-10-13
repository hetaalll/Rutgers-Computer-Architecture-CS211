#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "calc.h"

unsigned int size = 64;

int main(int argc, char *argv[])
{

  //declare all variables

    //first operand
  char* num1;
  char base_one;
  bool is_one_negative;
  int sigfigs_one;

    //second operand
  char* num2;
  char base_two;
  bool is_two_negative;
  int sigfigs_two;

    //output
  char output_base;
  char output_op;

  //Error check
  if(argc < 5 || argc > 5)
  {
    fprintf(stderr, "%s\n", "ERROR: Invalid number of arguments");
    exit(0);
  }

    //DEBUG
//  int j;
/*  for(j=0; j < argc; j++)
  {
    printf("Arguments argv[%d] is %s\n", j, argv[j]);
  } */


  int i;

  for(i=0; i < argc; i++)
  {

    // calc <op> <num1> <num2> <output base>

    switch(i)
    {

    case 0 : break; //because argv[0] is the path which we don't need to extract

    case 1 : op(argv[i], &output_op);//+ or -
             //printf("op: %c\n", output_op);
             //printf("\n");
             break;

    case 2 : num1 = first_number(argv[i], &is_one_negative, &base_one, &sigfigs_one);
              //DEBUG
             //printf("NumOne: %s\n", num1);
             //printf("is_negative: %d\n", is_one_negative);
             //printf("first_base: %c\n", base_one);
             //printf("number of sig1: %d\n", sigfigs_one);
             //printf("\n");
             break;

    case 3 : num2 = second_number(argv[i], &is_two_negative, &base_two, &sigfigs_two);
              //DEBUG
             //printf("NumTwo: %s\n", num2);
             //printf("is_negative: %d\n", is_two_negative);
             //printf("second_base: %c\n", base_two);
             //printf("number of sig2: %d\n", sigfigs_two);
             //printf("\n");
             break;

    case 4 : output_base = *argv[i];
             //printf("Output base %c\n", output_base);
             break;

    default : fprintf(stderr, "%s\n", "ERROR: too many arugments");
              exit(0);
              break;

  } //end switch
} //end for loop

  int tmp = 0;
  int* binary_arr1;

  switch(base_one)
  {
    case 'b' : //printf("%s\n", "In first operand case binary.");
               binary_arr1 = binaryASCII_to_int(num1);
               break;

    case 'd' : //printf("%s\n", "In first operand case decimal.");
               tmp = parse_int(num1);
               //printf("tmp %d\n", tmp);
               binary_arr1 = decimal_to_binary(tmp);
              /* printf("after converting decimal to binary array \n");
               for(i = 0; i < size; i++)
               {
                 printf("%d", binary_arr1[i]);
               }
               printf("\n");*/
               break;

    case 'o' : //printf("%s\n", "In first operand case octal");
               binary_arr1 = octal_to_binary(num1);
               //printf("after converting octal to binary\n");
               /*for(i = 0; i < size; i++)
               {
                 printf("%d", binary_arr1[i]);
               }
               printf("\n"); */
               break;

    case 'x' : //printf("%s\n", "In first operand case hexadecimal");
               binary_arr1 = hexa_to_binary(num1);
               printf("after converting hexadecimal to binary\n");
               for(i = 0; i < size; i++)
               {
                 printf("%d", binary_arr1[i]);
               }
               printf("\n");
               break;

  } //end switch base 1

  int tmp2 = 0;
  int* binary_arr2;

  switch(base_two)
  {
    case 'b' : //printf("%s\n", "In second operand case binary.");
               binary_arr2 = binaryASCII_to_int(num2);
               break;

    case 'd' : //printf("%s\n", "In second operand case decimal.");
               tmp2 = parse_int(num2);
               //printf("tmp %d\n", tmp2);
               binary_arr2 = decimal_to_binary(tmp2);
              /* printf("after converting decimal to binary array \n");
               for(i = 0; i < size; i++)
               {
                 printf("%d", binary_arr2[i]);
               }
               printf("\n");*/
               break;

    case 'o' : //printf("%s\n", "In second operand case octal");
               binary_arr2 = octal_to_binary(num2);
               printf("\nafter converting octal to binary\n");
               for(i = 0; i < size; i++)
               {
                 printf("%d", binary_arr2[i]);
               }
               printf("\n");
               break;

    case 'x' : //printf("%s\n", "In second operand case hexadecimal");
               binary_arr2 = hexa_to_binary(num2);
               //printf("after converting hexadecimal to binary\n");
               /*for(i = 0; i < size; i++)
               {
                 printf("%d", binary_arr2[i]);
               }
               printf("\n"); */
               break;

  } //end switch base two

  int * math_arr;

  //start the math
  if(output_op == '+')
  {
    if(is_one_negative)
    {
      binary_arr1 = fliping_bits(binary_arr1);
    }
    if(is_two_negative)
    {
      binary_arr2 = fliping_bits(binary_arr2);
    }
    math_arr = addition(binary_arr1, binary_arr2);
  //  printf("\n%s\n", "After addition: ");
  /*  for(i = 0; i < size; i++)
    {
      printf("%d", math_arr[i]);
    } */
  }
  else if(output_op == '-')
  {
    if(is_one_negative)
    {
      binary_arr1 = fliping_bits(binary_arr1);
    }
    if(is_two_negative)
    {
      //printf("\n%s\n", "After subtraction: ");
      math_arr = addition(binary_arr1, binary_arr2);
    }
    else
    {
      //printf("\n%s\n", "After subtraction: ");
      math_arr = subtraction(binary_arr1, binary_arr2);
    }
  /*   for(i = 0; i < size; i++)
    {
      printf("%d", math_arr[i]);
    } */
  }

    //converting to output base
    //FINAL OUTPUT

  //  printf("\n%s", "Final output:");

  if(output_base == 'b') //binary
  {
    printf("\n");
    printf("%c", 'b');
    for(i = 0; i < size; i++)
    {
      printf("%d", math_arr[i]);
    }
    printf("\n");
  }

  if(output_base == 'd') //decimal
  {
    int d = binary_to_decimal(math_arr);
    printf("\n%c%d\n", 'd', d);
  }

  if(output_base == 'o') //octal
  {
    char* o = binary_to_octal(math_arr);
    printf("\n%c", 'o');
    for(i = 0; i < size; i++)
    {
      printf("%c", o[i]);
    }
    printf("\n");
  }

  if(output_base == 'x') //hexa
  {
    char* h = binary_to_hexa(math_arr);
    printf("\n%c", 'x');
    for(i = 0; i < size; i++)
    {
      printf("%c", h[i]);
    }
    printf("\n");
  }

  return 0;
} // end main

void op(char *arg, char *output_op)
{
  *output_op = arg[0];
}


char* first_number(char* arg, bool* is_negative1 , char* base1, int* sig1)
{
  char* num_one;
  int a=0;
  int b=0;

    if(arg[0] == '-')
    {
      *is_negative1 = true;
    }
    else
    {
      *is_negative1 = false;
    }

    if(*is_negative1)
    {
      *base1 = arg[1];
    }
    else
    {
      *base1 = arg[0];
    }

    if(*is_negative1)
    {
      *sig1 = strlen(arg)-2;
    }
    else
    {
      *sig1 = strlen(arg)-1;
    }

    a = *is_negative1 ? 2 : 1;
    num_one = (char*) malloc((*sig1)+1);
    num_one[0] = '\0';
    num_one[*sig1]= '\0';

    for(; a < strlen(arg); a++)
    {
      //printf("arg %c\n", arg[a]);
      num_one[b] = arg[a];
      b++;
    }
    num_one[b] = '\0';
    //printf("num_one %s\n", num_one);

    return num_one;
} //end first_number


char* second_number(char* argg, bool* is_negative2 , char* base2, int* sig2)
{
  char* num_two;
  int c=0;
  int d=0;

    if(argg[0] == '-')
    {
      *is_negative2 = true;
    }
    else
    {
      *is_negative2 = false;
    }

    if(*is_negative2)
    {
      *base2 = argg[1];
    }
    else
    {
      *base2 = argg[0];
    }

    if(*is_negative2)
    {
      *sig2 = strlen(argg)-2;
    }
    else
    {
      *sig2 = strlen(argg)-1;
    }

    c = *is_negative2 ? 2 : 1;
    num_two = (char*) malloc((*sig2)+1);
    num_two[0] = '\0';
    num_two[*sig2]= '\0';

    for(; c < strlen(argg); c++)
    {
      //printf("arg %c\n", argg[c]);
      num_two[d] = argg[c];
      d++;
    }
    num_two[d] = '\0';
    //printf("num_two %s\n", num_two);

    return num_two;
} //end second_number


int parse_int(char* number)
{
  int i;
  int digits = 0;

  for(i = 0; i < strlen(number); i++)
  {
    digits = digits*10 + (number[i]-'0');
  }
//  printf("after parsing: %d\n", digits);

  return digits;
} //end parse_int


int* binaryASCII_to_int(char* number)
{
  int i;
  char ch = '0';
  int* binary = malloc(size*sizeof(int));
  int k = size -1;

  for(i = 0; i < size; i++)
  {
    binary[i] = 0;
  }

  for(i = (strlen(number)-1); i >= 0; i--)
  {
    ch = number[i];

    if(ch == '0')
    {
      binary[k--] = 0;
    }
    else if(ch == '1')
    {
      binary[k--] = 1;
    }
  }

//  printf("\n%s\n", "Converting to binary: ");
/*  for(i = 0; i < size; i++)
  {
    printf("%d", binary[i]);
  }

  printf("\n"); */
  return binary;
}


int* decimal_to_binary(int number)
{
  int remainder;
  int k;
  int* D_binary = malloc(size * sizeof(int));

    //intialize D_binary to 0
  for(k = 0; k < size; k++)
  {
    D_binary[k] = 0;
  }

  k = 1;
  while(number!=0)
  {
    remainder = number%2;
    number = number/2;
    D_binary[size - k] = remainder;
    k++;
  }

  return D_binary;
} // end decimal_to_binary


int* octal_to_binary(char* number)
{
  int a, b;
  int i , j , k;

  int* O_binary = malloc(size * sizeof(int));

    //initialize O_binary to 0
  for(a = 0; a < size; a++)
  {
    O_binary[a] = 0;
  }

  b = size - 1;
  for(a = (strlen(number))-1 ; a >= 0; a--)
  {
    //printf("octal digits: %c\n", number[a]);
    switch (number[a])
    {
      case '0' : i = 0; j = 0; k = 0; //000
                 break;

      case '1' : i = 0; j = 0; k = 1; //001
                 break;

      case '2' : i = 0; j = 1; k = 0; //010
                 break;

      case '3' : i = 0; j = 1; k = 1; //011
                 break;

      case '4' : i = 1; j = 0; k = 0; //100
                break;

      case '5' : i = 1; j = 0; k = 1; //101
                 break;

      case '6' : i = 1; j = 1; k = 0; //110
                 break;

     case '7' : i = 1; j = 1; k = 1; //111
                break;

     default : printf("\n%s\n","Invalid argument");
                break;
    }
      O_binary[b--] = k;
      O_binary[b--] = j;
      O_binary[b--] = i;

  }

  return O_binary;
} // end octal_to_binary


int* hexa_to_binary(char* number)
{
  int a, b;
  int h, i, j, k;
  b = size - 1;
  int* H_binary = malloc(size * sizeof(int));

    //initialize H_binary to 0
  for(a = 0; a < size; a++)
  {
    H_binary[a] = 0;
  }

  for(a = (strlen(number))-1 ; a >= 0; a--)
  {
    //printf("hexadecimal digits: %c\n", number[a]);
    switch (number[a])
    {
      case '0' : h = 0; i = 0; j = 0; k = 0; //0000
                 break;

      case '1' : h = 0; i = 0; j = 0; k = 1; //0001
                 break;

      case '2' : h = 0; i = 0; j = 1; k = 0; //0010
                 break;

      case '3' : h = 0; i = 0; j = 1; k = 1; //0011
                 break;

      case '4' : h = 0; i = 1; j = 0; k = 0; //0100
                 break;

      case '5' : h = 0; i = 1; j = 0; k = 1; //0101
                 break;

      case '6' : h = 0; i = 1; j = 1; k = 0; //0110
                break;

      case '7' : h = 0; i = 1; j = 1; k = 1; //0111
                 break;

      case '8' : h = 1; i = 0; j = 0; k = 0; //1000
                 break;

      case '9' : h = 1; i = 0; j = 0; k = 1; //1001
                 break;

      case 'A' :
      case 'a' : h = 1; i = 0; j = 1; k = 0; //1010
                 break;

      case 'B' :
      case 'b' : h = 1; i = 0; j = 1; k = 1; //1011
                 break;

      case 'C' :
      case 'c' : h = 1; i = 1; j = 0; k = 0; //1100
                 break;

      case 'D' :
      case 'd' : h = 1; i = 1; j = 0; k = 1; //1101
                 break;

      case 'E' :
      case 'e' : h = 1; i = 1; j = 1; k = 0; //1110
                 break;

      case 'F' :
      case 'f' : h = 1; i = 1; j = 1; k = 1; //1111
                 break;

     default : printf("\n%s\n","Invalid argument");
                break;

    }
      H_binary[b--] = k;
      H_binary[b--] = j;
      H_binary[b--] = i;
      H_binary[b--] = h;
  }
  return H_binary;
} //end hexa_to_binary


int* addition(int* n1, int* n2)
{
  bool carry = false;
  int* output = malloc(size * sizeof(int));
  int i,j;
  i = size - 1;

  for(j = 0; j < size; j++)
  {
    output[j]=0;
  }

  for(; i >= 0; i--)
  {
    if(carry) //true
    {
      if(n1[i] == 0 && n2[i] == 0)
      {
        output[i] = 1;
        carry = false;
      }
      else if((n1[i] == 1 && n2[i] == 0) || (n1[i] == 0 && n2[i] == 1))
      {
        output[i] = 0;
        carry = true;
      }
      else if(n1[i] == 1 && n2[i] == 1)
      {
        output[i] = 1;
        carry = true;
      }
    }
    else //false
    {
      if(n1[i] == 0 && n2[i] == 0)
      {
        output[i] = 0;
        carry = false;
      }
      else if((n1[i] == 1 && n2[i] == 0) || (n1[i] == 0 && n2[i] == 1))
      {
        output[i] = 1;
        carry = false;
      }
      else if(n1[i] == 1 && n2[i] == 1)
      {
        output[i] = 0;
        carry = true;
      }
    }
  } // for loop

  return output;
} // end addition

int* subtraction(int* n1, int* n2)
{
  bool carry = false;
  int* output = malloc(size * sizeof(int));
  int i,j;
  i = size - 1;

    for(j = 0; j < size; j++)
    {
      output[j]=0;
    }

    for(; i >= 0; i--)
    {
      if(carry) //true
      {
        if(n1[i] == 0 && n2[i] == 0)
        {
          output[i] = 1;
          carry = true;
        }
        if(n1[i] == 1 && n2[i] == 0)
        {
          output [i] = 0;
          carry = false;
        }
        if(n1[i] == 0 && n2[i] == 1)
        {
          output[i] = 0;
          carry = true;
        }
        if(n1[i] == 1 && n2[i] == 1)
        {
          output[i] = 1;
          carry = true;
        }
      }
      else //false
      {
        if(n1[i] == 0 && n2[i] == 0)
        {
          output[i] = 0;
          carry = false;
        }
        else if(n1[i] == 1 && n2[i] == 0)
        {
          output [i] = 1;
          carry = false;
        }
        else if(n1[i] == 0 && n2[i] == 1)
        {
          output[i] = 1;
          carry = true;
        }
        else if(n1[i] == 1 && n2[i] == 1)
        {
          output[i] = 0;
          carry = false;
        }
      }
    } // end for

    return output;
} // end subtraction


int power(int x, int y)
{
  //printf("%s%d\n", "x: ", x);
  //printf("%s%d\n", "y: ", y);

  int i;
  int result = 1;
  for(i = 0; i < y; i++)
  {
    result = result * x;
  }
  //printf("%s%d\n", "result: ", result);
  return result;
} //end power


int binary_to_decimal(int* number)
{
  int decimal = 0, i;

  for(i = (size - 1); i >= 0; i--)
  {
    if(number[i] == 1)
    {
      decimal += power(2,(size-i-1));
    }
  }

  return decimal;
} // end binary_to_decimal


char* binary_to_octal(int* number)
{
  char* octal = malloc(size*sizeof(char));
  int oct = 0, i, j, k, tmp;
  char ch = '0';

  for(i = 0; i < size; i++)
  {
    octal[i] = '0';
  }

  i = size - 1;
  k = size - 1;
  j = 1;
  tmp = 1;

  for(; i >= 0; i--)
  {
    oct += number[i]*j;
    j = j*2;

    if((tmp%3)==0)
    {
      if(oct<8)
      {
        ch = oct + '0';
      }
      else
      {
          printf("%s\n", "Error");
      }
      oct = 0;
      j = 1;
      tmp = 1;
      octal[k--] = ch;
      ch = '0';
    }
    else
    {
      tmp++;
    }
  } // for loop

  if(tmp!=3)
  {
    octal[0] = oct + '0';
  }
    return octal;
} // end binary_to_octal


char* binary_to_hexa(int* number)
{
  int hexa = 0, i, j, k;
  char ch = '0';
  char* hexadecimal = malloc(size*sizeof(char));

  for(i = 0; i < size; i++)
  {
    hexadecimal[i] = '0';
  }

  i = size-1;
  j = 1;
  k = size-1;

  for(; i >=0; i--)
  {
    hexa += number[i]*j;
    j = j*2;
    if((i%4)==0)
    {
      if(hexa<=9)
      {
        ch = hexa + '0';
      }
      else
      {
        switch(hexa)
        {
          case 10 : ch = 'A';
                    break;

          case 11 : ch = 'B';
                    break;

          case 12 : ch = 'C';
                    break;

          case 13 : ch = 'D';
                    break;

          case 14 : ch = 'E';
                    break;

          case 15 : ch = 'F';
                    break;

          default: printf("\n%s\n","Invalid argument");
                    break;
        } // switch
      }
      hexa = 0;
      j = 1;
      hexadecimal[k--] = ch;
    } // main if
  } // for loop

  return hexadecimal;
} // end binary_to_hexa


int* fliping_bits(int* num)
{
  int i, j;
  int* flipped = malloc(size*sizeof(int));
  int* one = malloc(size*sizeof(int));

    //DEBUG
/*  for(j = 0; j < size ; j++)
  {
    printf("%d", num[j]);
  }
*/

  for(j = 0; j < size; j++)
  {
    one[j] = 0;
  }

  one[size-1] = 1;

    //DEBUG
/*  for(j = 0; j < size ; j++)
  {
    printf("%d", one[j]);
  }
*/
  for(i = 0; i < size; i++)
  {
    if(num[i] == 1)
    {
      num[i] = 0;
    }
    else if(num[i] == 0)
    {
      num[i] = 1;
    }
  }
      //add 1 after flipping
    flipped = addition(num, one);

      //DEBUG
  //  printf("\n%s\n", "After flipping: ");
  /*  for(j = 0; j < size ; j++)
    {
      printf("%d", flipped[j]);
    }
    printf("\n"); */
  return flipped;
} // end fliping_bits
