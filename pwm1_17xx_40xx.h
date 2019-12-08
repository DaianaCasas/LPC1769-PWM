/*
 * pwm1_17xx_40xx.h
 *
 *  Created on: 27 de jun. de 2018
 *      Author: DaianaCasas
 */

#ifndef __PWM1_17XX_40XX_H_
#define __PWM1_17XX_40XX_H_
#ifdef __cplusplus
extern "C"{

#endif
/** @defgroup PWM1_17XX_40XX CHIP: LPC17xx/40xx PWM1 driver
 * @ingroup CHIP_17XX_40XX_Drivers
 * @{
 */
#if defined(CHIP_LPC175X_6X)
#include "clock_17xx_40xx.h"
/**
 * @brief PWM1 register block structure
 */
typedef struct{
	__IO uint32_t IR;		/*!< Interrupt Register */
	__IO uint32_t TCR; 		/*!< Timer Control Register */
	__IO uint32_t TC;		/*!< Timer Counter	*/
	__IO uint32_t PR;		/*!< Prescale Register */
	__IO uint32_t PC;		/*!< Prescale Counter */
	__IO uint32_t MCR;		/*!< Match Control REgister */
	__IO uint32_t MR0;		/*!< Match Register 0 */
	__IO uint32_t MR1;		/*!< Match Register 1 */
	__IO uint32_t MR2;		/*!< Match Register 2 */
	__IO uint32_t MR3;		/*!< Match Register 3 */
	__IO uint32_t CCR;		/*!< Capture Control Register */
	__I uint32_t CR0;		/*!< Capture Register 0 */
	__I uint32_t CR1;		/*!< Capture Register 1 */
	__I uint32_t CR2;		/*!< Capture Register 2 */
	__I uint32_t CR3;		/*!< Capture Register 3 */
		uint32_t RESERVED0;
	__IO uint32_t MR4;		/*!< Match Register 4 */
	__IO uint32_t MR5;		/*!< Match Register 5 */
	__IO uint32_t MR6;		/*!< Match Register 6 */
	__IO uint32_t PCR;		/*!< PWM Control Register */
	__IO uint32_t LER;		/*!< Load enable Register */
    	 uint32_t RESERVED1[7];
	__IO uint32_t CTCR;		/*!< Count Control Register */
}LPC_PWM1_T;

/**
 * @brief Pins of pwm's channels, to port1 and port2
 */

#define PUERTO2	1

#if defined(PUERTO1)

		#define PWM1_CH1OUT				1,18
		#define PWM1_CH2OUT				1,20
		#define PWM1_CH3OUT				1,21
		#define PWM1_CH4OUT				1,23
		#define PWM1_CH5OUT				1,24
		#define PWM1_CH6OUT				1,26

		#define FUNC_PWM             0x2				/*!< Selects pin function 0x10 */

#elif defined(PUERTO2)
		#define PWM1_CH1OUT				2,0
		#define PWM1_CH2OUT				2,1
		#define PWM1_CH3OUT				2,2
		#define PWM1_CH4OUT				2,3
		#define PWM1_CH5OUT				2,4
		#define PWM1_CH6OUT				2,5

		#define FUNC_PWM             0x1				/*!< Selects pin function 0x01 */

#endif /*defined(PUERTO x) */

/** Macros para identificar cada canal **/
#define CH0 0
#define CH1	1
#define CH2	2
#define CH3	3
#define CH4	4
#define CH5	5
#define CH6	6

/**********************************************************************
* MR register : macros
**********************************************************************/
/** Macro para obtener el bit de interrupcion de PWMMRx match, n = 0 to 3 */
#define PWM1_MATCH_INT_1(n) 	_BIT((n) & 0x0F)
/** Macro para obtener el bit de interrupcion de PWMMRx match, n = 4 to 6 */
#define PWM1_MATCH_INT_2(n)		_BIT((n<<4) & 0xF00)
/** Macro para configuracion de acciones ante el TC=MR **/
#define PWM1_MCR_I(n)			_BIT (1<< (n) )
#define PWM1_MCR_R(n)			_BIT (1<< (n+1) )
#define PWM1_MCR_S(n)			_BIT (1<< (n+2) )
/**********************************************************************
* TCR register : macros
**********************************************************************/
/** Macro para habilitar el TC y PC **/
#define PWM1_TCR_COUNTER_ENABLE 	1<<0
/** Macro para resetear sincronicamente el TC y PC **/
#define PWM1_TCR_RESET_ENABLE 		1<<1
/** Macro para habilitar el modo PWM **/
#define PWM1_TCR_PWM_ENABLE 		1<<3
/** Macro para no escribir en el bit 2 del registro **/
#define PWM1_TCR_BITMASK			0x0B

/**********************************************************************
* PCR register : macros
**********************************************************************/
#define PWM1_PCR_DOBLE_EDGE(n)		1<<n
#define PWM1_PCR_ENABLE_OUTPUT(n)	1<<(n+8)

/**********************************************************************
* LER register : macros
**********************************************************************/
#define PWM1_LER_ENABLE_MATCH(n)	1<<n


void PWM1_SelectChannel(LPC_PWM1_T *pPWM, uint32_t num);
void PWM1_EnableCounters(LPC_PWM1_T *pPWM);
void PWM1_ConfigMatch(LPC_PWM1_T *pPWM, uint8_t numchannel,uint8_t interr,uint8_t reset,uint8_t stop);
void PWM1_ResetCounters(LPC_PWM1_T *pPWM);
void PWM1_ControlChannel(LPC_PWM1_T *pPWM, uint8_t numchann,uint8_t modo_edge,uint8_t enable_out );
void PWM1_SetMatch(LPC_PWM1_T *pPWM, uint8_t numchann, uint32_t value);
void PWM1_ValuePrescale(LPC_PWM1_T *pPWM, uint32_t value);
void PWM1_GetMatch(LPC_PWM1_T *  pPWM, uint8_t numchann, uint32_t* value);
STATIC INLINE void PWM1_enableCLK (LPC_PWM1_T * pPWM)
{
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_PWM1);
	pPWM->PCR=0x0;
}
STATIC INLINE void PWM1_preescaleCLK( LPC_PWM1_T *pPWM, CHIP_SYSCTL_CLKDIV_T num )
{
	Chip_Clock_SetPCLKDiv(SYSCTL_PCLK_PWM1,num);
}
/**
 * @brief	Determine if a match interrupt is pending
 * @param	pPWM		: Pointer to timer IP register address
 * @param	matchnum	: Match interrupt number to check
 * @return	false if the interrupt is not pending, otherwise true
 */
