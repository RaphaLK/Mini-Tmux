#include "protocol.h"
#include "pty_utils.h"
#include <sys/socket.h>
#include <sys/signal.h>
#include <sys/un.h>
#include <poll.h>
#include <unistd.h>

struct Session {
  int id;
  pid_t child_pid;
  int pty_master_fd;
  int attached_client_fd;
  bool active;
};

Session sessions[MAX_SESSIONS];
int client_fds[MAX_CLIENTS];

int setup_socket() {
  // remove stale socket from previous run
  unlink(SOCKET_PATH); 

  int server_fd = socket(AF_UNIX, SOCK_STREAM, 0); // reliable ordered bytestream

  struct sockaddr_un addr {}; // define a sockaddr_un struct and memset to 0

  // AF_UNIX -- Local only (Faster than TCP)
  addr.sun_family = AF_UNIX; // socket unix family = local machine ipc via filesystem
  strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path) - 1);

  bind(server_fd, (struct sockaddr*) &addr, sizeof(addr));
  listen(server_fd, 10); // maximum 10 connections before kernel refuses

  return server_fd;
}

void setup_signals() {
  signal(SIGPIPE, SIG_IGN);
}


int main() {


}