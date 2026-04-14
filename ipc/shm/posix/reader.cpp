#include <iostream>
#include <cerrno>
#include <system_error>
#include <fcntl.h>
#include <sys/mman.h>




int main()
{
    /*
     * Open the existing POSIX shared memory object for read-only access.
     * "/shmfile" must match the name used by the writer.
     * O_RDONLY opens the object with read-only permission.
     * 0666 is ignored for existing objects but is required by the API.
     */
    int fd = shm_open("/shmfile", O_RDONLY, 0666);
    if (-1 == fd)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "shm_open() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }
    
    /*
     * Map the shared memory object into the process address space for reading.
     * NULL requests a kernel-chosen address.
     * 1024U is the number of bytes to map.
     * PROT_READ grants read-only access to the mapped region.
     * MAP_SHARED ensures the mapping is shared with other processes.
     */
    void *ptr = mmap(NULL, 1024U, PROT_READ, MAP_SHARED, fd, 0U);
    if (ptr == MAP_FAILED)
    {
        std::error_code ec(errno, std::generic_category());
        std::cerr << "mmap() failed (" << ec.value() << "): " << ec.message() << std::endl;
        return -1;
    }

    std::cout << "Read string: " << (char *)ptr << std::endl;
    munmap(ptr, 1024U);

    shm_unlink("/shmfile");


    return 0;
}

