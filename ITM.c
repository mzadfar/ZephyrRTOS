/////////////////////////////////////////////////////////////////////////////////////////////////////////
//					Implementation of printf like feature
// using ARM Cortex M3/M4/ ITM functionality
// This function will not work for ARM Cortex M0/M0+
// If you are using Cortex M0, then you can use semihosting feature of openOCD
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Debug Exception and Monitor Control Register base address
// From Libraries/CMSIS/Include/core_cm4.h

// /* Memory mapping of Cortex-M4 Hardware */
// #define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address  */
// #define ITM_BASE            (0xE0000000UL)                            /*!< ITM Base Address                   */
// #define CoreDebug_BASE      (0xE000EDF0UL)                            /*!< Core Debug Base Address            */
// #define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address               */
// #define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address                  */
// #define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address  */

// #define SCnSCB              ((SCnSCB_Type    *)     SCS_BASE      )   /*!< System control Register not in SCB */
// #define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB configuration struct           */
// #define SysTick             ((SysTick_Type   *)     SysTick_BASE  )   /*!< SysTick configuration struct       */
// #define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC configuration struct          */
// #define ITM                 ((ITM_Type       *)     ITM_BASE      )   /*!< ITM configuration struct           */
// #define CoreDebug           ((CoreDebug_Type *)     CoreDebug_BASE)   /*!< Core Debug configuration struct    */


// /** \brief  Structure type to access the Core Debug Register (CoreDebug).
//  */
// typedef struct
// {
//   __IO uint32_t DHCSR;                   /*!< Offset: 0x000 (R/W)  Debug Halting Control and Status Register    */
//   __O  uint32_t DCRSR;                   /*!< Offset: 0x004 ( /W)  Debug Core Register Selector Register        */
//   __IO uint32_t DCRDR;                   /*!< Offset: 0x008 (R/W)  Debug Core Register Data Register            */
//   __IO uint32_t DEMCR;                   /*!< Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */
// } CoreDebug_Type;

#define DEMCR *((volatile uint32_t *)0xE000EDFCU)

/* ITM register addresses */
#define ITM_STIMULUS_PORT0 *((volatile uint32_t *)0xE0000000)
#define ITM_TRACE_EN *((volatile uint32_t *)0xE0000E00)

void ITM_SendChar(uint8_t ch) {

  // Enable TRCENA
  DEMCR |= (1 << 24);

  // enable stimulus port 0
  ITM_TRACE_EN |= (1 << 0);

  // read FIFO status in bit [0]:
  while (!(ITM_STIMULUS_PORT0 & 1))
    ;

  // Write to ITM stimulus port0
  ITM_STIMULUS_PORT0 = ch;
}

/////////////////////////////////////////////////////////////////////////////////////////
// Use ITM_SendChar function from Libraries/CMSIS/Include/core_cm4.h
void SWO_PrintString(char const *s) {
  while (*s != '\0') {
    ITM_SendChar((uint32_t)*s++);
  }
}
void printString(char *const str) {
  // char msg[20];
  // static uint32_t counter = 0;
  // size_t const len = sprintf(str, "Counter = %lu\n\r", counter++);
  SWO_PrintString(str);
}

// To use in main() like:
printString("Task 2 function; semihosting\n");

////////////////////////////// Another detail example
/////////////////////////////////

// Some functions for printing ower SWO (debug only)
void SWO_PrintChar(char const c, uint8_t const portNo) {
  volatile int timeout;

  /* Check if Trace Control Register (ITM->TCR at 0xE0000E80) is set */
  /* check Trace Control Register if ITM trace is enabled*/
  if ((ITM->TCR & ITM_TCR_ITMENA_Msk) == 0) {
    return; /* not enabled? */
  }
  /* Check if the requested channel stimulus port (ITM->TER at 0xE0000E00) is
   * enabled */
  /* check Trace Enable Register if requested port is enabled */
  if ((ITM->TER & (1ul << portNo)) == 0) {
    return; /* requested port not enabled? */
  }
  timeout = 5000; /* arbitrary timeout value */
  while (ITM->PORT[0].u32 == 0) {
    /* Wait until STIMx is ready, then send data */
    if (--timeout == 0) {
      return; /* not able to send */
    }
  }
  ITM->PORT[0].u8 = (uint8_t)c;
}
void SWO_PrintString(char const *s, uint8_t const portNumber) {
  while (*s != '\0') {
    SWO_PrintChar(*s++, portNumber);
  }
}
void printString(char const *str) { SWO_PrintString(str, 0); }

// This circus is for demonstrating compiler optimizations
void f1();
void f2();
void f3();

// RTC will trigger every second, toggel LED and print message over SWO
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc) {
  char str[] = "Hello";
  f1();
}

void f1() {
  char c = 'c';
  f2();
}

void f2() {
  static uint8_t dummy;
  dummy++;
  f3();
}

void f3() {
  char msg[20];
  static uint32_t counter = 0;
  size_t const len = sprintf(msg, "Counter = %lu\n\r", counter++);
  printString(msg);
  HAL_UART_Transmit(&huart3, (uint8_t *)msg, len, 10);
  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_15);
}
