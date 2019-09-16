/*******************************************************************************
* File Name: NearLeftSensor.h  
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

#if !defined(CY_PINS_NearLeftSensor_H) /* Pins NearLeftSensor_H */
#define CY_PINS_NearLeftSensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "NearLeftSensor_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 NearLeftSensor__PORT == 15 && ((NearLeftSensor__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    NearLeftSensor_Write(uint8 value);
void    NearLeftSensor_SetDriveMode(uint8 mode);
uint8   NearLeftSensor_ReadDataReg(void);
uint8   NearLeftSensor_Read(void);
void    NearLeftSensor_SetInterruptMode(uint16 position, uint16 mode);
uint8   NearLeftSensor_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the NearLeftSensor_SetDriveMode() function.
     *  @{
     */
        #define NearLeftSensor_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define NearLeftSensor_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define NearLeftSensor_DM_RES_UP          PIN_DM_RES_UP
        #define NearLeftSensor_DM_RES_DWN         PIN_DM_RES_DWN
        #define NearLeftSensor_DM_OD_LO           PIN_DM_OD_LO
        #define NearLeftSensor_DM_OD_HI           PIN_DM_OD_HI
        #define NearLeftSensor_DM_STRONG          PIN_DM_STRONG
        #define NearLeftSensor_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define NearLeftSensor_MASK               NearLeftSensor__MASK
#define NearLeftSensor_SHIFT              NearLeftSensor__SHIFT
#define NearLeftSensor_WIDTH              1u

/* Interrupt constants */
#if defined(NearLeftSensor__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in NearLeftSensor_SetInterruptMode() function.
     *  @{
     */
        #define NearLeftSensor_INTR_NONE      (uint16)(0x0000u)
        #define NearLeftSensor_INTR_RISING    (uint16)(0x0001u)
        #define NearLeftSensor_INTR_FALLING   (uint16)(0x0002u)
        #define NearLeftSensor_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define NearLeftSensor_INTR_MASK      (0x01u) 
#endif /* (NearLeftSensor__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NearLeftSensor_PS                     (* (reg8 *) NearLeftSensor__PS)
/* Data Register */
#define NearLeftSensor_DR                     (* (reg8 *) NearLeftSensor__DR)
/* Port Number */
#define NearLeftSensor_PRT_NUM                (* (reg8 *) NearLeftSensor__PRT) 
/* Connect to Analog Globals */                                                  
#define NearLeftSensor_AG                     (* (reg8 *) NearLeftSensor__AG)                       
/* Analog MUX bux enable */
#define NearLeftSensor_AMUX                   (* (reg8 *) NearLeftSensor__AMUX) 
/* Bidirectional Enable */                                                        
#define NearLeftSensor_BIE                    (* (reg8 *) NearLeftSensor__BIE)
/* Bit-mask for Aliased Register Access */
#define NearLeftSensor_BIT_MASK               (* (reg8 *) NearLeftSensor__BIT_MASK)
/* Bypass Enable */
#define NearLeftSensor_BYP                    (* (reg8 *) NearLeftSensor__BYP)
/* Port wide control signals */                                                   
#define NearLeftSensor_CTL                    (* (reg8 *) NearLeftSensor__CTL)
/* Drive Modes */
#define NearLeftSensor_DM0                    (* (reg8 *) NearLeftSensor__DM0) 
#define NearLeftSensor_DM1                    (* (reg8 *) NearLeftSensor__DM1)
#define NearLeftSensor_DM2                    (* (reg8 *) NearLeftSensor__DM2) 
/* Input Buffer Disable Override */
#define NearLeftSensor_INP_DIS                (* (reg8 *) NearLeftSensor__INP_DIS)
/* LCD Common or Segment Drive */
#define NearLeftSensor_LCD_COM_SEG            (* (reg8 *) NearLeftSensor__LCD_COM_SEG)
/* Enable Segment LCD */
#define NearLeftSensor_LCD_EN                 (* (reg8 *) NearLeftSensor__LCD_EN)
/* Slew Rate Control */
#define NearLeftSensor_SLW                    (* (reg8 *) NearLeftSensor__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define NearLeftSensor_PRTDSI__CAPS_SEL       (* (reg8 *) NearLeftSensor__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define NearLeftSensor_PRTDSI__DBL_SYNC_IN    (* (reg8 *) NearLeftSensor__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define NearLeftSensor_PRTDSI__OE_SEL0        (* (reg8 *) NearLeftSensor__PRTDSI__OE_SEL0) 
#define NearLeftSensor_PRTDSI__OE_SEL1        (* (reg8 *) NearLeftSensor__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define NearLeftSensor_PRTDSI__OUT_SEL0       (* (reg8 *) NearLeftSensor__PRTDSI__OUT_SEL0) 
#define NearLeftSensor_PRTDSI__OUT_SEL1       (* (reg8 *) NearLeftSensor__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define NearLeftSensor_PRTDSI__SYNC_OUT       (* (reg8 *) NearLeftSensor__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(NearLeftSensor__SIO_CFG)
    #define NearLeftSensor_SIO_HYST_EN        (* (reg8 *) NearLeftSensor__SIO_HYST_EN)
    #define NearLeftSensor_SIO_REG_HIFREQ     (* (reg8 *) NearLeftSensor__SIO_REG_HIFREQ)
    #define NearLeftSensor_SIO_CFG            (* (reg8 *) NearLeftSensor__SIO_CFG)
    #define NearLeftSensor_SIO_DIFF           (* (reg8 *) NearLeftSensor__SIO_DIFF)
#endif /* (NearLeftSensor__SIO_CFG) */

/* Interrupt Registers */
#if defined(NearLeftSensor__INTSTAT)
    #define NearLeftSensor_INTSTAT            (* (reg8 *) NearLeftSensor__INTSTAT)
    #define NearLeftSensor_SNAP               (* (reg8 *) NearLeftSensor__SNAP)
    
	#define NearLeftSensor_0_INTTYPE_REG 		(* (reg8 *) NearLeftSensor__0__INTTYPE)
#endif /* (NearLeftSensor__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_NearLeftSensor_H */


/* [] END OF FILE */
