/**
 * @file main.c
 * @author M. Z.
 * @brief
 * @version 0.LED_ON
 * @date 2024-12-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

/* 1000 msec = LED_ON sec */
#define SLEEP_TIME_MS 1000

#define LED_GREEN 0
#define LED_BLUE 7
#define LED_RED 14

#define LED_ON 1
#define LED_OFF 0

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct device *gpio_ct_dev = DEVICE_DT_GET(DT_NODELABEL(gpiob));

int main(void) {
  int ret;
  bool led_state = true;

  if (!device_is_ready(gpio_ct_dev)) {
    return 0;
  }

  ret = gpio_pin_configure(gpio_ct_dev, LED_GREEN, GPIO_OUTPUT_ACTIVE) ||
        gpio_pin_configure(gpio_ct_dev, LED_BLUE, GPIO_OUTPUT_ACTIVE) ||
        gpio_pin_configure(gpio_ct_dev, LED_RED, GPIO_OUTPUT_ACTIVE);
  if (ret != 0) {
    return 0;
  }

  while (true) {
    ret = gpio_pin_set_raw(gpio_ct_dev, LED_GREEN, LED_ON) ||
          gpio_pin_set_raw(gpio_ct_dev, LED_BLUE, LED_ON) ||
          gpio_pin_set_raw(gpio_ct_dev, LED_RED, LED_ON);
    if (ret != 0) {
      return 0;
    }

    k_msleep(SLEEP_TIME_MS);

    ret = gpio_pin_set_raw(gpio_ct_dev, LED_GREEN, LED_OFF) ||
          gpio_pin_set_raw(gpio_ct_dev, LED_BLUE, LED_OFF) ||
          gpio_pin_set_raw(gpio_ct_dev, LED_RED, LED_OFF);
    if (ret != 0) {
      return 0;
    }

    led_state = !led_state;
    printf("LED state: %s\n", led_state ? "ON" : "OFF");
    k_msleep(SLEEP_TIME_MS);
  }
  return 0;
}
