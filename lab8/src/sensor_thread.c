#include "data_mgr.h"
#include "sensor_thread.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/random/random.h>

LOG_MODULE_REGISTER(sensor, LOG_LEVEL_INF);

#define SENSOR_STACK_SIZE 1024
#define SENSOR_PRIORITY 5
#define SAMPLE_INTERVAL_MS 2000

static float read_temperature(void)
{
	float base = 25.0f;
	float variation = ((float)(sys_rand32_get() % 100) - 50) / 10.0f;
	return base + variation;
}

static void sensor_thread_entry(void *p1, void *p2, void *p3)
{
	// printk("[Sensor] Thread started (priority %d)\n",
	// k_thread_priority_get(k_current_get()));

	while (1) {
		float temp;
		struct sensor_data reading;
		reading.temperature = read_temperature();
		reading.timestamp = k_uptime_get_32();
		reading.valid = true;
		temp = reading.temperature;
		data_mgr_post(&reading);
		LOG_INF("Temperature: %d.%d C", (int)temp, (int)((temp - (int)temp) * 10));
		// data_mgr_write(temp);

		// printk("[Sensor] Temperature: %d.%d C\n", (int)temp, (int)((temp - (int)temp) *
		// 10));

		k_msleep(SAMPLE_INTERVAL_MS);
	}
}

K_THREAD_DEFINE(sensor_tid, SENSOR_STACK_SIZE, sensor_thread_entry, NULL, NULL, NULL,
		SENSOR_PRIORITY, 0, 0);
