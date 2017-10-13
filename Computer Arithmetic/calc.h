#ifndef calc_h
#define calc_h

void op(char*, char*);
char* first_number(char* , bool* , char* , int*);
char* second_number(char* , bool* , char* , int*);
int parse_int(char*);
int* binaryASCII_to_int(char* number);
int* decimal_to_binary(int);
int* octal_to_binary(char*);
int* hexa_to_binary(char*);
int* addition(int*, int*);
int* subtraction(int*, int*);
int power(int, int);
int binary_to_decimal(int*);
char*  binary_to_octal(int*);
char* binary_to_hexa(int*);
int* fliping_bits(int*);


#endif
