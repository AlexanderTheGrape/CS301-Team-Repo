/*******************************************************************************
* File Name: NRSens_out.c  
* Version 1.90
*
* Description:
*  This file contains API to enable firmware to read the value of a Status 
*  Register.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "NRSens_out.h"

#if !defined(NRSens_out_sts_sts_reg__REMOVED) /* Check for removal by optimization */


/*******************************************************************************
* Function Name: NRSens_out_Read
********************************************************************************
*
* Summary:
*  Reads the current value assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The current value in the Status Register.
*
*******************************************************************************/
uint8 NRSens_out_Read(void) 
{ 
    return NRSens_out_Status;
}


/*******************************************************************************
* Function Name: NRSens_out_InterruptEnable
********************************************************************************
*
* Summary:
*  Enables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void NRSens_out_InterruptEnable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    NRSens_out_Status_Aux_Ctrl |= NRSens_out_STATUS_INTR_ENBL;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: NRSens_out_InterruptDisable
********************************************************************************
*
* Summary:
*  Disables the Status Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void NRSens_out_InterruptDisable(void) 
{
    uint8 interruptState;
    interruptState = CyEnterCriticalSection();
    NRSens_out_Status_Aux_Ctrl &= (uint8)(~NRSens_out_STATUS_INTR_ENBL);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: NRSens_out_WriteMask
********************************************************************************
*
* Summary:
*  Writes the current mask value assigned to the Status Register.
*
* Parameters:
*  mask:  Value to write into the mask register.
*
* Return:
*  None.
*
*******************************************************************************/
void NRSens_out_WriteMask(uint8 mask) 
{
    #if(NRSens_out_INPUTS < 8u)
    	mask &= ((uint8)(1u << NRSens_out_INPUTS) - 1u);
	#endif /* End NRSens_out_INPUTS < 8u */
    NRSens_out_Status_Mask = mask;
}


/*******************************************************************************
* Function Name: NRSens_out_ReadMask
********************************************************************************
*
* Summary:
*  Reads the current interrupt mask assigned to the Status Register.
*
* Parameters:
*  None.
*
* Return:
*  The value of the interrupt mask of the Status Register.
*
*******************************************************************************/
uint8 NRSens_out_ReadMask(void) 
{
    return NRSens_out_Status_Mask;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
