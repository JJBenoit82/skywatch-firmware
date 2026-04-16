#ifndef SENSOR_THREAD_H
#define SENSOR_THREAD_H

#include <zephyr/kernel.h>

struct sensor_data {
	float temperature;
	uint32_t timestamp;
	bool valid;
};

#endif /* SENSOR_THREAD_H */