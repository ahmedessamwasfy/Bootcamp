/*
 * dio_config.h
 *
 * Created: 2/22/2019 5:00:14 PM
 *  Author: AVE-LAP-44
 */ 


#ifndef DIO_CONFIG_H_
#define DIO_CONFIG_H_


#define PORT0_START          PORTB_START   
#define PORT0_END            PORTB_END

#define GPIO_PORT0_OUTPUT    PORTB
#define GPIO_PORT0_DIR       DDRB
#define GPIO_PORT0_INPUT     PINB

#define PORT1_START          PORTC_START
#define PORT1_END            PORTC_END

#define GPIO_PORT1_OUTPUT    PORTC
#define GPIO_PORT1_DIR       DDRC
#define GPIO_PORT1_INPUT     PINC

#define PORT2_START         PORTD_START
#define PORT2_END           PORTD_END

#define GPIO_PORT2_OUTPUT   PORTD
#define GPIO_PORT2_DIR      DDRD
#define GPIO_PORT2_INPUT    PIND

#define PORT3_START          PORTA_START
#define PORT3_END            PORTA_END

#define GPIO_PORT3_OUTPUT    PORTA	
#define GPIO_PORT3_DIR       DDRA
#define GPIO_PORT3_INPUT     PINA






#endif /* DIO_CONFIG_H_ */