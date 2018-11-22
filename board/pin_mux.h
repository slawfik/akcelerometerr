/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PIN_MUX_H_
#define _PIN_MUX_H_

/*!
 * @addtogroup pin_mux
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Calls initialization functions.
 *
 */
void BOARD_InitBootPins(void);

#define SOPT5_UART0RXSRC_UART_RX 0x00u /*!<@brief UART0 receive data source select: UART0_RX pin */
#define SOPT5_UART0TXSRC_UART_TX 0x00u /*!<@brief UART0 transmit data source select: UART0_TX pin */

/*! @name PORTA2 (number 28), J1[4]/D1/UART0_TX
  @{ */
#define BOARD_INITPINS_DEBUG_UART_TX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_DEBUG_UART_TX_PIN 2U     /*!<@brief PORTA pin index: 2 */
                                                /* @} */

/*! @name PORTA1 (number 27), J1[2]/D0/UART0_RX
  @{ */
#define BOARD_INITPINS_DEBUG_UART_RX_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_DEBUG_UART_RX_PIN 1U     /*!<@brief PORTA pin index: 1 */
                                                /* @} */

/*! @name PORTB18 (number 53), D3[1]/LEDRGB_RED
  @{ */
#define BOARD_INITPINS_LED_RED_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_INITPINS_LED_RED_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_LED_RED_PIN 18U    /*!<@brief PORTB pin index: 18 */
                                          /* @} */

/*! @name PORTB19 (number 54), D3[4]/LEDRGB_GREEN
  @{ */
#define BOARD_INITPINS_LED_GREEN_GPIO GPIOB /*!<@brief GPIO device name: GPIOB */
#define BOARD_INITPINS_LED_GREEN_PORT PORTB /*!<@brief PORT device name: PORTB */
#define BOARD_INITPINS_LED_GREEN_PIN 19U    /*!<@brief PORTB pin index: 19 */
                                            /* @} */

/*! @name PORTD1 (number 74), J2[12]/D3[3]/D13/LEDRGB_BLUE
  @{ */
#define BOARD_INITPINS_LED_BLUE_GPIO GPIOD /*!<@brief GPIO device name: GPIOD */
#define BOARD_INITPINS_LED_BLUE_PORT PORTD /*!<@brief PORT device name: PORTD */
#define BOARD_INITPINS_LED_BLUE_PIN 1U     /*!<@brief PORTD pin index: 1 */
                                           /* @} */

/*! @name PORTE24 (number 24), U7[4]/I2C0_SCL
  @{ */
#define BOARD_INITPINS_ACCEL_SCL_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_ACCEL_SCL_PIN 24U    /*!<@brief PORTE pin index: 24 */
                                            /* @} */

/*! @name PORTE25 (number 25), U7[6]/I2C0_SDA
  @{ */
#define BOARD_INITPINS_ACCEL_SDA_PORT PORTE /*!<@brief PORT device name: PORTE */
#define BOARD_INITPINS_ACCEL_SDA_PIN 25U    /*!<@brief PORTE pin index: 25 */
                                            /* @} */

/*! @name PORTA14 (number 34), U7[11]/INT1_ACCEL
  @{ */
#define BOARD_INITPINS_ACCEL_INT1_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_ACCEL_INT1_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_ACCEL_INT1_PIN 14U    /*!<@brief PORTA pin index: 14 */
                                             /* @} */

/*! @name PORTA15 (number 35), U7[9]/INT2_ACCEL
  @{ */
#define BOARD_INITPINS_ACCEL_INT2_GPIO GPIOA /*!<@brief GPIO device name: GPIOA */
#define BOARD_INITPINS_ACCEL_INT2_PORT PORTA /*!<@brief PORT device name: PORTA */
#define BOARD_INITPINS_ACCEL_INT2_PIN 15U    /*!<@brief PORTA pin index: 15 */
                                             /* @} */

/*!
 * @brief Configures pin routing and optionally pin electrical features.
 *
 */
void BOARD_InitPins(void);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _PIN_MUX_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
