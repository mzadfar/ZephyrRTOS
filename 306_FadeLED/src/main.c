/**
 * @file main.c
 * @author AH
 * @brief
 * @version 0.1
 * @date 2024-12-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define NUM_STEPS 100U
#define SLEEP_MSEC 20U

static const struct pwm_dt_spec pwm_led_g =
    PWM_DT_SPEC_GET(DT_ALIAS(pwmledgreen));
static const struct pwm_dt_spec pwm_led_b =
    PWM_DT_SPEC_GET(DT_ALIAS(pwmledblue));
static const struct pwm_dt_spec pwm_led_r =
    PWM_DT_SPEC_GET(DT_ALIAS(pwmledred));

void fade_led(struct pwm_dt_spec pwm_led) {
  static uint32_t pulse_width = 0U;
  uint32_t step = pwm_led.period / NUM_STEPS;
  static uint8_t dir = 1U;
  int ret;

  ret = pwm_set_pulse_dt(&pwm_led, pulse_width);
  if (ret) {
    printk("Error %d: failed to set pulse width\n", ret);
    // return 0;
  }
  printk("Using pulse width %d%%\n", 100 * pulse_width / pwm_led.period);

  if (dir) {
    pulse_width += step;
    if (pulse_width >= pwm_led.period) {
      pulse_width = pwm_led.period - step;
      dir = 0U;
    }
  } else {
    if (pulse_width >= step) {
      pulse_width -= step;
    } else {
      pulse_width = step;
      dir = 1U;
    }
  }
}

int main(void) {

  printk("PWM-based LED fade\n");

  if (!pwm_is_ready_dt(&pwm_led_g)) {
    printk("Error: PWM device %s is not ready\n", pwm_led_g.dev->name);
    return 0;
  }

  if (!pwm_is_ready_dt(&pwm_led_b)) {
    printk("Error: PWM device %s is not ready\n", pwm_led_b.dev->name);
    return 0;
  }

  if (!pwm_is_ready_dt(&pwm_led_r)) {
    printk("Error: PWM device %s is not ready\n", pwm_led_r.dev->name);
    return 0;
  }

  while (1) {
    fade_led(pwm_led_g);
    fade_led(pwm_led_b);
    fade_led(pwm_led_r);
    k_sleep(K_MSEC(SLEEP_MSEC));
  }
  return 0;
}