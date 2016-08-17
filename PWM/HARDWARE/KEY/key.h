# ifndef __KEY_H
# define __KEY_H
# include "sys.h"
# define KEY0 PEin(4)//	  I/O¿Ú Î»²Ù×÷
# define KEY1 PEin(3)//
# define KEY2 PEin(2)//
# define KEY3 PAin(0)//
# define KEY_UP 4
# define KEY_LEFT 3
# define KEY_DOWN 2
# define KEY_RIGHT 1
void KEY_Init(void);
u8 KEY_Scan(u8);
# endif
