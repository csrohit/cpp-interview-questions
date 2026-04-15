#include <cstring>
#include <iostream>
#include <mutex>
#include <thread>

volatile bool g_abrt = false;

class Account
{
    char       name[20];
    int        balance;
    std::mutex m;

  public:
    Account(const char* n, int b) : balance(b)
    {
        std::strcpy(name, n);
    }

    friend void transfer(Account&, Account&, int);
};

void transfer(Account& from, Account& to, int amount)
{
    if (&from == &to)
    {
        return;
    }

    while (false == g_abrt)
    {
        {
            /*
             * Lock both account mutexes together to avoid deadlock.
             * std::scoped_lock acquires the locks in a safe, deadlock-free
             * manner when multiple mutexes are provided.
             * from.m and to.m protect the balance fields of each account.
             */
            std::scoped_lock lock(from.m, to.m);

            if (from.balance >= amount)
            {
                from.balance -= amount;
                to.balance += amount;
                std::cout << "Transferred " << amount << " from " << from.name << " to " << to.name << ", balance=" << to.balance << std::endl;
            }
            else
            {
                std::cout << "Transfer failed due to insufficient balance for " << from.name << std::endl;
            }
        }

        /*
         * Sleep briefly between transfer attempts to simulate work and allow
         * the other thread to run. This also prevents the loop from spinning
         * too aggressively on a single CPU core.
         */
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main()
{
    Account     rohit("Rohit", 1000);
    Account     nehal("Nehal", 1000);
    /*
     * Create two threads that perform transfers in opposite directions.
     * std::ref() is used to pass the accounts by reference instead of by value.
     * The amount parameter specifies how much money to transfer each time.
     */
    std::thread t1(transfer, std::ref(rohit), std::ref(nehal), 100);
    std::thread t2(transfer, std::ref(nehal), std::ref(rohit), 200);

    std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    /*
     * Request the worker threads to stop by setting the global abort flag.
     * The threads periodically check g_abrt and will exit their loop when true.
     */
    g_abrt = true;

    /*
     * Wait for both threads to finish before exiting the program.
     * join() blocks until the associated thread has completed execution.
     */
    if (t1.joinable())
    {
        t1.join();
    }

    if (t2.joinable())
    {
        t2.join();
    }

    return 0;
}
