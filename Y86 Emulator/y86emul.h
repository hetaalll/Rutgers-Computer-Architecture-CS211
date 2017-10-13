#ifndef y86emul_h
#define y86emul_h


int convert_char(char );
char * read_file(char*);
int process_execute(char*);
int* hexa_to_binary(char*);
long binary_to_decimal(int*);
long hex_to_decimal(char*);
long power(int x, int y);
int convert_char(char c);
char * strdup(char*);


#endif
