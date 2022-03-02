/*
 * TMP_117.h
 *
 *  Created on: Sep 29, 2021
 *      Author: AppendixPi
 */

#ifndef INC_TMP117_H_
#define INC_TMP117_H_

/*
Includes
*/

typedef enum
{
  CU_OK       = 0x00,
  CU_ERROR    = 0x01,
  CU_BUSY     = 0x02,
  CU_TIMEOUT  = 0x03
} CU_StatusTypeDef;

// Address of the registers. This can be found on page 23 of the datasheet
enum TMP117_Register
{
  TMP117_TEMP_RESULT = 0X00,
  TMP117_CONFIGURATION = 0x01,
  TMP117_T_HIGH_LIMIT = 0X02,
  TMP117_T_LOW_LIMIT = 0X03,
  TMP117_EEPROM_UL = 0X04,
  TMP117_EEPROM1 = 0X05,
  TMP117_EEPROM2 = 0X06,
  TMP117_TEMP_OFFSET = 0X07,
  TMP117_EEPROM3 = 0X08,
  TMP117_DEVICE_ID = 0X0F
};

#define TMP117_RESOLUTION 0.0078125f	// Resolution of the device, found on (page 1 of datasheet)

extern I2C_HandleTypeDef hi2c1;
static const uint8_t TMP117_ADDR = 0x48 << 1; // Use 8-bit address
uint8_t tmp117_buf[50];

#define TMP117_TIMER_MAX 1000
uint32_t tmp117_Timer;
uint8_t tmp117_ret;
float tmp117_temp_f;


CU_StatusTypeDef TMP117_Init();
CU_StatusTypeDef TMP117_read_temp();
CU_StatusTypeDef TMP117_read_reg(uint8_t reg, uint8_t *R_reg);
CU_StatusTypeDef TMP117_write_reg(uint8_t reg, uint8_t *W_reg);


#endif /* INC_TMP117_H_ */
