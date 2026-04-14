#include<iostream>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<cerrno>
#include<system_error>

int main()
{
    // Generate the same IPC key as the writer using the same file path and project id.
    key_t key = ftok("/tmp/shmfile", 'a');
    if (-1 == key)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "ftok() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    // Obtain the shared memory ID for an existing segment.
    // The size parameter must match the segment size used by the writer.
    // 0666 requests read/write permissions.
    int shmid = shmget(key, 1024, 0666);
    if (-1 == shmid)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "shmget() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    // Attach the shared memory segment into the process address space.
    // NULL/0 means let the kernel choose the attach address and give default access.
    char* str = (char *)shmat(shmid, NULL, 0);
    if ((void *) -1 == str)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "shmat() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }
    
    // Print the string that the writer placed into shared memory.
    std::cout << "Read string: " << str << std::endl;

    // Detach from the shared memory segment when done reading.
    int ret = shmdt(str);
    if (-1 == ret)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "shmdt() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    // Remove the shared memory segment from the system.
    // This frees the segment once no processes are attached.
    ret = shmctl(shmid, IPC_RMID, nullptr);
    if (-1 == ret)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "shmctl() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    return 0;
}
