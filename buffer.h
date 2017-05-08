#ifndef __buffer_h
#define __buffer_h

#include <inttypes.h>
#include <stddef.h>
#include <stdbool.h>

#ifndef BUF_SIZE
#define BUF_SIZE 8
#endif

struct byteBuffer {
        volatile uint8_t buffer[BUF_SIZE];
        volatile uint8_t *head;
        volatile uint8_t *tail;
};

bool init(volatile struct byteBuffer *buffer);
bool push(volatile struct byteBuffer *buffer, uint8_t v);
bool pop(volatile struct byteBuffer *buffer, uint8_t *v);
bool hasData(volatile struct byteBuffer *buffer);
bool isEmpty(volatile struct byteBuffer *buffer);

#endif
