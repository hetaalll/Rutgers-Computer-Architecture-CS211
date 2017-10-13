#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "y86emul.h"

int debug = 0;
unsigned int size_arr = 64;


typedef struct cpu
{
	int registers[8];

	int pc;
	int cpu_size;

	int count;
	int OF;
	int ZF;
	int SF;
} cpu;

typedef union
{
	struct
	{
		unsigned int one : 4;
		unsigned int two : 4;
	} p;
	char bc;
} byte;

typedef union
{
	struct
	{
		char b1, b2, b3, b4;
	} ch;
	int int_p;
} long_p;

byte *mem;

long check_pt(long addr, cpu* cpu)
{
	if(addr < 0 || addr >= cpu->cpu_size)
	{
		fprintf(stderr, "ERROR!\n");
		exit(0);
	}
	return addr;
} //end check_point

int convert_char(char c)
{
  if(c >= '0' && c <= '9')
    return c - '0';
  if(c >= 'A' && c <= 'F')
    return 10 + c - 'A';
  if(c >= 'a' && c <= 'f')
    return 10 + c - 'a';
  fprintf(stderr, "ERROR: Invalid hex character: %c.\n", c);
  exit(0);
}


char * read_file(char* filename)
{
  long length = 0;
  char *readFile = 0;
  FILE *file = fopen(filename, "rb");

	if(file == NULL)
	{
		fprintf(stderr, "%s\n", "ERROR: Failed to open");
		exit(0);
	}

  if(file)
  {
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    readFile = malloc(length);

    if(readFile)
    {
      fread(readFile, 1, length, file);
    }

    fclose(file);
  }
  else
  {
    fprintf(stderr, "%s\n", "ERROR: File does not exist.");
    exit(0);
  }

	readFile[length] = '\0';
  if(readFile)
  {
    if(debug)
    {
      printf("After parsing the file: %s \n", readFile);
    }
    return readFile;
  }
  else
  {
    fprintf(stderr, "%s\n", "ERROR: Something wrong with the given file");
    return "";
  }
} // end read_file


long power(int x, int y)
{

  int i;
  long result = 1;
  for(i = 0; i < y; i++)
  {
    result = result * x;
  }
  return result;
} //end power


