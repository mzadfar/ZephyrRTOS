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

#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

static const struct pwm_dt_spec pwm_led_g =
    PWM_DT_SPEC_GET(DT_ALIAS(pwmledgreen));

static const struct pwm_dt_spec pwm_led_b =
    PWM_DT_SPEC_GET(DT_ALIAS(pwmledblue));

static const struct pwm_dt_spec pwm_led_r =
    PWM_DT_SPEC_GET(DT_ALIAS(pwmledred));

int main(void) {
  printk("PWM-based blinky\n");

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
    pwm_set_pulse_dt(&pwm_led_g, 0);
    pwm_set_pulse_dt(&pwm_led_b, 0);
    pwm_set_pulse_dt(&pwm_led_r, 0);
    k_sleep(K_SECONDS(1U));
    pwm_set_pulse_dt(&pwm_led_g, 10000);
    pwm_set_pulse_dt(&pwm_led_b, 10000);
    pwm_set_pulse_dt(&pwm_led_r, 10000);
    k_sleep(K_SECONDS(1U));
  }
  return 0;
}
