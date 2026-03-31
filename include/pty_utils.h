#ifndef PTY_UTILS_H
#define PTY_UTILS_H

// POSIX API Interface for terminal I/O behavior
#include <termios.h>
#include <sys/types.h>
#include <cstdint>

int create_pty_session(pid_t *child_pid);

void set_winsize(int fd, uint16_t rows, uint16_t cols);

void set_raw_mode(int fd, struct termios *saved);

void restore_term(int fd, struct termios *saved);

#endif