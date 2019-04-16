

#ifndef LED_H_
#define LED_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

void LED_INIT(void);
void TOG_LED1(void);
void TOG_LED2(void);



#endif /* LED_H_ */
