#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <zmq.h>

#include "common.h"

int main(void) {

  int major;
  int minor;
  int patch;
  zmq_version(&major, &minor, &patch);
  printf("ZMQ Version: %d.%d.%d\n", major, minor, patch);
  void* context = zmq_ctx_new();
  void* responder = zmq_socket(context, ZMQ_REP);
  int rc = zmq_bind(responder, "tcp://*:5555");
  assert(rc == 0);

  while (true) {
    char *buffer = s_recv(responder,  10);
    puts("Received Hello");
    zmq_sleep(1);
    zmq_send(responder, "World", 5, 0);
  }
  return 0;
}