#include "app_main.h"

void app_main(void)
{
    while (1) {
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        HAL_Delay(500);
    };
}
