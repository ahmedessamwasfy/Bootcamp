#ifndef bitwiseOperation_h
#define bitwiseOperation_h

#define Set_Bit(Reg,Bit)    (Reg |= (1<<Bit) )
#define Clear_Bit(Reg,Bit)  (Reg &=~ (1<<Bit) )
#define toggle_bit(Reg,Bit)    Reg ^= (1<<Bit)
#define get_bit(Reg,Bit )   ((Reg>>Bit) & (1))
#define BIT_IS_SET(Reg,Bit)  ((Reg>>Bit) & (1))
#define BIT_IS_CLEAR(Reg,Bit)  (!((Reg>>Bit) & (1)))

#endif 

