/*
 * <sys/alcor_timer.h> — userland control of the system tick rate.
 *
 * Part of the Alcor2 libc contract (forked musl). Latency-sensitive apps vote
 * for an elevated PIT rate; the vote is refcounted and auto-released on exit.
 */
#ifndef _SYS_ALCOR_TIMER_H
#define _SYS_ALCOR_TIMER_H

#include <stdint.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/* _IOW('T', 1, uint32_t); private here. */
#define _ALCOR_IOC_TIMER_FAST ((1U << 30) | (0x54U << 8) | 1U | (4U << 16))

/*
 * Vote for (on != 0) or release (on == 0) the elevated tick rate on the
 * controlling tty. 0 on success.
 */
static inline int alcor_timer_fast(int on)
{
	uint32_t v = on ? 1U : 0U;
	return ioctl(0, _ALCOR_IOC_TIMER_FAST, &v);
}

#ifdef __cplusplus
}
#endif
#endif /* _SYS_ALCOR_TIMER_H */
