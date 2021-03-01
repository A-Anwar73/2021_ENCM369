/*!*********************************************************************************************************************
@file user_app.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1Run(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u8 G_u8UserAppFlags;                             /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp_<type>" and be declared as static.
***********************************************************************************************************************/


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserAppInitialize(void)

@brief
Initializes the application's variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserAppInitialize(void)
{
    /* LED initialization */
    LATA = 0x80;
    
    /* Timer0 control register initialization to turn timer on, asynch mode, 16 bit
     * Fosc/4, 1:16 prescaler, 1:1postscaler */
    T0CON0 = 0x90;
    T0CON1 = 0x54;
    
} /* end UserAppInitialize() */

/*---------------------------------------------------------------------------------------------------------------------
 void TimeXus(u16 u16Microseconds)
 Sets Timer0 to count u16Microseconds
 
 Requires:
 - Timer0 configured such that each timer tick is 1 microsecond
 - u16Microseconds is the value in microseconds to time from 1 to 65535
 
 Promises:
 - Pre-loads TMr0H:L to clock out desired period
 - TMR0IF cleared
 - Timer0 enabled
 */
void TimeXus(u16 u16Microseconds)
{
    T0CON0 = 0x10;
    TMR0L = u16Microseconds & 0x00ff;
    TMR0H = (u16Microseconds & 0xff00) >> 8;
    PIR3 &= 0x7f;
    T0CON0 = 0x90;
}

/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserAppRun(void)

@brief Application code that runs once per system loop

Requires:
- 

Promises:
- 

*/
void UserAppRun(void)
{
    /*static u8 u8Counter = 0x00;
    u8Counter++;
    u8 u8Temp = LATA;
    u8Temp &= 0x80;
    u8Temp |= (u8Counter & 0x3f);
    LATA = u8Temp;*/
    static u16 u16Toggle = 0x0000;
    u16Toggle++;
    if(u16Toggle == 0x1f4)
    {
        u16Toggle &= 0x0000;
        LATA ^= 0x01; 
    }
    
} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
