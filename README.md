## RELOJ 7 SEGMENTOS F28335

* Este programa hace funcionar un display de 7 segmentos de 4 digitos para mostrar la hora y los minutos, aunque esta configurado para que cada minuto sea un segundo. Se utiliza la plaxca de desarrollo que contiene diferentes elementos como 2 botones, un seleccionador hexadecimal y 4 leds. 
**EL DISPLAY QUE SE UTILIZA ES DE ANODO COMUN**, para utilizar un display de catodo comun se debe modificar el archivo Display.c.

``#define SEGUNDO     1000000u            //Se define el segundo para la espera del timmer0``

* Es posible confgurar una alarma, cuando sea la hora cofigurada para la alarma, el LED 4 de la tarjeta de desarrollo parpadeara por 60 segundo, este tiempo se puede configurar en el archivo Reloj.h.

``#define ALARM_TIME  60                  //Veces que suena la alarma``

* El selector hexadecimal se utiliza para seleccioar el modo en que se encuentra el reloj, teniendo tres modos:
    1. Config: En este modo es donde se configura la hora, en este modo el reloj se continua desplegando en el display. Por defecto se encuentra en el numero 1 del selector hexadecimal.
    2. Alarma: En ste modo se configura la alarma, se despliega la alarma, es decir, que el tiempo se deja de motrar, sin embargo, continua contando. Por defecto se encuentra configurado en el numero 2 del selector hexadeximal.
    3. Reloj: Es el modo normal, donde el reloj funciona normalmente. Este modo se encuentra en cuanquier otro numero del selector hexadecimal que no sea el de config y alarm.
Para modificar se puede hacer desde las siguientes macros en el archivo Reloj.h. **Evitar seleccionar el mismo numero para ambas.**

``#define ALARM_MODE  2                   //Para seleccionar el numero del selector en el que se configura la alarma``
``#define CONFIG_MODE 1                   //Para seleccionar el numero del selector en el que se configura la hora``

* En modo reloj la alarma puede ser desactivada puslando cualquiera de los dos botones.

### CONEXIONES

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


