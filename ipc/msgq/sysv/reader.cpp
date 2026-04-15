#include <iostream>
#include <cerrno>
#include <system_error>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "msg_buffer.h"

int main()
{
    std::cout << "Reader\n";

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

    int ret = msgrcv(msgid, &buff, sizeof(msg_buffer_t), 1, IPC_NOWAIT);
    if (-1 == ret)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "msgrcv() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }
    
    std::cout << ret << " bytes received : " << buff.data << std::endl;

    ret = msgctl(msgid, IPC_RMID, nullptr);
    if (-1 == ret)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "msgctl() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    std::cout << "msgq deleted successfully\n";
    
    return 0;
}
