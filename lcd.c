/*
 *
 * Creado por: ESteban EScarraga, Kevin Lozada y Johan Ordoñez.
 * Fecha de creación: 02-12-2024
 * Circuitos Digitales II
 * Reloj Alarma
 *
 */



#include "lcd.h" // Incluye el encabezado con las definiciones y prototipos necesarios para el LCD.

void Lcd_Port(char a)
{
    // Configura los pines de datos del LCD según los bits del valor recibido.
    (a & 1) ? (D4 = 1) : (D4 = 0); // Configura el pin D4.
    (a & 2) ? (D5 = 1) : (D5 = 0); // Configura el pin D5.
    (a & 4) ? (D6 = 1) : (D6 = 0); // Configura el pin D6.
    (a & 8) ? (D7 = 1) : (D7 = 0); // Configura el pin D7.
}

void Lcd_Cmd(char a)
{
    RS = 0;           // RS en 0 para indicar un comando.
    Lcd_Port(a);      // Envía el valor al puerto de datos.
    EN = 1;           // Activa el pin EN.
    __delay_ms(4);    // Retardo para asegurar el tiempo necesario.
    EN = 0;           // Desactiva el pin EN.
}

void Lcd_Clear(void)
{
    // Limpia la pantalla del LCD.
    Lcd_Cmd(0); // Comando de borrado.
    Lcd_Cmd(1); // Ejecuta el borrado.
}

void Lcd_Set_Cursor(char a, char b)
{
    // Establece la posición del cursor en una fila (`a`) y columna (`b`).
    char temp, z, y;
    if (a == 1)       // Primera fila.
        temp = 0x80 + b - 1;
    else if (a == 2)  // Segunda fila.
        temp = 0xC0 + b - 1;
    else if (a == 3)  // Tercera fila (opcional).
        temp = 0x94 + b - 1;
    else if (a == 4)  // Cuarta fila (opcional).
        temp = 0xD4 + b - 1;

    z = temp >> 4;    // Parte alta del comando.
    y = temp & 0x0F;  // Parte baja del comando.
    Lcd_Cmd(z);       // Envía la parte alta.
    Lcd_Cmd(y);       // Envía la parte baja.
}

void Lcd_Init(void)
{
    // Inicializa el LCD.
    RS_DIR = 0;  // Configura el pin RS como salida.
    EN_DIR = 0;  // Configura el pin EN como salida.
    D4_DIR = 0;  // Configura el pin D4 como salida.
    D5_DIR = 0;  // Configura el pin D5 como salida.
    D6_DIR = 0;  // Configura el pin D6 como salida.
    D7_DIR = 0;  // Configura el pin D7 como salida.

    Lcd_Port(0x00); // Inicialización inicial.
    __delay_ms(20); // Retardo para estabilizar el LCD.

    // Secuencia de inicialización estándar.
    Lcd_Cmd(0x03);
    __delay_ms(5);
    Lcd_Cmd(0x03);
    __delay_ms(11);
    Lcd_Cmd(0x03);
    Lcd_Cmd(0x02);

    // Configura el LCD en modo de 4 bits.
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x08);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0C); // Habilita el display sin cursor.
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x06); // Configuración de entrada automática.

    Lcd_Clear(); // Limpia la pantalla al finalizar la inicialización.
}

void Lcd_Write_Char(char a)
{
    // Escribe un carácter en el LCD.
    char temp, y;
    temp = a & 0x0F;   // Extrae la parte baja del carácter.
    y = a & 0xF0;      // Extrae la parte alta del carácter.
    RS = 1;            // RS en 1 para indicar datos.
    Lcd_Port(y >> 4);  // Envía la parte alta.
    EN = 1;
    __delay_us(40);
    EN = 0;
    Lcd_Port(temp);    // Envía la parte baja.
    EN = 1;
    __delay_us(40);
    EN = 0;
}

void Lcd_Write_String(const char *a)
{
    // Escribe una cadena de texto en el LCD.
    int i;
    for (i = 0; a[i] != '\0'; i++)  // Itera sobre la cadena hasta encontrar el terminador.
        Lcd_Write_Char(a[i]);      // Escribe cada carácter.
}

void Lcd_Shift_Right(void)
{
    // Mueve el contenido del LCD hacia la derecha.
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x0C);
}

void Lcd_Shift_Left(void)
{
    // Mueve el contenido del LCD hacia la izquierda.
    Lcd_Cmd(0x01);
    Lcd_Cmd(0x08);
}

void Lcd_Blink(void)
{
    // Habilita el parpadeo del cursor.
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0F);
}

void Lcd_NoBlink(void)
{
    // Deshabilita el parpadeo del cursor.
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0C);
}

#ifdef USE_CGRAM_LCD
void Lcd_CGRAM_CreateChar(char add, const char* chardata)
{
    // Crea caracteres personalizados en la CGRAM del LCD.
    for (char i = 0; i < 8; i++) // Itera sobre los 8 bytes del carácter.
        Lcd_Write_Char(chardata[i]);
}

void Lcd_CGRAM_Init(void)
{
    // Inicializa la memoria CGRAM.
    Lcd_Cmd(0x04);
    Lcd_Cmd(0x00);
}

void Lcd_CGRAM_Close(void)
{
    // Cierra el uso de la CGRAM.
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x02);
}
#endif
