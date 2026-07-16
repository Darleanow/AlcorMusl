/**
 * @file arch/generic/bits/alcor_syscall.h
 * @brief Alcor2 custom syscall numbers.
 *
 * Defines both the __NR_ and SYS_ spellings so musl's syscall.h generator
 * never has to rewrite this file.
 */
#ifndef _BITS_ALCOR_SYSCALL_H
#define _BITS_ALCOR_SYSCALL_H

/** @brief Version of the Alcor2 kernel/userland ABI described by bits/alcor_*.h. */
#define ALCOR_ABI_VERSION 2

/**
 * @brief Namespace bit separating Alcor2 syscalls from upstream numbers.
 *
 * Upstream syscall numbers are positive C ints and bit 30 is the x32 marker,
 * so no present or future upstream number can ever carry bit 31. The Alcor2
 * space is disjoint by construction and never needs renumbering.
 */
#define ALCOR_SYSCALL_BIT 0x80000000U

/** @brief Register the TTY foreground PID that receives SIGINT on Ctrl+C. */
#define __NR_ALCOR_SET_FG_PID	(ALCOR_SYSCALL_BIT | 1)

/** @brief Fill a caller-provided ::alcor_fb_info_t with framebuffer geometry. */
#define __NR_ALCOR_FB_INFO	(ALCOR_SYSCALL_BIT | 2)

/** @brief Map the linear framebuffer into the calling process. */
#define __NR_ALCOR_FB_MMAP	(ALCOR_SYSCALL_BIT | 3)

/** @brief Alias of ::__NR_ALCOR_SET_FG_PID in the libc naming convention. */
#define SYS_ALCOR_SET_FG_PID	__NR_ALCOR_SET_FG_PID

/** @brief Alias of ::__NR_ALCOR_FB_INFO in the libc naming convention. */
#define SYS_ALCOR_FB_INFO	__NR_ALCOR_FB_INFO

/** @brief Alias of ::__NR_ALCOR_FB_MMAP in the libc naming convention. */
#define SYS_ALCOR_FB_MMAP	__NR_ALCOR_FB_MMAP

#endif /* _BITS_ALCOR_SYSCALL_H */
