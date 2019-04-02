
#ifndef ATMEGA32_H_
#define ATMEGA32_H_
#define F_CPU 16000000UL
/* GPIO */
#define PORTA_START   0
#define PORTA_END     7  

#define PORTB_START   8
#define PORTB_END     15

#define PORTC_START   16
#define PORTC_END     23

#define PORTD_START   24
#define PORTD_END     31

#define PORTA (*((volatile uint8*)0x3B)) // address of portA (output)
#define DDRA  (*((volatile uint8*)0x3A))//address of ddrA (direction)
#define PINA  (*((volatile uint8*)0x39))//address of pinA	(input)

#define PORTB (*((volatile uint8*)0x38))// address of portB
#define DDRB  (*((volatile uint8*)0x37))//address of ddrB
#define PINB  (*((volatile uint8*)0x36))//address of pinB

#define PORTC (*((volatile uint8*)0x35))// address of portC
#define DDRC  (*((volatile uint8*)0x34))//address of ddrC
#define PINC  (*((volatile uint8*)0x33))//address of pinC

#define PORTD (*((volatile uint8*)0x32))// address of portD
#define DDRD  (*((volatile uint8*)0x31))//address of ddrD
#define PIND  (*((volatile uint8*)0x30))//address of pinD

	


#define TCCR0 (*((volatile uint8*) 0x53))
#define CS00      BIT0
#define CS01      BIT1
#define CS02      BIT2
#define WGM01     BIT3
#define COM00     BIT4
#define COM01     BIT5
#define WGM00     BIT6
#define FOC0      BIT7

#define TIMSK      (*((volatile uint8*)  0x59))
#define TOIE0      BIT0
#define OCIE0      BIT1
#define TOIE1      BIT2
#define OCIE1B     BIT3
#define OCIE1A     BIT4
#define TICIE1     BIT5
#define TOIE2      BIT6
#define OCIE2      BIT7




#define TIFR  (*((volatile uint8*)  0x58))
#define TOV0      BIT0
#define OCF0      BIT1
#define TOV1      BIT2
#define OCF1B     BIT3
#define OCF1A     BIT4
#define ICF1      BIT5
#define TOV2      BIT6
#define OCF2      BIT7

#define TCNT0 (*((volatile uint8*)  0x52))

#define OCR0  (*((volatile uint8*) 0x5C))



#define TCCR1A (*((volatile uint8*) 0x4F))   /*$2F ($4F) TCCR1A COM1A1 COM1A0 COM1B1 COM1B0 FOC1A FOC1B WGM11 WGM10 107 */
#define TCCR1B (*((volatile uint8*) 0x4E))   /*$2E ($4E) TCCR1B ICNC1 ICES1 – WGM13 WGM12 CS12 CS11 CS10 110 */
#define TCNT1H (*((volatile uint8*) 0x4D))   /*$2D ($4D) TCNT1H Timer/Counter1 – Counter Register High Byte 111 */
#define TCNT1L (*((volatile uint8*) 0x4C))   /*$2C ($4C) TCNT1L Timer/Counter1 – Counter Register Low Byte 111 */
#define OCR1AH (*((volatile uint8*) 0x4B))   /*$2B ($4B) OCR1AH Timer/Counter1 – Output Compare Register A High Byte 111 */
#define OCR1AL (*((volatile uint8*) 0x4A))   /*$2A ($4A) OCR1AL Timer/Counter1 – Output Compare Register A Low Byte 111 */
#define OCR1BH (*((volatile uint8*) 0x49))   /*$29 ($49) OCR1BH Timer/Counter1 – Output Compare Register B High Byte 111 */
#define OCR1BL (*((volatile uint8*) 0x48))   /*$28 ($48) OCR1BL Timer/Counter1 – Output Compare Register B Low Byte 111 */
#define ICR1H  (*((volatile uint8*) 0x47))   /*$27 ($47) ICR1H Timer/Counter1 – Input Capture Register High Byte 111 */
#define ICR1L  (*((volatile uint8*) 0x46))   /*$26 ($46) ICR1L Timer/Counter1 – Input Capture Register Low Byte 111*/
#define WGM10      BIT0
#define WGM11      BIT1
#define FOC1B      BIT2
#define FOC1A      BIT3
#define COM1B0     BIT4
#define COM1B1     BIT5
#define COM1A0     BIT6
#define COM1A1     BIT7

#define CS10       BIT0
#define CS11       BIT1
#define CS12       BIT2
#define WGM12      BIT3
#define WGM13      BIT4

#define ICES1      BIT6
#define ICNC1      BIT7


#define UCSRA (*((volatile uint8*) 0x2B)) 

#define  MPCM          BIT0  
#define  U2X           BIT1   
#define  PE            BIT2  
#define  DOR           BIT3   
#define  FE            BIT4  
#define  UDRE          BIT5  
#define  TXC           BIT6  
#define  RXC           BIT7   


#define  UCSRB   (*((volatile uint8*) 0x2A))
#define  TXB8          BIT0   /* Bit 0 – TXB8: Transmit Data Bit 8 */
#define  RXB8          BIT1   /* Bit 1 – RXB8: Receive Data Bit 8 */
#define  UCSZ2         BIT2   /* Bit 2 – UCSZ2: Character Size */
#define  TXEN          BIT3   /* Bit 3 – TXEN: Transmitter Enable */
#define  RXEN          BIT4   /* Bit 4 – RXEN: Receiver Enable */
#define  UDRIE         BIT5   /* Bit 5 – UDRIE: USART Data Register Empty Interrupt Enable */
#define  TXCIE         BIT6   /* Bit 6 – TXCIE: TX Complete Interrupt Enable */
#define  RXCIE         BIT7   /* Bit 7 – RXCIE: RX Complete Interrupt Enable */


#define   UCSRC   (*((volatile uint8*) 0x40))
#define   UBRRH   (*((volatile uint8*) 0x40))

#define  UCPOL          BIT0
#define  UCSZ0          BIT1
#define  UCSZ1          BIT2
#define  USBS           BIT3
#define  UPM0           BIT4
#define  UPM1           BIT5    
#define  UMSEL          BIT6    
#define  URSEL          BIT7    


#define UBRRL   (*((volatile uint8*) 0x29))


#define UDR (*((volatile uint8*) 0x2C))
#define TCCR2 (*((volatile uint8*) 0x45))
#define CS20      BIT0
#define CS21      BIT1
#define CS22      BIT2
#define WGM21     BIT3
#define COM20     BIT4
#define COM21     BIT5
#define WGM20     BIT6
#define FOC2      BIT7
#define TCNT2 (*((volatile uint8*)  0x44))
#define OCR2  (*((volatile uint8*) 0x43))
#define SPCR (*((volatile uint8*)  0x2D))
#define SPR0      BIT0
#define SPR1      BIT1
#define CPHA      BIT2
#define CPOL      BIT3
#define MSTR      BIT4
#define DORD      BIT5
#define SPE       BIT6
#define SPIE      BIT7
#define SPDR (*((volatile uint8*)  0x2F))
#define SPSR (*((volatile uint8*)  0x2E))
#define SPI2X BIT0
#define WCOL  BIT6
#define SPIF  BIT7
#endif 