#include	<stdio.h>
#include	<string.h>
#include  <stdlib.h>
#include  <math.h>
#include  "format.h"

unsigned int size = 32;

union Number {
	int	i;
	float	f;
};

int main(int argc, char *argv[])
{

	char* input;
	char* type;
	int i, j;
	int result_i;
	char* output = malloc(size*sizeof(char));

	for(j = 0; j < size; j++)
	{
		output[j] = '\0';
	}


  //ERROR CHECK
 if(argc < 3 || argc > 3)
 {
	 fprintf(stderr, "%s\n", "ERROR: Invalid number of arguments");
	 exit(0);
 }

 		//DEBUG
	/*for(j = 0; j < argc; j++)
	{
		printf("Arguments in argv[%d] is %s\n", j, argv[j] );
	}*/

 		//ERROR CHECK FOR 32 BITS

	for(i = 0; i < argc; i++)
	{

		switch(i)
		{
			case 0 : break;

			case 1 : input = argv[i];
							 if(strlen(input) != 32)
							 {
								 fprintf(stderr, "%s\n", "ERROR: Invalid number of bits");
							 }
							 //printf("%s%s\n", "input: ", input);
							 break;

			case 2 : type = argv[i];
							 //printf("%s%s\n", "type: " , type);
							 break;

			default : fprintf(stderr, "%s\n", "ERROR: Invalid number of arguments.");

		}//switch
	} // for loop


		//CONVERTING TO INT
	if(strcmp(type, "int") == 0)
	{
		result_i = binary_to_int(1, input);
		//printf("\n%s%d\n", "After converting to int, result: ", result_i);
		if(result_i < 0)
		{
			append(output, '-');
			result_i *= -1; //number becomes positive
		}
		int_to_ASCII(result_i, output);
		printf("\n%s\n", output );
	}

		//CONVERTING TO FLOAT
	if(strcmp(type, "float") == 0)
	{
		union Number n;
		n.i = 0;
		j = 0;

		char * ch = argv[1];
    while(*ch != '\0'){
      n.i = n.i << 1;
      n.i += *ch - '0';
      ch++;
    }
    floatToASCII(n.f, output);
    if(n.f == -0.0 && input[0] == '1'){
      printf("\n-%s\n", output);
    }
    else{
      printf("\n%s\n", output);
    }

	}

  return 0;
} // end main


static void
append( char * s, char c )
{
	char		buf[2];

	buf[0] = c;
	buf[1] = '\0';
	strcat( s, buf );
}


void intToDecASCII(int i, char* output)
{
		char* str;
		char sign = '+';
		int j, num = 0, length = 12, negative;

		char tmp[length];

		for(j = 0; j < (length-2); j++)
		{
			tmp[j] = '0';
		}
			tmp[length-1] = '\0';

		if(i < 0)
		{
			negative = 1; //number is negative
		}
		else
		{
			negative = 0; //number is positive
		}

		switch(negative)
		{
			case 0 : sign = '+';
							 i = i*1;
							 break;

			case 1 : sign = '-';
							 i = i*-1;
							 break;
		}

		num = length-2;
		//printf("%s%d\n", "num: " ,num);
		while(num>=0)
		{
			tmp[num] = (i % 10) + '0';
			i = i/10;
			if(i==0)
			{
				break;
			}
			num--;
		}

		if(sign == '-')
		{
			num--;
			tmp[num] = '-';
		}

		str = output;
		while(num<12)
		{
			*str = tmp[num];
			str++;
			num++;
		}
		//printf("%s%s\n", "arr tmp: ", tmp);
		//printf("output = %s\n",output);

} // end intToDecASCII


void int_to_ASCII(int num, char* output)
{
	char result = '0';

	if(num!=0)
	{
		//printf("DecASCII: output: %s, num: %d, result: %c\n", output, num, result);
			result = ((num%10)+'0');
			int_to_ASCII((num/10),output);
			append(output, result);
	}
	else
	{
		return;
	}

} //end int_to_ASCII



