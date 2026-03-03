#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>
#include <cstring>

#define SOCKET_PATH "/tmp/mini-tmux.sock"
#define MAX_SESSIONS 5
#define BUFFER_SIZE 4096

enum class MsgType : uint8_t {
  CREATE_SESSION = 1,
  ATTACH_SESSION = 2,
  DETACH = 3,
  LIST_SESSION = 4,
  DATA = 5,
  WINSIZE_CHANGE = 6,
  SESSION_LIST = 7,
  ERROR_RESP = 8,
  OK_RESP = 9
};

#endif