#include <iostream>
#include <cerrno>
#include <system_error>
#include <mqueue.h>
#include "msg_buffer.h"

int main()
{
    /*
     * Open the existing message queue for read-only access.
     * Do not use O_CREAT here unless you want to create a new queue,
     * because creating it with different attributes can cause mq_receive()
     * to fail due to a mismatched mq_msgsize.
     */
    mqd_t mq = mq_open("/posix_q", O_RDONLY);
    if (-1 == mq)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "mq_open() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    msg_buffer_t buff;
    uint prio;

    int ret = mq_receive(mq, (char *)&buff, sizeof(msg_buffer_t), &prio);
    if (-1 == ret)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "mq_receive() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }
    
    std::cout << ret << " bytes read: " << buff.data << std::endl;

    mq_close(mq);
    mq_unlink("/posix_q");
    return 0;
}

