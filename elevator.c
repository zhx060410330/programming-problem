#include <stdio.h>

int main(int argc, char *argv[])
{
    /* the number of person will go to nth floor is index (n - 1)*/
    int nperson_nfloor[10] =
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    int i, all_floors = 0, all_persons = 0;
    for (i = 0; i < 10; ++i){
        all_floors += nperson_nfloor[i] * i;
        all_persons += nperson_nfloor[i];
    }
    
    int j, sum_below = 0;
    int current_floors = all_floors, min_floors = all_floors;
    int opt_floor = 0;
    for (j = 1; j < 10; ++j){
        sum_below += nperson_nfloor[j - 1];
        current_floors += sum_below - (all_persons - sum_below);
        printf ("current floors: %d\n", current_floors);
        if (current_floors < min_floors){
            min_floors = current_floors;
            opt_floor = j;
        }
    }

    printf ("opt floor: %d\n", opt_floor + 1);
    return 0;
}
