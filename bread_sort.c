#include <stdio.h>
#include <string.h>

void xor_swap(int *A, int *B)
{
    *A = *A ^ *B;
    *B = *B ^ *A;
    *A = *B ^ *A;
}

int reverse_stack(int *head, int len)
{
    int *tail = head + len - 1;

    while (head < tail){
        xor_swap(head, tail);
        
        head ++;
        tail --;
    }
    return 0;
}

int print_stack(int *stack, int len)
{
    int i;
    for (i = 0; i < len; ++i){
        printf ("%d%c", stack[i], i != len -1 ? ' ':'\n');
    }
    return 0;
}

int init_stack(int *stack, int len)
{
    int i;
    for (i = 0; i < len; ++i){
        stack[i] = random() % 10;
    }

}

/* the first way */
int bread_stack_sort()
{
    int bread_stack[10];
    int reverse_count = 0;
    
    init_stack(bread_stack, 10);
    /// print the orignal stack
    print_stack(bread_stack, 10);

    int i;
    for (i = 0; i < 10; ++i){
        int biggest = 0;
        int j = 9 - i;
        while(j > 0){
            if (bread_stack[j] > bread_stack[biggest]){
                biggest = j;
            }
            j --;
        }
        if (biggest == 9 - i){
            continue;
        }
        reverse_stack(bread_stack, biggest + 1);
        /// print_stack(bread_stack, 10);        
        reverse_stack(bread_stack, 10 - i);
        /// print_stack(bread_stack, 10);
        reverse_count += 2;
    }
    print_stack(bread_stack, 10);
    printf ("count = %d\n", reverse_count);

}

/// if the stack has been sorted return 1 or return 0
int check_sort(int *stack, int len)
{
    int i;
    for (i = 0; i < len - 1; ++i){
        if (!(stack[i] < stack[i + 1])){
            return 0;
        }
    }
    return 1;
}

/* the second way */
#define BREAD_STACK_HIGHT 6
#define STEP_UPPER_BOUNDARY (2 * (BREAD_STACK_HIGHT - 1))

int ya_stack[BREAD_STACK_HIGHT];
int ya_stack_backup[BREAD_STACK_HIGHT];
/// the global var is initalized
int ya_stack_step_log[STEP_UPPER_BOUNDARY];
int ya_stack_step_log_fin[STEP_UPPER_BOUNDARY];
int least_sum_steps = STEP_UPPER_BOUNDARY;

void ya_bread_stack_backup()
{
    int i;
    for (i = 0; i < BREAD_STACK_HIGHT; ++i){
        ya_stack_backup[i] = ya_stack[i];
    }
}

void ya_bread_stack_init()
{
    init_stack(ya_stack, BREAD_STACK_HIGHT);
    ya_bread_stack_backup();
}

/// this is not the actual step left
/// it is the most optimistic count
/// but even if this can not be satisfied, we dump it
int ya_bread_steps_left(){
    int i, ret = 0;
    for (i = 0; i < BREAD_STACK_HIGHT - 1; ++i){
        /// it is wrong here, the stack is not seq like n, n + 1
        /// i should use binary search to find the buddy
        int distance = ya_stack[i] - ya_stack[i + 1];
        if (!(distance == 1 || distance == -1)){
            ret ++;
        }
    }
    return ret;
}

int ya_print_step_log(int *log, int len)
{
    printf ("step log: ");
    int i;
    for (i = 0; i < len; ++i){
        printf ("%d%c", log[i], i != len -1 ? ' ':'\n');
    }
    printf ("the least sum steps is %d\n", least_sum_steps);

    return 0;
}

int simulate_step_log(int *bread_stack_backup, int *step_log, int len)
{
    printf ("simulate step:\n");
    printf ("orignal stack: ");
    print_stack(bread_stack_backup, len);
    
    int i;
    for (i = 0; i < least_sum_steps; ++i){
        if (step_log[i] == 0){
            continue;
        }
        reverse_stack(bread_stack_backup, step_log[i]);
        print_stack(bread_stack_backup, len);
    }
}
int ya_bread_stack_sort(int step, int prev_step)
{
    if (check_sort(ya_stack, BREAD_STACK_HIGHT)){
        if (step < least_sum_steps){
            least_sum_steps = step;
            int i;
            for (i = 0; i < least_sum_steps; ++i){
                ya_stack_step_log_fin[i] = ya_stack_step_log[i];
            }
        }
        return 1;
    }
    if (step + ya_bread_steps_left() > least_sum_steps){
        return 0;
    }
    int i;
    for (i = 1; i < BREAD_STACK_HIGHT; ++i){
        if (i == prev_step){
            /// do not revert the prev step
            continue;
        }
        reverse_stack(ya_stack, i + 1);
        ya_stack_step_log[step] = i + 1;
        ya_bread_stack_sort(step + 1, i);
        /// restore the stack
        reverse_stack(ya_stack, i + 1);        
    }
    return 0;
}

int main(int argc, char *argv[])
{
    bread_stack_sort();
    printf ("----------\n");
    ya_bread_stack_init();
    ya_bread_stack_sort(0, 0);
    ya_print_step_log(ya_stack_step_log_fin, STEP_UPPER_BOUNDARY);
    simulate_step_log(ya_stack_backup,  ya_stack_step_log_fin, BREAD_STACK_HIGHT);
    return 0;
}
