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
typedef p_arr_t (*pget_array_t)();


/**
 * @brief Add 1 to each array element   
 * 
 * @param parr pointer to array of 4 elements
 * @return p_arr_t pointer to same array
 */
p_arr_t add_1(p_arr_t parr, uint8_t);

// typedef for function pointer of above function
typedef p_arr_t (*padd_1_t)(p_arr_t parr, uint8_t);

/**
 * @brief Print contents of 2d array
 * 
 * @param parr pointer to array of 4 elements
 * @param n_rows numbers of rows
 */
void print_2d(p_arr_t parr, uint8_t n_rows);

// typedef for function pointer of above function
typedef void (*pprintf_2d_t)(p_arr_t, uint8_t);



int main()
{
    pget_array_t fptr_get_array = get_array;    // same as below line
    // int (*(*fptr_get_array)())[4] = get_array;

    padd_1_t fptr_add_1 = add_1;

    pprintf_2d_t fptr_print_2d = print_2d;

    fptr_print_2d(fptr_get_array(), 2U);
    fptr_print_2d(fptr_add_1(fptr_get_array(), 2U), 2U);
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