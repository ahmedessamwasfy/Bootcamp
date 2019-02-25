
#include "includes/_TIMER_.h"
#include <util/delay.h>

int main(void)
{
  pwm1_init();

while (1)
	{
		  uint8 i ;
		  for(i=0 ; i<100 ;i+=10)
		  {
			  SELECT_DUTY(i);
			  _delay_ms(3000);
		  }
		  if(i >= 100)
		  i = 0 ;
	}
	
}








