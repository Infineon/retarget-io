# Retarget IO

A utility library to retarget the standard input/output (STDIO) messages to a UART port. With this library, you can directly print messages on a UART terminal using `printf()`.

### What's Included?
* printf() support over a UART terminal
* Support for GCC, IAR, and ARM toolchains
* Thread safe write for NewLib

### What Changed?
#### v1.2.0
* Improve error handling
* Add de-initialization of the mutex to `cy_retarget_io_deinit`
* Update documentation for integration of the library in a RTOS environment.
#### v1.1.1
* Minor update for documentation & branding
#### v1.1.0
* Implemented system I/O retarget functions specific to ARM Compiler 6.
* Made _write implementation thread-safe for Newlib.
#### v1.0.0
* Initial release

### Supported Software and Tools
This version of the Retarget IO was validated for compatibility with the following Software and Tools:

| Software and Tools                        | Version |
| :---                                      | :----:  |
| ModusToolbox Software Environment         | 2.2.1   |
| GCC Compiler                              | 9.3.1   |
| IAR Compiler                              | 8.4     |
| ARM Compiler 6                            | 6.11    |

Minimum required ModusToolbox Software Environment: v2.0

### More information

* [API Reference Guide](https://cypresssemiconductorco.github.io/retarget-io/html/index.html)
* [Cypress Semiconductor, an Infineon Technologies Company](http://www.cypress.com)
* [Cypress Semiconductor GitHub](https://github.com/cypresssemiconductorco)
* [ModusToolbox](https://www.cypress.com/products/modustoolbox-software-environment)
* [PSoC 6 Code Examples using ModusToolbox IDE](https://github.com/cypresssemiconductorco/Code-Examples-for-ModusToolbox-Software)
* [PSoC 6 Middleware](https://github.com/cypresssemiconductorco/psoc6-middleware)
* [PSoC 6 Resources - KBA223067](https://community.cypress.com/docs/DOC-14644)

---
© Cypress Semiconductor Corporation, 2019-2021.