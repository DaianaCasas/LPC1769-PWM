/*
 * pwm1_17xx_40xx.c
 *
 *  Created on: 3 de jul. de 2018
 *      Author: DaianaCasas.
 */
#include "chip.h"
#include "pwm1_17xx_40xx.h"
#if defined(CHIP_LPC175X_6X)

/*	Configura el pin para que trabaje como PWM*/
void PWM1_SelectChannel(LPC_PWM1_T *pPWM, uint32_t num_channel)
{
	switch(num_channel)
	{
		case CH1:
			Chip_IOCON_PinMux(LPC_IOCON, PWM1_CH1OUT, IOCON_MODE_INACT , FUNC_PWM);
		break;
		case CH2:
			Chip_IOCON_PinMux(LPC_IOCON, PWM1_CH2OUT, IOCON_MODE_INACT , FUNC_PWM);
		break;
		case CH3:
			Chip_IOCON_PinMux(LPC_IOCON, PWM1_CH3OUT, IOCON_MODE_INACT , FUNC_PWM);
		break;
		case CH4:
			Chip_IOCON_PinMux(LPC_IOCON, PWM1_CH4OUT, IOCON_MODE_INACT , FUNC_PWM);
		break;
		case CH5:
			Chip_IOCON_PinMux(LPC_IOCON, PWM1_CH5OUT, IOCON_MODE_INACT , FUNC_PWM);
		break;
		case CH6:
			Chip_IOCON_PinMux(LPC_IOCON, PWM1_CH6OUT, IOCON_MODE_INACT , FUNC_PWM);
		break;
		default:
		break;
	}
}
/**
 * @brief	Habilita el TC y el PC para el conteo. A su vez activa el modo PWM
 * @param	pPWM		: Pointer to timer IP register address
 * @return	void
 */
void PWM1_EnableCounters(LPC_PWM1_T *pPWM)
{
	pPWM->TCR|=( PWM1_TCR_COUNTER_ENABLE | PWM1_TCR_PWM_ENABLE );
}
/**
 * @brief	Reseteo el TC y el PC para el conteo, lo hace en el prox ciclo del clock luego de invocar la llamada.
 * @param	pPWM		: Pointer to timer IP register address
 * @return	void
 */
void PWM1_ResetCounters(LPC_PWM1_T *pPWM)
{
	pPWM->TCR |= PWM1_TCR_RESET_ENABLE;
	pPWM->TCR &= ( (~PWM1_TCR_RESET_ENABLE) & PWM1_TCR_BITMASK );
	pPWM->TCR |= PWM1_TCR_COUNTER_ENABLE;
}
/**
 * @brief	Configura la accion del TC==MR :
 * @param	pPWM		: Pointer to timer IP register address
 * @param	numchannel	: Numero de canal de Match
 * @param	interr		: Habilita la generacion de interrupcion
 * @param	reset		: Habilita el reseteo del TC
 * @param	stop		: Habilita el stop del TC y PC, y ademas pone en 0 al TCR
 * @return	void
 */
void PWM1_ConfigMatch(LPC_PWM1_T *pPWM, uint8_t numchannel,uint8_t interr,uint8_t reset,uint8_t stop)
{
	pPWM->MCR|= ( (interr == 1)? PWM1_MCR_I(numchannel): 0x0 ) | ( (reset == 1)? PWM1_MCR_R(numchannel): 0x0 ) | ((stop == 1)? PWM1_MCR_S(numchannel): 0x0);
}
/**
 * @brief	Configura el control en los flancos y las salidas pwm :
 * @param	pPWM		: Pointer to timer IP register address
 * @param	numchannel	: Numero de canal de Match
 * @param	modo_edge	: 1 doble edge control 0 single edge control
 * @param	enable_out	: 1 habilita la salida 0 deshabilita la salida
 * @return	void
 */
void PWM1_ControlChannel(LPC_PWM1_T *pPWM, uint8_t numchann,uint8_t modo_edge,uint8_t enable_out )
{
	if(numchann>1 && numchann<7)
	{	pPWM->PCR |= ( ( modo_edge==	0)?  0x0 :PWM1_PCR_DOBLE_EDGE(numchann)	);	}
	if(numchann>0 && numchann<7)
	{	pPWM->PCR |= ( ( enable_out== 0)? 0x0 :PWM1_PCR_ENABLE_OUTPUT(numchann)	);	}

}
/**
 * @brief	Valor del MATCH register
 * @param	pPWM		: Pointer to timer IP register address
 * @param	matchnum	: Match interrupt number
 * @param	value		: Valor del MATCH
 * @return
 */
void PWM1_SetMatch(LPC_PWM1_T *pPWM, uint8_t numchann, uint32_t value)
{
	switch(numchann)
	{
		case CH0:
			pPWM->MR0=value;
		break;
		case CH1:
			pPWM->MR1=value;
		break;
		case CH2:
			pPWM->MR2=value;
		break;
		case CH3:
			pPWM->MR3=value;
		break;
		case CH4:
			pPWM->MR4=value;
		break;
		case CH5:
			pPWM->MR5=value;
		break;
		case CH6:
			pPWM->MR6=value;
		break;
		default:
		break;
	}
}
/**
 * @brief	Valor del MATCH register
 * @param	pPWM		: Pointer to timer IP register address
 * @param	matchnum	: Match interrupt number
 * @param	value		: Valor del MATCH
 * @return
 */
void PWM1_GetMatch(LPC_PWM1_T *  pPWM, uint8_t numchann, uint32_t* value)
{
	switch(numchann)
	{
		case CH0:
			*value=pPWM->MR0;
		break;
		case CH1:
			*value=pPWM->MR1;
		break;
		case CH2:
			*value=pPWM->MR2;
		break;
		case CH3:
			*value=pPWM->MR3;
		break;
		case CH4:
			*value=pPWM->MR4;
		break;
		case CH5:
			*value=pPWM->MR5;
		break;
		case CH6:
			*value=pPWM->MR6;
		break;
		default:
		break;
	}
}
/**
 * @brief	Valor del PREESCALE COUNTERregister
 * @param	pPWM		: Pointer to timer IP register address
 * @param	value		: Valor del prescaler
 * @return
 */
void PWM1_ValuePrescale(LPC_PWM1_T *pPWM, uint32_t value)
{
	pPWM->PR=value;
}

#endif /* defined(CHIP_LPC175X_6X) */
