/*============================================================================
 * License: BSD-3-Clause
 * Copyright 2018, Eric Pernia <ericpernia@gmail.com>
 * All rights reserved.
 * Date: 2018/10/04
 *===========================================================================*/

/*==================[inclusions]=============================================*/

#include "task2.h"  // <= own header
#include "task1.h" 

/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/
uint8_t var;
bool state;
uint8_t ms;
uint8_t value;



// Defining a list type enum named dbMEF_t that includes the only possible states its type can have
typedef enum{
  BUTTON_UP,
  BUTTON_FALLING,
  BUTTON_RISING,
  BUTTON_DOWN,
       
} dbnMEF_t;

// This structure defines the 3 components a botton should include
typedef struct{
  gpioMap_t tec; // Tecla que se está controlando TEC1,TEC2,...
  dbnMEF_t state; // Estado de la MEF antirebote
  delay_t delay; // Delay no bloqueante para temporizar 40ms
} dbn_t;

dbn_t vectorTeclas[4]={
   {TEC1,0,0},
   {TEC2,0,0},
   {TEC3,0,0},
   {TEC4,0,0},
  };
char *name[4] = {"Pulsador 1", "Pulsador 2", "Pulsador 3","Pulsador 4"};

// This is a list of all the bottons(structures) used in this code and with their initial values

/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/




/*==================[external functions definition]==========================*/

// Funcion que inicializa la tarea

void task2_Init( void ){}

// Funcion que se ejecuta periodicamente
void task2_Update(){   
     	
// This function checks  if the user input is 1,2,3 or 4 and calls certain functions accordingly 	
	if(uartReadByte(UART_USB,&var)){
  
		switch(var){	
   
			case 't':
				clear();
				for(uint8_t i=0; i<=3;i++){
					
					state=!gpioRead(vectorTeclas[i].tec);
						switch(state){
							
										
							case 1:
							vectorTeclas[i].state=3;
							printf("\nRising %s\n",name[i]);
							ms=tickRead();
							if(ms>=40){
							  if(!gpioRead(vectorTeclas[i].tec)){
				 			  //printf("\nticks count is %d\n",ms);
							  tickWrite(0);
							  printf("\nPressed %s\n",name[i]);
							   }
							 }
							  
							break;
							default:
							printf("\nReleased %s\n",name[i]);;
						}
				}
			break;

				
			

			case 'd':

				clear();
				// This function enables the ADC peripheral
				adcConfig(ADC_ENABLE); 
				//This line stores the return of the function call that takes a channel as an input to read from
				value=adcRead(CH1); 
				// This function prints out a message and the value of the stored data
				printf("\nThe ADC value is  %d\n",value); ;
			
				break;

			case 'l':

				
			
				clear();
				break;
			

			default:
				
				NULL;
        
		}
		
	}


}
/*==================[end of file]============================================*/
