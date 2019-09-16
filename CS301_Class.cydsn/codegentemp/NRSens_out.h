/*******************************************************************************
* File Name: NRSens_out.h  
* Version 1.90
*
* Description:
*  This file containts Status Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_STATUS_REG_NRSens_out_H) /* CY_STATUS_REG_NRSens_out_H */
#define CY_STATUS_REG_NRSens_out_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} NRSens_out_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 NRSens_out_Read(void) ;
void NRSens_out_InterruptEnable(void) ;
void NRSens_out_InterruptDisable(void) ;
void NRSens_out_WriteMask(uint8 mask) ;
uint8 NRSens_out_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define NRSens_out_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define NRSens_out_INPUTS              1


/***************************************
*             Registers
***************************************/

/* Status Register */
#define NRSens_out_Status             (* (reg8 *) NRSens_out_sts_sts_reg__STATUS_REG )
#define NRSens_out_Status_PTR         (  (reg8 *) NRSens_out_sts_sts_reg__STATUS_REG )
#define NRSens_out_Status_Mask        (* (reg8 *) NRSens_out_sts_sts_reg__MASK_REG )
#define NRSens_out_Status_Aux_Ctrl    (* (reg8 *) NRSens_out_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_NRSens_out_H */


/* [] END OF FILE */
