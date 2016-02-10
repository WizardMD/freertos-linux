/*
   Copyright 2016 sean93.park@gmail.com

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

/*
    FreeRTOS V8.2.3 - Copyright (C) 2015 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>>> AND MODIFIED BY <<<< the FreeRTOS exception.

    ***************************************************************************
    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<
    ***************************************************************************

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available on the following
    link: http://www.freertos.org/a00114.html

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that is more than just the market leader, it     *
     *    is the industry's de facto standard.                               *
     *                                                                       *
     *    Help yourself get started quickly while simultaneously helping     *
     *    to support the FreeRTOS project by purchasing a FreeRTOS           *
     *    tutorial book, reference manual, or both:                          *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org/FAQHelp.html - Having a problem?  Start by reading
    the FAQ page "My application does not run, what could be wrong?".  Have you
    defined configASSERT()?

    http://www.FreeRTOS.org/support - In return for receiving this top quality
    embedded software for free we request you assist our global community by
    participating in the support forum.

    http://www.FreeRTOS.org/training - Investing in training allows your team to
    be as productive as possible as early as possible.  Now you can receive
    FreeRTOS training directly from Richard Barry, CEO of Real Time Engineers
    Ltd, and the world's leading authority on the world's leading RTOS.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.FreeRTOS.org/labs - Where new FreeRTOS products go to incubate.
    Come and try FreeRTOS+TCP, our new open source TCP/IP stack for FreeRTOS.

    http://www.OpenRTOS.com - Real Time Engineers ltd. license FreeRTOS to High
    Integrity Systems ltd. to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and commercial middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/* The time between cycles of the 'check' functionality (defined within the
tick hook. */
#define mainCHECK_DELAY           ( ( TickType_t ) 5000 / portTICK_RATE_MS )


void vApplicationTickHook( void )
{
  static unsigned long ulTicksSinceLastDisplay = 0;
  static unsigned long ulCalled = 0;
  portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;

  /* Called from every tick interrupt.  Have enough ticks passed to make it
  time to perform our health status check again? */
  ulTicksSinceLastDisplay++;
  if( ulTicksSinceLastDisplay >= mainCHECK_DELAY )
  {
    ulTicksSinceLastDisplay = 0;
    ulCalled++;
  }
}


void vApplicationIdleHook( void )
{
  /* The co-routines are executed in the idle task using the idle task hook. */
  /* vCoRoutineSchedule(); */ /* Comment this out if not using Co-routines. */

  struct timespec xTimeToSleep, xTimeSlept;
  /* Makes the process more agreeable when using the Posix simulator. */
  xTimeToSleep.tv_sec = 1;
  xTimeToSleep.tv_nsec = 0;
  nanosleep( &xTimeToSleep, &xTimeSlept );
}


const TickType_t xDelay = 5000 / portTICK_PERIOD_MS;

void prvTest02TaskA(void *pvParameters)
{
  static unsigned int tickcount = 0;

  for ( ;; ) {
    vTaskDelay(xDelay);
    printf("Test02A ++++: %u\r\n", tickcount);
    tickcount++;
  }
  printf( "Test02A Task End.\r\n" );
  vTaskDelete( NULL );
}


void prvTest02TaskB(void *pvParameters)
{
  static unsigned int tickcount = 0;

  for ( ;; ) {
    vTaskDelay(xDelay);
    printf("Test02B ----: %u\r\n", tickcount);
    tickcount++;
  }
  printf( "Test02B Task End.\r\n" );
  vTaskDelete( NULL );
}


int main(void)
{
  xTaskHandle hTest02TaskA;
  xTaskHandle hTest02TaskB;

  vParTestInitialise();

  xTaskCreate( prvTest02TaskA,
               "Test02A",
               configMINIMAL_STACK_SIZE,
               NULL,
               tskIDLE_PRIORITY + 1,
               &hTest02TaskA );

  xTaskCreate( prvTest02TaskB,
               "Test02B",
               configMINIMAL_STACK_SIZE,
               NULL,
               tskIDLE_PRIORITY + 1,
               &hTest02TaskB );

  vTaskStartScheduler();
  return 1;
}
