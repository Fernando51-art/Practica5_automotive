
#include <stdio.h>
#include "MKL25Z4.h"
#include "Arduino.h"


void UART_vfnDriverInit (void);
void UART_bfnRead(uint8_t *recived);
void transmit(char *DATA);

void UART_vfnDriverInit (void){
	MCG->C4=0xA0;							//Configuramos reloj a 48MHz
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);	//Seleccionamos el reloj MCGFLLCLK
	SIM->SCGC4|=SIM_SCGC4_UART0_MASK;		//Habilitamos el reloj de UART0
	SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;		//Habilitamos el reloj del puerto A
	PORTA->PCR[1]|=PORT_PCR_MUX(2);			//Configuramos puerto A1 como Rx
	PORTA->PCR[2]|=PORT_PCR_MUX(2);			//Configuramos puerto A2 como Tx
	UART0->BDL=0x38;						//Valores bajos de Baudios
	UART0->BDH=0x1;							//Valores altos de Baudios
	UART0->C1=0x0;							//Configuracion UART: Sin paridad, 8 bits, funcionamiento normal(Rx Tx habilitados, modo de espera)
	UART0->C2=0xC;							//Habilitar transmisor y receptor
	UART0->C4=0x20;							//El receptor y transmisor usaran datos de 8 o 9 bits
}

void transmit(char *DATA){
	while(*DATA){
		UART0->D=*DATA;
		delayMs(500);
		while(!(UART0->S1&UART_S1_TDRE_MASK));
		DATA++;
	}
}


void UART_bfnRead(uint8_t *recived){
  //UART0->C2=0X4;
  *recived=UART0->D; //Guardar el valor recivido en buffer de UART
}
