#include <iostream>

using namespace std;

// typedef for pointer to array of 4 elements
typedef int (*p_arr_t)[4];

/**
 * @brief Get the array object
 * 
 * @return p_arr_t 
 */
p_arr_t get_array();

// typedef for function pointer of above function
typedef p_arr_t (*p_get_array_t)();


/**
 * @brief Add 1 to each array element   
 * 
 * @param parr pointer to array of 4 elements
 * @return p_arr_t pointer to same array
 */
p_arr_t add_1(p_arr_t parr, uint8_t);
//

// typedef for function pointer of above function
typedef p_arr_t (*p_add_1_t)(p_arr_t parr, uint8_t);

/**
 * @brief Print contents of 2d array
 * 
 * @param parr pointer to array of 4 elements
 * @param n_rows numbers of rows
 */
void print_2d(p_arr_t parr, uint8_t n_rows);

// typedef for function pointer of above function
typedef void (*p_printf_2d_t)(p_arr_t, uint8_t);



/**
 * @brief Prints hello world message
 * 
 */
void hello();

// void (*)() get_hello(){    => compiler does not allow this
//                            => we need to to define a type which returns a pointer to a functin

typedef void (*p_fun_void_void_t)();
/**
 * @brief Get pointer to hello function
 * 
 * @return p_fun_void_void_t pointer to a function which accepts void and returns void
 */
p_fun_void_void_t get_hello();

// pointer to a function which accepts void and returns pointer to a function{which accepts void and returns void}
typedef p_fun_void_void_t (*p_get_hello_t)();


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
 * @brief get a string and print that string
 * 
 * @param p_get_string pointer to a function which returns a string
 * @param p_print_string pointer to a function which accepts a string
 */
void get_print_string(p_get_string_t p_get_string , p_print_string_t p_print_string);
typedef void (*p_get_print_string_t)(p_get_string_t, p_print_string_t);
// void (*p_get_print_string_t)(char *(*p_get_string)(), void (*p_print_string)(char *)); =>same as above



int main()
{
    p_get_array_t fptr_get_array = get_array;    // same as below line
    // int (*(*fptr_get_array)())[4] = get_array;

    p_add_1_t fptr_add_1 = add_1;
    // int (*(*fptr_add_1)(int (*)[4]))[4]

    p_printf_2d_t fptr_print_2d = print_2d;

    // fptr_print_2d(fptr_get_array(), 2U);
    fptr_print_2d(fptr_add_1(fptr_get_array(), 2U), 2U);

    // print hello world
    p_get_hello_t fptr_get_hello = get_hello;
    p_fun_void_void_t fptr_hello = hello;

    hello();    // direct function call
    fptr_hello();   // function call using pointer to the function
    get_hello()();  // call a function which returns function pointer
    fptr_get_hello()();  // call above function using function pointer

    // print custom message
    printf("%s", get_string());
    print_string(get_string());
    get_print_string(get_string, print_string);

    p_get_string_t fptr_get_string = get_string;
    p_print_string_t fptr_print_string = print_string;
    p_get_print_string_t fptr_get_print_string = get_print_string;

    printf("%s", fptr_get_string());
    fptr_print_string(fptr_get_string());
    get_print_string(fptr_get_string, fptr_print_string);
    fptr_get_print_string(fptr_get_string, fptr_print_string);

    return 0;
}

/* Function definitions */
// int (*get_array())[4]
p_arr_t get_array()
{
    static int data[][4] = {11, 22, 33, 44, 55, 66, 77, 88};
    // here data points to first row i.e. array of 4 integers
    return data;
}


// int (*add_1(p_arr_t arr, int n_rows))[4]{
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

void hello(){
    printf("Hello world\n");
}

p_fun_void_void_t get_hello(){
    return &hello;
}


const char * get_string(){
    static const char * str = "My custom string\n";
    return str;
}

void print_string(const char *str){
    printf("%s", str);
}

void get_print_string(p_get_string_t p_get_string , p_print_string_t p_print_string){
    p_print_string(p_get_string());
}
