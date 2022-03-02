/*
 * TMP_117.c
 *
 *  Created on: Sep 29, 2021
 *      Author: AppendixPi
 */

#include "TMP117.h"

CU_StatusTypeDef TMP117_Init(){
	tmp117_Timer = TMP117_TIMER_MAX;
	uint8_t conf_buf[2];
	tmp117_ret = TMP117_read_reg(TMP117_CONFIGURATION,conf_buf);
	conf_buf[1] |= 0b00000100;
	tmp117_ret = TMP117_write_reg(TMP117_CONFIGURATION,conf_buf);
	HAL_Delay(150);
	TMP117_read_reg(TMP117_CONFIGURATION,conf_buf);
	return tmp117_ret;
}

CU_StatusTypeDef TMP117_read_temp(){
	tmp117_ret = TMP117_read_reg(TMP117_TEMP_RESULT, tmp117_buf);
	tmp117_temp_f = tmp117_buf[1] + (tmp117_buf[0]<<8);
	tmp117_temp_f *= TMP117_RESOLUTION;
	return tmp117_ret;
}

CU_StatusTypeDef TMP117_read_reg(uint8_t reg, uint8_t *R_reg){
	uint8_t buf[10];
	buf[0] = reg;
	tmp117_ret = HAL_I2C_Master_Transmit(&hi2c1, TMP117_ADDR, buf, 1, HAL_MAX_DELAY);
	if(tmp117_ret != CU_OK){
		return tmp117_ret;
	}
	tmp117_ret = HAL_I2C_Master_Receive(&hi2c1, TMP117_ADDR, R_reg, 2, HAL_MAX_DELAY);
	return tmp117_ret;
}

CU_StatusTypeDef TMP117_write_reg(uint8_t reg, uint8_t *W_reg){
	uint8_t buf[10];
	buf[0] = reg;
	buf[1] = W_reg[0];
	buf[2] = W_reg[1];
	tmp117_ret = HAL_I2C_Master_Transmit(&hi2c1, TMP117_ADDR, buf, 3, HAL_MAX_DELAY);
	if(tmp117_ret != CU_OK){
		return tmp117_ret;
	}
	return tmp117_ret;
}
