/*
 * #include "ds3231.h"
 *
 *
 * Creado por: ESteban EScarraga, Kevin Lozada y Johan Ordoñez.
 * Fecha de creación: 02-12-2024
 * Circuitos Digitales II
 * Reloj Alarma
 *
 */

#ifndef DS3231_H
#define DS3231_H

#include <xc.h>
#define _XTAL_FREQ 20000000

#include <stdint.h>
#include <stdio.h>
#include "i2c.h"

// Dirección del DS3231
#define DS3231_ADDRESS  0xD0

// Registros del DS3231
#define DS3231_SEC      0x00
#define DS3231_MIN      0x01
#define DS3231_HOUR     0x02

// Declaraciones de funciones
void DS3231_Set_Date_Time(uint8_t hr, uint8_t mn, uint8_t sc);

void DS3231_Set_Alarm(uint8_t hr, uint8_t min);
void DS3231_Get_Time(uint8_t *hr, uint8_t *min, uint8_t *sec);
uint8_t DS3231_Check_Alarm(uint8_t current_hr, uint8_t current_min);
uint8_t DS3231_Read(uint8_t reg);
uint8_t DS3231_Bin_Bcd(uint8_t binary_value);
uint8_t DS3231_Bcd_Bin(uint8_t bcd_value);

#endif // DS3231_H
