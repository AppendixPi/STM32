/*
 * MAX31855.h
 *
 *  Created on: Mar 3, 2022
 *      Author: gabri
 */

#ifndef INC_MAX31855_H_
#define INC_MAX31855_H_

#include "main.h"

extern SPI_HandleTypeDef hspi1;

typedef enum
{
  MAX31855_OK       = 0x00,
  MAX31855_ERROR    = 0x01,
  MAX31855_BUSY     = 0x02,
  MAX31855_TIMEOUT  = 0x03
} MAX31855_StatusTypeDef;

enum FAULT_MASK{
	OC_FAULT =  0x00000001,
	SCG_FAULT = 0x00000002,
	SCV_FAULT = 0x00000004,
	GEN_FAULT = 0x00010000		//if at least one of the previous fault is found
};

typedef union{
	uint8_t spi_rec_buf[4];
	uint32_t spi_rec_u32b;
}MAX31855_mem_data;

MAX31855_mem_data spi_rec_data;

/*variables for raw temperature data - signed int*/
int32_t rec_cold_tmp;		//Cold junction temperature
int32_t rec_hot_tmp;		//Thermocouple temperature

MAX31855_StatusTypeDef MAX31855_init();
MAX31855_StatusTypeDef MAX31855_read_intMemory();
MAX31855_StatusTypeDef MAX31855_read_temp_C(float *hot_tmp, float *cold_tmp);


#endif /* INC_MAX31855_H_ */
