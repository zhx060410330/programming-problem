#include <stdio.h>
#include <math.h>
#include <string.h>

#define max(a,b) (a > b ? a : b)

#define nitems 4
#define  knapsacksize 10
int weight[4] = {5,4,6,3};
int value[4] = {10,40,30,50};

/// use recursive algorithm, easy to understand. looks like a tree
int knapsack_rec(int index, int current_size){
    if (current_size + weight[index] <= knapsacksize && index < nitems){
        return max(value[index] + knapsack_rec(index + 1, current_size + weight[index]),
                   knapsack_rec(index + 1, current_size));
    }
    return 0;
}
#define check_bit(index, kind) (((1 << index) & kind) >> index)
void print_footprint(int foot_print)
{
    printf ("footprint: ");
    int j;
    for (j = 0; j < nitems; ++j){
        if (check_bit(j, foot_print)){
            printf ("%d ", weight[j]);
        }
    }
    printf ("\n");
}

int knapsack_bruteforce()
{
    int i, kinds = pow(2, nitems);
    int max_value = 0, foot_print = 0;
    
    for (i = 0; i < kinds; ++i){
        int j, weight_sum = 0, value_sum = 0;

        for (j = 0; j < nitems; ++j){
            weight_sum += weight[j] * check_bit(j, i);
            value_sum += value[j] * check_bit(j, i);            
        }

        if (weight_sum <= knapsacksize && value_sum > max_value){
            max_value = value_sum;
            foot_print = i;
        }
    }
    /// print_footprint(foot_print);
    return max_value;
}

int dynamic_tab[nitems + 1][knapsacksize + 1] = {0};
int knapsack_dynamic()
{
    int i;
    for (i = 1; i <= nitems; ++i){
        int j;
        for (j = 1; j <= knapsacksize; ++j){
            if (weight[i - 1] <= j){
                dynamic_tab[i][j] = max(dynamic_tab[i - 1][j],
                                        value[i - 1] +
                                        dynamic_tab[i - 1][j - weight[i - 1]]);
            }
            else{
                dynamic_tab[i][j] = dynamic_tab[i - 1][j];
            }
        }
    }
    return dynamic_tab[nitems][knapsacksize];
}

int dynamic_tab_rec[nitems + 1][knapsacksize + 1];
int knapsack_dynamic_rec(int index, int size_left)
{
    int max_value = 0;

    if (index == 0){
        dynamic_tab_rec[index][size_left] = 0;
        return 0;
    }

    int take = 0;
    if (weight[index - 1] <= size_left){
        if (dynamic_tab_rec[index - 1][size_left - weight[index - 1]] != -1){
            take = value[index - 1]
                + dynamic_tab_rec[index - 1][size_left - weight[index - 1]];
        }
        else{
            take = value[index - 1]
                + knapsack_dynamic_rec(index - 1, size_left - weight[index - 1]);
        }
    }
    int dontake = knapsack_dynamic_rec(index - 1, size_left);
    
    max_value = max(take, dontake);
    dynamic_tab_rec[index][size_left] = max_value;
    
    return max_value;
}

void print_footprint_from_tab(int tab[nitems + 1][knapsacksize + 1], int line_index, int column_index)
{
    if (line_index == 0){
        return;
    }
    if (column_index >= weight[line_index - 1] &&
        tab[line_index][column_index] == value[line_index - 1]
            + tab[line_index - 1][column_index - weight[line_index - 1]]){
        printf ("%d ", weight[line_index - 1]);
        print_footprint_from_tab(tab, line_index - 1,
                                 column_index - weight[line_index -1]);            
    }
    else{
        print_footprint_from_tab(tab, line_index - 1, column_index);
    }
}

void print_tab(int tab[nitems + 1][knapsacksize + 1], int line_index, int column_index)
{
    int i;
    for (i = 0; i <= line_index; ++i){
        int j;
        for (j = 0; j <= column_index; ++j){
            printf ("%d%c", tab[i][j], j != column_index? ' ':'\n');
        }
    }
}

int main()
{
    printf ("1. rec max value = %d\n", knapsack_rec(0, 0));
    printf ("2. bru max value = %d\n", knapsack_bruteforce());
    printf ("3. dyn max value = %d\n", knapsack_dynamic());

    memset(dynamic_tab_rec, -1, sizeof(dynamic_tab_rec));
    printf ("4. dre max value = %d\n", knapsack_dynamic_rec(nitems, knapsacksize));
    
    return 0;
}