int binary_to_int(int num, char* output)
{

	int j, flip;
	int result = 0;

	if(output[0] == '1' && num == 1)
	{
		output = fliping_bits(output);
		flip = 1;
	}

	for(j = (strlen(output)-1); j > 0; j--)
	{
		if(output[j]=='1')
		{
			result +=pow(2,((strlen(output)-j-1)));
		}
	}

	if(flip == 1)
	{
		result += 1;
		result *=-1;
	}
	//printf("\n%s%d\n","result in function binary_to_int: ", result );
	return result;
} //end binary_to_int


char* fliping_bits(char* num)
{
	int i;

	for(i = 1; i < strlen(num); i++)
	{
		if(num[i] == '1')
		{
			num[i] = '0';
		}
		else if(num[i] == '0')
		{
			num[i] = '1';
		}
	}

	return num;
} // end fliping_bits


static void
get_float_digit( float x, char * digit, int * pow10, float * remainder )
{
	int			p10;

	if ( x == 0.0 )
	{
		*digit = '0';			// digit is always '0'
		*pow10 = 0;
		*remainder = 0.0;
	}
	else
	{
		*pow10 = 0;			// start with 10^0
		while ( x >= 10.0 )		// reduce
		{
			x /= 10.0;		// large values get smaller
			*pow10 += 1;
		}
		while ( x < 1.0 )		// increase
		{
			x *= 10.0;		// small values get larger
			*pow10 -= 1;
		}
		*digit = '0';
		do {				// 10.0 > x >= 1.0
			x -= 1.0;
			*digit += 1;		// digit is always non-'0'zero
		} while ( x >= 1.0 );
		p10 = 0;
		while ( p10 > *pow10 )		// leading digit is now removed from x
		{
			x /= 10;
			p10 -= 1;
		}
		while ( p10 < *pow10 )
		{
			x *= 10;
			p10 += 1;
		}
		*remainder = x;
	}
}

void
floatToASCII( float x, char * output )
{
	char		c;
	int		pow10, p10, plast;
	int		i;
	float		remainder;
	char		exponent[10];
	union Number	a;
	unsigned int	biasedExp;
	unsigned int	mantissa;
	int		sign;

	a.f = x;
	biasedExp = a.i >> 23 & 0x000000ff;
	mantissa = a.i & 0x007fffff;
	sign = a.i >> 31;

	// +/- inf, +/- Nan stuff here
	if(biasedExp == 0xff)
	{
		if(mantissa == 0)
		{
			if(sign == 0)
			{
				strcpy(output, "pinf");
				return;
			}
			else
			{
				strcpy(output, "ninf");
				return;
			}
		}//mantissa
		else
		{
			strcpy(output, "NaN");
			return;
		}
	}//biasedExp

	output[0] ='\0';
	if ( x < 0.0 )
	{
		append( output, '-' );
		x = -x;					// make x positive
	}
	get_float_digit( x, &c, &pow10, &remainder );
	append( output, c );
	append( output, '.' );
	x = remainder;
	plast = p10 = pow10;			// pow10 set by get_float_digit()
	for ( i = 1 ; i < 7 ; i++ )		// 7 significant digits in 32-bit float
	{
		get_float_digit( x, &c, &p10, &remainder );
		if ( (plast - p10) > 1 )
		{
			append( output, '0' );	// fill in zero to next nonzero digit
			plast -= 1;
		}
		else
		{
			append( output, c );
			x = remainder;
			plast = p10;
		}
	}
	if ( pow10 < 0 )		// negative exponent
	{
		exponent[0] = 'e';
		intToDecASCII( pow10, exponent+1 );
	}
	else if ( pow10 < 10 )		// positive single-digit exponent
	{
		exponent[0] = 'e';
		exponent[1] = '+';
		exponent[2] = '0';
		intToDecASCII( pow10, exponent+3 );
	}
	else				// positive multi-digit exponent
	{
		exponent[0] = 'e';
		exponent[1] = '+';
		intToDecASCII( pow10, exponent+2 );
	}
	strcat( output, exponent );
}
