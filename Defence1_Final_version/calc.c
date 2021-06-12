#include<stdio.h>
#include<stdlib.h>
#include<ncurses.h>
#include<math.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include "calc.h"

void calc(int nb_par)
{
    if(nb_par > 1)
    {
      fprintf(stderr, "SYNTAX ERROR:\nUsage: calc. Try 'help' for more information.\n");
      return;
    }

    int choice, i, a, b;

    float x, y, result;



    while (1)
    {
        printf("\nSelect your operation (0 to exit):\n\n");
        printf("1. Addition          2. Subtraction          3. Multiplication          4. Division\n\n");
        printf("5. Square root       6. X ^ Y                7. X ^ 2                   8. X ^ 3\n\n");
        printf("9. 1 / X             10. X ^ (1 / Y)         11. X ^ (1 / 3)            12. 10 ^ X\n\n");
        printf("13. X!               14. %%                   15. log10(x)               16. Modulus\n\n");
        printf("17. Sin(X)           18. Cos(X)              19. Tan(X)                 20. Cosec(X)\n\n");
        printf("21. Cot(X)           22. Sec(X)\n");
        printf("\nChoice: ");
        int check = scanf("%d", &choice);

        while((getchar() != '\n'));
        if (check != 1){
            printf("ERROR: Invalid Input\n");
            continue;
        }

        
        if (choice == 0) return;
        if (choice < 0 || choice > 22) continue;
        switch(choice)
        {
            case 1:
                printf("Enter X: ");
                scanf("%f", &x);
                printf("\nEnter Y: ");
                scanf("%f", &y);
                result = x + y;
                printf("\nResult: %f\n\n", result);
                break;
            case 2:
                printf("Enter X: ");
                scanf("%f", &x);
                printf("\nEnter Y: ");
                scanf("%f", &y);
                result = x - y;
                printf("\nResult: %f", result);
                break;
            case 3:
                printf("Enter X: ");
                scanf("%f", &x);
                printf("\nEnter Y: ");
                scanf("%f", &y);
                result = x * y;
                printf("\nResult: %f", result);
                break;
            case 4:
                printf("Enter X: ");
                scanf("%f", &x);
                printf("\nEnter Y: ");
                scanf("%f", &y);
                result = x / y;
                printf("\nResult: %f", result);
                break;
            case 5:
                printf("Enter X: ");
                scanf("%f", &x);
                result = sqrt(x);
                printf("\nResult: %f", result);
                break;
            case 6:
                printf("Enter X: ");
                scanf("%f", &x);
                printf("\nEnter Y: ");
                scanf("%f", &y);
                result = pow(x, y);
                printf("\nResult: %f", result);
                break;
            case 7:
                printf("Enter X: ");
                scanf("%f", &x);
                result = pow(x, 2);
                printf("\nResult: %f", result);
                break;
            case 8:
                printf("Enter X: ");
                scanf("%f", &x);
                result = pow(x, 3);
                printf("\nResult: %f", result);
                break;
            case 9:
                printf("Enter X: ");
                scanf("%f", &x);
                result = pow(x, -1);
                printf("\nResult: %f", result);
                break;
            case 10:
                printf("Enter X: ");
                scanf("%f", &x);
                printf("\nEnter Y: ");
                scanf("%f", &y);
                result = pow(x, (1/y));
                printf("\nResult: %f", result);
                break;
            case 11:
                printf("Enter X: ");
                scanf("%f", &x);
                y = 3;
                result = pow(x, (1/y));
                printf("\nResult: %f", result);
                break;
            case 12:
                printf("Enter X: ");
                scanf("%f", &x);
                result = pow(10, x);
                printf("\nResult: %f", result);
                break;
            case 13:
                printf("Enter X: ");
                scanf("%f", &x);
                result = 1;
                for(i = 1; i <= x; i++)
                {
                    result = result * i;
                }
                printf("\nResult: %.f", result);
                break;
            case 14:
                printf("Enter X: ");
                scanf("%f", &x);
                printf("\nEnter Y: ");
                scanf("%f", &y);
                result = (x * y) / 100;
                printf("\nResult: %.2f", result);
                break;
            case 15:
                printf("Enter X: ");
                scanf("%f", &x);
                result = log10(x);
                printf("\nResult: %.2f", result);
                break;
            case 16:
                printf("Enter X: ");
                scanf("%d", &a);
                printf("\nEnter Y: ");
                scanf("%d", &b);
                result = a % b;
                printf("\nResult: %f", result);
                break;
            case 17:
                printf("Enter X: ");
                scanf("%f", &x);
                result = sin(x * 3.14159 / 180);
                printf("\nResult: %.2f", result);
                break;
            case 18:
                printf("Enter X: ");
                scanf("%f", &x);
                result = cos(x * 3.14159 / 180);
                printf("\nResult: %.2f", result);
                break;
            case 19:
                printf("Enter X: ");
                scanf("%f", &x);
                result = tan(x * 3.14159 / 180);
                printf("\nResult: %.2f", result);
                break;
            case 20:
                printf("Enter X: ");
                scanf("%f", &x);
                result = 1 / (sin(x * 3.14159 / 180));
                printf("\nResult: %.2f", result);
                break;
            case 21:
                printf("Enter X: ");
                scanf("%f", &x);
                result = 1 / tan(x * 3.14159 / 180);
                printf("\nResult: %.2f", result);
                break;
            case 22:
                printf("Enter X: ");
                scanf("%f", &x);
                result = 1 / cos(x * 3.14159 / 180);
                printf("\nResult: %.2f", result);
                break;
            default:
                printf("\nInvalid Choice!\n");
        }
    }
        //getch();

}
