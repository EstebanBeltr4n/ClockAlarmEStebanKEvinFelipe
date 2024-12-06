/* 
 *
 * Creado por: Esteban Escarraga, Kevin Lozada y Johan Ordoñez.
 * Fecha de creación: 02-12-2024
 * Circuitos Digitales II
 * Reloj Alarma
 *
 */
// CONFIGURACIONES DEL MICROCONTROLADOR
#pragma config PLLDIV = 5
#pragma config CPUDIV = OSC1_PLL2
#pragma config USBDIV = 1
#pragma config FOSC = HS
#pragma config FCMEN = OFF
#pragma config IESO = OFF
#pragma config PWRT = OFF
#pragma config BOR = OFF
#pragma config BORV = 3
#pragma config VREGEN = OFF
#pragma config WDT = OFF
#pragma config WDTPS = 32768
#pragma config CCP2MX = ON
#pragma config PBADEN = OFF
#pragma config LPT1OSC = OFF
#pragma config MCLRE = ON
#pragma config STVREN = ON
#pragma config LVP = OFF
#pragma config ICPRT = OFF
#pragma config XINST = OFF
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPB = OFF
#pragma config CPD = OFF
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config WRTC = OFF
#pragma config WRTB = OFF
#pragma config WRTD = OFF
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF

#define _XTAL_FREQ 20000000

#include <xc.h>
#include <stdint.h>
#include <stdio.h>

// INCLUIR LIBRERÍAS DE I2C, LCD Y DS3231
#include "i2c.h"
#include "lcd.h"
#include "ds3231.h"

// VARIABLES GLOBALES
int8_t estado = 0;
int8_t hr, min, sec, alarm_hr = 0, alarm_min = 0;
char buffer[20];

// FUNCIÓN PARA CONFIGURAR LA HORA INICIAL EN EL RTC
void inicializarHoraColombia() {
    DS3231_Set_Date_Time(21, 0, 0); // Configurar hora inicial (ejemplo: 10:30:00 AM)
}

void main() {
    ADCON1bits.PCFG = 0x0F; // Configurar todos los pines como digitales
    TRISAbits.RA0 = 1; // Configurar RA0 como entrada (botón para cambiar estado)
    TRISAbits.RA1 = 1; // Configurar RA1 como entrada (botón para incrementar)
    TRISAbits.RA2 = 1; // Configurar RA2 como entrada (botón para decrementar)
    TRISBbits.RB2 = 0; // Configurar RB2 como salida (buzzer)
    Lcd_Init(); // Inicializar LCD
    I2C_Init_Master(I2C_100KHZ); // Inicializar I2C

    inicializarHoraColombia(); // Configurar la hora inicial

    Lcd_Clear(); // Limpiar pantalla LCD

    while (1) {
        if (PORTAbits.RA0 == 1) {
            while (PORTAbits.RA0 == 1); // Esperar liberación del botón
            __delay_ms(20);
            Lcd_Clear();
            estado = (estado + 1) % 3; // Ciclar entre estados 0, 1 y 2
        }

        switch (estado) {
            case 0: // Mostrar hora actual
                DS3231_Get_Time(&hr, &min, &sec);
                sprintf(buffer, "Hora: %02u:%02u:%02u", hr, min, sec);
                Lcd_Set_Cursor(1, 1);
                Lcd_Write_String(buffer);

                if (hr == alarm_hr && min == alarm_min) {
                    Lcd_Set_Cursor(2, 1);
                    Lcd_Write_String("ALARMA ACTIVADA!");
                    LATBbits.LATB2 = 1; // Activar señal de alarma
                    __delay_ms(500);
                    LATBbits.LATB2 = 0; // Desactivar señal de alarma
                    __delay_ms(500);
                }
                break;

            case 1: // Configurar hora de la alarma
                sprintf(buffer, "Alarma H: %02u", alarm_hr);
                Lcd_Set_Cursor(1, 1);
                Lcd_Write_String(buffer);
                if (PORTAbits.RA1 == 1) { // Incrementar hora de la alarma
                    while (PORTAbits.RA1 == 1);
                    __delay_ms(20);
                    alarm_hr = (alarm_hr + 1) % 24;
                }
                if (PORTAbits.RA2 == 1) { // Decrementar hora de la alarma
                    while (PORTAbits.RA2 == 1);
                    __delay_ms(20);
                    alarm_hr = (alarm_hr - 1 + 24) % 24;
                }
                break;

            case 2: // Configurar minutos de la alarma
                sprintf(buffer, "Alarma M: %02u", alarm_min);
                Lcd_Set_Cursor(1, 1);
                Lcd_Write_String(buffer);
                if (PORTAbits.RA1 == 1) { // Incrementar minutos de la alarma
                    while (PORTAbits.RA1 == 1);
                    __delay_ms(20);
                    alarm_min = (alarm_min + 1) % 60;
                }
                if (PORTAbits.RA2 == 1) { // Decrementar minutos de la alarma
                    while (PORTAbits.RA2 == 1);
                    __delay_ms(20);
                    alarm_min = (alarm_min - 1 + 60) % 60;
                }
                break;

            default:
                estado = 0;
                break;
        }
    }
}
