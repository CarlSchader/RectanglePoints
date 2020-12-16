/* Author: Carl Schader
Function definitions for certain algorithms associated with the Point struct. */

#if defined(__MSVS__)
#include "pch.h"
#endif

#include "point_alg.h"
#include "point_search.h"
#include <stdlib.h>
#include <stdio.h>

#define min(x, y) (((x) <= (y)) ? (x) : (y))

void point_merge_sort(struct Point* points, int size, pointLessThanOp less_than) {
    int arraySize = 1;
    int left = 0;
    int middle = 0;
    int right = 1;
    struct Point* buffer = (struct Point*)malloc(size * sizeof(struct Point));

    // printf("\n");
    while (arraySize <= size) {
        point_merge(points, buffer, left, middle, right, less_than);
        
        if (right >= size - 1) {
            arraySize = arraySize * 2;
            left = 0;
            middle = min(left + arraySize - 1, size - 1);
            right = min(middle + arraySize, size - 1);
        }
        else {
            left = min(right + 1, size - 1);
            middle = min(left + arraySize - 1, size - 1);
            right = min(middle + arraySize, size - 1);
        }
    }
    free(buffer);
}

float buffer_string(struct Point* buffer, int bl, int index) {
    if (index > bl) {
        return -1.0;
    }
    else {
        return buffer[index].x;
    }
}

/* Middle is the index of the last element of the left array.
(This could be easier to read, but for the sake of less cycles spent copying data it's a bit more complicated.) */
void point_merge(struct Point* points, struct Point* buffer, int left, int middle, int right, pointLessThanOp less_than) {
    int buffer_right = 0;
    int buffer_left = 0;
    int right_index = middle + 1;
    int index = left;

    while (index < right_index && right_index < right + 1) {
        // printf("l: %d r: %d bl: %d br: %d | %.1f %.1f %.1f %.1f | %.1f %.1f %.1f %.1f\n", index, right_index, buffer_left, buffer_right, points[0].x, points[1].x, points[2].x, points[3].x, buffer_string(buffer, buffer_left, 0), buffer_string(buffer, buffer_left, 1), buffer_string(buffer, buffer_left, 2), buffer_string(buffer, buffer_left, 3));
        if (index < middle + 1) {
            if (buffer_right != buffer_left) {
                if (less_than(&points[right_index], &buffer[buffer_left])) {
                    buffer[buffer_right] = points[index];
                    points[index] = points[right_index];
                    buffer_right++;
                    right_index++;
                }
                else {
                    buffer[buffer_right] = points[index];
                    points[index] = buffer[buffer_left];
                    buffer_right++;
                    buffer_left++;
                }
            }
            else {
                if (less_than(&points[right_index], &points[index])) {
                    buffer[buffer_right] = points[index];
                    points[index] = points[right_index];
                    buffer_right++;
                    right_index++;
                }
            }
        }
        else {
            if (less_than(&points[right_index], &buffer[buffer_left])) {
                points[index] = points[right_index];
                right_index++;
            }
            else {
                points[index] = buffer[buffer_left];
                buffer_left++;
            }
        }
        index++;
    }

    while (buffer_left < buffer_right) {
        points[index] = buffer[buffer_left];
        buffer_left++;
        index++;
    }
}

/* Returns the index of the point closest to the searchValue comparing the searchValue using less_than.
If the value is larger than all the points it returns -1.
Complexity: O(logn) */
int point_closest_greater_index(struct Point* points, float searchValue, int size, componentLessThanValue less_than) {
    if (size < 1) {
        return -1;
    }
    int min = 0;
    int max = size - 1;
    int index = -1;

    while (min <= max) {
        index = (min + max) / 2;
        if (less_than(&points[index], searchValue)) {
            min = index + 1;
        }
        else {
            max = index - 1;
        }
    }
    if (less_than(&points[index], searchValue)) {
        index++;
    }

    if (index > size - 1) {
        return -1;
    }
    else {
        return index;
    }
}

/* Returns the index of the point closest to the searchValue comparing the searchValue using less_than.
If the value is smaller than all the points it returns -1.
Complexity: O(logn) */
int point_closest_lesser_index(struct Point* points, float searchValue, int size, valueLessThanComponent less_than) {
    if (size < 1) {
        return -1;
    }
    int min = 0;
    int max = size - 1;
    int index = -1;

    while (min <= max) {
        index = (min + max) / 2;
        if (less_than(searchValue, &points[index])) {
            max = index - 1;
        }
        else {
            min = index + 1;
        }
    }
    if (less_than(searchValue, &points[index])) {
        index--;
    }

    if (index < 0) {
        return -1;
    }
    else {
        return index;
    }
}

/* Puts the smallest k points by rank in the first k indexes. */
void point_k_smallest(struct Point* points, int k, int left, int right) {
    while (k > 0 && k < right - left + 1) {
        int partition_index = point_partition(points, left, right);
        if (partition_index == k || partition_index == k + 1) {
            return;
        }
        else if (partition_index < k) {
            k = k - (partition_index + 1 - left);
            left = partition_index + 1;
        }
        else {
            right = partition_index - 1;
        }
    }
}

