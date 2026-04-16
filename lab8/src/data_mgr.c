#include "sensor_thread.h"
#include <zephyr/kernel.h>

// static K_MUTEX_DEFINE(data_mutex);
// static K_SEM_DEFINE(data_ready_sem, 0, 1);

#define MSG_QUEUE_SIZE 4

K_MSGQ_DEFINE(sensor_msgq, sizeof(struct sensor_data), MSG_QUEUE_SIZE, 4);

void data_mgr_post(struct sensor_data *data)
{
	/* Non-blocking put - drop oldest if full */
	if (k_msgq_put(&sensor_msgq, data, K_NO_WAIT) != 0) {
		k_msgq_purge(&sensor_msgq);
		k_msgq_put(&sensor_msgq, data, K_NO_WAIT);
	}
}

int data_mgr_receive(struct sensor_data *data, k_timeout_t timeout)
{
	return k_msgq_get(&sensor_msgq, data, timeout);
}

/* void data_mgr_write(float temperature)
{
    k_mutex_lock(&data_mutex, K_FOREVER);
    latest_reading.temperature = temperature;
    latest_reading.timestamp = k_uptime_get_32();
    latest_reading.valid = true;
    k_mutex_unlock(&data_mutex);

    k_sem_give(&data_ready_sem);
}

int data_mgr_wait_for_data(k_timeout_t timeout)
{
    return k_sem_take(&data_ready_sem, timeout);
}

struct sensor_data data_mgr_read(void)
{
    struct sensor_data copy;
    k_mutex_lock(&data_mutex, K_FOREVER);
    copy = latest_reading;
    k_mutex_unlock(&data_mutex);
    return copy;
} */