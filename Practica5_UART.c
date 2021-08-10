/**
 * @file    Practica5_UART.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "Arduino.h"
#include "LCD1.h"
#include "UART.h"

int main(void){

  	/* Init board hardware. */
	BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    UART_vfnDriverInit ();  //Inicializar UART
    LCD_init(); 			//Inicializar LCD
    PWM_vfnDriverInit(); 	//Inicializar PWM


    DPY_bInitialPosition(); //Servo en Pos. Inicial 0°

    unsigned int vActual=0;
    unsigned int vPasado=0;
    unsigned int Grados = 0;
    unsigned int r0=0;
    char buffer[11];

    while(1){
    	UART_bfnRead(&r0);

    	if(r0 != 0){
    		vActual = r0;
    		printf("%i\n",r0);
    		if(vActual != vPasado){
    			Grados = r0;
    			PWM_bfnAngleAdjustment (Grados);
    		 	LCD_command(DISPLAY_CLEAR);
    		 	DPY_bfnWriteMsg("TEMP:");
    		 	enteroACadena(r0,buffer);
    		 	DPY_bfnWriteMsg(buffer);
    		}
    		vPasado = r0;
    	}
    }
    return 0;
}