void point_quicksort(struct Point* points, int left, int right) {
    if (left < right) {
        int partition_index = point_partition(points, left, right);
        point_quicksort(points, left, partition_index - 1);
        point_quicksort(points, partition_index + 1, right);
    }
}

int point_partition(struct Point* points, int left, int right) {
    int32_t pivot_rank = points[right].rank;
    int i = left - 1;
    struct Point buffer_point;
    for (int j = left; j <= right; j++) {
        if (points[j].rank < pivot_rank) {
            i++;
            buffer_point = points[i];
            points[i] = points[j];
            points[j] = buffer_point;
        }
    }
    i++;
    buffer_point = points[i];
    points[i] = points[right];
    points[right] = buffer_point;
    return i;
}

void count_sort_heap(struct Point* points, int left, int right) {
    struct Point* buffer = (struct Point*)malloc((right - left + 1) * sizeof(struct Point));
    int i = 0;
    int counts[128] = {0};

    for (i = left; i < right + 1; i++) {
        // printf("%d %d\n", 1, i);
        counts[points[i].rank]++;
    }
    for (i = 1; i < 128; i++) {
        // printf("%d %d\n", 2, i);
        counts[i] += counts[i - 1];
    }
    for (i = right; i >= left; i--) {
        // printf("%d %d\n", 3, i);
        buffer[counts[points[i].rank] - 1] = points[i];
        counts[points[i].rank]--;
    }
    for (i = 0; i < right - left + 1; i++) {
        // printf("%d %d\n", 4, i);
        points[i + left] = buffer[i];
    }
    free(buffer);
}

void count_sort_stack(struct Point* points, int left, int right) {
    struct Point buffer[right - left + 1];
    int i = 0;
    int counts[128] = {0};

    for (i = left; i < right + 1; i++) {
        counts[points[i].rank]++;
    }
    for (i = 1; i < 128; i++) {
        counts[i] += counts[i - 1];
    }
    for (i = right; i >= left; i--) {
        buffer[counts[points[i].rank] - 1] = points[i];
        counts[points[i].rank]--;
    }
    for (i = left; i < right + 1; i++) {
        points[i] = buffer[i];
    }
}

void count_sort_128(struct Point* points, int size) {
    struct Point buffer[size];
    int i = 0;
    int counts[128] = {0};

    for (i = 0; i < size; i++) {
        counts[points[i].rank]++;
    }
    for (i = 1; i < 128; i++) {
        counts[i] += counts[i - 1];
    }
    for (i = size - 1; i >=0; i--) {
        buffer[counts[points[i].rank] - 1] = points[i];
        counts[points[i].rank]--;
    }
    for (i = 0; i < size; i++) {
        points[i] = buffer[i];
    }
}

void count_sort_rank_heap(struct Point* points, int size, int exponent) {
    struct Point* buffer = (struct Point*) malloc(size * sizeof(struct Point));
    int i = 0;
    int counts[10] = {0};

    for (i = 0; i < size; i++) {
        counts[(points[i].rank / exponent) % 10]++;
    }
    for (i = 1; i < 10; i++) {
        counts[i] += counts[i - 1];
    }
    for (i = size - 1; i >= 0; i--) {
        buffer[counts[(points[i].rank / exponent) % 10] - 1] = points[i];
        counts[(points[i].rank / exponent) % 10]--;
    }
    for (i = 0; i < size; i++) {
        points[i] = buffer[i];
    }
    free(buffer);
}

void count_sort_rank_stack(struct Point* points, int size, int exponent) {
    struct Point buffer[size];
    int i = 0;
    int counts[10] = {0};

    for (i = 0; i < size; i++) {
        counts[(points[i].rank / exponent) % 10]++;
    }
    for (i = 1; i < 10; i++) {
        counts[i] += counts[i - 1];
    }
    for (i = size - 1; i >= 0; i--) {
        buffer[counts[(points[i].rank / exponent) % 10] - 1] = points[i];
        counts[(points[i].rank / exponent) % 10]--;
    }
    for (i = 0; i < size; i++) {
        points[i] = buffer[i];
    }
}

void point_radix_rank_heap(struct Point* points, int size, int max) {
    for (int exponent = 1; max / exponent > 0; exponent *= 10) {
        count_sort_rank_heap(points, size, exponent);
    }
}

void point_radix_rank_stack(struct Point* points, int size, int max) {
    for (int exponent = 1; max / exponent > 0; exponent *= 10) {
        count_sort_rank_stack(points, size, exponent);
    }
}

bool point_less_than_x(const struct Point* p1, const struct Point* p2) {
    return p1->x < p2->x;
}

bool point_less_than_y(const struct Point* p1, const struct Point* p2) {
    return p1->y < p2->y;
}

bool point_less_than_rank(const struct Point* p1, const struct Point* p2) {
    return p1->rank < p2->rank;
}

bool x_less_than_value(const struct Point* point, float value) {
    return point->x < value;
}

bool y_less_than_value(const struct Point* point, float value) {
    return point->y < value;
}

bool value_less_than_x(float value, const struct Point* point) {
    return value < point->x;
}

bool value_less_than_y(float value, const struct Point* point) {
    return value < point->y;
}