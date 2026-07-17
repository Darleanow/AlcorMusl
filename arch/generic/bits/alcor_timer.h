/**
 * @file arch/generic/bits/alcor_timer.h
 * @brief System timer ABI: the fast tick rate ioctl.
 */
#ifndef _BITS_ALCOR_TIMER_H
#define _BITS_ALCOR_TIMER_H

#include <stdint.h>

/** @brief ioctl, group 'T': vote for the fast tick rate from a uint32_t flag. */
#define ALCOR_IOC_TIMER_FAST ((1U << 30) | (0x54U << 8) | 1U | (4U << 16))

#endif /* _BITS_ALCOR_TIMER_H */
