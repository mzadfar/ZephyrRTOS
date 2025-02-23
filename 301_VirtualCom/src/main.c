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

#include <zephyr/kernel.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS 1000

int main(void) {
  bool switch_state = true;

  while (true) {
    switch_state = !switch_state;
    printf("Hello World!: %s\n",
           switch_state ? "Todays is not the beginning and not the end!"
                        : "Just leave at this moment! Smile please!");
    k_msleep(SLEEP_TIME_MS);
  }
  return 0;
}
