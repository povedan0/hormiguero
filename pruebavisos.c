
#include <stdio.h>
#include <stdio.h>

int main(){
    int num, val;

    printf("Para determinar si es par o impar introduce entero positivo: ");
    scanf("%d", &num);

    int aux1;

    val = 2 * (int)(num/2);

    if (val == num)
        printf("%d par\n", num);
    else
        printf("%d impar\n", num);

    return;

}