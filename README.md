# LPC1769-PWM
Este repositorio contiene los drivers para poder utilizar el periférico PWM del LPC1769 (Cortex M3 - ARM). 
<br />Se deben agregar en la carpeta lpc1769: 
<br />chip/inc :
<br />|En chip_lpc175x_6x.h : 
<br />|Se agrega y define las direcciones del PWM.
<br />|En pwm1_17xx_40xx.h:
<br />|Se define la estructura de los registros del PWM, también macros utiles para el driver.
<br />chip/src
<br />|En pwm1_17xx_40xx.c:
<br />|Funciones para configurar el PWM.



LPC1769 : User manual Rev 4.1. 19 December 2016 
https://www.nxp.com/docs/en/user-guide/UM10360.pdf

