/*
 * Reloj.h
 *
 *  Created on: 15 nov 2022
 *      Author: fidel
 */

#ifndef INC_RELOJ_H_
#define INC_RELOJ_H_

#define SEGUNDO     1000000u

typedef struct {
    unsigned int minuto;
    unsigned int hora;
}Reloj_Hora;

typedef struct{
    Reloj_Hora Hora_Actual;
    Reloj_Hora Hora_Alarma;
}Reloj_Handler;

void Reloj_Init(Reloj_Handler * RelojHandler);

void Reloj_Run(Reloj_Handler * RelojHandler);


#endif /* INC_RELOJ_H_ */
