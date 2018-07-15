/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15.1
        Device            :  PIC18F45K50
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include <pic18f45k50.h>

#include "mcc_generated_files/mcc.h"
#include "libfreedom4550.h"

/*
                         Main application
 */
void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighEnable();

    // Enable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowEnable();

    // Disable high priority global interrupts
    //INTERRUPT_GlobalInterruptHighDisable();

    // Disable low priority global interrupts.
    //INTERRUPT_GlobalInterruptLowDisable();

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
    int x=0;
    int delay = 0;
    int passi=0;
    int direzione=0;
    int contfaseiniziale=0;
    int contultimaregolazionez=0;
    int select=0;
    int numero=1;
    


        delay_ms(1000);
 
        while(1)    //ciclo principaòeò
 {
        while (contfaseiniziale==0)   //fase di regolazione iniziale
        {
            if (PORTDbits.RD7==0) //se premo bottone select
            {
                if (select<=3)  //incremento di uno
                {
                select++;
                }
                
                if (select==4)  //solo se <=3
                {
                    select=1;
                }
                if (select==1)  //accendo led per fase 1 2 3
                {
                LATDbits.LD1=1;
                LATDbits.LD0=0;
                LATCbits.LC2=0;
                }
                
                if (select==2)
                {
                LATDbits.LD0=1;
                LATDbits.LD1=0;
                LATCbits.LC2=0;
                }
                
                if (select==3)
                {
                LATCbits.LC2=1;
                LATDbits.LD1=0;
                LATDbits.LD0=0;
                }
            }
            delay_ms(50);
            if (PORTDbits.RD6==0)//se premo tasto su
            {
                if (select==1)//muovo asse y
                {
                    movey (5,100,1);
                }
                
                if (select==2)//muovo asse x
                {
                    movex (10,100,1);
                }
                
                if (select==3)//muovo asse z
                {
                    movez (50,500,1);
                }
            }
            if (PORTDbits.RD5==0)//se premo tasto giu
            {
                if (select==1)//muovo asse y
                {
                    movey (5,100,0);
                }
                
                if (select==2)//muovo asse x
                {
                    movex (10,100,0);
                }
                
                if (select==3)//muovo asse z
                {
                    movez (50,500,0);
                }
            }
            if (PORTDbits.RD4==0)//se premo tasto ok
            {
                LATCbits.LC2=0;//spengo trutte le luci accese
                LATDbits.LD1=0;
                LATDbits.LD0=0;
                    movey (8745,250,1);//mi sposto all'oggetto #48 per verificarne l'allineamento
                    while(PORTDbits.RD4==1)//attendo di premere nuovamente tasto ok
                    {}
                    movey (8745,250,0);// torno in posizione oggetto #1
                    contultimaregolazionez=0;
                    while(contultimaregolazionez==0)//premo tasto ok per regolare ancora z
                    {
                    LATCbits.LC2=1; //accendo led di segnalazione
                    if (PORTDbits.RD5==0)//se premo tasto giu
                    {
                        movez (50,500,0);    
                    }
                    if (PORTDbits.RD6==0)//se premo tasto su
                    {
                        movez (50,500,1);
                    }
                    delay_ms(10);
                    if (PORTDbits.RD4==0)//attendo di premere nuovamente tasto ok per finire regolazione
                    {
                    LATCbits.LC2=0;//spengo ledi di segnalazione
                    contultimaregolazionez=1; //incremento per accettare ultima regolazione di z
                    LATDbits.LD1=1;
                    LATCbits.LC0=1;
                    delay_ms(250);
                    LATDbits.LD1=0;
                    LATCbits.LC0=0;
                    LATDbits.LD0=1;
                    LATCbits.LC1=1;
                    delay_ms(250);
                    LATDbits.LD0=0;
                    LATCbits.LC1=0;
                    LATCbits.LC2=1;
                    delay_ms(250);
                    LATCbits.LC2=0;
                    contfaseiniziale=1;//incremento per uscire dal ciclo di regolazione iniziale generale
                    }
                    }
                }
            }
      // posso iniziare il programma di posizionamento
    LATEbits.LE0=1;
    delay_ms(100);
    movez(1000,250,1);
    movex(2000,250,1);
    movey(1000,250,1);
    movez(1000,250,0);
    LATEbits.LE0=0;
    delay_ms(100);
    movez(1000,250,1);
    movey(1000,250,0);
    movex(2000,250,0);
    numero=piglias1(numero);
    movez(1000,250,0);
    
        
        
//    LATEbits.LE0=1;
//    movez(1000,250,1);
//    movex(2000,500,1);
//    movez(1050,250,0);
//    LATEbits.LE0=0;
//    delay_ms(500);
//    movez(1050,250,1);
//    movex(2000,500,0);
//    movey(159,500,1);  
        
        }
    

    
    
}


//        do
//        {
//            LATEbits.LE1=1;
//            delay_ms(2);
//            LATEbits.LE1=0;
//            delay_ms(2);
//            cont++;
//        }while((cont<500));
        
//        vaia (48);
        
//        cont=0;
//        
//        LATEbits.LE0=1;
//        
//        delay_ms(500);
//        
//        direzione=1;
//        passi=500;
//        delay=500;
//        
//        movez ( passi ,  delay ,  direzione);
//    
//        direzione=1;
//        passi=2000;
//        delay=500;
//        
//        movex ( passi ,  delay ,  direzione);
// 
//        direzione=1;
//        passi=500;//160 passi pe smd
//        delay=300;
//        
//        movey ( passi ,  delay ,  direzione);
//        
//        direzione=0;
//        passi=500;
//        delay=1000;
//        
//        movez ( passi ,  delay ,  direzione);
//        
//        LATEbits.LE0=0;
//  
//        delay_ms(1000);
//        
//        
//        
//        direzione=1;
//        passi=500;
//        delay=500;
//        
//        movez ( passi ,  delay ,  direzione);    
//        
//        direzione=0;
//        passi=500;//160 passi pe smd
//        delay=300;
//        
//        movey ( passi ,  delay ,  direzione);
//        
//        direzione=0;
//        passi=2000;
//        delay=500;
//        
//        movex ( passi ,  delay ,  direzione);
//        
//        direzione=0;
//        passi=160;//160 passi pe smd
//        delay=1000;
//        
//        movey ( passi ,  delay ,  direzione);      
//        
//        direzione=0;
//        passi=500;
//        delay=1000;
//        
////        movez ( passi ,  delay ,  direzione);        
////        
//                do
//        {
//            LATEbits.LE1=1;
//            delay_ms(2);
//            LATEbits.LE1=0;
//            delay_ms(2);
//            cont++;
//        }while((cont<500));
//       delay_ms(10000);
//     
//    }
//}
/**
 End of File
 * 0    
*/