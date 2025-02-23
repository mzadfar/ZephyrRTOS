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

#define NUM_STEPS 100U
#define SLEEP_DELTA_MSEC 20U

static const struct pwm_dt_spec pwm_led_g =
    PWM_DT_SPEC_GET(DT_ALIAS(pwmledgreen));
static const struct pwm_dt_spec pwm_led_b =
    PWM_DT_SPEC_GET(DT_ALIAS(pwmledblue));
static const struct pwm_dt_spec pwm_led_r =
    PWM_DT_SPEC_GET(DT_ALIAS(pwmledred));

void led_delta_timer_handler(struct k_timer *timer_info) {
  static uint32_t pulse_width_nsec = 0U;
  static uint32_t pulse_width_delta_nsec = 0U;
  static uint32_t steps_taken = 0U;
  static bool increasing_intensity = true;
  int ret;

  pulse_width_delta_nsec = pwm_led_g.period / NUM_STEPS;

  if (increasing_intensity) {
    if (steps_taken < NUM_STEPS) {
      ret = pwm_set_pulse_dt(&pwm_led_g, pulse_width_nsec);
      if (ret) {
        printk("Error %d: PWM device %s failed to set pulse width\n", ret,
               pwm_led_g.dev->name);
      }
      ret = pwm_set_pulse_dt(&pwm_led_b, pulse_width_nsec);
      if (ret) {
        printk("Error %d: PWM device %s failed to set pulse width\n", ret,
               pwm_led_b.dev->name);
      }
      ret = pwm_set_pulse_dt(&pwm_led_r, pulse_width_nsec);
      if (ret) {
        printk("Error %d: PWM device %s failed to set pulse width\n", ret,
               pwm_led_r.dev->name);
      }
      steps_taken++;
      pulse_width_nsec += pulse_width_delta_nsec;
    } else {
      increasing_intensity = false;
      steps_taken--;
      pulse_width_nsec -= pulse_width_delta_nsec;
    }
  } else {
    if (steps_taken > 0) {
      ret = pwm_set_pulse_dt(&pwm_led_g, pulse_width_nsec);
      if (ret) {
        printk("Error %d: PWM device %s failed to set pulse width\n", ret,
               pwm_led_g.dev->name);
      }
      ret = pwm_set_pulse_dt(&pwm_led_b, pulse_width_nsec);
      if (ret) {
        printk("Error %d: PWM device %s failed to set pulse width\n", ret,
               pwm_led_b.dev->name);
      }
      ret = pwm_set_pulse_dt(&pwm_led_r, pulse_width_nsec);
      if (ret) {
        printk("Error %d: PWM device %s failed to set pulse width\n", ret,
               pwm_led_r.dev->name);
      }
      steps_taken--;
      pulse_width_nsec -= pulse_width_delta_nsec;
    } else {
      increasing_intensity = true;
      steps_taken++;
      pulse_width_nsec += pulse_width_delta_nsec;
    }
  }
}

K_TIMER_DEFINE(led_delta_timer, led_delta_timer_handler, NULL);

int main(void) {
  printk("PWM-based LED fade\n");

  if (!device_is_ready(pwm_led_g.dev)) {
    printk("Error: PWM device %s is not ready\n", pwm_led_g.dev->name);
    return 0;
  }

  if (!device_is_ready(pwm_led_b.dev)) {
    printk("Error: PWM device %s is not ready\n", pwm_led_b.dev->name);
    return 0;
  }

  if (!device_is_ready(pwm_led_r.dev)) {
    printk("Error: PWM device %s is not ready\n", pwm_led_r.dev->name);
    return 0;
  }

  k_timer_start(&led_delta_timer, K_MSEC(SLEEP_DELTA_MSEC),
                K_MSEC(SLEEP_DELTA_MSEC));
  return 0;
}
