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
interrupt void set_hora_isr(void);
interrupt void set_minute_isr(void);

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


    GpioCtrlRegs.GPBDIR.bit.GPIO48 = 0;

    //Se asegura que las interrupciones de botones se encuentran activas
    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 17;      //Seleccionar el GPIO17 sea el que acepte la interrupción
    XIntruptRegs.XINT1CR.bit.ENABLE = 1;            //Habilitar la interrupccion XInt1
    XIntruptRegs.XINT1CR.bit.POLARITY = 0;          //Seleccionar por flanco de bajada

    GpioIntRegs.GPIOXINT5SEL.bit.GPIOSEL = 48;      //Seleccionar el GPIO17 sea el que acepte la interrupción
    XIntruptRegs.XINT5CR.bit.ENABLE = 1;            //Habilitar la interrupccion XInt1
    XIntruptRegs.XINT5CR.bit.POLARITY = 0;          //Seleccionar por flanco de bajada


    EDIS;
}

static void interrupt_set(void)
{
    EALLOW;
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

    //Se modifica la tabla de vectores de interrupciones
    PieVectTable.TINT0 = &segundero_isr;            //Se cambia la direccion de la ISR del TIMER0 a -> cpu_timer0_isr

    //Se aesegura que las interrupciones requeridas se encuentren activadas
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;              //Se habilita la interrupción 1.7 TIMER_0
    PieCtrlRegs.PIEIER1.bit.INTx4 = 1;              //Se habilita la interrupción 1.4 XINT1

    PieCtrlRegs.PIEIER12.bit.INTx3 = 1;

    PieVectTable.XINT1 = &set_hora_isr;             //Se cambia la direccion de la ISR del GPIO17 a -> set_hora_isr
    PieVectTable.XINT5 = &set_minute_isr;           //Se cambia la direccion de la ISR del GPIO17 a -> gpio_int1_isr

    //Se inicia el TIMER0
    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 150, SEGUNDO);       //Timer a utilizar, frecuencia del reloj en MHz, duración timer us

    EALLOW;
    IER |= 0x0001;                                  //Habilitar la interrupción  del grupo 1
    IER |= 0x0800;                                  //Habilitar la interrupción  del grupo 12

    EINT;

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

static void check_mode(Reloj_Handler * RelojHandler)
{
    Reloj = RelojHandler;

    unsigned int mode_sel  = (GpioDataRegs.GPADAT.bit.GPIO12) + 2*(GpioDataRegs.GPADAT.bit.GPIO13) + 4*(GpioDataRegs.GPADAT.bit.GPIO14) + 8*(GpioDataRegs.GPADAT.bit.GPIO15);

    if (mode_sel == 1)
    {
        Reloj->Mode = CONFIG;
        GpioDataRegs.GPASET.bit.GPIO11 = 1;
        GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
    }else if(mode_sel == 2)
    {
        Reloj->Mode = ALARM;
        GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;
        GpioDataRegs.GPBSET.bit.GPIO34 = 1;
    }else
    {
        Reloj->Mode = RELOJ;
        GpioDataRegs.GPACLEAR.bit.GPIO11 = 1;
        GpioDataRegs.GPBCLEAR.bit.GPIO34 = 1;
    }
}

void check_alarm(Reloj_Handler *RelojHandler)
{
    Reloj = RelojHandler;

    if(Reloj->Hora_Actual.hora == Reloj->Hora_Alarma.hora && Reloj->Hora_Actual.minuto == Reloj->Hora_Alarma.minuto && Reloj->Alarma_set == ALARM_SET)
    {
        Reloj->Alarma_Estado = ALARM_ON;
    }else if(Reloj->Hora_Actual.hora == Reloj->Hora_Alarma.hora && Reloj->Hora_Actual.minuto == (Reloj->Hora_Alarma.minuto + 59))
    {
        Reloj->Alarma_Estado = ALARM_OFF;
        GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;
    }
}

void alarm(void)
{
    if(Reloj->Alarma_Estado == ALARM_ON)
    {
        GpioDataRegs.GPBTOGGLE.bit.GPIO49 = 1;
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

    //Se configguran las interrupciones necesarias
    interrupt_set();

    //Se inicia el reloj
    CpuTimer0Regs.TCR.bit.TSS = 0;

    Reloj->Alarma_Estado = ALARM_OFF;
    Reloj->Alarma_set = ALARM_UNSET;
}

void Reloj_Run(Reloj_Handler * RelojHandler)
{
    //Se verifica en que modo se encuentra el reloj
    check_mode(RelojHandler);

    Reloj = RelojHandler;
    unsigned int hora = (Reloj->Hora_Actual.hora*100) + (Reloj->Hora_Actual.minuto);
    unsigned int alarma = (Reloj->Hora_Alarma.hora*100) + (Reloj->Hora_Alarma.minuto);

    if(Reloj->Mode == RELOJ || Reloj->Mode == CONFIG)
    {
        decodificadordisplay(hora);
    }else if(Reloj->Mode == ALARM)
    {
        decodificadordisplay(alarma);
    }

    //Se verifica la alarma
    check_alarm(RelojHandler);
}

interrupt void segundero_isr(void)
{

    aumentar_reloj();
    alarm();
    CpuTimer0.InterruptCount++;

    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    GpioDataRegs.GPATOGGLE.bit.GPIO9 = 1;
}

interrupt void set_hora_isr(void)
{
    if(Reloj->Mode == CONFIG)
    {
        Reloj->Hora_Actual.hora++;
        if(Reloj->Hora_Actual.hora > 23)
            Reloj->Hora_Actual.hora = 0;
    }else if(Reloj->Mode == ALARM)
    {
        Reloj->Alarma_set = ALARM_SET;
        Reloj->Hora_Alarma.hora++;
        if(Reloj->Hora_Alarma.hora > 23)
            Reloj->Hora_Alarma.hora = 0;
    }else if(Reloj->Mode == RELOJ && Reloj->Alarma_Estado == ALARM_ON)
    {
        Reloj->Alarma_Estado = ALARM_OFF;
        GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;
    }
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

interrupt void set_minute_isr(void)
{
    if(Reloj->Mode == CONFIG)
    {
        Reloj->Hora_Actual.minuto++;
        if(Reloj->Hora_Actual.minuto > 59)
            Reloj->Hora_Actual.minuto = 0;
    }else if(Reloj->Mode == ALARM)
    {
        Reloj->Alarma_set = ALARM_SET;
        Reloj->Hora_Alarma.minuto++;
        if(Reloj->Hora_Alarma.minuto > 59)
            Reloj->Hora_Alarma.minuto = 0;
    }else if(Reloj->Mode == RELOJ && Reloj->Alarma_Estado == ALARM_ON)
    {
        Reloj->Alarma_Estado = ALARM_OFF;
        GpioDataRegs.GPBCLEAR.bit.GPIO49 = 1;
    }
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;
}
