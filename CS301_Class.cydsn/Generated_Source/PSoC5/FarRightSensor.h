/*******************************************************************************
* File Name: FarRightSensor.h  
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

#if !defined(CY_PINS_FarRightSensor_H) /* Pins FarRightSensor_H */
#define CY_PINS_FarRightSensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FarRightSensor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FarRightSensor__PORT == 15 && ((FarRightSensor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FarRightSensor_Write(uint8 value);
void    FarRightSensor_SetDriveMode(uint8 mode);
uint8   FarRightSensor_ReadDataReg(void);
uint8   FarRightSensor_Read(void);
void    FarRightSensor_SetInterruptMode(uint16 position, uint16 mode);
uint8   FarRightSensor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FarRightSensor_SetDriveMode() function.
     *  @{
     */
        #define FarRightSensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FarRightSensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FarRightSensor_DM_RES_UP          PIN_DM_RES_UP
        #define FarRightSensor_DM_RES_DWN         PIN_DM_RES_DWN
        #define FarRightSensor_DM_OD_LO           PIN_DM_OD_LO
        #define FarRightSensor_DM_OD_HI           PIN_DM_OD_HI
        #define FarRightSensor_DM_STRONG          PIN_DM_STRONG
        #define FarRightSensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FarRightSensor_MASK               FarRightSensor__MASK
#define FarRightSensor_SHIFT              FarRightSensor__SHIFT
#define FarRightSensor_WIDTH              1u

/* Interrupt constants */
#if defined(FarRightSensor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FarRightSensor_SetInterruptMode() function.
     *  @{
     */
        #define FarRightSensor_INTR_NONE      (uint16)(0x0000u)
        #define FarRightSensor_INTR_RISING    (uint16)(0x0001u)
        #define FarRightSensor_INTR_FALLING   (uint16)(0x0002u)
        #define FarRightSensor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FarRightSensor_INTR_MASK      (0x01u) 
#endif /* (FarRightSensor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FarRightSensor_PS                     (* (reg8 *) FarRightSensor__PS)
/* Data Register */
#define FarRightSensor_DR                     (* (reg8 *) FarRightSensor__DR)
/* Port Number */
#define FarRightSensor_PRT_NUM                (* (reg8 *) FarRightSensor__PRT) 
/* Connect to Analog Globals */                                                  
#define FarRightSensor_AG                     (* (reg8 *) FarRightSensor__AG)                       
/* Analog MUX bux enable */
#define FarRightSensor_AMUX                   (* (reg8 *) FarRightSensor__AMUX) 
/* Bidirectional Enable */                                                        
#define FarRightSensor_BIE                    (* (reg8 *) FarRightSensor__BIE)
/* Bit-mask for Aliased Register Access */
#define FarRightSensor_BIT_MASK               (* (reg8 *) FarRightSensor__BIT_MASK)
/* Bypass Enable */
#define FarRightSensor_BYP                    (* (reg8 *) FarRightSensor__BYP)
/* Port wide control signals */                                                   
#define FarRightSensor_CTL                    (* (reg8 *) FarRightSensor__CTL)
/* Drive Modes */
#define FarRightSensor_DM0                    (* (reg8 *) FarRightSensor__DM0) 
#define FarRightSensor_DM1                    (* (reg8 *) FarRightSensor__DM1)
#define FarRightSensor_DM2                    (* (reg8 *) FarRightSensor__DM2) 
/* Input Buffer Disable Override */
#define FarRightSensor_INP_DIS                (* (reg8 *) FarRightSensor__INP_DIS)
/* LCD Common or Segment Drive */
#define FarRightSensor_LCD_COM_SEG            (* (reg8 *) FarRightSensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define FarRightSensor_LCD_EN                 (* (reg8 *) FarRightSensor__LCD_EN)
/* Slew Rate Control */
#define FarRightSensor_SLW                    (* (reg8 *) FarRightSensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FarRightSensor_PRTDSI__CAPS_SEL       (* (reg8 *) FarRightSensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FarRightSensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FarRightSensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FarRightSensor_PRTDSI__OE_SEL0        (* (reg8 *) FarRightSensor__PRTDSI__OE_SEL0) 
#define FarRightSensor_PRTDSI__OE_SEL1        (* (reg8 *) FarRightSensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FarRightSensor_PRTDSI__OUT_SEL0       (* (reg8 *) FarRightSensor__PRTDSI__OUT_SEL0) 
#define FarRightSensor_PRTDSI__OUT_SEL1       (* (reg8 *) FarRightSensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FarRightSensor_PRTDSI__SYNC_OUT       (* (reg8 *) FarRightSensor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FarRightSensor__SIO_CFG)
    #define FarRightSensor_SIO_HYST_EN        (* (reg8 *) FarRightSensor__SIO_HYST_EN)
    #define FarRightSensor_SIO_REG_HIFREQ     (* (reg8 *) FarRightSensor__SIO_REG_HIFREQ)
    #define FarRightSensor_SIO_CFG            (* (reg8 *) FarRightSensor__SIO_CFG)
    #define FarRightSensor_SIO_DIFF           (* (reg8 *) FarRightSensor__SIO_DIFF)
#endif /* (FarRightSensor__SIO_CFG) */

/* Interrupt Registers */
#if defined(FarRightSensor__INTSTAT)
    #define FarRightSensor_INTSTAT            (* (reg8 *) FarRightSensor__INTSTAT)
    #define FarRightSensor_SNAP               (* (reg8 *) FarRightSensor__SNAP)
    
	#define FarRightSensor_0_INTTYPE_REG 		(* (reg8 *) FarRightSensor__0__INTTYPE)
#endif /* (FarRightSensor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FarRightSensor_H */


/* [] END OF FILE */
