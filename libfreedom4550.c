// Libreria di funzioni di base per scheda FREEDOM II & PIC18F4550
//  Versione 0.98                      25/Apr/2015
// rispetto alla versione 0.96 sono state aggiunte le funzioni per I2C
// rispetto alla versione 0.96 e' stata migliorata  la funzione OpenRS232()
// rispetto alla versione 0.9 e' stata aggiunta la funzione OpenRS232()


#include <xc.h>
#include <string.h>
//#include <plib/usart.h>
#include "libfreedom4550.h"
//#include "ConfigBits.h"
//#include "i2c.h"
#include <pic18f45k50.h>

#include "mcc_generated_files/mcc.h"

#define _XTAL_FREQ 48000000L

int piglias1 (int numero)  //oggennto raggiungibile max #48
{
    int passi,passiperspostamento=159;
    
    
    passi=passiperspostamento;
    if (numero==6) {passi=passiperspostamento+(4*passiperspostamento);}
    if (numero==27) {passi=passiperspostamento+(4*passiperspostamento);}
    
    numero++;
    
    movey (passi,500,1);
    return(numero);
}
void movex (int passi , int delay , int direzione)
{
    int x;
    int rallentatore;
    int contapassi=0;
    int contapassi2=0;
    if (direzione==1)
    {
        LATAbits.LA1=1;
        for(x=0;x<passi;x++)
            {
            if (contapassi<=100){rallentatore=delay-contapassi*5;}
            if (contapassi>100) {rallentatore=0;}
            if (contapassi>=passi-100) 
            {
                rallentatore=delay+contapassi2*5;
                contapassi2++;
            }
                LATAbits.LA0=1;
                    delay_us(delay+rallentatore);
                LATAbits.LA0=0;  
                    delay_us(delay+rallentatore);
                    contapassi++;
            }
        }
    if (direzione==0)
    {
        LATAbits.LA1=0;
        for(x=0;x<passi;x++)
            {
            if (contapassi<=100){rallentatore=delay-contapassi*5;}
            if (contapassi>100) {rallentatore=0;}
            if (contapassi>=passi-100) 
            {
                rallentatore=delay+contapassi2*5;
                contapassi2++;
            }
                LATAbits.LA0=1;
                    delay_us(delay+rallentatore);
                LATAbits.LA0=0;
                    delay_us(delay+rallentatore);
                    contapassi++;
            }
    }
}


void movey (int passi , int delay , int direzione)
{
    int x;
    
    if (direzione==1)
    {
        LATAbits.LA3=1;
        for(x=0;x<passi;x++)
            {
                LATAbits.LA2=1;
                    delay_us(delay);
                LATAbits.LA2=0;
                    delay_us(delay);
            }
        }
    if (direzione==0)
    {
        LATAbits.LA3=0;
        for(x=0;x<passi;x++)
            {
                LATAbits.LA2=1;
                    delay_us(delay);
                LATAbits.LA2=0;
                    delay_us(delay);
            }
    }
}


void movez (int passi , int delay , int direzione)
{
    int x;
    
    if (direzione==1)
    {
        LATAbits.LA5=1;
        for(x=0;x<passi;x++)
            {
                LATAbits.LA4=1;
                    delay_us(delay);
                LATAbits.LA4=0;
                    delay_us(delay);
            }
        }
    if (direzione==0)
    {
        LATAbits.LA5=0;
        for(x=0;x<passi;x++)
            {
                LATAbits.LA4=1;
                    delay_us(delay);
                LATAbits.LA4=0;
                    delay_us(delay);
            }
    }
}



// Funzione per generare un ritardo di T millisecondi
// <in> T  [0...65535]   rappresenta il numero di ms da ritardare
void delay_ms(unsigned int T)
{
    unsigned int N_ms; // indice per ciclo ms

    for  (N_ms=0; N_ms<T; N_ms++){
        // ritarda di 1 ms cioè 1000 usecondi
        _delay((unsigned long)(_XTAL_FREQ/4000.0));

    }

    
}


// Funzione per generare un ritardo di T microsecondi
// <in> T  [0...65535]   rappresenta il numero di ms da ritardare
void delay_us(unsigned int T)
{
    unsigned int N_us; // indice per ciclo ms

    for  (N_us=0; N_us<T; N_us++){
        // ritarda di 1 ms cioè 1000 usecondi
        _delay((unsigned long)(_XTAL_FREQ/4000000.0));
    }
}

