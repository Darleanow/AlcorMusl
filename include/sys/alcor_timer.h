/**
 * @file include/sys/alcor_timer.h
 * @brief Userland control of the system tick rate.
 *
 * Verb wrapper over the ABI declared in <bits/alcor_timer.h>. The vote is
 * refcounted by the kernel and auto-released on process exit.
 */
#ifndef _SYS_ALCOR_TIMER_H
#define _SYS_ALCOR_TIMER_H

#include <bits/alcor_timer.h>
#include <sys/ioctl.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Vote for or release the elevated tick rate on the controlling tty.
 * @param on Non-zero adds a vote, 0 releases it.
 * @return 0 on success, negative on failure.
 */
static inline int alcor_timer_fast(int on)
{
	uint32_t v = on ? 1U : 0U;
	return ioctl(0, ALCOR_IOC_TIMER_FAST, &v);
}

#ifdef __cplusplus
}
#endif
#endif /* _SYS_ALCOR_TIMER_H */
