
#include <stdint.h>
#include "Manager.h"
#include "includes/Types.h"
#include "includes/uart.h"

uint8 Get_Distance()
{
    uint8 Distance=0;
    uint8 Duty=UART_Reseive();
 Distance = (2.55535 * Duty);
 return Distance;
}
