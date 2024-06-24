/*
 * Safe.c
 *
 * Created: 11/04/2024 03:56:25 ص
 *  Author: FREINDS
 */ 

#define F_CPU 8000000UL
#include<util/delay.h>
#include <avr/io.h>
#include"EEPROM_DRIVER.h"
#include"LCD.h"
#include"keypad_driver.h"

#define password_location0 0x0000
#define password_location1 0x0001
#define password_location2 0x0002
#define password_location3 0x0003
#define password_location4 0x0004
#define password_location5 0x0005
#define password_set_location 0x0006
#define TRIES 3
char value[6] = {NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED,NOTPRESSED};
unsigned char counter = 0;
unsigned char triesl = TRIES;
unsigned char flag = 1;
int main(void)
{
	LCD_vInit();
	keypad_vInit();
	
    while(1)
    {
		if(EEPROM_read(password_set_location) == 0xFF)
		{
			LCD_vSend_string("Set Password:");
			LCD_movecursor(2,1);
			for(counter = 0;counter<6;counter++)
			{
				do{
					value[counter] = keypad_u8check_press();
				}while(value[counter] == NOTPRESSED);
				_delay_ms(300);
				EEPROM_write(password_location0+counter,value[counter]);
				LCD_vSend_char(value[counter]);
				_delay_ms(300);
				LCD_movecursor(2,1+counter);
				LCD_vSend_char('*');
				
			}	
					
			EEPROM_write(password_set_location,0x00);
			LCD_clearscreen();
		}
		else if(0x00 == EEPROM_read(password_set_location))
		{
			if(1 == flag)
			{
				LCD_vSend_string("Enter Password:");
				LCD_movecursor(2,1);
				flag = 0;
				
			}
			
			for(counter = 0;counter<6;counter++)
			{
				do{
					value[counter] = keypad_u8check_press();
				}while(NOTPRESSED == value[counter]);
				_delay_ms(300);
				LCD_vSend_char(value[counter]);
				_delay_ms(100);
				LCD_movecursor(2,counter+1);
				LCD_vSend_char('*');
				if(EEPROM_read(password_location0 + counter) != value[counter])
				{
					value[0] = NOTPRESSED;
				}
				
			}
			LCD_clearscreen();
			if(NOTPRESSED == value[0])
			{
				LCD_movecursor(1,2);
				LCD_vSend_string("Wrong Password");
				_delay_ms(1000);
				triesl--;
				if(triesl > 0)
				{
					
					LCD_clearscreen();
					LCD_movecursor(1,3);
					LCD_vSend_string("Tries Left:");
					LCD_vSend_char(triesl+48);
					LCD_movecursor(2,4);
					LCD_vSend_string("Try Again");
					_delay_ms(1000);
					LCD_clearscreen();
					LCD_vSend_string("Enter Password:");
					LCD_movecursor(2,1);
				}
				
			}
			else
			{
				LCD_movecursor(1,5);
				LCD_vSend_string("Well done!");
				_delay_ms(1000);
				LCD_movecursor(2,3);
				LCD_vSend_string("Safe Opened");
				break;
			}
			
		}	
		if(0 == triesl)
		{
			LCD_movecursor(2,4);
			LCD_vSend_string("Safe closed");
			break;
		}		
        
    }
}