/*
 * #include "i2c.h"
 *
 * Creado por: ESteban EScarraga, Kevin Lozada y Johan Ordo�ez.
 * Fecha de creaci�n: 02-12-2024
 * Circuitos Digitales II
 * Reloj Alarma
 *
 */

#include "i2c.h"

// Habilitar solo el modo maestro de I2C
#ifdef I2C_MASTER_MODE

// Inicializar I2C en modo maestro con la velocidad especificada
void I2C_Init_Master(unsigned char sp_i2c)
{
    TRIS_SCL = 1; // Configurar SCL como entrada
    TRIS_SDA = 1; // Configurar SDA como entrada
    SSPSTAT = sp_i2c; // Configuraci�n de velocidad
    SSPCON1 = 0x28;   // Habilitar m�dulo I2C en modo maestro
    SSPCON2 = 0x00;   // Configuraci�n inicial

    // Configuraci�n de velocidad (frecuencia de reloj)
    if (sp_i2c == I2C_100KHZ)
    {
        SSPADD = 119; // Velocidad est�ndar (100 kHz)
    }
    else if (sp_i2c == I2C_400KHZ)
    {
        SSPADD = 29; // Velocidad r�pida (400 kHz)
    }
}

// Enviar condici�n de inicio
void I2C_Start(void)
{
    SSPCON2bits.SEN = 1; // Iniciar condici�n de inicio
    while (!PIR1bits.SSPIF); // Esperar a que se complete
    PIR1bits.SSPIF = 0;     // Limpiar bandera
}

// Enviar condici�n de parada
void I2C_Stop(void)
{
    SSPCON2bits.PEN = 1; // Iniciar condici�n de parada
    while (!PIR1bits.SSPIF); // Esperar a que se complete
    PIR1bits.SSPIF = 0;     // Limpiar bandera
}

// Enviar condici�n de reinicio
void I2C_Restart(void)
{
    SSPCON2bits.RSEN = 1; // Iniciar condici�n de reinicio
    while (!PIR1bits.SSPIF); // Esperar a que se complete
    PIR1bits.SSPIF = 0;     // Limpiar bandera
}

// Enviar se�al de reconocimiento
void I2C_Ack(void)
{
    SSPCON2bits.ACKDT = 0; // Preparar se�al de reconocimiento (ACK)
    SSPCON2bits.ACKEN = 1; // Habilitar se�al de reconocimiento
    while (!PIR1bits.SSPIF); // Esperar a que se complete
    PIR1bits.SSPIF = 0;     // Limpiar bandera
}

// Enviar se�al de no reconocimiento
void I2C_Nack(void)
{
    SSPCON2bits.ACKDT = 1; // Preparar se�al de no reconocimiento (NACK)
    SSPCON2bits.ACKEN = 1; // Habilitar se�al de no reconocimiento
    while (!PIR1bits.SSPIF); // Esperar a que se complete
    PIR1bits.SSPIF = 0;     // Limpiar bandera
}

// Escribir un dato en el bus I2C
short I2C_Write(char data)
{
    SSPBUF = data;         // Cargar dato en el buffer
    while (!PIR1bits.SSPIF); // Esperar a que se complete
    PIR1bits.SSPIF = 0;     // Limpiar bandera
    return SSPCON2bits.ACKSTAT; // Retornar estado de reconocimiento
}

// Leer un dato del bus I2C
unsigned char I2C_Read(void)
{
    SSPCON2bits.RCEN = 1;  // Habilitar recepci�n
    while (!PIR1bits.SSPIF); // Esperar a que se complete
    PIR1bits.SSPIF = 0;     // Limpiar bandera
    return SSPBUF;          // Retornar dato recibido
}

#endif // Fin de I2C_MASTER_MODE
