/*============================================================================
 * License: BSD-3-Clause
 * Copyright 2018, Eric Pernia <ericpernia@gmail.com>
 * All rights reserved.
 * Date: 2018/10/04
 *===========================================================================*/

/*==================[inclusions]=============================================*/

#include "task1.h"  // <= own header


/*==================[macros and definitions]=================================*/

/*==================[internal data declaration]==============================*/

rtc_t rtc;

/*==================[internal functions declaration]=========================*/

void clear();
void time();

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

//This function clears the screen completely 
void clear(){
  
  // This code tells the compiler the following line is a command to the virtual terminal
  uartWriteByte(UART_USB,27); 
  //clear screen
  uartWriteString(UART_USB,"[2J"); 
  uartWriteByte(UART_USB,27);
  // start move cursor to the begining   
  uartWriteString(UART_USB,"[H");
  uartWriteString(UART_USB,"Presiona T para visualizar el estado de los pulsadores\n\r");
  uartWriteString(UART_USB,"Presiona D para entrar al modo ADC\n\r");
  uartWriteString(UART_USB,"Presiona L limpiar la pantalla\n\r");
  //Print a seperation 
  time();
  uartWriteString(UART_USB,"\n\n**************************************************************\n\r"); 		
}

//This functions shows the current time
void time(){

  //This funciton takes the rtc address to update the structure enteries      
  rtcRead(&rtc);
  //Show date and time 
  printf( "\n\n\n                                       %02d/%02d/%04d,%02d:%02d:%02d\r\n", 
  rtc.mday, rtc.month, rtc.year,rtc.hour, rtc.min, rtc.sec );
}


/*==================[external functions definition]==========================*/

// Funcion que inicializa la tarea
void task1_Init( void ){

// These definitions must be executed inside the app.c fine and would not work if defined outside
  rtc.year = 2019;
  rtc.month = 5;
  rtc.mday = 7;
  rtc.wday = 3;
  rtc.hour = 12;
  rtc.min = 15;
  rtc.sec= 0;
  rtcConfig(&rtc);
  uartConfig(UART_USB,115200); 
}

// Funcion que se ejecuta periodicamente
void task1_Update( void* taskParam ){ 
 
   uartWriteByte(UART_USB,27);
  // start move cursor to the begining   
  uartWriteString(UART_USB,"[H"); 
  uartWriteString(UART_USB,"Presiona T para visualizar el estado de los pulsadores\n\r");
  uartWriteString(UART_USB,"Presiona D para entrar al modo ADC\n\r");
  uartWriteString(UART_USB,"Presiona L limpiar la pantalla\n\r");
  //Print a seperation 
  time();
  uartWriteString(UART_USB,"\n\n**************************************************************\n\r");
}
 
  


/*==================[end of file]============================================*/
