/*******************************************************************************
* File Name: MSens_out.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_MSens_out_ALIASES_H) /* Pins MSens_out_ALIASES_H */
#define CY_PINS_MSens_out_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define MSens_out_0			(MSens_out__0__PC)
#define MSens_out_0_INTR	((uint16)((uint16)0x0001u << MSens_out__0__SHIFT))

#define MSens_out_INTR_ALL	 ((uint16)(MSens_out_0_INTR))

#endif /* End Pins MSens_out_ALIASES_H */


/* [] END OF FILE */
