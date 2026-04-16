#ifndef DATA_MGR_H
#define DATA_MGR_H

#include "sensor_thread.h"

//void data_mgr_write(float temperature);
//struct sensor_data data_mgr_read(void);

void data_mgr_post(struct sensor_data *data);
int data_mgr_receive(struct sensor_data *data, k_timeout_t timeout);

#endif /* DATA_MGR_H */