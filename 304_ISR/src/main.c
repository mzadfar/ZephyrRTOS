/**
 * @file main.c
 * @author M. Z.
 * @brief
 * @version 0.1
 * @date 2024-12-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <inttypes.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

/*
 * Get button configuration from the devicetree sw0 alias. This is mandatory.
 */
static const struct gpio_dt_spec button =
    GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);
static struct gpio_callback button_cb_data;

/*
 * The led0 devicetree alias is optional. If present, we'll use it
 * to turn on the LED whenever the button is pressed.
 */
static struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

void button_pressed(const struct device *dev, struct gpio_callback *cb,
                    uint32_t pins) {
  int ret;
  ret = gpio_pin_toggle_dt(&led);
  if (ret != 0) {
    printk("Could not toggle LED\n");
  }
}

int main(void) {
  int ret;

  if (!device_is_ready(led.port)) {
    printk("Error: led device %s is not ready\n", led.port->name);
    return 0;
  }

  if (!device_is_ready(button.port)) {
    printk("Error: button device %s is not ready\n", button.port->name);
    return 0;
  }

  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
  if (ret != 0) {
    printk("Error %d: failed to configure %s pin %d\n", ret, led.port->name,
           led.pin);
    return 0;
  }

  ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
  if (ret != 0) {
    printk("Error %d: failed to configure %s pin %d\n", ret, button.port->name,
           button.pin);
    return 0;
  }

  ret = gpio_pin_interrupt_configure_dt(&button, GPIO_INT_EDGE_TO_ACTIVE);
  if (ret != 0) {
    printk("Error %d: failed to configure interrupt on %s pin %d\n", ret,
           button.port->name, button.pin);
    return 0;
  }

  gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
  gpio_add_callback(button.port, &button_cb_data);
  printk("Set up button at %s pin %d\n", button.port->name, button.pin);

  return 0;
}
