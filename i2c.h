/* i2c.h
 *
 * Creado por: ESteban EScarraga, Kevin Lozada y Johan Ordo�ez.
 * Fecha de creaci�n: 02-12-2024
 * Circuitos Digitales II
 * Reloj Alarma
 */

#ifndef I2C_H
#define I2C_H

#include <xc.h> // Librer�a principal de perif�ricos
#define _XTAL_FREQ 20000000 // Frecuencia de operaci�n del microcontrolador

// Configuraci�n de pines I2C
#define TRIS_SCL TRISBbits.TRISB1 // Pin SCL configurado como entrada/salida
#define TRIS_SDA TRISBbits.TRISB0 // Pin SDA configurado como entrada/salida

// Velocidades est�ndar de I2C
#define I2C_100KHZ 0x80 // Velocidad est�ndar (100 kHz)
#define I2C_400KHZ 0x00 // Velocidad alta (400 kHz)

// Definici�n de modo maestro (habilitado por defecto)
#define I2C_MASTER_MODE

#ifdef I2C_MASTER_MODE
/**
 * @brief Inicializa el m�dulo I2C en modo maestro.
 * @param sp_i2c Velocidad de operaci�n (I2C_100KHZ o I2C_400KHZ).
 */
void I2C_Init_Master(unsigned char sp_i2c);

/**
 * @brief Genera una condici�n de inicio en el bus I2C.
 */
void I2C_Start(void);

/**
 * @brief Genera una condici�n de parada en el bus I2C.
 */
void I2C_Stop(void);

/**
 * @brief Genera una condici�n de reinicio en el bus I2C.
 */
void I2C_Restart(void);

/**
 * @brief Envia un Acknowledge (ACK) al esclavo.
 */
void I2C_Ack(void);

/**
 * @brief Envia un Not Acknowledge (NACK) al esclavo.
 */
void I2C_Nack(void);

/**
 * @brief Lee un byte desde el esclavo I2C.
 * @return Byte le�do.
 */
unsigned char I2C_Read(void);

/**
 * @brief Escribe un byte en el esclavo I2C.
 * @param data Byte a enviar.
 * @return Resultado de la operaci�n (0: �xito, 1: error).
 */
short I2C_Write(char data);

#endif // I2C_MASTER_MODE

#endif // I2C_H
