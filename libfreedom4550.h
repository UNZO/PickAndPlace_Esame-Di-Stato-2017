// Libreria di funzioni di base per scheda FREEDOM II & PIC18F4550
//  Versione 0.96                      13/nov/2014
// rispetto alla versione 0.96 e' stata migliorata  la funzione OpenRS232()
// rispetto alla versione 0.9 e' stata aggiunta la funzione OpenRS232()

//#include <plib\delays.h>
//#include <plib/usart.h>


//#define _XTAL_FREQ 20000000L
#define _XTAL_FREQ 48000000L

// Funzione per generare un ritardo di T millisecondi senza uso di Timer

int piglias1 (int numero);

void movex (int passi , int delay , int direzione);

void movey (int passi , int delay , int direzione);

void movez (int passi , int delay , int direzione);

void delay_ms(unsigned int T);

void delay_us(unsigned int NCicli);

///* prototipi delle Funzioni */
//void lcd_character4( char character );
//
//void lcd_initialize4( unsigned char size , unsigned char Formato);
//void lcd_command4( char command );
//void lcd_number4( char number );
//
////visualizza una stringa sulla posizione corrente del display
//void DisplayStr(char *Str);
//
//// sposta a riga e colonna il cursore , restituisce 1 se coordinate sensate (<4 e <40)
//int GotoRC (int Riga, int Colonna);
//
//// disegna cornice attorno a perimetro display LCD a 4 Righe
//void Cornice (char CarxCornice);
//
//
//// scrive un carattere su RS232 con la printf o simili.
//// Necessaria per poter simulare USART-1 in MPLAB-X;
////sostituisce la versione 'segnaposto' appositamente implementata in XC8
//void putch(char data) ;
//
//// apre rtx seriale rs232 alla velocita specificata
//float OpenRS232(unsigned long int Speed);
//
////funzione per leggere da memoria SERIALE I2C 24C32
//unsigned char Read24C32(unsigned char AddIC, int Add);
////funzione per scrivere su memoria SERIALE I2C 24C32
//void Write4C32(unsigned char AddIC, int Add, unsigned char Byte);
//
//
//
///* Define some commands */
//const int LCD_CLEAR	 = 0x01; /* Clear the display and send cursor to Home */
//const int LCD_CUR_HOME	 = 0x02; /* Send the cursor to Home but keep display  */
//
//const int LCD_CUR_DEC	 = 0x04; /* Set cursor to move left after character   */
//const int LCD_CUR_INC	 = 0x06; /* Set cursor to move right after character  */
//const int LCD_CUR_SCR_R  = 0x05; /* Set display to move right after character */
//const int LCD_CUR_SCR_L  = 0x07; /* Set display to move left after character  */
//
//const int LCD_DISP_OFF	 = 0x08; /* Turn off the LCD display		      */
//const int LCD_DISP_ON	 = 0x0C; /* Turn on display, no cursor		      */
//const int LCD_DISP_CUR	 = 0x0E; /* Turn on display, with cursor	      */
//const int LCD_DISP_BLINK = 0x0F; /* Turn on display, with blinking cursor     */
//
//const int LCD_SHFT_CUR_L = 0x10; /* Decrement the cursor (move left)	      */
//const int LCD_SHFT_CUR_R = 0x14; /* Increment the cursor (move right)	      */
//const int LCD_SHFT_SCR_L = 0x18; /* Shift the display (scroll) to the left    */
//const int LCD_SHFT_SCR_R = 0x1C; /* Shift the display (scroll) to the right   */
//
//const int LCD_SIZE_LARGE = 0x34; /* Large cursor, one line, 8 bit interface   */
//const int LCD_SIZE_SMALL = 0x38; /* Small cursor, two lines, 8 bit interface  */
//const int LCD_SIZE_SMALL_4B = 0x28;  /* Small cursor, two lines, 4 bit interface  */
//const int LCD_SIZE_2x40  = 0x38; /* Small cursor, two lines, 8 bit interface  */
//
//
//
///* Address is added to the following two values, up to 0F for each line       */
//const int LCD_DD_ADD_L1  = 0x80; /* First Display RAM address on Line 1       */
//const int LCD_DD_ADD_L2  = 0xC0; /* First Display RAM address on Line 2       */
//const int LCD_DD_ADD_L3  = 0x94; /* First Display RAM address on Line 3       */
//const int LCD_DD_ADD_L4  = 0xD4; /* First Display RAM address on Line 4       */
//
//
///* Line number for dots is added to each of the following addresses, up to 07 */
//const int LCD_CG_ADD_C0  = 0x40; /* First Character Generator RAM address     */
//const int LCD_CG_ADD_C1  = 0x48; /* Second Character Generator RAM address    */
//const int LCD_CG_ADD_C2  = 0x50; /* Third Character Generator RAM address     */
//const int LCD_CG_ADD_C3  = 0x58; /* Fourth Character Generator RAM address    */
//const int LCD_CG_ADD_C4  = 0x60; /* Fifth Character Generator RAM address     */
//const int LCD_CG_ADD_C5  = 0x68; /* Sixth Character Generator RAM address     */
//const int LCD_CG_ADD_C6  = 0x70; /* Seventh Character Generator RAM address   */
//const int LCD_CG_ADD_C7  = 0x78; /* Eighth Character Generator RAM address    */
//
//const int R1C08  = 18;  // display 1 riga  x  8 colonne
//const int R1C16  = 116; // display 1 Riga  x 16 colonne
//const int R1C20  = 120; // display 1 Riga  x 20 colonne
//const int R1C40  = 140; // display 1 Riga  x 20 colonne
//
//const int R2C08  = 28;  // display 2 righe x  8 colonne
//const int R2C16  = 216; // display 2 Righe x 16 colonne
//const int R2C20  = 220; // display 2 Righe x 20 colonne
//const int R2C32  = 232; // display 2 Righe x 32 colonne
//const int R2C40  = 232; // display 2 Righe x 40 colonne
//
//const int R4C20  = 204; // display 2 Righe x 40 colonne
//
//int GNRighe=0;
//int GNCol=0;
//int GFormato=0;
//
//
