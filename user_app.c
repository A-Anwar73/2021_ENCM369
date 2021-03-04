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
    
    /* Timer0 control register initialization to turn timer on, asynchronous mode, 16 bit
     * Fosc/4, 1:16 pre-scaler, 1:1post-scaler */
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
    /*Disabling the Timer*/
    T0CON0 &= 0x7f;
    
    /*Pre-loading TMR0H and TMROL*/
    u16 u16Timer = 0xffff - u16Microseconds;
    TMR0L = u16Timer & 0x00ff;
    TMR0H = (u8) ( (u16Timer & 0xff00) >> 8 );
    
    /*Clearing TMR0IF*/
    PIR3 &= 0x7f;
    
    /*Enabling Timer*/
    T0CON0 |= 0x80;
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
    static u16 u16Delay = 0x0000;
    
    /*variable used to index array*/
    static int intLedState = 0;
    
    u8 au8Pattern [6] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20};
    u16Delay++;
    
    /*After 500ms delay the pattern changes*/
    if(u16Delay == 500)
    {
       u16Delay = 0x0000;
       u8 u8Temp = LATA;
       
       /*Clearing 6 LSB's*/
       u8Temp &= 0x80;
       
       /*Updating LATA to display next pattern*/
       u8Temp |= au8Pattern[intLedState];
       LATA = u8Temp;
       intLedState++;
       
       /*Resets pattern to start repeating*/
       if(intLedState == 6)
       {
           intLedState = 0;
       }
    }
} /* end UserAppRun */



/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/





/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
