/* Copyright 2017-2018, Eric Pernia
 * All rights reserved.
 *
 * This file is part of sAPI Library.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*==================[inlcusiones]============================================*/

// Includes de FreeRTOS
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "task.h"
#include "task1.h"
#include "task2.h"
#include "task2.h"
#include "queue.h"

// sAPI header
#include "sapi.h"

/*==================[definiciones y macros]==================================*/

/*==================[definiciones de datos internos]=========================*/
xQueueHandle queueHandler =0;
/*==================[definiciones de datos externos]=========================*/

DEBUG_PRINT_ENABLE;
int i=1;
int x=0;

/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/

// Prototipo de funcion de la tarea
void task1( void* taskParmPtr );
void task2( void* taskParmPtr );

/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main(void)
{
   // ---------- CONFIGURACIONES ------------------------------
   // Inicializar y configurar la plataforma
   boardConfig();

  //Crear el queue 
  queueHandler =xQueueCreate(1,sizeof(int)); // reservar espacio en la memoria de 5 elementos de tipo int

   // UART for debug messages
   debugPrintConfigUart( UART_USB, 115200 );
   debugPrintlnString( "Blinky con freeRTOS y sAPI." );

   // Led para dar se�al de vida
   gpioWrite( LED3, ON );

   // Crear tarea1 en freeRTOS
   xTaskCreate(
      task1,                     // Funcion de la tarea a ejecutar
      (const char *)"task1",     // Nombre de la tarea como String amigable para el usuario
      configMINIMAL_STACK_SIZE*2, // Cantidad de stack de la tarea
      0,                          // Parametros de tarea
      tskIDLE_PRIORITY+1,         // Prioridad de la tarea
      0                           // Puntero a la tarea creada en el sistema
   );

  // Crear tarea2 en freeRTOS
   xTaskCreate(
      task2,                     // Funcion de la tarea a ejecutar
      (const char *)"task2",     // Nombre de la tarea como String amigable para el usuario
      configMINIMAL_STACK_SIZE*2, // Cantidad de stack de la tarea
      0,                          // Parametros de tarea
      tskIDLE_PRIORITY+1,         // Prioridad de la tarea
      0                           // Puntero a la tarea creada en el sistema
   );
   // Iniciar scheduler
   vTaskStartScheduler();

   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE ) {
      // Si cae en este while 1 significa que no pudo iniciar el scheduler
   }

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta
   // directamenteno sobre un microcontroladore y no es llamado por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

// Implementacion de funcion de las tareas
void task1( void* taskParmPtr )
{
   task1_Init();
   

   // Tarea periodica cada 500 ms
   portTickType xPeriodicity =  1000 / portTICK_RATE_MS;
   portTickType xLastWakeTime = xTaskGetTickCount();
   
   // ---------- REPETIR POR SIEMPRE --------------------------
   while(TRUE) {
     
  
  task1_Update();

  //mandar i a l cola y esperar 1 segundo
  if( !xQueueSend(queueHandler,&i,1000)){
   
   uartWriteString(UART_USB,"tas 1 has been updated\n\r");

  }
     
  // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
  vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
   }
}

void task2( void* taskParmPtr )
{
   task2_Init();
  //espera 1 segundo y lea el valor enviado al queue y guardarlo en el variable x si es cierto manda mensaje
    if( xQueueReceive(queueHandler,&x,1000)){
   
     uartWriteString(UART_USB,"task 1 was updated successfully\n\r");

    }

   // Tarea periodica cada 500 ms
   portTickType xPeriodicity =  50 / portTICK_RATE_MS;
   portTickType xLastWakeTime = xTaskGetTickCount();
   
   // ---------- REPETIR POR SIEMPRE --------------------------
   while(TRUE) {
     
  
  task2_Update();
     
  // Envia la tarea al estado bloqueado durante xPeriodicity (delay periodico)
  vTaskDelayUntil( &xLastWakeTime, xPeriodicity );
   }
}

/*==================[fin del archivo]========================================*/
