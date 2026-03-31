#include "pty_utils.h"

#include <pty.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int create_pty_session(pid_t *child_pid)
{
  int master_fd, flags;
  struct winsize ws = {24, 80, 0, 0};

  // openpty() + fork()
  pid_t pid = forkpty(&master_fd, nullptr, nullptr, &ws);

  if (pid < 0)
    return -1;

  // if child process, replace process image with bash 
  // _exit if it fails, doesn't flush parent's stdio buffers
  if (pid == 0)
  {
    execl("/bin/bash", "bash", nullptr);
    _exit(1);
  }

  flags = fcntl(master_fd, F_GETFL, 0);
  // master_fd is non blocking -- poll() wont block on read     
  fcntl(master_fd, F_SETFL, flags | O_NONBLOCK);
  *child_pid = pid;
  return master_fd;
}

void set_winsize(int fd, uint16_t rows, uint16_t cols)
{
  struct winsize ws;
  ws.ws_row = rows;
  ws.ws_col = cols;
  ws.ws_xpixel = 0;
  ws.ws_ypixel = 0;
  // set window size
  ioctl(fd, TIOCSWINSZ, &ws);
}

void set_raw_mode(int fd, struct termios *saved)
{
  // save the current terminal settings
  tcgetattr(fd, saved);
  struct termios raw = *saved;

  // abstracted off for ECHO, ICANON, ISIG, IXON, OPOST
  cfmakeraw(&raw);
  raw.c_cc[VMIN] = 1;
  raw.c_cc[VTIME] = 0;
  tcsetattr(fd, TCSAFLUSH, &raw);
}

void restore_term(int fd, struct termios *saved)
{
  tcsetattr(fd, TCSAFLUSH, saved);
}