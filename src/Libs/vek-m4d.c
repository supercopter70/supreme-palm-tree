#include "vek-m4d.h"

VEK_DATA vekData;

int shortTelegram(int address, int control){
        char telegram[5];
        telegram[0] = DLE;
        telegram[1] = control;
        telegram[2] = address;
        telegram[3] = control + address;
        telegram[4] = EOT;
        int i = 0;
        while(i<strlen(telegram)){//sizeof?
            DRV_USART_WriteByte(vekData.handleRS485, telegram[i]);
            i++;
        }
}

int vekRequest(int address, int control, int data){
        int size = 3;
        char telegram[size + 6];

        telegram[0] = STX;
        telegram[1] = size;
        telegram[2] = size;
        telegram[3] = STX;
        telegram[4] = control;
        telegram[5] = address;
        telegram[6] = data;
        telegram[7] = control + address + data;
        telegram[8] = EOT;
        int i = 0;
        while(i<(size+6)){//sizeof?
            DRV_USART_WriteByte(vekData.handleRS485, telegram[i]);
            i++;
        }
}

int vekResponse(){
    vekData.rx_count = 0;
    bool DataLeft = 0;
    if(!DRV_USART_ReceiverBufferIsEmpty(vekData.handleRS485))
        DataLeft = 1;
    while (DataLeft){
        vekData.vek_rx_buffer[vekData.rx_count] = DRV_USART_ReadByte(vekData.handleRS485);
    }
}

void VEK_Initialize(void){
    vekData.state = VEK_INIT;
    vekData.handleRS485 = DRV_HANDLE_INVALID;
    vekLoopState = 0b00000000;
    vekLoopLastState = vekLoopState;
}

void VEK_Task(void){
    switch (vekData.state)
    {
        default:
        case VEK_INIT:
        {
            int vekialized = 1;
            vekData.rx_count = 0;
            if (vekData.handleRS485 == DRV_HANDLE_INVALID)
            {
                vekData.handleRS485 = DRV_USART_Open(0, DRV_IO_INTENT_READWRITE|DRV_IO_INTENT_NONBLOCKING);
                vekialized &= ( DRV_HANDLE_INVALID != vekData.handleRS485 );
            }        
            if (vekialized)
            {
                vekData.state = VEK_IDLE;
            }    
        }break;
        case VEK_IDLE:
        {
            
            LEDgToggle();
        }break;
        case VEK_REQUEST:
        {
            vekRequest(vekData.vekID, vekData.ctl, vekData.param);
            vekData.state = VEK_RESPONSE;  
        }break;
         case VEK_RESPONSE:
        {       

        }break;
        
        case VEK_DATA_GET:
        {
            LEDwToggle();
            vekData.rx_count = 0;
            vekData.state = VEK_IDLE;
        }break;
    }
}

void vekDataProcess(){
    vekLoopLastState = vekLoopState;
}

void vekLoopStatusRequest(int vekID){
    vekData.vekID = vekID;
    vekData.ctl = REQ_DATA;
    vekData.param = MASK_LOOP_STATUS;
    vekData.state = VEK_REQUEST;
}

void vekLoopShow(){
    char txt[17];
    if(vekLoopState != vekLoopLastState){
        LCD_Clear();
        LCD_gotoLine1();
        LCD_writeString("1 2 3 4 5 6 7 8");
        sprintf(txt, "%01x %01x %01x %01x %01x %01x %01x %01x", (vekLoopState & 0x80)>>7, (vekLoopState & 0x40)>>6, (vekLoopState & 0x20)>>5, (vekLoopState & 0x10)>>4, (vekLoopState & 0x08)>>3, (vekLoopState & 0x04)>>2, (vekLoopState & 0x02)>>1, (vekLoopState & 0x01)>>0);
        LCD_gotoLine2();
        LCD_writeString(txt);
    }
}

void vekLoopStatusGet(int loopNr){
    
}