/**************************************************************
 *                                                            *
 *                                                            *
 *             PLANTILLA DE PROYECTOS DEL F28335              *
 *                                                            *
 *                DR. OSCAR CARRANZA CASTILLO                 *
 *                                                            *
 *               INSTITUTO POLITECNICO NACIONAL               *
 *                                                            *
 *                   3 DE SEPTIEMBRE 2014                     *
 *                                                            *
 *             Actualizado el 3 de Abril del 2019            *
 *                                                            *
 **************************************************************
 */

#include "DSP2833x_Device.h"
#include "Inc/Reloj.h"

extern void InitSysCtrl(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
extern void GPIO_Init(void);
extern void decodificadordisplay(unsigned int num);

void delay(void);
void display_binario(unsigned int num);

unsigned int contador = 0;
long i;

extern unsigned int decenas, unidades;

Reloj_Handler Reloj1;

void main(void) {

	// Paso 1: Inicializar el sistema de Control:
	// PLL, WatchDog, Habilitar el reloj de los periféricos
	// Esta funcion se encuentra en el archivo DSP2833x_SysCtrl.c

	   InitSysCtrl();

	// Paso 2. Inicializar GPIO:

	   GPIO_Init();

	// Paso 3. Limpiar todas las Interrupciones e Inicializar la Tabla del vector PIE:

	// Deshabilita Interrupciones del CPU

	   DINT;

	// Inicializar los registros de control de PIE a sus estados iniciales.
	// El estado de default es que todas las interrupciones esten deshabilitadas
	// y las banderas limpiadas.
	// Esta funcion se encuentra en el archivo DSP2833x_PieCtrl.c.

	   InitPieCtrl();

	// Deshabilitar las interrupciones del CPU y limpiar todas las banderas de las
	// interrupciones del CPU:

	   IER = 0x0000;
	   IFR = 0x0000;

	// Inicializar la tabla del vector de PIE con los punteros que establecen las rutinas
	// de servicio (ISR).
	// Las estructuras de las rutinas ISR se encuentran en DSP2833x_DefaultIsr.c.
	// Esta funcion se encuentra en el Archivo DSP2833x_PieVect.c.

	   InitPieVectTable();


	// Paso 4. Inicializar todos los dispositivos periféricos:
	// Esta funcion se encuentra en el archivo DSP2833x_InitPeripherals.c
	// InitPeripherals();

	// Paso 5. Código del Usuario:

	   Reloj_Init(&Reloj1);

       while(1)
       {
           Reloj_Run(&Reloj1);

       }
}



