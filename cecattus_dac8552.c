#define _STM32_HAL_DAC8552_DRIVER_ 1
#if _STM32_HAL_DAC8552_DRIVER_

// Copyright 2025 AlanCui4080
//
// Licensed under the Apache License, Version 2.0 (the "License"): you may
// not use this file except in compliance with the License. You may obtain
// a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations
// under the License

#define SPI_HANDLE      &hspi2
#define SYNC_PORT  DAC_SYNC_GPIO_Port
#define SYNC_PIN   DAC_SYNC_Pin

// 
// Portable STM32 HAL DAC8552 driver
//
// To use: modify macros above

static inline uint16_t dac8552_get_value(float vref, float voltage)
{
  // Convert float value to 16-bit DAC value
  if (voltage < 0.0f) voltage = 0.0f;
  if (voltage > vref) voltage = vref;
  
  return (uint16_t)((voltage / vref) * 65535.0f);
}

HAL_StatusTypeDef dac8552_write_cha(uint16_t data)
{
  uint32_t data_to_write = 0;

  // DB15 - DB0 data bits
  data_to_write |= data;
  // LDA = 1 load DAC A, buffer select = 0
  data_to_write |= 0x100000;

  // Convert data_to_write from little-endian to big-endian (24 bits)
  data_to_write = ((data_to_write & 0xFF) << 16) | (data_to_write & 0xFF00) | ((data_to_write >> 16) & 0xFF);
  
  HAL_GPIO_WritePin(SYNC_PORT, SYNC_PIN, GPIO_PIN_RESET);
  HAL_StatusTypeDef retval = HAL_SPI_Transmit(SPI_HANDLE, (uint8_t *)&data_to_write, 3, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(SYNC_PORT, SYNC_PIN, GPIO_PIN_SET);

  return retval;
}

HAL_StatusTypeDef dac8552_write_chb(uint16_t data)
{
  uint32_t data_to_write = 0;

  // DB15 - DB0 data bits
  data_to_write |= data;
  // LDA = 1 load DAC B, buffer select = 1
  data_to_write |= 0x240000;

  // Convert data_to_write from little-endian to big-endian (24 bits)
  data_to_write = ((data_to_write & 0xFF) << 16) | (data_to_write & 0xFF00) | ((data_to_write >> 16) & 0xFF);

  HAL_GPIO_WritePin(SYNC_PORT, SYNC_PIN, GPIO_PIN_RESET);
  HAL_StatusTypeDef retval = HAL_SPI_Transmit(SPI_HANDLE, (uint8_t *)&data_to_write, 3, HAL_MAX_DELAY);
  HAL_GPIO_WritePin(SYNC_PORT, SYNC_PIN, GPIO_PIN_SET);

  return retval;
}

#undef SPI_HANDLE
#undef VREF
#undef SYNC_PORT
#undef SYNC_PIN
#endif
