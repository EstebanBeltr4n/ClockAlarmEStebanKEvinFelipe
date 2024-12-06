/*
 * #include "ds3231.h"
 * Creado por: ESteban EScarraga, Kevin Lozada y Johan Ordoñez.
 * Fecha de creación: 02-12-2024
 * Circuitos Digitales II
 * Reloj Alarma
 *
 */
#include "ds3231.h"

uint8_t alarm_hour = 0;   // Hora de la alarma
uint8_t alarm_minute = 0; // Minuto de la alarma

// Configurar la fecha y hora en el DS3231
void DS3231_Set_Date_Time(uint8_t hr, uint8_t mn, uint8_t sc)


{
    sc &= 0x7F; // Asegurar que el bit MSB esté apagado
    hr &= 0x3F; // Asegurar que los bits no utilizados estén apagados

    I2C_Start();
    I2C_Write(DS3231_ADDRESS);
    I2C_Write(0x00); // Dirección inicial
    I2C_Write(DS3231_Bin_Bcd(sc)); // Segundo
    I2C_Write(DS3231_Bin_Bcd(mn)); // Minuto
    I2C_Write(DS3231_Bin_Bcd(hr)); // Hora
    I2C_Stop();
}

// Configurar la alarma
void DS3231_Set_Alarm(uint8_t hr, uint8_t min)
{
    alarm_hour = hr;
    alarm_minute = min;
}


// Obtener la hora actual Colombia del DS3231 
void DS3231_Get_Time(uint8_t *hr, uint8_t *min, uint8_t *sec) {
    *sec = DS3231_Bcd_Bin(DS3231_Read(DS3231_SEC) & 0x7F);
    *min = DS3231_Bcd_Bin(DS3231_Read(DS3231_MIN) & 0x7F);
    *hr = DS3231_Bcd_Bin(DS3231_Read(DS3231_HOUR) & 0x3F);

    // Ajustar a UTC-5
    if (*hr >= 5) {
        *hr -= 5;
    } else {
        *hr = (*hr + 24) - 5; // Ajustar horas negativas
    }
}


/*
// Obtener la hora actual del DS3231
void DS3231_Get_Time(uint8_t *hr, uint8_t *min, uint8_t *sec)
{
    *sec = DS3231_Bcd_Bin(DS3231_Read(DS3231_SEC) & 0x7F);
    *min = DS3231_Bcd_Bin(DS3231_Read(DS3231_MIN) & 0x7F);
    *hr = DS3231_Bcd_Bin(DS3231_Read(DS3231_HOUR) & 0x3F);

    // Comprobar si la alarma debe activarse
    DS3231_Check_Alarm(*hr, *min);
}
*/
// Comprobar si la hora actual coincide con la alarma
uint8_t DS3231_Check_Alarm(uint8_t current_hr, uint8_t current_min)
{
    if (current_hr == alarm_hour && current_min == alarm_minute)
    {
        LATBbits.LATB0 = 1; // Activar bocina
        __delay_ms(500);
        LATBbits.LATB0 = 0; // Desactivar bocina
        return 1; // Indicar que la alarma está activa
    }
    return 0; // Alarma no activa
}

// Leer un registro específico del DS3231
uint8_t DS3231_Read(uint8_t reg)
{
    uint8_t data = 0;
    I2C_Start();
    I2C_Write(DS3231_ADDRESS);
    I2C_Write(reg);
    I2C_Restart();
    I2C_Write(DS3231_ADDRESS | 0x01); // Leer
    data = I2C_Read();
    I2C_Nack();
    I2C_Stop();
    return data;
}

// Convertir un valor binario a BCD
uint8_t DS3231_Bin_Bcd(uint8_t binary_value)
{
    uint8_t temp;
    uint8_t retval;
    temp = binary_value;
    retval = 0;
    while (1)
    {
        if (temp >= 10)
        {
            temp -= 10;
            retval += 0x10;
        }
        else
        {
            retval += temp;
            break;
        }
    }
    return retval;
}

// Convertir un valor BCD a binario
uint8_t DS3231_Bcd_Bin(uint8_t bcd_value)
{
    uint8_t temp;
    temp = (bcd_value >> 4) * 10; // Parte alta del BCD
    temp += (bcd_value & 0x0F);  // Parte baja del BCD
    return temp;
}
