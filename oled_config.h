// adapter for PIC-IOT WG board mikroBUS socket
#define OLED_CS(state)      LATAbits.LATA0 = state // CS
#define OLED_DC(state)      LATCbits.LATC6 = state // PWM
#define OLED_RST(state)     LATBbits.LATB15 = state // RST
#define SPI_Write(data)     spiMaster[OLED].exchangeByte(data)
