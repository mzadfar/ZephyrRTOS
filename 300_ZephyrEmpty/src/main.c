/**
 * @file main.c
 * @author M. Z.
 * @brief
 * @version 0.1
 * @date 2024-12-28
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <zephyr/kernel.h>

int main(void) {
#ifdef CONFIG_SAMPLE_DO_OUTPUT
  printk("Hello World from minimal!\n");
#endif

  return 0;
}