STATIC INLINE bool PWM1_IntMatchPending(LPC_PWM1_T *pPWM, uint8_t matchnum)
{
	return (bool) (matchnum<4)? ((pPWM->IR & PWM1_MATCH_INT_1(matchnum)) !=0) : ( (pPWM->IR & PWM1_MATCH_INT_2(matchnum)) !=0 ) ;
}
/**
 * @brief	Limpia el bit de la interruption del match correspondiente
 * @param	pPWM		: Pointer to timer IP register address
 * @param	matchnum	: Match interrupt number to clear
 * @return	void
 */
STATIC INLINE void PWM1_IntClearPending(LPC_PWM1_T *pPWM, uint8_t matchnum)
{
	pPWM->IR |=( (matchnum<4)? PWM1_MATCH_INT_1(matchnum) : PWM1_MATCH_INT_2(matchnum) );
}
/**
 * @brief	Habilita el nuevo valor de Match que seteamos
 * @param	pPWM		: Pointer to timer IP register address
 * @param	numchannel	: Numero de canal de Match
 * @return	void
 */
STATIC INLINE void PWM1_EnableMatchValue(LPC_PWM1_T *pPWM, uint8_t numchannel)
{
	pPWM->LER|= (numchannel<7)? PWM1_LER_ENABLE_MATCH(numchannel): 0x00;
}


#endif /* defined(CHIP_LPC175X_6X) */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* MODULES_LPC1769_CHIP_INC_PWM1_17XX_40XX_H_ */
