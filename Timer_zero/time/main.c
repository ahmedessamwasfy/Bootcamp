/*
 * AUTHOR: Ahmed Nofal, Avelabs Embedded R&D software team
 */
#include <stdio.h>
/* Complete the function below to detect the endianness of the machine*/
void Detect_Endianness(void){
	  unsigned int x = 0x66449900;
	  char *c = (char*) &x;

	  printf ("*c is: 0x%x\n", *c);
	  if (*c == 0x00)
	  {
	    printf (" little endian. \n");
	  }
	  else
	  {
	     printf (" big endian. \n");
	  }

	  return 0;
}

int main(void){
	Detect_Endianness();
}
