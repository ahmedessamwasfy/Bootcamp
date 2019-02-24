#include "../includes/schadular.h"

void prefield(void (*ptr[])(void),uint8 size )
{
	uint8 i ;
	for(i=0 ; i<3;i++)
	{
		ptr[i]();
		_delay_ms(2000);
	}
}