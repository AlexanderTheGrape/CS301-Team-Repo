/*******************************************************************************
* File Name: FarLeftSensor.h  
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

#if !defined(CY_PINS_FarLeftSensor_H) /* Pins FarLeftSensor_H */
#define CY_PINS_FarLeftSensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "FarLeftSensor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 FarLeftSensor__PORT == 15 && ((FarLeftSensor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    FarLeftSensor_Write(uint8 value);
void    FarLeftSensor_SetDriveMode(uint8 mode);
uint8   FarLeftSensor_ReadDataReg(void);
uint8   FarLeftSensor_Read(void);
void    FarLeftSensor_SetInterruptMode(uint16 position, uint16 mode);
uint8   FarLeftSensor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the FarLeftSensor_SetDriveMode() function.
     *  @{
     */
        #define FarLeftSensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define FarLeftSensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define FarLeftSensor_DM_RES_UP          PIN_DM_RES_UP
        #define FarLeftSensor_DM_RES_DWN         PIN_DM_RES_DWN
        #define FarLeftSensor_DM_OD_LO           PIN_DM_OD_LO
        #define FarLeftSensor_DM_OD_HI           PIN_DM_OD_HI
        #define FarLeftSensor_DM_STRONG          PIN_DM_STRONG
        #define FarLeftSensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define FarLeftSensor_MASK               FarLeftSensor__MASK
#define FarLeftSensor_SHIFT              FarLeftSensor__SHIFT
#define FarLeftSensor_WIDTH              1u

/* Interrupt constants */
#if defined(FarLeftSensor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FarLeftSensor_SetInterruptMode() function.
     *  @{
     */
        #define FarLeftSensor_INTR_NONE      (uint16)(0x0000u)
        #define FarLeftSensor_INTR_RISING    (uint16)(0x0001u)
        #define FarLeftSensor_INTR_FALLING   (uint16)(0x0002u)
        #define FarLeftSensor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define FarLeftSensor_INTR_MASK      (0x01u) 
#endif /* (FarLeftSensor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FarLeftSensor_PS                     (* (reg8 *) FarLeftSensor__PS)
/* Data Register */
#define FarLeftSensor_DR                     (* (reg8 *) FarLeftSensor__DR)
/* Port Number */
#define FarLeftSensor_PRT_NUM                (* (reg8 *) FarLeftSensor__PRT) 
/* Connect to Analog Globals */                                                  
#define FarLeftSensor_AG                     (* (reg8 *) FarLeftSensor__AG)                       
/* Analog MUX bux enable */
#define FarLeftSensor_AMUX                   (* (reg8 *) FarLeftSensor__AMUX) 
/* Bidirectional Enable */                                                        
#define FarLeftSensor_BIE                    (* (reg8 *) FarLeftSensor__BIE)
/* Bit-mask for Aliased Register Access */
#define FarLeftSensor_BIT_MASK               (* (reg8 *) FarLeftSensor__BIT_MASK)
/* Bypass Enable */
#define FarLeftSensor_BYP                    (* (reg8 *) FarLeftSensor__BYP)
/* Port wide control signals */                                                   
#define FarLeftSensor_CTL                    (* (reg8 *) FarLeftSensor__CTL)
/* Drive Modes */
#define FarLeftSensor_DM0                    (* (reg8 *) FarLeftSensor__DM0) 
#define FarLeftSensor_DM1                    (* (reg8 *) FarLeftSensor__DM1)
#define FarLeftSensor_DM2                    (* (reg8 *) FarLeftSensor__DM2) 
/* Input Buffer Disable Override */
#define FarLeftSensor_INP_DIS                (* (reg8 *) FarLeftSensor__INP_DIS)
/* LCD Common or Segment Drive */
#define FarLeftSensor_LCD_COM_SEG            (* (reg8 *) FarLeftSensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define FarLeftSensor_LCD_EN                 (* (reg8 *) FarLeftSensor__LCD_EN)
/* Slew Rate Control */
#define FarLeftSensor_SLW                    (* (reg8 *) FarLeftSensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define FarLeftSensor_PRTDSI__CAPS_SEL       (* (reg8 *) FarLeftSensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define FarLeftSensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) FarLeftSensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define FarLeftSensor_PRTDSI__OE_SEL0        (* (reg8 *) FarLeftSensor__PRTDSI__OE_SEL0) 
#define FarLeftSensor_PRTDSI__OE_SEL1        (* (reg8 *) FarLeftSensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define FarLeftSensor_PRTDSI__OUT_SEL0       (* (reg8 *) FarLeftSensor__PRTDSI__OUT_SEL0) 
#define FarLeftSensor_PRTDSI__OUT_SEL1       (* (reg8 *) FarLeftSensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define FarLeftSensor_PRTDSI__SYNC_OUT       (* (reg8 *) FarLeftSensor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(FarLeftSensor__SIO_CFG)
    #define FarLeftSensor_SIO_HYST_EN        (* (reg8 *) FarLeftSensor__SIO_HYST_EN)
    #define FarLeftSensor_SIO_REG_HIFREQ     (* (reg8 *) FarLeftSensor__SIO_REG_HIFREQ)
    #define FarLeftSensor_SIO_CFG            (* (reg8 *) FarLeftSensor__SIO_CFG)
    #define FarLeftSensor_SIO_DIFF           (* (reg8 *) FarLeftSensor__SIO_DIFF)
#endif /* (FarLeftSensor__SIO_CFG) */

/* Interrupt Registers */
#if defined(FarLeftSensor__INTSTAT)
    #define FarLeftSensor_INTSTAT            (* (reg8 *) FarLeftSensor__INTSTAT)
    #define FarLeftSensor_SNAP               (* (reg8 *) FarLeftSensor__SNAP)
    
	#define FarLeftSensor_0_INTTYPE_REG 		(* (reg8 *) FarLeftSensor__0__INTTYPE)
#endif /* (FarLeftSensor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_FarLeftSensor_H */


/* [] END OF FILE */
