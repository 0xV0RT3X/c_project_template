#include "calculations.h"

int main(void) {    
    int add_result = add(5, 1);
    int sub_result = substract(5, 1);
    int mul_result = multiply(5, 1);
    int div_result = divide(5, 1);

    fprintf(stdout, "add_result = %d\n", add_result);
    fprintf(stdout, "sub_result = %d\n", sub_result);
    fprintf(stdout, "mul_result = %d\n", mul_result);
    fprintf(stdout, "div_result = %d\n", div_result);

    return 0;
}
