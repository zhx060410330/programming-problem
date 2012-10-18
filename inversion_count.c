#include <stdio.h>

int inversion_count = 0;

void print_array(int *array, int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%d%c", array[i], i == size - 1? '\n':' ');
    }
}

void merge(int *orig, int *dest, int left, int middle, int right){
    int i = left, j = middle + 1, k = left;

    while((i <= middle) && (j <= right)){
        if(orig[i] <= orig[j]){
            dest[k++] = orig[i++];
        }else{
            dest[k++] = orig[j++];
            inversion_count += middle - i + 1;
        }
    }

    if (i <= middle){
        for(; i <= middle; i++)
            dest[k++] = orig[i];
    }    
    else if(j <= right){
        for(; j <= right; j++)
            dest[k++] = orig[j];
    }
}
void mergePass(int *orig, int *dest, int unit, int size){
    int i = 0;
    while(i + 2*unit < size){
        merge(orig, dest, i, i+unit-1, i+2*unit-1);
        i = i + 2*unit;
    }

    if(i + unit < size){
        /// there are items more than unit
        /// but less than 2*unit left
        merge(orig, dest, i, i+unit-1, size-1);
    }else if (i < size){
        /// if only items less or equal than unit
        /// just copy them
        for (; i < size; i++)
            dest[i] = orig[i];
    }
}

void mergesort(int *array,int size)
{
    int array_buf[size], unit = 1;
    while(unit < size){
        mergePass(array, array_buf, unit, size);
        unit += unit;
        mergePass(array_buf, array, unit, size);
        unit += unit;
    }
}

int main()
{
    int array[5] = {1, 2, 3, 4, 5};
    mergesort(array, 5);
    printf ("inversion count = %d\n",inversion_count);
    return 0;
}
