#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <cstdint>
#include <cstring>

#define SOCKET_PATH "/tmp/mini-tmux.sock"
#define MAX_SESSIONS 5
#define BUFFER_SIZE 4096
#define MAX_CLIENTS 5

// message type defintion
enum class MsgType : uint8_t {
  CREATE_SESSION = 1,
  ATTACH_SESSION = 2,
  DETACH = 3, // close session, keep pty alive
  LIST_SESSION = 4,
  DATA = 5,
  WINSIZE_CHANGE = 6, // TIOCSWINSZ
  SESSION_LIST = 7,
  ERROR_RESP = 8,
  OK_RESP = 9
};

// message header definition, ensure packing - 9 bytes: 1 byte type, 4 bytes session id, 4 bytes payload_len
struct __attribute__((packed)) MsgHeader {
  MsgType type;
  uint32_t session_id;
  uint32_t payload_len;
};

// 
struct __attribute__((packed)) WinsizePayload {
  uint16_t rows; // horizontal lines  
  uint16_t cols; // chars per line
};

#endif