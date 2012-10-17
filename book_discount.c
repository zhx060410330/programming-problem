#include <stdio.h>

void xor_swap(int *A, int *B)
{
    *A = *A ^ *B;
    *B = *B ^ *A;
    *A = *B ^ *A;
}

/// the simple bubble sort, max first
int tune_shelf(int *book_shelf, int height)
{
    int i;
    for (i = 0; i < height; ++i){
        int j;
        for (j = 0; j < height - i - 1; ++j){
            if (book_shelf[j] < book_shelf[j + 1]){
                xor_swap(&(book_shelf[j]), &(book_shelf[j + 1]));
            }
        }
    }
    return 0;
}

int show_shelf(int *book_shelf, int height)
{
    printf ("the shelf: ");
    int i;
    for (i = 0; i < height; ++i){
        printf ("%d%c",book_shelf[i], i != height -1? ' ':'\n');
    }
    return 0;
}
int remove_books(int *book_shelf, int height)
{
    int i;
    for (i = 0; i < height; ++i){
        book_shelf[i] -= 1;
    }
    return 0;
}

int putback_books(int *book_shelf, int height)
{
    int i;
    for (i = 0; i < height; ++i){
        book_shelf[i] += 1;
    }
    return 0;
}

int single_cost = 8;
float discount[5] = {0, 0.05, 0.10, 0.20, 0.25};

int book_shelf_save(int *book_shelf_backup, int *book_shelf, int height)
{
    int i;
    for (i = 0; i < height; ++i){
        book_shelf_backup[i] = book_shelf[i];
    }
    return 0;
}

float mini_cost(int *book_shelf, int height)
{
    int book_shelf_local[5];
    book_shelf_save(book_shelf_local, book_shelf, height);
    tune_shelf(book_shelf_local, height);
    
    float sum, mini = 0xFFFFFF;
    int i, flag = 0;
    for (i = 0; i < height; ++i){
        if (book_shelf_local[i] > 0){
            flag = 1;
            remove_books(book_shelf_local, i + 1);
            sum = single_cost * (i + 1) * (1 - discount[i]) + mini_cost(book_shelf_local, height);
            putback_books(book_shelf_local, i + 1);
            if (sum < mini){
                mini = sum;
            }
        }
    }
    return flag == 0? 0 : mini;
}

int main(int argc, char *argv[])
{
    int book_shelf[5] = {2, 2, 2, 1, 1};
    printf ("the mini cost is %.2f\n", mini_cost(book_shelf, 5));
    return 0;
}
