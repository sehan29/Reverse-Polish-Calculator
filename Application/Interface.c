#include <stdio.h>

void getUserInput() {
    char calculation[100];
    printf("* Enter Postfix calculations with operands and operators separated by spaces, or 'q' to quit:\n");
    scanf("%s", calculation);
}

int main() {
    printf("\t\t\t******** Reverse Polish Calculator ********\t\t\t\n\n\n");
    getUserInput();
    return 0;
}
