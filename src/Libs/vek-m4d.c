#include "vek-m4d.h"

char test_buffer[] = {0x02,0x03,0x03,0x02,0x51,0x01,0x04,0x56,0x04};

void writeTest(void){
    int i = 0;
    while(i<sizeof(test_buffer)){
        //while(!DRV_USART0_TransmitBufferIsFull);
        DRV_USART1_WriteByte(test_buffer[i]);
        //delay_ms(1000);
        i++;
    }    
}

int shortTelegram(int address, int control){
        char telegram[5];
        telegram[0] = DLE;
        telegram[1] = control;
        telegram[2] = address;
        telegram[3] = control + address;
        telegram[4] = EOT;
        int i = 0;
        while(i<strlen(telegram)){//sizeof?
            DRV_USART1_WriteByte(telegram[i]);
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
            DRV_USART1_WriteByte(telegram[i]);
            i++;
        }
}

int vekLoopStatus(int loopNumber){
    #define DATA_OFFSET 7
    int vekID = 0;
    int c = 0;
    char b[64];
    if(!U2STAbits.URXDA){//if rx buffer empty
        vekRequest(vekID, REQ_DATA, MASK_LOOP_STATUS);
        while(!U2STAbits.URXDA);//wait for rcv char
        while(U2STAbits.URXDA){//rcv till empty buffer
            
            b[c] = DRV_USART1_ReadByte();
            c++;
        }            
        b[c] = '\0';
        
        return b[loopNumber + DATA_OFFSET];
        
    }else
        return -1;
}