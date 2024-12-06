/* i2c.h
 *
 * Creado por: ESteban EScarraga, Kevin Lozada y Johan Ordoñez.
 * Fecha de creación: 02-12-2024
 * Circuitos Digitales II
 * Reloj Alarma
 */

#ifndef I2C_H
#define I2C_H

#include <xc.h> // Librería principal de periféricos
#define _XTAL_FREQ 20000000 // Frecuencia de operación del microcontrolador

// Configuración de pines I2C
#define TRIS_SCL TRISBbits.TRISB1 // Pin SCL configurado como entrada/salida
#define TRIS_SDA TRISBbits.TRISB0 // Pin SDA configurado como entrada/salida

// Velocidades estándar de I2C
#define I2C_100KHZ 0x80 // Velocidad estándar (100 kHz)
#define I2C_400KHZ 0x00 // Velocidad alta (400 kHz)

// Definición de modo maestro (habilitado por defecto)
#define I2C_MASTER_MODE

#ifdef I2C_MASTER_MODE
/**
 * @brief Inicializa el módulo I2C en modo maestro.
 * @param sp_i2c Velocidad de operación (I2C_100KHZ o I2C_400KHZ).
 */
void I2C_Init_Master(unsigned char sp_i2c);

/**
 * @brief Genera una condición de inicio en el bus I2C.
 */
void I2C_Start(void);

/**
 * @brief Genera una condición de parada en el bus I2C.
 */
void I2C_Stop(void);

/**
 * @brief Genera una condición de reinicio en el bus I2C.
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
 * @return Byte leído.
 */
unsigned char I2C_Read(void);

/**
 * @brief Escribe un byte en el esclavo I2C.
 * @param data Byte a enviar.
 * @return Resultado de la operación (0: éxito, 1: error).
 */
short I2C_Write(char data);

#endif // I2C_MASTER_MODE

#endif // I2C_H
