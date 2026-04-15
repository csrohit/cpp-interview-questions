#include <iostream>
#include <cerrno>
#include <system_error>
#include <mqueue.h>
#include "msg_buffer.h"



int main()
{
    /*
     * Create the message queue with attributes that match the message size.
     * The mq_msgsize field must be at least as large as the buffer passed to
     * mq_send() and mq_receive(), otherwise mq_receive() can fail with EMSGSIZE.
     */
    struct mq_attr attr = {};
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = sizeof(msg_buffer_t);

    mqd_t mq = mq_open("/posix_q", O_CREAT | O_WRONLY, 0644, &attr);
    if (-1 == mq)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "mq_open() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    msg_buffer_t buff;
    buff.type = 1;
    std::snprintf(buff.data, sizeof(buff.data), "Hello from mq\n");

    int ret = mq_send(mq, (const char *)&buff, sizeof(msg_buffer_t), 1);
    if (-1 == ret)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "mq_send() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }
    
    std::cout << "Message sent: " << buff.data << std::endl;
    mq_close(mq);
    return 0;
}
