#include "buffer.h"

#ifdef __AVR_ARCH__
#include <avr/interrupt.h>
#endif

bool
isEmpty(volatile struct byteBuffer *buffer)
{
        return buffer->head == buffer->tail;
}

bool
isFull(volatile struct byteBuffer *buffer)
{
        return ((size_t) (buffer->head + 1) % (size_t) BUF_SIZE) == ((size_t) buffer->tail);
}


bool
hasData(volatile struct byteBuffer *buffer)
{
        return !isEmpty(buffer);
}

bool
init(volatile struct byteBuffer *buffer)
{
        buffer->head = buffer->buffer;
        buffer->tail = buffer->buffer;
        return true;
}

bool
push(volatile struct byteBuffer *buffer, uint8_t v)
{
        if (isFull(buffer)) {
                return false;
        }

        *(buffer->tail) = v;

        buffer->tail = buffer->tail + 1;
        if (buffer->tail > buffer->buffer + BUF_SIZE) {
                buffer->tail = buffer->buffer;
        }

        return true;
}

bool
pop(volatile struct byteBuffer *buffer, uint8_t *v) {
#ifdef __AVR_ARCH__
        cli();
#endif
        if (isEmpty(buffer)) {
                return false;
        }

        *v = *(buffer->head);

        if (++(buffer->head) > buffer->buffer + BUF_SIZE) {
                buffer->head = buffer->buffer;
        }
#ifdef __AVR_ARCH__
        sei();
#endif
        return true;
}
