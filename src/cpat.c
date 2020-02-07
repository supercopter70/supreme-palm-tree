/*******************************************************************************
 CONTAPAT
  
  Company:
    PAT-Traffic.
  
  File Name:
    cpat.c

  Summary:
    Contador de vehículos.

  Description:
    Contador de vehículos con RTC interno y externo, tarjeta micro sd,
    puerto rs485, y otros lujos.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2019-2020 PAT-Traffic.  All rights reserved.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files 
// *****************************************************************************
// *****************************************************************************

#include "cpat.h"
#include "Libs/LCD-Serial.h"
#include "Libs/vek-m4d.h"

// *****************************************************************************
// *****************************************************************************
// Section: Global Data Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    This structure should be initialized by the APP_Initialize function.
    
    Application strings and buffers are be defined outside this structure.
*/

CPAT_DATA cpatData;
static uint8_t app_tx_buf[] = "*** SUPERCOPTER ***";
static uint8_t app_rx_buf[10];

int c = 0;
int d = 0;


// *****************************************************************************
// *****************************************************************************
// Section: Application Callback Functions
// *****************************************************************************
// *****************************************************************************

/* TODO:  Add any necessary callback functions.
*/

// *****************************************************************************
// *****************************************************************************
// Section: Application Local Functions
// *****************************************************************************
// *****************************************************************************


static void USART_Task (void)
{

}

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void CPAT_Initialize ( void )

  Remarks:
    See prototype in cpat.h.
 */

void CPAT_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    cpatData.state = CPAT_STATE_INIT;
    cpatData.handleSerial = DRV_HANDLE_INVALID;
    LCD_Clear();
    LCD_writeString("$");
    c = 0;
    d = 0;
}


/******************************************************************************
  Function:
    void CPAT_Tasks ( void )

  Remarks:
    See prototype in cpat.h.
 */

void CPAT_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( cpatData.state )
    {
        /* Application's initial state. */
        case CPAT_STATE_INIT:
        {
            bool appInitialized = true;
            if (cpatData.handleSerial == DRV_HANDLE_INVALID)
            {
                cpatData.handleSerial = DRV_USART_Open(1, DRV_IO_INTENT_READWRITE|DRV_IO_INTENT_NONBLOCKING);
                appInitialized &= ( DRV_HANDLE_INVALID != cpatData.handleSerial );
            }
            if (appInitialized)
            {
                /* initialize the USART state machine */
                cpatData.state = CPAT_STATE_SERVICE_TASKS;
            }
            break;
        }

        case CPAT_STATE_SERVICE_TASKS:
        {
            //USART_Task();
            //delay_ms(2);
            c++;
            d++;
            if(c>=10){
                //vekLoopStatusRequest(0x02);//Hacer Autoscan
                c=0;
                vekLoopState = 0x55;
            }
            if(d>=15){
                //vekLoopStatusRequest(0x02);//Hacer Autoscan
                d=0;
                vekLoopState = 0xaa;
            }
            delay_ms(100);
            vekLoopShow();
            vekDataProcess();
            break;
        }
        /* The default state should never be executed. */
        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

 

/*******************************************************************************
 End of File
 */
