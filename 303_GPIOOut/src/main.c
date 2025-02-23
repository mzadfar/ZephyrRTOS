/**
 * @file main.c
 * @author M. Z.
 * @brief
 * @version 0.1
 * @date 2024-12-01
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <stdio.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

/* The devicetree node identifier for the "led0" alias. */
#define LED_GREEN DT_ALIAS(led0)
#define LED_BLUE DT_ALIAS(led1)
#define LED_RED DT_ALIAS(led2)
/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec ledGreen =
    GPIO_DT_SPEC_GET(DT_NODELABEL(green_led_1), gpios);
static const struct gpio_dt_spec ledBlue = GPIO_DT_SPEC_GET(LED_BLUE, gpios);
static const struct gpio_dt_spec ledRed = GPIO_DT_SPEC_GET(LED_RED, gpios);

int main(void) {
  // int ret;
  bool led_state = true;

  if ((!device_is_ready(ledGreen.port)) || (!gpio_is_ready_dt(&ledBlue)) ||
      (!gpio_is_ready_dt(&ledRed))) {
    return 0;
  }

  /* ret = gpio_pin_configure_dt(&ledGreen, GPIO_OUTPUT_ACTIVE);
  /if (ret <0){
    return 0;
  }*/
  // for below line gpio_pin_configure(ledGreen.port, ledGreen.pin,
  // ledGreen.dt_flags) does not
  // error, but does not work, even we add #include <zephyr/device.h>
  if ((gpio_pin_configure_dt(&ledGreen, GPIO_OUTPUT_ACTIVE) < 0) ||
      (gpio_pin_configure_dt(&ledBlue, GPIO_OUTPUT_ACTIVE) < 0) ||
      (gpio_pin_configure_dt(&ledRed, GPIO_OUTPUT_ACTIVE) < 0)) {
    return 0;
  }

  while (true) {
    if ((gpio_pin_toggle_dt(&ledGreen) < 0) ||
        (gpio_pin_toggle_dt(&ledBlue) < 0) ||
        (gpio_pin_toggle_dt(&ledRed) < 0)) {
      return 0;
    }

    led_state = !led_state;
    printf("LED state: %s\n", led_state ? "ON" : "OFF");
    k_msleep(SLEEP_TIME_MS);
  }
  return 0;
}
