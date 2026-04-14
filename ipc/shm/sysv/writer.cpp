#include <cstring>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <cerrno>
#include <iostream>
#include <system_error>

int main()
{
    // Data to write into the shared memory segment.
    const char* data = "Data written by Writer process\n";
    int shmid = -1;

    // Generate a key for the shared memory segment.
    // ftok() uses a file path and an id character to generate a unique System V IPC key.
    key_t key = ftok("/tmp/shmfile", 'a');
    if (key == -1) {
        std::error_code ec(errno, std::generic_category());
        std::cout << "ftok() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    // Create a shared memory segment of 1024 bytes.
    // 0666 gives read/write permissions to user, group and others.
    // IPC_CREAT creates the segment if it doesn't exist, and IPC_EXCL makes it fail if it already exists.
    shmid = shmget(key, 1024, 0666 | IPC_CREAT | IPC_EXCL);
    if (-1 == shmid)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "shmget() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }
    std::cout<< "shmget() succeeded shmid=" << shmid << std::endl;

    // Attach the shared memory segment into this process's address space.
    // The second argument is the desired attach address (nullptr lets the kernel choose).
    // The third argument is flags (0 means default read/write access).
    char* str = (char *)shmat(shmid, nullptr, 0);
    if((void *) -1 == str)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "shmat() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    // Copy the message into shared memory so the reader process can access it.
    strcpy(str, data);

    std::cout << "shmat() succeeded addr=" << static_cast<void *>(str) << std::endl;
    
    // Detach from the shared memory segment when finished.
    int ret = shmdt(str);
    if (-1 == ret)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "shmdt() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    return 0;
}

