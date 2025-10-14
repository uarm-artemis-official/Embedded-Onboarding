#include "cmsis_os.h"
#include "stm32f4xx_hal.h"

extern osMessageQId position_command_queueHandle;

void display_byte(uint8_t byte) {
  uint16_t pin_numbers[] = {
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5,
    GPIO_PIN_6,
    GPIO_PIN_7,
    GPIO_PIN_8
  };

  for (int i = 0; i < 8; i++) {
    if ((byte & (1 << i)) != 0) {
      HAL_GPIO_WritePin(GPIOG, pin_numbers[i], GPIO_PIN_RESET);
    } else {
      HAL_GPIO_WritePin(GPIOG, pin_numbers[i], GPIO_PIN_SET);
    }
  }
}

void blinky_task(void const * argument) {
    (void) argument;
    TickType_t long_delay = pdMS_TO_TICKS(2000);
    TickType_t short_delay = pdMS_TO_TICKS(500);
    uint8_t position_command = 0;

    while (1) {
        position_command = (position_command + 30) % 240;
        display_byte(position_command);
        vTaskDelay(short_delay);
        xQueueSend(position_command_queueHandle, &position_command, 0);
        vTaskDelay(long_delay);
    }
}