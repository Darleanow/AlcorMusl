/**
 * @file arch/generic/bits/alcor_input.h
 * @brief Keyboard and mouse ABI: layouts, event record, ioctl codes.
 *
 * ioctl request encoding: bit 30 write flag, bits 23:16 argument size,
 * bits 15:8 subsystem group, bits 7:0 command ordinal.
 */
#ifndef _BITS_ALCOR_INPUT_H
#define _BITS_ALCOR_INPUT_H

#include <stdint.h>

/** @brief Selectable keyboard layouts. */
typedef enum
{
	ALCOR_KBD_US = 0, /**< US QWERTY. */
	ALCOR_KBD_FR = 1, /**< AZERTY lettering on a US scan map. */
	ALCOR_KBD_COUNT   /**< Number of layouts, not a selectable value. */
} alcor_kbd_layout_t;

/** @brief ioctl, group 'K': set the keyboard layout from a uint32_t id. */
#define ALCOR_IOC_KBD_SET_LAYOUT                                               \
	((1U << 30) | (0x4BU << 8) | 1U | (sizeof(uint32_t) << 16))

/** @brief ioctl, group 'K': toggle key-release sentinels from a uint32_t flag. */
#define ALCOR_IOC_KBD_RELEASE_EVENTS                                           \
	((1U << 30) | (0x4BU << 8) | 2U | (sizeof(uint32_t) << 16))

/** @brief One mouse event delivered by each read of /dev/mouse. */
typedef struct
{
	int32_t dx;      /**< Relative X delta. */
	int32_t dy;      /**< Relative Y delta. */
	int16_t dwheel;  /**< Vertical wheel notches, positive is up. */
	uint8_t buttons; /**< Bitmask of the ALCOR_MOUSE_BTN_* bits. */
	uint8_t flags;   /**< Reserved, zero today. */
} alcor_mouse_event_t;

/** @brief Left button bit in ::alcor_mouse_event_t buttons. */
#define ALCOR_MOUSE_BTN_LEFT 0x01

/** @brief Right button bit in ::alcor_mouse_event_t buttons. */
#define ALCOR_MOUSE_BTN_RIGHT 0x02

/** @brief Middle button bit in ::alcor_mouse_event_t buttons. */
#define ALCOR_MOUSE_BTN_MIDDLE 0x04

/** @brief ioctl, group 'M': toggle relative mode from a uint32_t flag. */
#define ALCOR_IOC_MOUSE_SET_RELATIVE                                           \
	((1U << 30) | ((uint32_t)'M' << 8) | 1U | (4U << 16))

/** @brief ioctl, group 'M': read the relative-mode flag into a uint32_t. */
#define ALCOR_IOC_MOUSE_GET_RELATIVE                                           \
	((2U << 30) | ((uint32_t)'M' << 8) | 2U | (4U << 16))

/** @brief ioctl, group 'M': read the cursor position into two int32_t. */
#define ALCOR_IOC_MOUSE_GET_POS                                                \
	((2U << 30) | ((uint32_t)'M' << 8) | 3U | (8U << 16))

#endif /* _BITS_ALCOR_INPUT_H */
