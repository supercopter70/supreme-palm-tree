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
static uint8_t vekLoopState;
static uint8_t app_tx_buf[] = "*** SUPERCOPTER ***";
static uint8_t app_rx_buf[10];

static enum 
{
    USART_BM_INIT,
    USART_BM_SEND_MSG,
    USART_BM_ECHO,
    USART_BM_DONE
} usartBMState;

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
    switch (usartBMState)
    {
        default:
        case USART_BM_INIT:
        {
            cpatData.tx_count = 0;
            cpatData.rx_count = 0;
            usartBMState = USART_BM_SEND_MSG;
        }break;

        case USART_BM_SEND_MSG:
        {
            if (cpatData.tx_count < sizeof(app_tx_buf)) 
            {
                if(!DRV_USART_TransmitBufferIsFull(cpatData.handleUSART0))
                {
                    DRV_USART_WriteByte(cpatData.handleUSART0, app_tx_buf[cpatData.tx_count]);
                    cpatData.tx_count++;
                }
            }
            //LCD_writeString("ASD");

            /* Have we finished sending message? */
            if (cpatData.tx_count == sizeof(app_tx_buf))
            {
                usartBMState = USART_BM_ECHO;
            }
        }break;

        case USART_BM_ECHO:
        {
            if (cpatData.rx_count < sizeof(app_rx_buf)) 
            {
                if(!DRV_USART_ReceiverBufferIsEmpty(cpatData.handleUSART1))
                {
                    /* Read the received character */
                    app_rx_buf[cpatData.rx_count] = DRV_USART_ReadByte(cpatData.handleUSART1);
                
                    /* Echo back the received character */                
                    if(!DRV_USART_TransmitBufferIsFull(cpatData.handleUSART0))
                    {
                        DRV_USART_WriteByte(cpatData.handleUSART0, app_rx_buf[cpatData.rx_count]);
                    }
                    cpatData.rx_count++;    
                }
            }
            /* Have we finished character echo? */
            if (cpatData.rx_count == sizeof(app_rx_buf))
            {
                usartBMState = USART_BM_DONE;
            }
        }break;

        case USART_BM_DONE:
        {
            LEDrToggle();
            cpatData.tx_count = 0;
            cpatData.rx_count = 0;
            usartBMState = USART_BM_ECHO;
        }break;
    }
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
    cpatData.handleUSART0 = DRV_HANDLE_INVALID;
    cpatData.handleUSART1 = DRV_HANDLE_INVALID;
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
            if (cpatData.handleUSART0 == DRV_HANDLE_INVALID)
            {
                cpatData.handleUSART0 = DRV_USART_Open(1, DRV_IO_INTENT_READWRITE|DRV_IO_INTENT_NONBLOCKING);
                appInitialized &= ( DRV_HANDLE_INVALID != cpatData.handleUSART0 );
            }
            
            if (cpatData.handleUSART1 == DRV_HANDLE_INVALID)
            {
                cpatData.handleUSART1 = DRV_USART_Open(0, DRV_IO_INTENT_READWRITE|DRV_IO_INTENT_NONBLOCKING);
                appInitialized &= ( DRV_HANDLE_INVALID != cpatData.handleUSART0 );
            }        
            if (appInitialized)
            {
                /* initialize the USART state machine */
                usartBMState = USART_BM_INIT;
                cpatData.state = CPAT_STATE_SERVICE_TASKS;
            }
            break;
        }

        case CPAT_STATE_SERVICE_TASKS:
        {
            USART_Task();
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
