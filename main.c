#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "ch.h"
#include "hal.h"

#undef USE_DYNAMIC_SERIAL_CFG

static THD_WORKING_AREA(waThread1, 128);
static THD_FUNCTION(Thread1, arg) {
  (void)arg;

  chRegSetThreadName("blinker");
  while (true) {
    palClearPad(GPIOC, 13U);
    chThdSleepMilliseconds(500);
    palSetPad(GPIOC, 13U);
    chThdSleepMilliseconds(2500);
  }
}

int main(void) {
  halInit();
  chSysInit();

#if defined(USE_DYNAMIC_SERIAL_CFG)

  // Initialise serial driver for UART1

  const SerialConfig serialcfg = {
    .speed = 115200,
    .cr1 = 0U,
    .cr2 = 0U,
    .cr3 = 0U
  };

  palSetPadMode(GPIOA, 9, PAL_MODE_ALTERNATE(7));       /* USART1 TX.       */
  palSetPadMode(GPIOA, 10, PAL_MODE_ALTERNATE(7));      /* USART1 RX.       */

  sdStart(&SD1, &serialcfg);

#else

  // Initialise serial driver for UART1

  sdStart(&SD1, NULL);

#endif

  const char * const msg = "Hello ChibiOS-RT!\n";
  size_t const msg_len = strlen(msg);

  chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO + 1, Thread1, NULL);

  // Run the main thread

  while (true) {
    sdWrite(&SD1, (uint8_t const * const) msg, msg_len);
    chThdSleepMilliseconds(1000);
  }
}