int* hexa_to_binary(char* number)
{
	int a, b;
  int h, i, j, k;
  b = size_arr - 1;
  int* H_binary = malloc(size_arr * sizeof(int));

    //initialize H_binary to 0
  for(a = 0; a < size_arr; a++)
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


long binary_to_decimal(int* number)
{
  long decimal = 0, i;

  for(i = (size_arr - 1); i >= 0; i--)
  {
    if(number[i] == 1)
    {
      decimal += power(2,(size_arr-i-1));
    }
  }

  return decimal;
} // end binary_to_decimal

long hex_to_decimal(char* num)
{
  int * bin = 0;
	//int j = 0;
	bin = hexa_to_binary(num);

	long dec = 0;
 	dec = binary_to_decimal(bin);
	return dec;

}//end hex_to_decimal

//starting switch functions

void inc(int num, cpu* cpu)
{
	cpu->pc += num;
	if(cpu->pc >= cpu->cpu_size)
	{
		fprintf(stderr, "%s\n", "ERROR!");
		exit(0);
	}
}//end inc

int reg(int r)
{
	if(r > 7)
	{
		fprintf(stderr, "%s\n", "ERROR: Invalid register");
		exit(0);
	}
	return r;
} //end reg

void rrmovl(cpu *cpu)
{
  if(mem[cpu->pc].p.one != 0)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  inc(1, cpu);
  reg(mem[cpu->pc].p.two);
  reg(mem[cpu->pc].p.one);

  cpu->registers[mem[cpu->pc].p.one] = cpu->registers[mem[cpu->pc].p.two];
  inc(1, cpu);
}//end rrmovl

void irmovl(cpu *cpu)
{
  if(mem[cpu->pc].p.one != 0)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  inc(1, cpu);
  if(mem[cpu->pc].p.two != 15)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  unsigned int r = reg(mem[cpu->pc].p.one);

  long_p val;

  inc(1, cpu);
  val.ch.b1 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b2 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b3 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b4 = mem[cpu->pc].bc;

  cpu->registers[r] = val.int_p;
  inc(1, cpu);
}//end rmmovl

void rmmovl(cpu *cpu)
{
  if(mem[cpu->pc].p.one != 0)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  inc(1, cpu);

  unsigned int rA = reg(mem[cpu->pc].p.two);
  unsigned int rB = reg(mem[cpu->pc].p.one);
  long_p val;

  inc(1, cpu);
  val.ch.b1 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b2 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b3 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b4 = mem[cpu->pc].bc;

  val.int_p = val.int_p + cpu->registers[rB];

  if(val.int_p < 0 || val.int_p + 3 >= cpu->cpu_size)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  long_p num;
  num.int_p = cpu->registers[rA];

  mem[val.int_p].bc = num.ch.b1;
  mem[val.int_p + 1].bc = num.ch.b2;
  mem[val.int_p + 2].bc = num.ch.b3;
  mem[val.int_p + 3].bc = num.ch.b4;

  inc(1, cpu);
}

void mrmovl(cpu *cpu)
{
  if(mem[cpu->pc].p.one != 0)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  inc(1, cpu);

  unsigned int rA = reg(mem[cpu->pc].p.two);
  unsigned int rB = reg(mem[cpu->pc].p.one);
  long_p val;

  inc(1, cpu);
  val.ch.b1 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b2 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b3 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b4 = mem[cpu->pc].bc;

  val.int_p = val.int_p + cpu->registers[rB];

  if(val.int_p < 0 || val.int_p + 3 >= cpu->cpu_size)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  long_p num;

  num.ch.b1 = mem[val.int_p].bc;
  num.ch.b2 = mem[val.int_p + 1].bc;
  num.ch.b3 = mem[val.int_p + 2].bc;
  num.ch.b4 = mem[val.int_p + 3].bc;

  cpu->registers[rA] = num.int_p;

  inc(1, cpu);
}

void addl(cpu *cpu)
{
  int rA = cpu->registers[mem[cpu->pc].p.two];
  int rB = cpu->registers[mem[cpu->pc].p.one];

  if(rA > 0 && rB > 0 && rA + rB < 0)
    cpu->OF = 1;
  else if(rA < 0 && rB < 0 && rA + rB > 0)
    cpu->OF = 1;
  else
    cpu->OF = 0;

  cpu->registers[mem[cpu->pc].p.one] = rB + rA;

  if(cpu->registers[mem[cpu->pc].p.one] == 0)
    cpu->ZF = 1;
  else
    cpu->ZF = 0;

  if(cpu->registers[mem[cpu->pc].p.one] < 0)
    cpu->SF = 1;
  else
    cpu->SF = 0;
}

void subl(cpu *cpu)
{
  int rA = cpu->registers[mem[cpu->pc].p.two];
  int rB = cpu->registers[mem[cpu->pc].p.one];

  if(rA < 0 && rB > 0 && rA - rB > 0)
    cpu->OF = 1;
  else if(rA > 0 && rB < 0 && rA - rB < 0)
    cpu->OF = 1;
  else
    cpu->OF = 0;

  cpu->registers[mem[cpu->pc].p.one] = rB - rA;

  if(cpu->registers[mem[cpu->pc].p.one] == 0)
    cpu->ZF = 1;
  else
    cpu->ZF = 0;

  if(cpu->registers[mem[cpu->pc].p.one] < 0)
    cpu->SF = 1;
  else
    cpu->SF = 0;
}

void andl(cpu *cpu)
{
  int val = cpu->registers[mem[cpu->pc].p.two] & cpu->registers[mem[cpu->pc].p.one];

  cpu->OF = 0;

  if(val == 0)
    cpu->ZF = 1;
  else
    cpu->ZF = 0;

  if(val < 0)
    cpu->SF = 1;
  else
    cpu->SF = 0;
}

void xorl(cpu *cpu)
{
  int val = cpu->registers[mem[cpu->pc].p.two] ^ cpu->registers[mem[cpu->pc].p.one];

  cpu->OF = 0;

  if(val == 0)
    cpu->ZF = 1;
  else
    cpu->ZF = 0;

  if(val < 0)
    cpu->SF = 1;
  else
    cpu->SF = 0;
}

void mull(cpu *cpu)
{
	int rA = cpu->registers[mem[cpu->pc].p.two];
  int rB = cpu->registers[mem[cpu->pc].p.one];

  if(rA > 0 && rB > 0 && rA * rB < 0)
    cpu->OF = 1;
  else if(rA < 0 && rB < 0 && rA * rB < 0)
    cpu->OF = 1;
  else if(rA > 0 && rB < 0 && rA * rB > 0)
    cpu->OF = 1;
  else if(rA < 0 && rB > 0 && rA * rB > 0)
    cpu->OF = 1;
  else
    cpu->OF = 0;

  cpu->registers[mem[cpu->pc].p.one] = rB * rA;

  if(cpu->registers[mem[cpu->pc].p.one] == 0)
    cpu->ZF = 1;
  else
    cpu->ZF = 0;

  if(cpu->registers[mem[cpu->pc].p.one] < 0)
    cpu->SF = 1;
  else
    cpu->SF = 0;
}

void cmpl(cpu *cpu)
{
  int rA = cpu->registers[mem[cpu->pc].p.two];
  int rB = cpu->registers[mem[cpu->pc].p.one];

  cpu->OF = 0;

  int res =  rB - rA;

  if(res == 0)
    cpu->ZF = 1;
  else
    cpu->ZF = 0;

  if(res < 0)
    cpu->SF = 1;
  else
    cpu->SF = 0;
}

void opl(cpu *cpu)
{
  int op = mem[cpu->pc].p.one;
  inc(1, cpu);

  switch(op)
	{
    case 0:	addl(cpu);
      			break;

    case 1:	subl(cpu);
      			break;

    case 2:	andl(cpu);
       		  break;

    case 3:	xorl(cpu);
      			break;

    case 4:	mull(cpu);
      			break;

    case 5: cmpl(cpu);
      			break;

    default: fprintf(stderr, "ERROR!\n");
      			exit(0);
  }

  inc(1, cpu);
}


void jmp(cpu *cpu)
{
  long_p val;

  val.ch.b1 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b2 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b3 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b4 = mem[cpu->pc].bc;

  if(val.int_p >= cpu->cpu_size || val.int_p < 0)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  cpu->pc = val.int_p;
}

void jmp_cond(cpu *cpu)
{
  int op = mem[cpu->pc].p.one;
  inc(1, cpu);

  switch(op)
	{
    case 0: jmp(cpu);
      			break;

    case 1: if((cpu->SF ^ cpu->OF) == 1 || cpu->ZF == 1)
        			jmp(cpu);
      			else
        			inc(4, cpu);
      			break;

    case 2: if((cpu->SF ^ cpu->OF) == 1)
        			jmp(cpu);
      			else
        			inc(4, cpu);
      			break;

    case 3:	if(cpu->ZF == 1)
        			jmp(cpu);
      			else
        			inc(4, cpu);
      			break;

    case 4:	if(cpu->ZF == 0)
        			jmp(cpu);
      			else
        			inc(4, cpu);
      			break;

    case 5:	if((cpu->SF ^ cpu->OF) == 0)
        			jmp(cpu);
      			else
        			inc(4, cpu);
      			break;

    case 6:	if((cpu->SF ^ cpu->OF) == 0 && cpu->ZF == 0)
        			jmp(cpu);
      			else
        			inc(4, cpu);
      			break;

    default: fprintf(stderr, "ERROR!\n");
      			 exit(0);
  }

}

void call(cpu *cpu)
{
  if(mem[cpu->pc].p.one != 0)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  inc(1, cpu);


  long_p val;

  val.ch.b1 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b2 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b3 = mem[cpu->pc].bc;
  inc(1, cpu);
  val.ch.b4 = mem[cpu->pc].bc;
  inc(1, cpu);


  long_p num;
  num.int_p = cpu->pc;

  if(cpu->registers[4] - 4 <= 0)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  mem[cpu->registers[4] - 4].bc = num.ch.b1;
  mem[cpu->registers[4] - 3].bc = num.ch.b2;
  mem[cpu->registers[4] - 2].bc = num.ch.b3;
  mem[cpu->registers[4] - 1].bc = num.ch.b4;

  cpu->registers[4] -= 4;


  if(val.int_p < 0 || val.int_p >= cpu->cpu_size)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  cpu->pc = val.int_p;
}

void ret(cpu *cpu)
{
  if(mem[cpu->pc].p.one != 0)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  if(cpu->registers[4] + 3 >= cpu->cpu_size)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  long_p num;

  num.ch.b4 = mem[cpu->registers[4] + 3].bc;
  num.ch.b3 = mem[cpu->registers[4] + 2].bc;
  num.ch.b2 = mem[cpu->registers[4] + 1].bc;
  num.ch.b1 = mem[cpu->registers[4]].bc;

  if(num.int_p < 0 || num.int_p >= cpu->cpu_size)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  cpu->registers[4] += 4;

  cpu->pc = num.int_p;
}

void pushl(cpu *cpu)
{
  if(mem[cpu->pc].p.one != 0)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  inc(1, cpu);
  reg(mem[cpu->pc].p.two);

  if(mem[cpu->pc].p.one != 15)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  if(cpu->registers[4] - 4 <= 0)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  long_p num;
  num.int_p = cpu->registers[mem[cpu->pc].p.two];

  mem[cpu->registers[4] - 4].bc = num.ch.b1;
  mem[cpu->registers[4] - 3].bc = num.ch.b2;
  mem[cpu->registers[4] - 2].bc = num.ch.b3;
  mem[cpu->registers[4] - 1].bc = num.ch.b4;

  cpu->registers[4] -= 4;

  inc(1, cpu);
}

void popl(cpu *cpu)
{
  if(mem[cpu->pc].p.one != 0)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  inc(1, cpu);
  reg(mem[cpu->pc].p.two);

  if(mem[cpu->pc].p.one != 15)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  if(cpu->registers[4] + 3 >= cpu->cpu_size)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  long_p num;

  num.ch.b1 = mem[cpu->registers[4]].bc;
  num.ch.b2 = mem[cpu->registers[4] + 1].bc;
  num.ch.b3 = mem[cpu->registers[4] + 2].bc;
  num.ch.b4 = mem[cpu->registers[4] + 3].bc;

  cpu->registers[4] += 4;

  cpu->registers[mem[cpu->pc].p.two] = num.int_p;
  inc(1, cpu);
}

void readX(cpu *cpu)
{
  int op = mem[cpu->pc].p.one;

  if(op < 0 || op > 1)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  inc(1, cpu);

  if(mem[cpu->pc].p.one != 15)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  reg(mem[cpu->pc].p.two);
  int val = cpu->registers[mem[cpu->pc].p.two];

  long_p result;

  inc(1, cpu);
  result.ch.b1 = mem[cpu->pc].bc;
  inc(1, cpu);
  result.ch.b2 = mem[cpu->pc].bc;
  inc(1, cpu);
  result.ch.b3 = mem[cpu->pc].bc;
  inc(1, cpu);
  result.ch.b4 = mem[cpu->pc].bc;
  inc(1, cpu);

  val += result.int_p;

  if(val < 0 || val >= cpu->cpu_size){
    fprintf(stderr, "ERROR: ADR - Segmentation Fault for val %i in readX. cpu->pc: %i\n", val, cpu->pc);
    exit(0);
  }

  if(op == 0)
	{
    mem[val].bc = getchar();

    if(mem[val].bc == -1)
      cpu->ZF = 1;
    else
      cpu->ZF = 0;

  }
	else
	{
    if(val + 4 < 0 || val + 4 >= cpu->cpu_size)
		{
      fprintf(stderr, "ERROR!\n");
      exit(0);
    }

    if(EOF == scanf("%d", &result.int_p))
      cpu->ZF = 1;
    else
      cpu->ZF = 0;

    mem[val + 3].bc = result.ch.b4;
    mem[val + 2].bc = result.ch.b3;
    mem[val + 1].bc = result.ch.b2;
    mem[val].bc = result.ch.b1;
  }
}

void writeX(cpu *cpu)
{
  int op = mem[cpu->pc].p.one;

  if(op < 0 || op > 1)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  inc(1, cpu);

  if(mem[cpu->pc].p.one != 15)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  reg(mem[cpu->pc].p.two);
  int val = cpu->registers[mem[cpu->pc].p.two];

  long_p result;

  inc(1, cpu);
  result.ch.b1 = mem[cpu->pc].bc;
  inc(1, cpu);
  result.ch.b2 = mem[cpu->pc].bc;
  inc(1, cpu);
  result.ch.b3 = mem[cpu->pc].bc;
  inc(1, cpu);
  result.ch.b4 = mem[cpu->pc].bc;
  inc(1, cpu);

  val += result.int_p;

  if(val < 0 || val >= cpu->cpu_size)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  if(op == 0){
    printf("%c", mem[val].bc);

  }
	else
	{
    if(val + 4 < 0 || val + 4 >= cpu->cpu_size)
		{
      fprintf(stderr, "ERROR!\n");
      exit(0);
    }

    result.ch.b4 = mem[val + 3].bc;
    result.ch.b3 = mem[val + 2].bc;
    result.ch.b2 = mem[val + 1].bc;
    result.ch.b1 = mem[val].bc;

    printf("%d", result.int_p);
  }
}

void movsbl(cpu *cpu)
{
  if(mem[cpu->pc].p.one != 0)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  inc(1, cpu);

  reg(mem[cpu->pc].p.two);
  reg(mem[cpu->pc].p.one);

  int num = mem[cpu->pc].p.two;
  int val = cpu->registers[mem[cpu->pc].p.one];

  long_p result;

  inc(1, cpu);
  result.ch.b1 = mem[cpu->pc].bc;
  inc(1, cpu);
  result.ch.b2 = mem[cpu->pc].bc;
  inc(1, cpu);
  result.ch.b3 = mem[cpu->pc].bc;
  inc(1, cpu);
  result.ch.b4 = mem[cpu->pc].bc;
  inc(1, cpu);

  val += result.int_p;

  if(val < 0 || val >= cpu->cpu_size)
	{
    fprintf(stderr, "ERROR!\n");
    exit(0);
  }

  if(mem[val].p.two >= 8)
	{
    result.int_p = -1;
    result.ch.b1 = mem[val].bc;

  }
	else
	{
    result.int_p = 0;
    result.ch.b1 = mem[val].bc;
  }

  cpu->registers[num] = result.int_p;
}

int process_execute( char * file)
{
	//processing
	long size = 0;
	char * token = 0;
	char * hex;
	long addr;
	char * arg;
	char * temp;
	long_p var;
	int val;

  cpu* cpu;

	char * dup_str = strdup(file);
	token = strtok(dup_str, "\t\n");

	while(token != NULL)
	{
		if(strcmp(token, ".size") == 0)
		{
			token = strtok(NULL, "\t\n");
			if(debug)
			{
				printf("size in hex: %s\n", token);
			}
			size = (int) strtol(token, NULL, 16);
			if(debug)
			{
				printf("size in decimal: %ld\n", size);
			}
			mem = malloc(size*sizeof(byte));
			if(debug)
			{
				printf("Memory allocated\n");
			}
		}//if .size
		else
		{
			token = strtok(NULL, "\t\n");
		}
	} //while

	free(dup_str);
	if(debug)
	{
		printf("Duplicated string again\n");
	}

	cpu = malloc(sizeof(*cpu));
	if(debug)
	{
		printf("Memory allocated to cpu\n");
	}

	cpu->pc = -1;
	if(debug)
	{
		printf("Program counter is -1\n");
	}

	cpu->cpu_size = size;
	if(debug)
	{
		printf("cpu size: %d\n", cpu->cpu_size);
	}

	int i;
	for(i = 0; i < 8; i++)
	{
		cpu->registers[i] = 0;
	}

	dup_str = strdup(file);
	token = strtok(dup_str, "\t\n");
	if(debug)
	{
		printf("reduplicated and retokanized\n");
	}

	while(token != NULL)
	{
		if (debug)
		{
			printf("token: %s\n", token);
		}

		if(strcmp(token, ".size") == 0)
		{
			token = strtok(NULL, "\t\n");
			if(debug)
			{
				printf("token: %s\n", token);
			}
			if (debug)
			{
				printf("Skipped .size\n");
			}
		}//if .size
		else if(strcmp(token, ".string") == 0)
		{
			if(debug)
			{
				printf("In .string \n");
			}
			token = strtok(NULL, "\t\n");
			hex = token;
			addr = hex_to_decimal(hex);
			if(debug)
			{
				printf("hex: %s, decimal: %ld\n", hex, addr);
			}
			arg = strtok(NULL, "\t\n");
			temp = arg + 1;

			while(*temp != '\0')
			{
				addr = check_pt(addr, cpu);
				mem[addr].bc = *temp;
				temp++;
				addr++;
			}
		}//if .string
		else if(strcmp(token, ".long") == 0)
		{
			if(debug)
			{
				printf("In .long \n");
			}
			token = strtok(NULL, "\t\n");
			hex = token;
			addr = hex_to_decimal(hex);
			if(debug)
			{
				printf("hex: %s, decimal: %ld\n", hex, addr);
			}
			arg = strtok(NULL, "\t\n");
			var.int_p = (int) strtol(arg, NULL, 16);

			mem[check_pt(addr, cpu)].bc = var.ch.b1;
			mem[check_pt(addr, cpu) + 1].bc = var.ch.b2;
			mem[check_pt(addr, cpu) + 2].bc = var.ch.b3;
			mem[check_pt(addr, cpu) + 3].bc = var.ch.b4;
		}//if .long
		else if(strcmp(token, ".byte") == 0)
		{
			if(debug)
			{
				printf("In .byte\n");
			}
			token = strtok(NULL, "\t\n");
			hex = token;
			addr = hex_to_decimal(hex);
			if(debug)
			{
				printf("hex: %s, decimal: %ld\n", hex, addr);
			}
			arg = strtok(NULL, "\t\n");

			val = (int) strtol(arg, NULL, 16);
			if(debug)
			{
				printf("value: %d\n", val);
			}
			mem[check_pt(addr, cpu)].bc = (char) val;
		}//if .byte
		else if(strcmp(token, ".text") == 0)
		{
			if(debug)
			{
				printf("In .text\n");
			}
			token = strtok(NULL, "\t\n");
			hex = token;
			addr = hex_to_decimal(hex);
			if(debug)
			{
				printf("hex: %s, decimal: %ld\n", hex, addr);
			}

			cpu->pc = (int)addr;
			if(debug)
			{
				printf("program counter: %d\n", cpu->pc);
			}
			arg = strtok(NULL, "\t\n");
			temp = arg;

			while(*temp != '\0' && isspace(*temp) == 0)
			{
				addr = check_pt(addr, cpu);
				mem[addr].p.two = convert_char(*temp);
				temp++;
				if(*temp!= '\0' && isspace(*temp) == 0)
				{
					mem[addr].p.one = convert_char(*temp);
					temp++;
				}
				addr++;
			}
		}//if .text
		token = strtok(NULL, "\t\n");
	} //while

//end processing
//start executing

	int execute = 0;

	while(execute != -1)
	{
		execute = mem[cpu->pc].p.two;

		switch (execute)
		{
			case 0:	inc(1, cpu);
							break;

			case 1:	execute = -1;
							break;

			case 2:	rrmovl(cpu);
							break;

			case 3:	irmovl(cpu);
							break;

			case 4:	rmmovl(cpu);
							break;

			case 5:	mrmovl(cpu);
							break;

			case 6:	opl(cpu);
							break;

			case 7:	jmp_cond(cpu);
							break;

			case 8:	call(cpu);
							break;

			case 9:	ret(cpu);
							break;

			case 10: pushl(cpu);
							 break;

			case 11: popl(cpu);
							 break;

			case 12: readX(cpu);
							 break;

			case 13: writeX(cpu);
							 break;

			case 14: movsbl(cpu);
							 break;

			default: fprintf(stderr, "%s\n", "ERROR: Invalid command.");
							 exit(0);
		}//switch
	}//end while execute

	free(mem);
  return 0;
} // end process_execute

int main(int argc, char *argv[])
{
//  int i = 0;
  char *arg = 0;
  char *file = 0;

  if(argc != 2)
  {
    fprintf(stderr, "%s\n", "ERROR: Invalid number of arguments");
    exit(0);
  }

  if (argv[1][0] == '-' && argv[1][1] == 'h')
  {
  		printf("Usage: y86emul <y86 input file>\n");
      exit(0);
  }

	char* input = strstr(argv[1], ".y86");
	if(input == NULL || strlen(input) != 4 || strlen(argv[1]) < 5)
	{
		fprintf(stderr, "%s\n", "ERROR: Incorrect file name");
		exit(0);
	}

  arg = argv[1];
  file = read_file(arg);
  process_execute(file);

  return 0;
} //end main
