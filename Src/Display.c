/*
 * Display.c
 *
 *  Created on: 8 nov 2022
 *      Author: fidel
 */

#include "DSP2833x_Device.h"

void display(unsigned int num);
void decodificadordisplay(unsigned int num);



/*
 * @brief: Funcion para mostrar numeros del 0x0 - 0xf en el display de 7 segmentos
 * @param: El numero a mostrar en el display
 */
void display(unsigned int num)
{
    //Se apaga todo el display
    GpioDataRegs.GPASET.bit.GPIO0 = 1;
    GpioDataRegs.GPASET.bit.GPIO1 = 1;
    GpioDataRegs.GPASET.bit.GPIO2 = 1;
    GpioDataRegs.GPASET.bit.GPIO3 = 1;
    GpioDataRegs.GPASET.bit.GPIO4 = 1;
    GpioDataRegs.GPASET.bit.GPIO5 = 1;
    GpioDataRegs.GPASET.bit.GPIO6 = 1;

    //Se selecciona el numero a mostrar en el display

    switch (num)
    {
    case 0:
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        GpioDataRegs.GPASET.bit.GPIO6 = 1;
        break;

    case 1:
        GpioDataRegs.GPASET.bit.GPIO0 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        GpioDataRegs.GPASET.bit.GPIO3 = 1;
        GpioDataRegs.GPASET.bit.GPIO4 = 1;
        GpioDataRegs.GPASET.bit.GPIO5 = 1;
        GpioDataRegs.GPASET.bit.GPIO6 = 1;
        break;

    case 2:
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
        GpioDataRegs.GPASET.bit.GPIO2 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
        GpioDataRegs.GPASET.bit.GPIO5 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        break;

    case 3:
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        GpioDataRegs.GPASET.bit.GPIO4 = 1;
        GpioDataRegs.GPASET.bit.GPIO5 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        break;

    case 4:
        GpioDataRegs.GPASET.bit.GPIO0 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        GpioDataRegs.GPASET.bit.GPIO3 = 1;
        GpioDataRegs.GPASET.bit.GPIO4 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        break;

    case 5:
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
        GpioDataRegs.GPASET.bit.GPIO1 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        GpioDataRegs.GPASET.bit.GPIO4 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        break;

    case 6:
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
        GpioDataRegs.GPASET.bit.GPIO1 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        break;

    case 7:
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        GpioDataRegs.GPASET.bit.GPIO3 = 1;
        GpioDataRegs.GPASET.bit.GPIO4 = 1;
        GpioDataRegs.GPASET.bit.GPIO5 = 1;
        GpioDataRegs.GPASET.bit.GPIO6 = 1;
        break;

    case 8:
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        break;

    case 9:
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        GpioDataRegs.GPASET.bit.GPIO3 = 1;
        GpioDataRegs.GPASET.bit.GPIO4 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        break;

    case 10:
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        GpioDataRegs.GPASET.bit.GPIO3 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        break;

    case 11:
        GpioDataRegs.GPASET.bit.GPIO0 = 1;
        GpioDataRegs.GPASET.bit.GPIO1 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        break;

    case 12:
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
        GpioDataRegs.GPASET.bit.GPIO1 = 1;
        GpioDataRegs.GPASET.bit.GPIO2 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        GpioDataRegs.GPASET.bit.GPIO6 = 1;
        break;

    case 13:
        GpioDataRegs.GPASET.bit.GPIO0 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO1 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
        GpioDataRegs.GPASET.bit.GPIO5 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        break;

    case 14:
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
        GpioDataRegs.GPASET.bit.GPIO1 = 1;
        GpioDataRegs.GPASET.bit.GPIO2 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        break;

    case 15:
        GpioDataRegs.GPACLEAR.bit.GPIO0 = 1;
        GpioDataRegs.GPASET.bit.GPIO1 = 1;
        GpioDataRegs.GPASET.bit.GPIO2 = 1;
        GpioDataRegs.GPASET.bit.GPIO3 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO4 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO5 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO6 = 1;
        break;
    default:
        break;
    }
}

void decodificadordisplay(unsigned int num)
{
    static unsigned int decenas = 0, unidades = 0, centenas = 0, millar = 0, j = 0;
    millar = num*0.001;
    num = num%1000;
    centenas = num*0.01;
    num = num%100;
    decenas = num*0.1;
    num = num%10;
    unidades = num;

    if(j == 3000)
    {
        display(unidades);
        GpioDataRegs.GPACLEAR.bit.GPIO7 = 1;
        GpioDataRegs.GPASET.bit.GPIO8 = 1;
        GpioDataRegs.GPASET.bit.GPIO10 = 1;
        GpioDataRegs.GPBSET.bit.GPIO60 = 1;
    }

    if(j == 6000)
    {
        display(decenas);
        GpioDataRegs.GPASET.bit.GPIO7 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO8 = 1;
        GpioDataRegs.GPASET.bit.GPIO10 = 1;
        GpioDataRegs.GPBSET.bit.GPIO60 = 1;
    }

    if(j == 9000)
    {
        display(centenas);
        GpioDataRegs.GPASET.bit.GPIO7 = 1;
        GpioDataRegs.GPASET.bit.GPIO8 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO10 = 1;
        GpioDataRegs.GPBSET.bit.GPIO60 = 1;
    }

    if(j == 12000)
    {
        display(millar);
        GpioDataRegs.GPASET.bit.GPIO7 = 1;
        GpioDataRegs.GPASET.bit.GPIO8 = 1;
        GpioDataRegs.GPASET.bit.GPIO10 = 1;
        GpioDataRegs.GPBCLEAR.bit.GPIO60 = 1;
        j = 0;
    }

    j++;
}
