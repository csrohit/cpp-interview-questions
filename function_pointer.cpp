#include <cstdint>
#include <cstdio>
#include <iostream>

using namespace std;
using std::uint8_t;

/**
 * Demonstrates complex function pointer and array pointer usage in C++.
 * The code shows how to define typedefs for pointers to arrays, function
 * pointers, and pointer-to-function-pointer constructs.
 */

/* ------------------------------------------------------------------ */
/* Array pointer typedefs */
/* ------------------------------------------------------------------ */
/**
 * Typedef for a pointer to an array of 4 integers.
 * This is convenient when returning or passing a pointer to a 2D array.
 */
typedef int (*p_arr_t)[4];

/**
 * @brief Return a pointer to a statically defined 2D array.
 *
 * @return p_arr_t Pointer to an array of 4 integers (the first row).
 */
p_arr_t get_array();

/**
 * Typedef for a pointer to a function that returns p_arr_t.
 */
typedef p_arr_t (*p_get_array_t)();

/* ------------------------------------------------------------------ */
/* 2D Array processing function pointers */
/* ------------------------------------------------------------------ */

/**
 * @brief Add 1 to each element of a 2D array.
 *
 * @param parr Pointer to a 2D array where each row has 4 integers.
 * @param n_rows Number of rows to process.
 * @return p_arr_t Pointer to the same modified array.
 */
p_arr_t add_1(p_arr_t parr, uint8_t n_rows);

/**
 * Typedef for a function that accepts a 2D array pointer and row count.
 */
typedef p_arr_t (*p_add_1_t)(p_arr_t parr, uint8_t n_rows);

/**
 * @brief Print the values stored in a 2D array.
 *
 * @param parr Pointer to the first row of a 2D array with 4 columns.
 * @param n_rows Number of rows to print.
 */
void print_2d(p_arr_t parr, uint8_t n_rows);

/**
 * Typedef for a function pointer to print_2d.
 */
typedef void (*p_printf_2d_t)(p_arr_t, uint8_t);

/* ------------------------------------------------------------------ */
/* Simple void function pointer types */
/* ------------------------------------------------------------------ */

/**
 * @brief Print a simple hello message.
 */
void hello();

/**
 * Typedef for a function that accepts no arguments and returns void.
 */
typedef void (*p_fun_void_void_t)();

/**
 * @brief Return a pointer to the hello() function.
 *
 * @return p_fun_void_void_t Pointer to a function taking void and returning void.
 */
p_fun_void_void_t get_hello();

/**
 * Typedef for a function pointer that returns another function pointer.
 */
typedef p_fun_void_void_t (*p_get_hello_t)();

/* ------------------------------------------------------------------ */
/* String helper function pointer types */
/* ------------------------------------------------------------------ */

/**
 * @brief Get the string object
 * 
 * @return char* pointer to a string
 */
const char * get_string();
typedef const char *(*p_get_string_t)();

/**
 * @brief Print string to stdout
 * 
 * @param str pointer to the string
 */
void print_string(const char * str);
typedef void (*p_print_string_t)(const char *);

/**
 * @brief Get a string via one function and print it via another.
 *
 * @param p_get_string Function pointer that returns a C-string.
 * @param p_print_string Function pointer that accepts a C-string and prints it.
 */
void get_print_string(p_get_string_t p_get_string , p_print_string_t p_print_string);

/**
 * Typedef for a function pointer that accepts two helper function pointers.
 */
typedef void (*p_get_print_string_t)(p_get_string_t, p_print_string_t);
// void (*p_get_print_string_t)(char *(*p_get_string)(), void (*p_print_string)(char *)); =>same as above

/* ------------------------------------------------------------------ */
/* Function pointer usage demo in main() */
/* ------------------------------------------------------------------ */

int main()
{
    /*
     * 2D array function pointer definitions.
     */
    p_get_array_t fptr_get_array = get_array;    // same as below line
    // int (*(*fptr_get_array)())[4] = get_array;

    p_add_1_t fptr_add_1 = add_1;
    // int (*(*fptr_add_1)(int (*)[4]))[4]

    p_printf_2d_t fptr_print_2d = print_2d;

    // fptr_print_2d(fptr_get_array(), 2U);
    fptr_print_2d(fptr_add_1(fptr_get_array(), 2U), 2U);

    /*
     * Hello function pointer definitions.
     */
    p_get_hello_t fptr_get_hello = get_hello;
    p_fun_void_void_t fptr_hello = hello;

    hello();    // direct function call
    fptr_hello();   // function call using pointer to the function
    get_hello()();  // call a function which returns function pointer
    fptr_get_hello()();  // call above function using function pointer

    /*
     * String helper calls using direct function references.
     */
    printf("%s", get_string());
    print_string(get_string());
    get_print_string(get_string, print_string);

    /* ------------------------------------------------------------------ */
    /* String helper function pointer definitions. */
    /* ------------------------------------------------------------------ */
    p_get_string_t fptr_get_string = get_string;
    p_print_string_t fptr_print_string = print_string;
    p_get_print_string_t fptr_get_print_string = get_print_string;

    /*
     * String helper calls using function pointers.
     */
    printf("%s", fptr_get_string());
    fptr_print_string(fptr_get_string());
    get_print_string(fptr_get_string, fptr_print_string);
    fptr_get_print_string(fptr_get_string, fptr_print_string);

    return 0;
}

/**
 * Function definitions for the function pointer example.
 */
/* ------------------------------------------------------------------ */
/* 2D array function implementations */
/* ------------------------------------------------------------------ */
// int (*get_array())[4]
p_arr_t get_array()
{
    static int data[][4] = {11, 22, 33, 44, 55, 66, 77, 88};
    // here data points to first row i.e. array of 4 integers
    return data;
}

/**
 * Increment every element in the selected rows of the 2D array.
 */
p_arr_t add_1(p_arr_t arr, uint8_t n_rows){
    uint8_t i, j;
    for (i = 0; i < n_rows; i++)
    {
        for (j = 0; j < 4; j++)
        {
            *(*(arr + i) + j) += 1;
        }
    }
    return arr;
}

/**
 * Print a 2D array row by row.
 * The pointer arithmetic treats p_arr_t as a pointer to a row of 4 ints.
 */
void print_2d(p_arr_t arr, uint8_t n_rows)
{
    // here ptr is a pointer with scale factor of 16 i.e. sizeof(int) * 4
    uint8_t i, j;
    for (i = 0; i < n_rows; i++)
    {
        for (j = 0; j < 4; j++)
        {
            cout << (*(arr + i))[j] << " ";
        }
        cout << endl;
    }
}

/* ------------------------------------------------------------------ */
/* Hello function implementations */
/* ------------------------------------------------------------------ */
/**
 * Print a hello message to stdout.
 */
void hello(){
    printf("Hello world\n");
}

/**
 * Return a pointer to the hello() function.
 */
p_fun_void_void_t get_hello(){
    return &hello;
}

/* ------------------------------------------------------------------ */
/* String helper function implementations */
/* ------------------------------------------------------------------ */
/**
 * Return a static string pointer.
 */
const char * get_string(){
    static const char * str = "My custom string\n";
    return str;
}

/**
 * Print the provided C-string to stdout.
 */
void print_string(const char *str){
    printf("%s", str);
}

/**
 * Call one function to obtain a string and another function to print it.
 */
void get_print_string(p_get_string_t p_get_string , p_print_string_t p_print_string){
    p_print_string(p_get_string());
}