//////////////////////////////////////////////////////////////////////////////////
//
///* ========== VERSIONE PER FREEDOM II , PIC18F4550 e compilatore XC8 ======= */
///* versione 1.0   -  21/07/2011 - prof. Vicenzi Giuliano   */
//
////   Rispetto alla versione per schedaPIC è stata modificata
//// 1) Gestione dei PIN di I/O poichè la FREEDOM usa solo PORT-D
////    per gestire sia DATA/Command Per DISPLAY che segnal idi controllo
//// 2) GOTORC: modificato calcolo indirizzi per 3a e 4a riga
//
// 
//
//// ==============================================================================
////  ATTENZIONE OCCORRE METTERE IN OUT TUTTI I PIN del PORT-D
//// ==============================================================================
//
//
//// segnali di Read/Write, Register Select e Enable dell' LCD
//#define LCD_RW_LINE LATDbits.LD1
//#define LCD_RS_LINE LATDbits.LD2
//#define LCD_EN_LINE LATDbits.LD3
//
//
//// funzione per inizializzarre il display a 4 BIT (i più significativi della porta d)
//void lcd_initialize4( unsigned char size , unsigned char Formato)
///* Initialises the display incase the initialisation at startup failed or the */
///*  cursor size is to be changed. 'size' is LCD_SIZE_SMALL or LCD_SIZE_LARGE  */
//{
//   char i;
//   unsigned char NibbleLowD=0;
//   unsigned char RW_Line = 0x02;
//   unsigned char RS_Line = 0x04;
//   unsigned char EN_Line = 0x08;
//
//   // LCD_RW_LINE = 00000010
//   // LCD_RS_LINE = 00000100
//   // LCD_EN_LINE = 00001000
//   //SET_TRIS_D( 0x00 );
//   LATD=0;
//   TRISD=0;
//
//    GFormato=Formato;
//    if (Formato==R1C20) {GNRighe=1;GNCol=20;}
//    if (Formato==R1C40) {GNRighe=1;GNCol=40;}
//
//    if (Formato==R2C20) {GNRighe=2;GNCol=20;}
//    if (Formato==R2C40) {GNRighe=2;GNCol=40;}
//
//    if (Formato==R4C20) {GNRighe=4;GNCol=20;}
//
//    // LCD_RW_LINE (D1);  Register Read/WRITE line
//    // LCD_RS_LINE (D2);  Register Select line command or character
//    // LCD_EN_LINE (D3);  Enable device, high-low to clock data
//
//    //output_low( LCD_RW_LINE );   output_low( PIN_D1 );   NibbleLowD=NibbleLowD & (~RW_Line);
//    LCD_RW_LINE=0;
//    NibbleLowD=NibbleLowD & (~RW_Line);
//
//    //output_low( LCD_RS_LINE );   NibbleLowD=NibbleLowD & (~RS_Line);
//    LCD_RS_LINE=0;
//    NibbleLowD=NibbleLowD & (~RS_Line);
//
//    //output_low( LCD_EN_LINE );   NibbleLowD=NibbleLowD & (~RS_Line);
//    LCD_EN_LINE=0;
//    NibbleLowD=NibbleLowD & (~RS_Line);
//    delay_ms( 250 );
//
//    //output_low( LCD_EN_LINE );   NibbleLowD=NibbleLowD & (~RS_Line);
//    LCD_EN_LINE=0;
//    NibbleLowD=NibbleLowD & (~RS_Line);
//    delay_ms( 15 );
//
//    for( i = 0; i < 3; i++ )   	{
//        //delay_cycles(1);
//        Delay1TCY( );
//
//        //output_high( LCD_EN_LINE );    NibbleLowD=NibbleLowD | EN_Line;
//        LCD_EN_LINE=1;
//        NibbleLowD=NibbleLowD | EN_Line;
//        delay_us( 1 );
//      
//        //  output_d(0x30 | NibbleLowD);
//        LATD= 0x30 | NibbleLowD;
//
//        delay_us( 1 );
//
//        //output_low( LCD_EN_LINE );   NibbleLowD=NibbleLowD & (~EN_Line);
//        LCD_EN_LINE=0;
//        NibbleLowD=NibbleLowD & (~EN_Line);
//
//
//	delay_ms(5);
//   }
//
//   //delay_cycles(1);
//   Delay1TCY();
//   //output_high( LCD_EN_LINE );    NibbleLowD=NibbleLowD | EN_Line;
//   LCD_EN_LINE=1;    NibbleLowD=NibbleLowD | EN_Line;
//
//
//
//   delay_us( 2 );
//
//   //output_d(0x20| NibbleLowD);
//   LATD= 0x20| NibbleLowD;
//   delay_us( 1 );
//   //output_low( LCD_EN_LINE );   NibbleLowD=NibbleLowD & (~EN_Line);
//   LCD_EN_LINE=0;
//   NibbleLowD=NibbleLowD & (~EN_Line);
//
//    lcd_command4( size );
//    lcd_command4( LCD_DISP_ON );
//    lcd_command4( LCD_CUR_INC );
//    lcd_command4( LCD_CLEAR );
//}
//
//
//
////invia un comando all'LCD (usa i 4 bit più significativi della port-D)
//void lcd_command4( char command )
///* Sends the given command to the LCD display. Most of the commands are       */
///*  defined in the header.		   */
//{  char tmp;
//
//   unsigned char NibbleLowD=0;
//   unsigned char RW_Line = 0x02;
//   unsigned char RS_Line = 0x04;
//   unsigned char EN_Line = 0x08;
//
//
//
//
//   //output_low( LCD_RW_LINE );  NibbleLowD=NibbleLowD & (~RW_Line);
//   LCD_RW_LINE=0;
//   NibbleLowD=NibbleLowD & (~RW_Line);
//
//   //output_low( LCD_RS_LINE );   NibbleLowD=NibbleLowD & (~RS_Line);
//   LCD_RS_LINE=0;
//   NibbleLowD=NibbleLowD & (~RS_Line);
//
//   //sarà inviato un comando
//   //delay_cycles(2);
//   Delay1TCY();
//   Delay1TCY();
//
//   //output_low( LCD_EN_LINE );   NibbleLowD=NibbleLowD & (~EN_Line);
//   LCD_EN_LINE=0;   NibbleLowD=NibbleLowD & (~EN_Line);
//
//   delay_ms(5);
//
//   /* Send the command: high nibble */
//   tmp= command & 0xf0;
//
//   //delay_cycles(1);
//   Delay1TCY();
//
//
//   //output_high( LCD_EN_LINE );    NibbleLowD=NibbleLowD | EN_Line;
//   LCD_EN_LINE=1;
//   NibbleLowD=NibbleLowD | EN_Line;
//
//
//
//   delay_us( 1 );
//   //output_d(tmp | NibbleLowD );
//   LATD=tmp | NibbleLowD;
//   delay_us( 1 );
//
//   //output_low( LCD_EN_LINE );   NibbleLowD=NibbleLowD & (~EN_Line);
//   LCD_EN_LINE=0;   NibbleLowD=NibbleLowD & (~EN_Line);
//
//
//   tmp=command<< 4;
//   tmp=tmp & 0xf0;
//
//   //delay_cycles(1);
//   Delay1TCY();
//
//   //output_high( LCD_EN_LINE );    NibbleLowD=NibbleLowD | EN_Line;
//
//   LCD_EN_LINE=1;
//   NibbleLowD=NibbleLowD | EN_Line;
//
//   delay_us( 1 );
//   //output_d(tmp | NibbleLowD );
//   LATD= tmp | NibbleLowD;
//   delay_us( 1 );
//
//   //output_low( LCD_EN_LINE );   NibbleLowD=NibbleLowD & (~EN_Line);
//   LCD_EN_LINE=0;
//   NibbleLowD=NibbleLowD & (~EN_Line);
//
//   /* Impose a 5ms delay while the command is processed */
//   delay_ms( 15 );
//
//}
//
//
//void lcd_character4( char character )
///* Sends the given character to the LCD display. ASCII Numbers and letters    */
///*  are valid, and punctuation below 0x7F. Characters 0x00 to 0x0F are the    */
///*  Generated Characters, which will be blank initially. Other useful symbols */
///*  and Greek characters may be found in the range 0x80 to 0xFF 	      */
//{
//    char tmp;
//    unsigned char NibbleLowD=0;
//    unsigned char RW_Line = 0x02;
//    unsigned char RS_Line = 0x04;
//    unsigned char EN_Line = 0x08;
//
//    //output_low( LCD_RW_LINE );   NibbleLowD=NibbleLowD & (~RW_Line);
//    LCD_RW_LINE=0;
//    NibbleLowD=NibbleLowD & (~RW_Line);
//
//    //output_high( LCD_RS_LINE );    NibbleLowD=NibbleLowD | RS_Line;
//    LCD_RS_LINE=1;
//    NibbleLowD=NibbleLowD | RS_Line;
//
//    delay_us(1);
//
//    /* Send the command: high nibble */
//    tmp= character ;
//
//    tmp=tmp & 0xf0;
//
//    //output_high( LCD_EN_LINE );    NibbleLowD=NibbleLowD | EN_Line;
//    LCD_EN_LINE=1;
//    NibbleLowD=NibbleLowD | EN_Line;
//
//    delay_us( 1 );
//    //output_d(tmp | NibbleLowD);
//    LATD=tmp | NibbleLowD;
//    delay_us( 1 );
//
//    //output_low( LCD_EN_LINE );   NibbleLowD=NibbleLowD & (~EN_Line);
//    LCD_EN_LINE=0;
//    NibbleLowD=NibbleLowD & (~EN_Line);
//
//
//   /* Impose a 5ms delay while the command is processed */
//    delay_ms( 5 );  // allungare il ritardoooo!!!!!!
//    /* Send the command: low nibble */
//   tmp=character<<4;
//   tmp=tmp & 0xf0;
//
//   //output_high( LCD_EN_LINE );    NibbleLowD=NibbleLowD | EN_Line;
//   LCD_EN_LINE=1;
//   NibbleLowD=NibbleLowD | EN_Line;
//
//   delay_us( 1 );
//   //output_d(tmp | NibbleLowD);
//   LATD= tmp | NibbleLowD;
//   delay_us( 1 );
//
//   //output_low( LCD_EN_LINE );   NibbleLowD=NibbleLowD & (~EN_Line);
//   LCD_EN_LINE=0;
//   NibbleLowD=NibbleLowD & (~EN_Line);
//
//
//   delay_ms( 1 );
//   /* Impose a 5ms delay while the command is processed */
//   delay_ms( 5 );
//
//}
//
//// sposta il cursore ad una certa Riga e Colonna
//int GotoRC (int Riga, int Colonna)
//{
//    Colonna--;
//    if (Riga>=0 && Riga<=GNRighe && Colonna>=0 && Colonna <=GNCol) {
//		if (GFormato==R4C20) {
//			if (Riga==1) lcd_command4(0x80 + Colonna );
//			if (Riga==2) lcd_command4(0xC0 + Colonna );
//			if (Riga==3) lcd_command4(0x94 + Colonna );
//			if (Riga==4) lcd_command4(0xD4 + Colonna );
//		}
//		else {	if (Riga==2 )
//					lcd_command4(0xC0 | Colonna );
//				else
//					lcd_command4(0x80 | Colonna );
//			}
//		return 1;
//    }
//    return 0;
//}
//
//
//
//void lcd_number4( char number )
///* Sends the given number to the LCD display, with up to 2 characters. This   */
///*  limits number to 100						      */
//{
//   char tens = 0;
//   char units = 0;
//
//   while( number > 9 )
//   {
//      tens++;
//      number -= 10;
//   }
//   units = number;
//
//   lcd_character4( '0' + tens );
//   lcd_character4( '0' + units );
//}
//
//
//// visualizza una stringa sul display dalla posizione corrente
//void DisplayStr(char *Str)
//{
//    while (*Str!=0)
//	lcd_character4(*Str++);
//}
//
//
//
//void Cornice (char CarxCornice)
//// versione 1.1 con gestione posizione cursore
//// disegna una cornice di 4 righe con il carattere specificato
//{  unsigned char i;
//   char Str[21];
//
//   // riempie la stringa con caratterie ricevuto
//   for (i=0; i <20; i++ ) Str[i]=CarxCornice;
//   Str[20]= '\0' ;  	// aggiungi fine stringa
//
//   GotoRC (1, 1);   	// Sposta il cursore ad una certa Riga e Colonna
//   DisplayStr(Str);    // scrive prima riga in alto
//   // disegna margine sinistro ------------
//   GotoRC (2, 1);
//   lcd_character4(CarxCornice );
//   GotoRC (3, 1);
//   lcd_character4(CarxCornice );
//
//   // disegna margine destro  ----------
//   GotoRC (2, 20);
//   lcd_character4(CarxCornice );
//   GotoRC (3, 20);
//   lcd_character4(CarxCornice );
//
//
//   GotoRC (4, 1); 		// Sposta il cursore ad una certa Riga e Colonna
//   DisplayStr(Str);    	// scrive ultima riga in basso
////	PosR=1; PosC=1;
////   	GotoRC (PosR, PosC);   	// riporta cursore a HOME
//
//
//}   // fine funzione
//
//
//// scrive un carattere su RS232 con la printf o simili.
//// Necessaria per poter simulare USART-1 in MPLAB-X;
////sostituisce la versione 'segnaposto' appositamente implementata in XC8
//void putch(char data) {
//  while( ! TXIF)    continue;
//  TXREG = data;
//}
//
//
//
//
///*****************************
// Attiva comunicazione seriale standard RS232 con el opzioni di base
// <input>  Speed: 300 bps...115200
// occorre aver definito : _XTAL_FREQ con la opportuna frequenza di lavoro del uC
//
// *****************************/
////restituisce errore 255 se velocità troppo bassa per il clock scelto,
////restituisce errore  percentuale rispetto velocita richiesta
//
//float OpenRS232(unsigned long int Speed)
//{
//    unsigned char config;   // byte per config USART
//    unsigned int spbrg;    // pbyte per config velocità USART
//    float f_spbrg;
//    unsigned char baudconfig;    // pbyte per config velocità USART
//    float f_Speed;  // velocità 'esatta' ricalcolata per determinare errore
//    float SpeedError=0;
//    // inizializza porta seriale
//    
//    CloseUSART(); // per sicurezza ..turn off usart if was previously on
//    //-----configure USART -----
//    if (Speed<=9600 ) {  // opzione a bassa velocità cioè USART_BRGH_LOW
//        // e senza interrupt...
//        config = USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX  & USART_BRGH_LOW;
//        //-----SPBRG needs to be changed depending upon oscillator frequency-------
//        //spbrg = 51; //At 8Mhz of oscillator frequency & baud rate of 2400.
//        // N.B. occorre arrotondare,per alte velocita !!.
//        f_spbrg = ((_XTAL_FREQ/64.) /Speed)-1;
//        spbrg = ((_XTAL_FREQ/64) /Speed)-1;
//        if ((f_spbrg-spbrg) > 0.5) spbrg++; // arrotonda
//        f_Speed= _XTAL_FREQ/(64.*(spbrg+1));
//       
//    }
//    else {  //  a velocità alta  cioè USART_BRGH_HIGH
//        config = USART_TX_INT_OFF & USART_RX_INT_OFF & USART_ASYNCH_MODE & USART_EIGHT_BIT & USART_CONT_RX  & USART_BRGH_HIGH;
//        // N.B. occorre arrotondare,per alte velocita !!
//
//        f_spbrg = ((_XTAL_FREQ/16.) /Speed)-1;
//        spbrg = ((_XTAL_FREQ/16) /Speed)-1;
//        if ((f_spbrg-spbrg) > 0.5) spbrg++; // arrotonda a intero successivo
//        f_Speed= _XTAL_FREQ/(16.*(spbrg+1));
//
//    }
//
//    if (spbrg>255) return 255; // codice errore per velocit'troppo bassa per clock
//    SpeedError=100.*((Speed-f_Speed)/(float)Speed);
//    OpenUSART(config, spbrg); //API configures USART for desired parameters
//
//    //se attivo il bit BRG16 ,attivo la modalità 'velocità a 16 bit' e',di conseguenza
//    // nelle formule precedenti inseriro`/4 alposto di /16
//    //                                 e /16 al posto di /64
//    //consente (diverametne dai chip precedenti) di settare agevolmente velocità basse e
//    // anche velocita'piu alte di 115200
//    //BAUDCONbits.BRG16=1;  //attiva registro a 16 bit per lelocità
//    
//    return SpeedError;
//    //baudconfig = BAUD_16_BIT_RATE | BAUD_AUTO_OFF;
////    baudconfig = BAUD_8_BIT_RATE | BAUD_AUTO_OFF;
////    baudUSART (baudconfig);
//    
//
//
//}
//
//
//
//
//// legge dalla memoria 24C32 un singolo byte
//// <input> AddIC: indirizzo del; chip di memoria x FreedomII 0x50
//// <input> Add  : indirizzo a 12 Bite del Byte da leggere
//unsigned char Read24C32(unsigned char AddIC, int Add)
//{
//    unsigned char ByteLetto;    // dato letto dalla memoria I2C
//    unsigned char data,status;
//    unsigned char AddHigh,AddLow; // Parte alta, e bassa dell'indirizzo
//    
//
//    AddIC=AddIC<<1;
//
//    // scompongo indirizzo in parte alta e bassa
//    AddLow=Add & 0xff;
//    AddHigh= Add >>8;
//
//
//    //attivo il bit che indica Lettura dalla memoria I2C
//    AddIC=AddIC | 0x00 ;   // 0x00 per SCRIVERE indirizzo da cui leggere
//    // scrittura comando di lettura (primo byte su I2C)
//    do {
//        IdleI2C();
//       //---START I2C---
//       StartI2C();
//       data = SSPBUF; //read any previous stored content in buffer to clear buffer full   status
//       status = WriteI2C( AddIC ); //write the address of slave
//       if(status == -1) //check if bus collision happened
//       {
//                data = SSPBUF; //upon bus collision detection clear the buffer,
//                SSPCON1bits.WCOL=0; // clear the bus collision status bit
//       }
//     } while(status!=0); //write untill successful communication
//
//    // invio prima parte indizzo da leggere
//    IdleI2C();
//    data = SSPBUF; //read any previous stored content in buffer to clear buffer full   status
//    status = WriteI2C( AddHigh ); //write the address of slave
//
//    IdleI2C();
//    data = SSPBUF; //read any previous stored content in buffer to clear buffer full   status
//    status = WriteI2C( AddLow ); //write the address of slave
//
//    IdleI2C();
//    StartI2C();
//    data = SSPBUF; //read any previous stored content in buffer to clear buffer full   status
//    status = WriteI2C( AddIC  | 0x01); //read byte successivo
//    IdleI2C();
//
//    ByteLetto=  ReadI2C(); //leggi il byte selezionato dalla Memoria I2C
//    IdleI2C();
//
//
//    return ByteLetto;
//}
//
//
//// legge dalla memoria 24C32 un singolo byte
//// <input> AddIC: indirizzo del; chip di memoria x FreedomII 0x50
//// <input> Add  : indirizzo a 12 Bite del Byte da leggere
//// <input> Byte:  dato da scrivere all' indirizzo scelto
//void Write4C32(unsigned char AddIC, int Add, unsigned char Byte)
//{
//    unsigned char ByteLetto;    // dato letto dalla memoria I2C
//    unsigned char data,status;
//    unsigned char AddHigh,AddLow; // Parte alta, e bassa dell'indirizzo
//
//
//    AddIC=AddIC<<1;
//
//    // scompongo indirizzo in parte alta e bassa
//    AddLow=Add & 0xff;
//    AddHigh= Add >>8;
//
//    //attivo il bit che indica Lettura dalla memoria I2C
//    AddIC=AddIC | 0x00 ;   // 0x00 per SCRIVERE indirizzo da cui leggere
//    // scrittura comando di lettura (primo byte su I2C)
//
//    IdleI2C();
//    //---START I2C---
//    StartI2C();
//    data = SSPBUF; //read any previous stored content in buffer to clear buffer full   status
//    status = WriteI2C( AddIC ); //write the address of slave
//       
//    // invio prima parte indirizzo da leggere
//    data = SSPBUF; //read any previous stored content in buffer to clear buffer full   status
//    status = WriteI2C( AddHigh ); //write the address of slave
//
//    // invio parte bassa indirizzo da leggere
//    data = SSPBUF; //read any previous stored content in buffer to clear buffer full   status
//    status = WriteI2C( AddLow ); //write the address of slave
//
//    status = WriteI2C( Byte ); //write the address of slave
//    //NotAckI2C();  //manda comando fine, al termine scrive in 5m su EEPROM
//    IdleI2C();
//    CloseI2C();
//
//    
//}

