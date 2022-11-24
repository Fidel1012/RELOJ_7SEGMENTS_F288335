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

#define SEGUNDO     1000000u            //Se define el segundo para la espera del timmer0
#define MINUTO      60*SEGUNDO          //Se define el minuto por si se desea usar en el timmer0
#define ALARM_TIME  60                  //Veces que suena la alarma
#define ALARM_MODE  2                   //Para seleccionar el numero del selector en el que se configura la alarma
#define CONFIG_MODE 1                   //Para seleccionar el numero del selector en el que se configura la hora


/*
 * @brief: Enumeración para indicar en que modo se encuentra el relo, existen tres modos: Reloj, Alarma y Configuración
 */
typedef enum{
    RELOJ,
    ALARM,
    CONFIG,
}Reloj_Mode;

/*
 * @brief: Enumeración para determinar si la alarma se encuentra sonando o esta apagada
 */
typedef enum{
    ALARM_ON,
    ALARM_OFF,
}Reloj_Alarm_State;

/*
 * @brief: Enumeración para determinar si se ha configurado la alarma por el usuario, esto para evitar que se active en 00:00
 */
typedef enum{
    ALARM_SET,
    ALARM_UNSET,
}Reloj_Alarm_Set;

/*
 * @brief: Estructura de la hora, contiene minuto y hora
 */
typedef struct {
    unsigned int minuto;
    unsigned int hora;
}Reloj_Hora;

/*
 * @brief: Estructura que contiene lo necesario para administrar el reloj
 */
typedef struct{
    Reloj_Hora Hora_Actual;
    Reloj_Hora Hora_Alarma;
    Reloj_Mode Mode;
    Reloj_Alarm_State Alarma_Estado;
    Reloj_Alarm_Set Alarma_set;
    unsigned int alarm_time;
}Reloj_Handler;

/*
 * @brief: Función que inicia y configura el reloj, debe ir dentro del main antes de while
 */
void Reloj_Init(Reloj_Handler * RelojHandler);

/*
 * @brief: Funcion que hace funcionar el reloj, es necesario que esta funcion se enecuentre dentro del while del main
 */
void Reloj_Run(Reloj_Handler * RelojHandler);

#endif /* INC_RELOJ_H_ */
