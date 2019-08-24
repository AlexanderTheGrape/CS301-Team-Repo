/*******************************************************************************
* File Name: button_pin.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_button_pin_H) /* Pins button_pin_H */
#define CY_PINS_button_pin_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "button_pin_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 button_pin__PORT == 15 && ((button_pin__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    button_pin_Write(uint8 value);
void    button_pin_SetDriveMode(uint8 mode);
uint8   button_pin_ReadDataReg(void);
uint8   button_pin_Read(void);
void    button_pin_SetInterruptMode(uint16 position, uint16 mode);
uint8   button_pin_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the button_pin_SetDriveMode() function.
     *  @{
     */
        #define button_pin_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define button_pin_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define button_pin_DM_RES_UP          PIN_DM_RES_UP
        #define button_pin_DM_RES_DWN         PIN_DM_RES_DWN
        #define button_pin_DM_OD_LO           PIN_DM_OD_LO
        #define button_pin_DM_OD_HI           PIN_DM_OD_HI
        #define button_pin_DM_STRONG          PIN_DM_STRONG
        #define button_pin_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define button_pin_MASK               button_pin__MASK
#define button_pin_SHIFT              button_pin__SHIFT
#define button_pin_WIDTH              1u

/* Interrupt constants */
#if defined(button_pin__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in button_pin_SetInterruptMode() function.
     *  @{
     */
        #define button_pin_INTR_NONE      (uint16)(0x0000u)
        #define button_pin_INTR_RISING    (uint16)(0x0001u)
        #define button_pin_INTR_FALLING   (uint16)(0x0002u)
        #define button_pin_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define button_pin_INTR_MASK      (0x01u) 
#endif /* (button_pin__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define button_pin_PS                     (* (reg8 *) button_pin__PS)
/* Data Register */
#define button_pin_DR                     (* (reg8 *) button_pin__DR)
/* Port Number */
#define button_pin_PRT_NUM                (* (reg8 *) button_pin__PRT) 
/* Connect to Analog Globals */                                                  
#define button_pin_AG                     (* (reg8 *) button_pin__AG)                       
/* Analog MUX bux enable */
#define button_pin_AMUX                   (* (reg8 *) button_pin__AMUX) 
/* Bidirectional Enable */                                                        
#define button_pin_BIE                    (* (reg8 *) button_pin__BIE)
/* Bit-mask for Aliased Register Access */
#define button_pin_BIT_MASK               (* (reg8 *) button_pin__BIT_MASK)
/* Bypass Enable */
#define button_pin_BYP                    (* (reg8 *) button_pin__BYP)
/* Port wide control signals */                                                   
#define button_pin_CTL                    (* (reg8 *) button_pin__CTL)
/* Drive Modes */
#define button_pin_DM0                    (* (reg8 *) button_pin__DM0) 
#define button_pin_DM1                    (* (reg8 *) button_pin__DM1)
#define button_pin_DM2                    (* (reg8 *) button_pin__DM2) 
/* Input Buffer Disable Override */
#define button_pin_INP_DIS                (* (reg8 *) button_pin__INP_DIS)
/* LCD Common or Segment Drive */
#define button_pin_LCD_COM_SEG            (* (reg8 *) button_pin__LCD_COM_SEG)
/* Enable Segment LCD */
#define button_pin_LCD_EN                 (* (reg8 *) button_pin__LCD_EN)
/* Slew Rate Control */
#define button_pin_SLW                    (* (reg8 *) button_pin__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define button_pin_PRTDSI__CAPS_SEL       (* (reg8 *) button_pin__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define button_pin_PRTDSI__DBL_SYNC_IN    (* (reg8 *) button_pin__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define button_pin_PRTDSI__OE_SEL0        (* (reg8 *) button_pin__PRTDSI__OE_SEL0) 
#define button_pin_PRTDSI__OE_SEL1        (* (reg8 *) button_pin__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define button_pin_PRTDSI__OUT_SEL0       (* (reg8 *) button_pin__PRTDSI__OUT_SEL0) 
#define button_pin_PRTDSI__OUT_SEL1       (* (reg8 *) button_pin__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define button_pin_PRTDSI__SYNC_OUT       (* (reg8 *) button_pin__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(button_pin__SIO_CFG)
    #define button_pin_SIO_HYST_EN        (* (reg8 *) button_pin__SIO_HYST_EN)
    #define button_pin_SIO_REG_HIFREQ     (* (reg8 *) button_pin__SIO_REG_HIFREQ)
    #define button_pin_SIO_CFG            (* (reg8 *) button_pin__SIO_CFG)
    #define button_pin_SIO_DIFF           (* (reg8 *) button_pin__SIO_DIFF)
#endif /* (button_pin__SIO_CFG) */

/* Interrupt Registers */
#if defined(button_pin__INTSTAT)
    #define button_pin_INTSTAT            (* (reg8 *) button_pin__INTSTAT)
    #define button_pin_SNAP               (* (reg8 *) button_pin__SNAP)
    
	#define button_pin_0_INTTYPE_REG 		(* (reg8 *) button_pin__0__INTTYPE)
#endif /* (button_pin__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_button_pin_H */


/* [] END OF FILE */
