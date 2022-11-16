/*
 * Reloj.c
 *
 *  Created on: 15 nov 2022
 *      Author: fidel
 */

#include "DSP2833x_Device.h"
#include "Inc/Reloj.h"

static Reloj_Handler *Reloj;

extern void decodificadordisplay(unsigned int num);
interrupt void segundero_isr(void);

static void Reloj_GPIO_Init(void)
{
    EALLOW;

    //Se asegura que los GPIO requeridos se encuentran configurados como GPIO
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 0;
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;
    GpioCtrlRegs.GPBMUX2.bit.GPIO49 = 0;

    //Se asegura que los GPIO requeridos se encuentran configurados como salidas
    //GPIOs de datos
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO5 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;
    //GPIOs de selección
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO8 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO10 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1;
    //GPIOs de leds externos
    GpioCtrlRegs.GPADIR.bit.GPIO9 = 1;
    GpioCtrlRegs.GPADIR.bit.GPIO11 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;
    GpioCtrlRegs.GPBDIR.bit.GPIO49 = 1;

    EDIS;
}

static void aumentar_reloj(void)
{
    Reloj->Hora_Actual.minuto++;

    if(Reloj->Hora_Actual.minuto == 60)
    {
        Reloj->Hora_Actual.minuto = 0;
        Reloj->Hora_Actual.hora++;

        if(Reloj->Hora_Actual.hora == 24)
        {
            Reloj->Hora_Actual.hora = 0;
        }
    }
}

void Reloj_Init(Reloj_Handler * RelojHandler)
{
    Reloj = RelojHandler;

    //Se establece en cero la hora actual
    Reloj->Hora_Actual.hora = 0;
    Reloj->Hora_Actual.minuto = 0;

    //Se establece en cero la hora de alarma
    Reloj->Hora_Alarma.hora = 0;
    Reloj->Hora_Alarma.minuto = 0;

    //Se inicializan los GPIO necesarios
    Reloj_GPIO_Init();

    //Se asegura que el reloj de TIMER0 se ecneuntre activado
    EALLOW;
    SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = 1; // CPU Timer 0
    EDIS;

    //Se modifica la tabla de vectores de interrupciones
    EALLOW;
    PieVectTable.TINT0 = &segundero_isr;        //Se cambia la direccion de la ISR del TIMER0 a -> cpu_timer0_isr
    EDIS;

    //Se aesegura que las interrupciones requeridas se encuentren activadas
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;           //Se habilita la interrupción 1.7 TIMER_0
    IER |= 0x0001;                               //Habilitar la interrupción  del grupo 1
    EINT;

    //Se inicia el TIMER0
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 150, SEGUNDO);    //Timer a utilizar, frecuencia del reloj en MHz, duración timer us

    //Se inicia el reloj
    CpuTimer0Regs.TCR.bit.TSS = 0;
}

void Reloj_Run(Reloj_Handler * RelojHandler)
{
    Reloj = RelojHandler;
    unsigned int hora = (Reloj->Hora_Actual.hora*100) + (Reloj->Hora_Actual.minuto);
    decodificadordisplay(hora);
}

interrupt void segundero_isr(void)
{

    aumentar_reloj();
    CpuTimer0.InterruptCount++;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    GpioDataRegs.GPATOGGLE.bit.GPIO9 = 1;
}

