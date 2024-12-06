#include <xc.h> 
#define _XTAL_FREQ 20000000 // Definici�n de la frecuencia del oscilador principal para retardos.

// Configuraci�n de pines para el LCD
#define RS LATDbits.LD2     // Pin de selecci�n de registro del LCD.
#define EN LATDbits.LD3     // Pin de habilitaci�n del LCD.
#define D4 LATDbits.LD4     // Pin de datos D4 del LCD.
#define D5 LATDbits.LD5     // Pin de datos D5 del LCD.
#define D6 LATDbits.LD6     // Pin de datos D6 del LCD.
#define D7 LATDbits.LD7     // Pin de datos D7 del LCD.

#define RS_DIR TRISDbits.TRISD2 // Direcci�n del pin RS (entrada/salida).
#define EN_DIR TRISDbits.TRISD3 // Direcci�n del pin EN (entrada/salida).
#define D4_DIR TRISDbits.TRISD4 // Direcci�n del pin D4 (entrada/salida).
#define D5_DIR TRISDbits.TRISD5 // Direcci�n del pin D5 (entrada/salida).
#define D6_DIR TRISDbits.TRISD6 // Direcci�n del pin D6 (entrada/salida).
#define D7_DIR TRISDbits.TRISD7 // Direcci�n del pin D7 (entrada/salida).

// Funciones principales del LCD
void Lcd_Port(char a);                // Configura los pines de datos del LCD.
void Lcd_Cmd(char a);                 // Env�a comandos al LCD.
void Lcd_Clear(void);                 // Limpia la pantalla del LCD.
void Lcd_Set_Cursor(char a, char b);  // Establece la posici�n del cursor en el LCD.
void Lcd_Init(void);                  // Inicializa el LCD.
void Lcd_Write_Char(char a);          // Escribe un car�cter en el LCD.
void Lcd_Write_String(const char *a); // Escribe una cadena de texto en el LCD.
void Lcd_Shift_Right(void);           // Mueve el texto del LCD hacia la derecha.
void Lcd_Shift_Left(void);            // Mueve el texto del LCD hacia la izquierda.
void Lcd_Blink(void);                 // Habilita el parpadeo del cursor.
void Lcd_NoBlink(void);               // Deshabilita el parpadeo del cursor.

// Funciones opcionales relacionadas con la memoria CGRAM del LCD.
#ifdef USE_CGRAM_LCD
void Lcd_CGRAM_CreateChar(char add, const char* chardata); // Crea un car�cter personalizado en CGRAM.
void Lcd_CGRAM_Init(void);                                // Inicializa el uso de CGRAM.
void Lcd_CGRAM_Close(void);                               // Cierra el uso de CGRAM.
#endif
