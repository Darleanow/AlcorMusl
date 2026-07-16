/**
 * @file arch/x86_64/bits/alcor_syscall.h
 * @brief Alcor2 custom syscall numbers, single source of the contract.
 *
 * The 1024+ band can never collide with numbers assigned upstream.
 * Both spellings are defined here so this file needs no sed processing.
 */
#ifndef _BITS_ALCOR_SYSCALL_H
#define _BITS_ALCOR_SYSCALL_H

/** @brief Version of the Alcor2 kernel/userland ABI described by bits/alcor_*.h. */
#define ALCOR_ABI_VERSION 1

/** @brief Register the TTY foreground PID that receives SIGINT on Ctrl+C. */
#define __NR_ALCOR_SET_FG_PID	1024

/** @brief Fill a caller-provided ::alcor_fb_info_t with framebuffer geometry. */
#define __NR_ALCOR_FB_INFO	1025

/** @brief Map the linear framebuffer into the calling process. */
#define __NR_ALCOR_FB_MMAP	1026

/** @brief Alias of ::__NR_ALCOR_SET_FG_PID in the libc naming convention. */
#define SYS_ALCOR_SET_FG_PID	__NR_ALCOR_SET_FG_PID

/** @brief Alias of ::__NR_ALCOR_FB_INFO in the libc naming convention. */
#define SYS_ALCOR_FB_INFO	__NR_ALCOR_FB_INFO

/** @brief Alias of ::__NR_ALCOR_FB_MMAP in the libc naming convention. */
#define SYS_ALCOR_FB_MMAP	__NR_ALCOR_FB_MMAP

#endif /* _BITS_ALCOR_SYSCALL_H */
