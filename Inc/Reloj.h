/*
 * Reloj.h
 *
 *  Created on: 15 nov 2022
 *      Author: fidel
 */

#ifndef INC_RELOJ_H_
#define INC_RELOJ_H_


/*
 * CONFIGURACIÓN DE LOS GPIOS Y CONEXIÓN
 * SEGMENTOS
 * 1A -> SEGMENT_A
 * 1B -> SEGMENT_B
 * 2A -> SEGMENT_C
 * 2B -> SEGMENT_D
 * 3A -> SEGMENT_E
 * 3B -> SEGMENT_F
 * 4A -> SEGMENT_G
 *
 * SELECCIÓN DE DIGITOS
 * 4B -> DIGIT_1_SELECT
 * 5A -> DIGIT_2_SELECT
 * 6A -> DIGIT_3_SELECT
 * GPIO60 -> DIGIT_4_SEKECT
 *
 * LEDS DE TARJETA
 * GPIO9 -> LED1
 * GPIO11 -> LED2
 * GPIO34 -> LED3
 * GPIO49 -> LED4
 *
 * GPIOs DE ENCODER HEXADECIMAL
 * GPIO12 -> HEX_1
 * GPIO13 -> HEX_2
 * GPIO15 -> HEX_3
 * GPIO16 -> HEX_4
 *
 * BOTONES
 * GPIO17 -> PUSH_BOTTON_1
 * GPIO48 -> PUSH_BOTTON_2
 */
#define SEGUNDO     1000000u

typedef enum{
    RELOJ,
    ALARM,
    CONFIG,
}Reloj_Mode;

typedef enum{
    ALARM_ON,
    ALARM_OFF,
}Reloj_Alarm_State;

typedef enum{
    ALARM_SET,
    ALARM_UNSET,
}Reloj_Alarm_Set;

typedef struct {
    unsigned int minuto;
    unsigned int hora;
}Reloj_Hora;

typedef struct{
    Reloj_Hora Hora_Actual;
    Reloj_Hora Hora_Alarma;
    Reloj_Mode Mode;
    Reloj_Alarm_State Alarma_Estado;
    Reloj_Alarm_Set Alarma_set;
}Reloj_Handler;

void Reloj_Init(Reloj_Handler * RelojHandler);

void Reloj_Run(Reloj_Handler * RelojHandler);


#endif /* INC_RELOJ_H_ */
