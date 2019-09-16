/*******************************************************************************
* File Name: FRSens_out.h  
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

#if !defined(CY_STATUS_REG_FRSens_out_H) /* CY_STATUS_REG_FRSens_out_H */
#define CY_STATUS_REG_FRSens_out_H

#include "cytypes.h"
#include "CyLib.h"

    
/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 statusState;

} FRSens_out_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

uint8 FRSens_out_Read(void) ;
void FRSens_out_InterruptEnable(void) ;
void FRSens_out_InterruptDisable(void) ;
void FRSens_out_WriteMask(uint8 mask) ;
uint8 FRSens_out_ReadMask(void) ;


/***************************************
*           API Constants
***************************************/

#define FRSens_out_STATUS_INTR_ENBL    0x10u


/***************************************
*         Parameter Constants
***************************************/

/* Status Register Inputs */
#define FRSens_out_INPUTS              1


/***************************************
*             Registers
***************************************/

/* Status Register */
#define FRSens_out_Status             (* (reg8 *) FRSens_out_sts_sts_reg__STATUS_REG )
#define FRSens_out_Status_PTR         (  (reg8 *) FRSens_out_sts_sts_reg__STATUS_REG )
#define FRSens_out_Status_Mask        (* (reg8 *) FRSens_out_sts_sts_reg__MASK_REG )
#define FRSens_out_Status_Aux_Ctrl    (* (reg8 *) FRSens_out_sts_sts_reg__STATUS_AUX_CTL_REG )

#endif /* End CY_STATUS_REG_FRSens_out_H */


/* [] END OF FILE */
