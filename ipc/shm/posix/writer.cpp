#include <cstring>
#include <iostream>
#include <cerrno>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
    const char* str = "String is written by writer\n";

    /*
     * Open or create a POSIX shared memory object.
     * 
     * "/shmfile" is the name of the shared memory object.
     * O_CREAT requests creation if it does not already exist.
     * O_RDWR opens the object for read and write access.
     * 0666 sets read/write permission for owner, group, and others.
     */
    int fd = shm_open("/shmfile", O_CREAT|O_RDWR, 0666);
    if (-1 == fd)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "shm_open() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    std::cout << "Opened fd=" << fd << std::endl;

    /*
     * Allocate the shared memory object size.
     * ftruncate() sets the object length to 1024 bytes.
     * Without this call, mmap() cannot safely map the region.
     */
    if (ftruncate(fd, 1024U) == -1) {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "ftruncate() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }
    
    /*
     * Map the shared memory object into the process address space.
     * NULL requests the kernel select the mapping address.
     * 1024U is the number of bytes to map.
     * PROT_WRITE grants write access to the mapped region.
     * MAP_SHARED ensures updates are visible to other processes.
     * fd is the shared memory file descriptor.
     * 0U is the offset within the object to start mapping from.
     */
    void *ptr = mmap(NULL, 1024U, PROT_WRITE, MAP_SHARED, fd, 0U);
    if (ptr == MAP_FAILED)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "mmap() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    std::cout << "Mapped to address " << ptr << std::endl;

    /*
     * Copy the string into the mapped shared memory region.
     * The reader process can then read this value from the same shared object.
     */
    strcpy((char *)ptr, str);
    munmap(ptr, 1024U);

    return 0;
}
