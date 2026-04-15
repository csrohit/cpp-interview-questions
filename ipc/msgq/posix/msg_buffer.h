#ifndef __MSG_BUFFER_H__
#define __MSG_BUFFER_H__

#include <cstdint>
struct msg_buffer_t
{
    uint64_t type;
    char data[50];
};

#endif /* __MSG_BUFFER_H__ */
