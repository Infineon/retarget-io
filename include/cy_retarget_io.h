/***********************************************************************************************//**
 * \file cy_retarget_io.h
 *
 * \brief
 * Provides APIs for transmitting messages to or from the board via standard
 * printf/scanf functions. Messages are transmitted over a UART connection which
 * is generally connected to a host machine. Transmission is done at 115200 baud
 * using the tx and rx pins provided by the user of this library. The UART
 * instance is made available via cy_retarget_io_uart_obj in case any changes
 * to the default configuration are desired.
 * NOTE: If the application is built using newlib-nano, by default, floating
 * point format strings (%f) are not supported. To enable this support you must
 * add '-u _printf_float' to the linker command line.
 *
 ***************************************************************************************************
 * \copyright
 * Copyright 2018-2022 Cypress Semiconductor Corporation (an Infineon company) or
 * an affiliate of Cypress Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 **************************************************************************************************/

/**
 * \addtogroup group_board_libs Retarget IO
 * \{
 */

#pragma once

#include <stdio.h>
#include "cy_result.h"
#if defined(COMPONENT_MTB_HAL)
#include "mtb_hal_hw_types.h"
#elif defined(CY_USING_HAL)
#include "cyhal_hw_types.h"
#else
#include "cy_pdl.h"
#include <stdbool.h>
#endif


#if defined(__cplusplus)
extern "C" {
#endif

#if !defined(COMPONENT_MTB_HAL)

/* Define module errors */
/** A null pointer was passed as a function parameter. */
#define CY_RETARGET_IO_RSLT_NULL_UART_PTR    \
    (CY_RSLT_CREATE(CY_RSLT_TYPE_ERROR, CY_RSLT_MODULE_BOARD_LIB_RETARGET_IO, 0))

/** UART baud rate */
#define CY_RETARGET_IO_BAUDRATE             (115200)

/** UART HAL object used by this library */
#if defined (CY_USING_HAL)
extern cyhal_uart_t cy_retarget_io_uart_obj;
#endif

#endif //!defined(COMPONENT_MTB_HAL)


#if defined(COMPONENT_MTB_HAL)
/**
 * \brief Initialization function for redirecting low level IO commands to allow
 * sending messages over a UART interface. This will setup the communication
 * interface to allow using printf and related functions.
 *
 * Users of the library must do the following before invoking the init function
 *     1. Configure the UART using the device configurator generated structures or
 *        through manually written config structures. Configuration includes the UART TX
 *        and RX pins, CTS/RTS pins if flow control is desired, Baud Rate and other UART
 *        config parameters.
 *     2. Set up the clock source to the UART peripheral. This could be done using the
 *        device configurator or manually. Set up the clock divider value depending on
 *        the desired baud rate.
 *     2. Initialize the UART HW.
 *     3. Set up the HAL UART object.
 *     4. Pass the initilialized HAL UART object to the init
 *
 * In an RTOS environment, this function must be called after the RTOS has been
 * initialized.
 *
 * \param obj Pointer to the pre-initialized HAL UART object
 *
 * \returns CY_RSLT_SUCCESS if successfully initialized, else an error about
 * what went wrong
 */
cy_rslt_t cy_retarget_io_init(mtb_hal_uart_t* obj);
#elif defined(CY_USING_HAL)
/**
 * \brief Initialization function for redirecting low level IO commands to allow
 * sending messages over a UART interface. This will setup the communication
 * interface to allow using printf and related functions.
 *
 * In an RTOS environment, this function must be called after the RTOS has been
 * initialized.
 *
 * \param tx UART TX pin, if no TX pin use NC
 * \param rx UART RX pin, if no RX pin use NC
 * \param baudrate UART baudrate
 * \returns CY_RSLT_SUCCESS if successfully initialized, else an error about
 * what went wrong
 */
#define cy_retarget_io_init(tx, rx, baudrate) cy_retarget_io_init_fc(tx, rx, NC, NC, baudrate)

/**
 * \brief Initialization function for redirecting low level IO commands to allow
 * sending messages over a UART interface with flow control. This will setup the
 * communication interface to allow using printf and related functions.
 *
 * In an RTOS environment, this function must be called after the RTOS has been
 * initialized.
 *
 * \param tx UART TX pin, if no TX pin use NC
 * \param rx UART RX pin, if no RX pin use NC
 * \param cts UART CTS pin, if no CTS pin use NC
 * \param rts UART RTS pin, if no RTS pin use NC
 * \param baudrate UART baudrate
 * \returns CY_RSLT_SUCCESS if successfully initialized, else an error about
 * what went wrong
 */
cy_rslt_t cy_retarget_io_init_fc(cyhal_gpio_t tx, cyhal_gpio_t rx, cyhal_gpio_t cts,
                                 cyhal_gpio_t rts, uint32_t baudrate);

/**
 * \brief Initialization function for redirecting low level IO commands to allow
 * sending messages over a UART interface with a configurator generated configuration
 * struct. This will setup the communication interface to allow using printf and
 * related functions.
 *
 * This function assumes that you've already initialized cy_retarget_io_uart_obj
 * using some other mechanism.
 *
 * In an RTOS environment, this function must be called after the RTOS has been
 * initialized.
 *
 * \returns CY_RSLT_SUCCESS if successfully initialized, else an error about
 * what went wrong
 */
cy_rslt_t cy_retarget_io_init_hal(void);
#else // if defined(COMPONENT_MTB_HAL)
/**
 * \brief Initialization function for redirecting low level IO commands to allow
 * sending messages over a UART interface with a configurator generated configuration
 * struct. This will setup the communication interface to allow using printf and
 * related functions.
 *
 * This function assumes that you've already 1) initialized, and 2) enabled the
 * UART instance using PDL function calls.
 *
 * When not using the HAL, retarget-io is not thread safe.  Consider using printf
 * from a single thread or using a mutex to protect the printf calls.
 *
 * \param uart Pointer to UART object, usually named and defined in device-configurator.
 *
 * \returns CY_RSLT_SUCCESS if successfully initialized, else an error if the UART
 * parameter is a null pointer.
 */
cy_rslt_t cy_retarget_io_init(CySCB_Type* uart);
#endif // defined(COMPONENT_MTB_HAL)

#ifdef DOXYGEN

/** Defining this macro enables conversion of line feed (LF) into carriage
 * return followed by line feed (CR & LF) on the output direction (STDOUT). You
 * can define this macro through the DEFINES variable in the application
 * Makefile.
 */
#define CY_RETARGET_IO_CONVERT_LF_TO_CRLF

#endif // DOXYGEN

/**
 * \brief Checks whether there is data waiting to be written to the serial console.
 * \returns true if there are pending TX transactions, otherwise false
 */
bool cy_retarget_io_is_tx_active(void);

/**
 * \brief Releases the UART interface allowing it to be used for other purposes.
 * After calling this, printf and related functions will no longer work.
 */
void cy_retarget_io_deinit(void);

#if defined(__cplusplus)
}
#endif

/** \} group_board_libs */
