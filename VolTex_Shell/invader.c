#include <stdlib.h>
#include <stdio.h>
#include "invader.h"
void SpaceInvaders(int nb_par){
    if (nb_par > 1)
    {
        printf("ERROR: Invalid Number of arguments. Type 'help invader' to know more\n");
        return;
    }
    system("./space_imvader");
}
