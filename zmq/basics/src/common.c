#include "common.h"

#include <string.h>
#include <zmq.h>

char* s_recv(void* socket, unsigned int buf_size) {
  char buffer[buf_size + 1];
  int size = zmq_recv(socket, buffer, buf_size, 0);
  if (size == -1) return NULL;
  if (size > 255) size = 255;
  buffer[size] = '\0';
  return strdup(buffer);
}