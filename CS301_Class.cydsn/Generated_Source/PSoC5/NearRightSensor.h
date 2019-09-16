/*******************************************************************************
* File Name: NearRightSensor.h  
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

#if !defined(CY_PINS_NearRightSensor_H) /* Pins NearRightSensor_H */
#define CY_PINS_NearRightSensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "NearRightSensor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 NearRightSensor__PORT == 15 && ((NearRightSensor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    NearRightSensor_Write(uint8 value);
void    NearRightSensor_SetDriveMode(uint8 mode);
uint8   NearRightSensor_ReadDataReg(void);
uint8   NearRightSensor_Read(void);
void    NearRightSensor_SetInterruptMode(uint16 position, uint16 mode);
uint8   NearRightSensor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the NearRightSensor_SetDriveMode() function.
     *  @{
     */
        #define NearRightSensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define NearRightSensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define NearRightSensor_DM_RES_UP          PIN_DM_RES_UP
        #define NearRightSensor_DM_RES_DWN         PIN_DM_RES_DWN
        #define NearRightSensor_DM_OD_LO           PIN_DM_OD_LO
        #define NearRightSensor_DM_OD_HI           PIN_DM_OD_HI
        #define NearRightSensor_DM_STRONG          PIN_DM_STRONG
        #define NearRightSensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define NearRightSensor_MASK               NearRightSensor__MASK
#define NearRightSensor_SHIFT              NearRightSensor__SHIFT
#define NearRightSensor_WIDTH              1u

/* Interrupt constants */
#if defined(NearRightSensor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in NearRightSensor_SetInterruptMode() function.
     *  @{
     */
        #define NearRightSensor_INTR_NONE      (uint16)(0x0000u)
        #define NearRightSensor_INTR_RISING    (uint16)(0x0001u)
        #define NearRightSensor_INTR_FALLING   (uint16)(0x0002u)
        #define NearRightSensor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define NearRightSensor_INTR_MASK      (0x01u) 
#endif /* (NearRightSensor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NearRightSensor_PS                     (* (reg8 *) NearRightSensor__PS)
/* Data Register */
#define NearRightSensor_DR                     (* (reg8 *) NearRightSensor__DR)
/* Port Number */
#define NearRightSensor_PRT_NUM                (* (reg8 *) NearRightSensor__PRT) 
/* Connect to Analog Globals */                                                  
#define NearRightSensor_AG                     (* (reg8 *) NearRightSensor__AG)                       
/* Analog MUX bux enable */
#define NearRightSensor_AMUX                   (* (reg8 *) NearRightSensor__AMUX) 
/* Bidirectional Enable */                                                        
#define NearRightSensor_BIE                    (* (reg8 *) NearRightSensor__BIE)
/* Bit-mask for Aliased Register Access */
#define NearRightSensor_BIT_MASK               (* (reg8 *) NearRightSensor__BIT_MASK)
/* Bypass Enable */
#define NearRightSensor_BYP                    (* (reg8 *) NearRightSensor__BYP)
/* Port wide control signals */                                                   
#define NearRightSensor_CTL                    (* (reg8 *) NearRightSensor__CTL)
/* Drive Modes */
#define NearRightSensor_DM0                    (* (reg8 *) NearRightSensor__DM0) 
#define NearRightSensor_DM1                    (* (reg8 *) NearRightSensor__DM1)
#define NearRightSensor_DM2                    (* (reg8 *) NearRightSensor__DM2) 
/* Input Buffer Disable Override */
#define NearRightSensor_INP_DIS                (* (reg8 *) NearRightSensor__INP_DIS)
/* LCD Common or Segment Drive */
#define NearRightSensor_LCD_COM_SEG            (* (reg8 *) NearRightSensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define NearRightSensor_LCD_EN                 (* (reg8 *) NearRightSensor__LCD_EN)
/* Slew Rate Control */
#define NearRightSensor_SLW                    (* (reg8 *) NearRightSensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define NearRightSensor_PRTDSI__CAPS_SEL       (* (reg8 *) NearRightSensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define NearRightSensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) NearRightSensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define NearRightSensor_PRTDSI__OE_SEL0        (* (reg8 *) NearRightSensor__PRTDSI__OE_SEL0) 
#define NearRightSensor_PRTDSI__OE_SEL1        (* (reg8 *) NearRightSensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define NearRightSensor_PRTDSI__OUT_SEL0       (* (reg8 *) NearRightSensor__PRTDSI__OUT_SEL0) 
#define NearRightSensor_PRTDSI__OUT_SEL1       (* (reg8 *) NearRightSensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define NearRightSensor_PRTDSI__SYNC_OUT       (* (reg8 *) NearRightSensor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(NearRightSensor__SIO_CFG)
    #define NearRightSensor_SIO_HYST_EN        (* (reg8 *) NearRightSensor__SIO_HYST_EN)
    #define NearRightSensor_SIO_REG_HIFREQ     (* (reg8 *) NearRightSensor__SIO_REG_HIFREQ)
    #define NearRightSensor_SIO_CFG            (* (reg8 *) NearRightSensor__SIO_CFG)
    #define NearRightSensor_SIO_DIFF           (* (reg8 *) NearRightSensor__SIO_DIFF)
#endif /* (NearRightSensor__SIO_CFG) */

/* Interrupt Registers */
#if defined(NearRightSensor__INTSTAT)
    #define NearRightSensor_INTSTAT            (* (reg8 *) NearRightSensor__INTSTAT)
    #define NearRightSensor_SNAP               (* (reg8 *) NearRightSensor__SNAP)
    
	#define NearRightSensor_0_INTTYPE_REG 		(* (reg8 *) NearRightSensor__0__INTTYPE)
#endif /* (NearRightSensor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_NearRightSensor_H */


/* [] END OF FILE */
