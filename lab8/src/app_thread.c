#include "app_thread.h"
#include "data_mgr.h"
#include "sensor_thread.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(app, LOG_LEVEL_INF);

#define APP_STACK_SIZE  1024
#define APP_PRIORITY    7
#define APP_INTERVAL_MS 3000

#define TEMP_HIGH_THRESHOLD 28.0f
#define TEMP_LOW_THRESHOLD  22.0f

static struct k_work alert_work;

void alert_work_handler(struct k_work *work)
{
    LOG_INF("[Alert] Processing temperature alert\n");
    LOG_INF("[Alert] Logging event...\n");
    k_msleep(50); /* Simulate logging delay */
    LOG_INF("[Alert] Alert processing complete\n");
}

static void app_thread_entry(void *p1, void *p2, void *p3)
{

    //printk("[App] Controller thread started (priority %d)\n", k_thread_priority_get(k_current_get()));
    k_work_init(&alert_work, alert_work_handler);

    while (1)
    {
        //int ret = data_mgr_wait_for_data(K_FOREVER);
        struct sensor_data reading;
        int ret = data_mgr_receive(&reading, K_FOREVER);

        if (ret == 0)
        {
            LOG_INF("Received: %d.%d C,\n", (int)reading.temperature, (int)((reading.temperature - (int)reading.temperature) * 10));

            if (reading.temperature > TEMP_HIGH_THRESHOLD)
            {
                //printk("[App] ALERT: Temperature HIGH! Submitting alert...\n");
                LOG_WRN("ALERT: Temperature HIGH!");
                k_work_submit(&alert_work);
            }
/*          struct sensor_data reading = data_mgr_read();
            if (reading.valid)
            {
                float temp = reading.temperature;
                printk("[App] Reading sensor: %d.%d C (age: %u ms)\n",
                        (int)temp,
                        (int)((temp - (int)temp) * 10),
                        k_uptime_get_32() - reading.timestamp);

                if (temp > TEMP_HIGH_THRESHOLD)
                {
                        printk("[App] ALERT: Temperature HIGH!\n");
                }
                else if (temp < TEMP_LOW_THRESHOLD)
                {
                        printk("[App] ALERT: Temperature LOW!\n");
                }
                else
                {
                        printk("[App] Temperature normal\n");
                }
                    
                }
            else
            {
                printk("[App] Waiting for sensor data...\n");
            } */
            /* code */
        }       

        //k_msleep(APP_INTERVAL_MS);
        
    }
    
}

K_THREAD_DEFINE(app_tid, 
                APP_STACK_SIZE,
                app_thread_entry,
                NULL,
                NULL,
                NULL,
                APP_PRIORITY,
                0,
                0);