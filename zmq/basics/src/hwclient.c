#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <zmq.h>

int main(void) {
  int major;
  int minor;
  int patch;
  zmq_version(&major, &minor, &patch);
  printf("ZMQ Version: %d.%d.%d\n", major, minor, patch);

  void *context = zmq_ctx_new();
  void *requester = zmq_socket(context, ZMQ_REQ);
  zmq_connect(requester, "tcp://localhost:5555");

  for (int request_number = 0; request_number < 10; request_number++) {
    char buffer[10];
    printf("Sending Hello %d...\n", request_number);
    zmq_send(requester, "Hello", 5, 0);
    zmq_recv(requester, buffer, 10, 0);
    printf("Received World %d\n", request_number);
  }
  zmq_close(requester);
  zmq_ctx_destroy(context);
  return 0;
}