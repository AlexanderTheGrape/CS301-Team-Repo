/*******************************************************************************
* File Name: Timer_Deadzone_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Deadzone.h"

static Timer_Deadzone_backupStruct Timer_Deadzone_backup;


/*******************************************************************************
* Function Name: Timer_Deadzone_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Deadzone_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Deadzone_SaveConfig(void) 
{
    #if (!Timer_Deadzone_UsingFixedFunction)
        Timer_Deadzone_backup.TimerUdb = Timer_Deadzone_ReadCounter();
        Timer_Deadzone_backup.InterruptMaskValue = Timer_Deadzone_STATUS_MASK;
        #if (Timer_Deadzone_UsingHWCaptureCounter)
            Timer_Deadzone_backup.TimerCaptureCounter = Timer_Deadzone_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Deadzone_UDB_CONTROL_REG_REMOVED)
            Timer_Deadzone_backup.TimerControlRegister = Timer_Deadzone_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Deadzone_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Deadzone_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Deadzone_RestoreConfig(void) 
{   
    #if (!Timer_Deadzone_UsingFixedFunction)

        Timer_Deadzone_WriteCounter(Timer_Deadzone_backup.TimerUdb);
        Timer_Deadzone_STATUS_MASK =Timer_Deadzone_backup.InterruptMaskValue;
        #if (Timer_Deadzone_UsingHWCaptureCounter)
            Timer_Deadzone_SetCaptureCount(Timer_Deadzone_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Deadzone_UDB_CONTROL_REG_REMOVED)
            Timer_Deadzone_WriteControlRegister(Timer_Deadzone_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Deadzone_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Deadzone_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Deadzone_Sleep(void) 
{
    #if(!Timer_Deadzone_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Deadzone_CTRL_ENABLE == (Timer_Deadzone_CONTROL & Timer_Deadzone_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Deadzone_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Deadzone_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Deadzone_Stop();
    Timer_Deadzone_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Deadzone_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Deadzone_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Deadzone_Wakeup(void) 
{
    Timer_Deadzone_RestoreConfig();
    #if(!Timer_Deadzone_UDB_CONTROL_REG_REMOVED)
        if(Timer_Deadzone_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Deadzone_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
