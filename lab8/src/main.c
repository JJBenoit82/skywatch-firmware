/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>
#include <zephyr/app_version.h>
#include <zephyr/kernel.h>
#include <zephyr/version.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include "sensor_thread.h"
#include "app_thread.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE DT_ALIAS(led0)

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

/* static void print_system_info(void)
{
	printk("\n");
	printk("========================================\n");
	printk(" Lab 6: Threading Fundamentals\n");
	printk("========================================\n");
	printk("System initialized successfully\n");
	printk("Current thread: %s\n", k_thread_name_get(k_current_get()));
	printk("Main thread priority: %d\n", k_thread_priority_get(k_current_get()));
	printk("========================================\n");
	printk("\n");
}

static void print_idle_thread_info(void)
{
	printk("\n");
	printk("--- Idle Thread Information ---\n");
	printk("The idle thread runs when no other threads are ready.\n");
	printk("It has the lowest priority in the system.\n");
	printk("During idle, the CPU can enter low-power modes.\n");
	printk("-------------------------------\n");
	printk("\n");
} */

int main(void)
{
	LOG_INF("Firmware version: %s", APP_VERSION_STRING);
	LOG_INF("Zephyr: %s", KERNEL_VERSION_STRING);
	LOG_INF("Board: %s", CONFIG_BOARD);
	// print_system_info();
	LOG_DBG("Debug: Application starting");
	LOG_INF("SkyWatch Weather Station - Lab 8");
	LOG_INF("Main thread: %s (priority %d)", k_thread_name_get(k_current_get()),
		k_thread_priority_get(k_current_get()));

	int ret;

	/* 	printk("\n========================================\n");
		printk(" SkyWatch Weather Station - Lab 6\n");
		printk("========================================\n");
		printk("Main thread: %s (priority %d)\n", k_thread_name_get(k_current_get()),
	   k_thread_priority_get(k_current_get()));
		printk("========================================\n\n"); */

	if (!gpio_is_ready_dt(&led)) {
		printk("Error: LED not ready\n");
		return -1;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	/* 	printk("[Main] Threads running:\n");
		printk(" - Main: heartbeat LED (priority 0)\n");
		printk(" - Sensor: temperature sampling (priority 5)\n");
		printk(" - App: controller/alerts (priority 7)\n\n");

		printk("LED will blink every %d ms\n", SLEEP_TIME_MS);
		printk("Main thread entering blink loop...\n\n"); */

	// print_idle_thread_info();

	while (1) {
		gpio_pin_toggle_dt(&led);
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
