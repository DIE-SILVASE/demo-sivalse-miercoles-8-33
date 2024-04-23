/**
 * @file interr.c
 * @brief Interrupt service routines for the STM32F4 platform.
 * @author Sistemas Digitales II
 * @date 2024-01-01
 */
// Include HW dependencies:
#include "port_system.h"
#include "port_button.h"

// Include headers of different port elements:

//------------------------------------------------------
// INTERRUPT SERVICE ROUTINES
//------------------------------------------------------
/**
 * @brief Interrupt service routine for the System tick timer (SysTick).
 *
 * @note This ISR is called when the SysTick timer generates an interrupt.
 * The program flow jumps to this ISR and increments the tick counter by one millisecond.
 *
 * > **TO-DO alumnos:**
 * >
 * > ✅ 1. **Increment the System tick counter `msTicks` in 1 count.** To do so, use the function `port_system_get_millis()` and `port_system_get_millis()`.
 *
 * @warning **The variable `msTicks` must be declared volatile!** Just because it is modified by a call of an ISR, in order to avoid [*race conditions*](https://en.wikipedia.org/wiki/Race_condition). **Added to the definition** after *static*.
 *
 */
void SysTick_Handler(void)
{
    port_system_set_millis(port_system_get_millis() + 1);
}

void EXTI15_10_IRQHandler(void)
{
    /* ISR user button */
    if (EXTI->PR & BIT_POS_TO_MASK(buttons_arr[BUTTON_0_ID].pin))
    {
        buttons_arr[BUTTON_0_ID].flag_pressed = !port_system_gpio_read(buttons_arr[BUTTON_0_ID].p_port, buttons_arr[BUTTON_0_ID].pin);
        EXTI->PR = BIT_POS_TO_MASK(buttons_arr[BUTTON_0_ID].pin);
    }
}
