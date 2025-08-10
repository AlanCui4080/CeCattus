#define _STM32_HAL_MCP4728_DRIVER_ 1
#if _STM32_HAL_MCP4728_DRIVER_

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

#define IIC_HANDLE      &hi2c2
#define ADDR       0xc0
#define LDAC_PORT  AUXDAC_LDAC_GPIO_Port
#define LDAC_PIN   AUXDAC_LDAC_Pin
#define RDY_PORT   AUXDAC_RDY_GPIO_Port
#define RDT_PIN    AUXDAC_RDY_Pin


// 
// Portable STM32 HAL MCP4728 driver
//
// To use: modify macros above

static inline uint16_t mcp4728_get_value(float vref, float voltage)
{
  // Convert float value to 12-bit DAC value
  if (voltage < 0.0f) voltage = 0.0f;
  if (voltage > vref) voltage = vref;
  
  return (uint16_t)((voltage / vref) * 4096.0f);
}

HAL_StatusTypeDef mcp4728_write_cha(uint16_t data)
{
  uint8_t data_to_write [3] = {0};

  data_to_write[0] = 0x58;
  data_to_write[1] = ((data >> 8) & 0xff) | 0x80; 
  data_to_write[2] = data & 0xff;

  while (HAL_GPIO_ReadPin(RDY_PORT, RDT_PIN) == GPIO_PIN_RESET)
  {
  }

  HAL_GPIO_WritePin(LDAC_PORT, LDAC_PIN, GPIO_PIN_RESET);
  return HAL_I2C_Master_Transmit(IIC_HANDLE, ADDR, (uint8_t *)&data_to_write, 3, HAL_MAX_DELAY);
}
HAL_StatusTypeDef mcp4728_write_chb(uint16_t data)
{
  uint8_t data_to_write [3] = {0};

  data_to_write[0] = 0x5a;
  data_to_write[1] = ((data >> 8) & 0xff) | 0x80; 
  data_to_write[2] = data & 0xff;

  while (HAL_GPIO_ReadPin(RDY_PORT, RDT_PIN) == GPIO_PIN_RESET)
  {
  }

  HAL_GPIO_WritePin(LDAC_PORT, LDAC_PIN, GPIO_PIN_RESET);
  return HAL_I2C_Master_Transmit(IIC_HANDLE, ADDR, (uint8_t *)&data_to_write, 3, HAL_MAX_DELAY);
}

HAL_StatusTypeDef mcp4728_write_chc(uint16_t data)
{
  uint8_t data_to_write [3] = {0};

  data_to_write[0] = 0x5c;
  data_to_write[1] = ((data >> 8) & 0xff) | 0x80; 
  data_to_write[2] = data & 0xff;

  while (HAL_GPIO_ReadPin(RDY_PORT, RDT_PIN) == GPIO_PIN_RESET)
  {
  }

  HAL_GPIO_WritePin(LDAC_PORT, LDAC_PIN, GPIO_PIN_RESET);
  return HAL_I2C_Master_Transmit(IIC_HANDLE, ADDR, (uint8_t *)&data_to_write, 3, HAL_MAX_DELAY);
}

HAL_StatusTypeDef mcp4728_write_chd(uint16_t data)
{
  uint8_t data_to_write [3] = {0};

  data_to_write[0] = 0x5e;
  data_to_write[1] = ((data >> 8) & 0xff) | 0x80; 
  data_to_write[2] = data & 0xff;

  while (HAL_GPIO_ReadPin(RDY_PORT, RDT_PIN) == GPIO_PIN_RESET)
  {
  }

  HAL_GPIO_WritePin(LDAC_PORT, LDAC_PIN, GPIO_PIN_RESET);
  return HAL_I2C_Master_Transmit(IIC_HANDLE, ADDR, (uint8_t *)&data_to_write, 3, HAL_MAX_DELAY);
}

#undef IIC_HANDLE
#undef ADDR
#undef LDAC_PORT
#undef LDAC_PIN
#undef RDY_PORT
#undef RDT_PIN
#endif
