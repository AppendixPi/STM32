/*
 * MAX31855.c
 *
 *  Created on: Mar 3, 2022
 *      Author: AppendixPi
 */

#include "MAX31855.h"

/*
 No Init is required, CS low only when reading internal memory, the conversion start after reading. Tconv = 100ms
 */
MAX31855_StatusTypeDef MAX31855_init(){
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, SET);		//cs is active low
	return MAX31855_OK;
}
MAX31855_StatusTypeDef MAX31855_read_intMemory(){
	MAX31855_StatusTypeDef ret_val = MAX31855_OK;
	uint8_t rec_buf[4];

	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, RESET);		//Select device
	ret_val = HAL_SPI_Receive(&hspi1, rec_buf, 4, 1000);
	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, SET);		//cs is active low

	//Fill the data structure with received buffer
	spi_rec_data.spi_rec_buf[0]=rec_buf[3];
	spi_rec_data.spi_rec_buf[1]=rec_buf[2];
	spi_rec_data.spi_rec_buf[2]=rec_buf[1];
	spi_rec_data.spi_rec_buf[3]=rec_buf[0];

	if(spi_rec_data.spi_rec_u32b & GEN_FAULT){
		ret_val = MAX31855_ERROR;
	}

	return ret_val;
}

MAX31855_StatusTypeDef MAX31855_read_temp_C(float *hot_tmp, float *cold_tmp){
	MAX31855_StatusTypeDef ret_val = MAX31855_OK;
	ret_val = MAX31855_read_intMemory();
	if(ret_val == MAX31855_OK){
		//Hot-J temperature
		rec_hot_tmp = spi_rec_data.spi_rec_u32b;		//copy into signed int to extend the sign when shift
		rec_hot_tmp = rec_hot_tmp >> 18;
		*hot_tmp = rec_hot_tmp*0.25;					//Sensitivity from datasheet
		//Cold-J temperature
		rec_cold_tmp = (spi_rec_data.spi_rec_u32b << 16);	//copy into signed int to extend the sign when shift
		rec_cold_tmp = (rec_cold_tmp >> 20);
		*cold_tmp = rec_cold_tmp*0.0625;				//Sensitivity from datasheet
	}
	return ret_val;
}
