#include <iostream>
#include <cerrno>
#include <system_error>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msg_buffer.h"

int main()
{
    std::cout << "Writer\n";

    key_t key = ftok("/tmp/msgq", 'a');
    if (-1 == key)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "ftok() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    int msgid = msgget(key, 0666 | IPC_CREAT);
    if (-1 == msgid)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "msgget() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    msg_buffer_t buff;
    buff.type = 1;
    std::snprintf(buff.data, sizeof(buff.data), "This is message written into msgqueue\n");

    int ret = msgsnd(msgid, &buff, sizeof(msg_buffer_t), 0);
    if (-1 == ret)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "msgsnd() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }
    
    std::cout << "Msg sent: " << buff.data << std::endl;
    
    return 0;
}
