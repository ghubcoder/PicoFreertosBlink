/*
 * LED blink with FreeRTOS
 */
#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"

struct led_task_arg
{
    int gpio;
    int delay;
};

void led_task(void *p)
{
    struct led_task_arg *a = (struct led_task_arg *)p;

    gpio_init(a->gpio);
    gpio_set_dir(a->gpio, GPIO_OUT);
    while (true)
    {
        gpio_put(a->gpio, 1);
        vTaskDelay(pdMS_TO_TICKS(a->delay));
        gpio_put(a->gpio, 0);
        vTaskDelay(pdMS_TO_TICKS(a->delay));
        printf("%s: core%u\n", pcTaskGetName(NULL), get_core_num());
    }
}

int main()
{
    stdio_init_all();
    printf("Start LED blink\n");

    struct led_task_arg arg1 = {25, 100};
    xTaskCreate(led_task, "LED_Task 1", 256, &arg1, 1, NULL);

    struct led_task_arg arg2 = {28, 200};
    xTaskCreate(led_task, "LED_Task 2", 256, &arg2, 1, NULL);

    // Create a 3rd task
    // Force it to run on core1
    TaskHandle_t task3_handle;
    UBaseType_t uxCoreAffinityMask;
    struct led_task_arg arg3 = {8, 300};
    xTaskCreate(led_task, "LED_Task 3", 256, &arg3, 1, &( task3_handle ));
    // To force to run on core0:
    // uxCoreAffinityMask = ( ( 1 << 0 ));
    uxCoreAffinityMask = ( ( 1 << 1 ));
    vTaskCoreAffinitySet( task3_handle, uxCoreAffinityMask );

    vTaskStartScheduler();

    while (true)
        ;
}
