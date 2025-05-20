#include <stdint.h>
#include <stddef.h>

/*

Deadlock -> 

P1 -> holds R1, wants R2 -> waits in waiting q of R2

P2 -> Holdds R2, wants R1 -> waits in waiting queue of R1


P1 H -> holds R1 -> Release R1

P3 M -> complete execution

P2 H -> Wants access R1 -> complete

P4 VH



Map -> insert and erase

count++

1
2 
3 -> P1 preempted by P2(H)
4
5
6

int a = 20;
int c;

erase -> 1 element


mutex Lock -> waiting queue
isEmpty()
------- Preempted
remove from queue 

Mutex Unlock

completes


RO Data -> char literal, R
Text -> RX
DATA -> RW
BSS -> RW -> 0


100

a = 50
b = 50

Physical address -> virtual address

p1 -> VA(100) -> PA(900)
p2 -> VA(100) -> PA(800)


A process only holds a block of address
100 -> 200

4096 bytes

OS wants 8KB of memory
Assign the address of these 2 pages to the process


nAddresses => 2^32
nAddressesForEachPage = 64 * 2 ^ 10

number of pages = nAddresses / addresessePerPage

2 ^ 32 / 2 ^ 6 * 2 ^ 10 => 2^16

print odd and even values in 2 threads

thread_odd()
{
    wait for condition-even-done
    print a value
    signal condition-odd-done
}


- signal condition-even-done
thread_even()
{
    wait for condition-odd-done
    print a value
    signal condition-even-done

}

event_handler_thread()
{
    wait on a condVar
    then retrieve the data for the event
}


callback_fn()
{
    save the event data, in queue
    signal the condVar

}


Memory mapping
shared memory
5000

P1 -> block of addresses 
P2 ->

100 -> 200
100 -> 500 (300 new addresses are mapped) 

SHM_KEY -> shared between both the process
P1 -> 
    Request OS to create shared memory region based on SHM_KEY -> handle
    attach the handle to its virtual memory address space
    200   => 5000
    204 -> mutex_t => 5004

    Initialize mutex, other sync mechanism


P2 -> 
    Request OS for a shared memory region based on SHM_KEY -> handle
    attach the handle to its virtual memory address space

    300 => 5000

    use the shared memory
    304 -> mutex_t 5004


*/
/*
struct Context
{
    int data;
    mutex_t syncLock;
}
// 12 bytes of memory


p1  -> va = shmat(hndl)
struct Context* context = (struct Context*)va; -> 200
mutex_lock(&context->syncLock)


p2  -> va = shmat(hndl)
struct Context* context = (struct Context*)va; -> 300

mutex_lock(&context->syncLock)

typedef int*  rohit_int;
#define  rohit_int int*
#define rohit_float float

#define abc rohit_int##rohit_float   -> intfloat


int  *v1, v2;

struct GPIO
{
    uint32_t ODR;
    uint32_t IDR;
    uint32_t ODR;
    uint32_t ODR;
    uint32_t ODR;
    uint32_t ODR;
    uint32_t ODR;
    uint32_t ODR;
}

// addresses starting from 5000 -> 5010

struct GPIO* PORTA = 0x5000;


int main()
{
    uint32_t a = 10; -> 300


    uint32_t value = PORTA->IDR;
    uint32_t b = a;

}


int main()
{
    P2
    int b = 20;
    &b => 100;
}

int addition(int a, int b)
{
    if (INT_MAX - a < b)
    {
        // overflow
    }
    return a + b;
}

*/


/*

Primary Stack - S1 (Dequeue)

Secondary Stack - (enqueue)

S1: 6 7 8


S2: 9


Q:  6 7 8 9

Full Binary tree
Each node has 2 nodes

       P
   L       R
LL   LR  RL   RR
LL   LR  RL   RR
LL   LR  RL   RR -> node 1 -> Node 2
LL   LR  RL   RR
LL   LR  RL   RR
LL   LR  RL   RR
LL   LR  RL   RR  -> Node 2


from 1st node
traverse to the root node and push the address of parent nodes in a queue

for 2nd node
start traversing to the root node, check the currentParent node against the all the elements in the q
the first element to be matched will be the LCA

1st- calculate

Node 2 -> 8

Node 1 -> 4

traverse to the root node simultaneously
compare the current node, if matches then LCA





Implement a c function to count a leading zeros


*/
0000
3, 0
int countZeros(uint32_t n)
{
    int count = 0;
    
    for (int32_t idx = 31; idx >= 0; --idx)
    {
        uint32_t mask = (1 << idx); // 10000
        uint32_t currentBit = n & mask; // 01000 & 10000 -> 00000
        if(mask == currentBit)
        {
            break;
        }
        count++;
    }

    return count;
}

