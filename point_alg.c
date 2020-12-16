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

void point_merge_x(struct Point* points, struct Point* buffer, int left, int middle, int right) {
    int buffer_right = 0;
    int buffer_left = 0;
    int right_index = middle + 1;
    int index = left;

    while (index < right_index && right_index < right + 1) {
        if (index < middle + 1) {
            if (buffer_right != buffer_left) {
                if (points[right_index].x < buffer[buffer_left].x) {
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
                if (points[right_index].x < points[index].x) {
                    buffer[buffer_right] = points[index];
                    points[index] = points[right_index];
                    buffer_right++;
                    right_index++;
                }
            }
        }
        else {
            if (points[right_index].x < buffer[buffer_left].x) {
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

void point_merge_y(struct Point* points, struct Point* buffer, int left, int middle, int right) {
    int buffer_right = 0;
    int buffer_left = 0;
    int right_index = middle + 1;
    int index = left;

    while (index < right_index && right_index < right + 1) {
        if (index < middle + 1) {
            if (buffer_right != buffer_left) {
                if (points[right_index].y < buffer[buffer_left].y) {
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
                if (points[right_index].y < points[index].y) {
                    buffer[buffer_right] = points[index];
                    points[index] = points[right_index];
                    buffer_right++;
                    right_index++;
                }
            }
        }
        else {
            if (points[right_index].y < buffer[buffer_left].y) {
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

void point_merge_rank(struct Point* points, struct Point* buffer, int left, int middle, int right) {
    int buffer_right = 0;
    int buffer_left = 0;
    int right_index = middle + 1;
    int index = left;

    while (index < right_index && right_index < right + 1) {
        if (index < middle + 1) {
            if (buffer_right != buffer_left) {
                if (points[right_index].rank < buffer[buffer_left].rank) {
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
                if (points[right_index].rank < points[index].rank) {
                    buffer[buffer_right] = points[index];
                    points[index] = points[right_index];
                    buffer_right++;
                    right_index++;
                }
            }
        }
        else {
            if (points[right_index].rank < buffer[buffer_left].rank) {
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

void point_merge_sort_x(struct Point* points, int size) {
    int arraySize = 1;
    int left = 0;
    int middle = 0;
    int right = 1;
    struct Point* buffer = (struct Point*)malloc(size * sizeof(struct Point));

    while (arraySize <= size) {
        point_merge_x(points, buffer, left, middle, right);
        
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

void point_merge_sort_y(struct Point* points, int size) {
    int arraySize = 1;
    int left = 0;
    int middle = 0;
    int right = 1;
    struct Point* buffer = (struct Point*)malloc(size * sizeof(struct Point));

    while (arraySize <= size) {
        point_merge_y(points, buffer, left, middle, right);
        
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

void point_merge_sort_rank(struct Point* points, int size) {
    int arraySize = 1;
    int left = 0;
    int middle = 0;
    int right = 1;
    struct Point* buffer = (struct Point*)malloc(size * sizeof(struct Point));

    while (arraySize <= size) {
        point_merge_rank(points, buffer, left, middle, right);
        
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

int point_closest_greater_index_x(struct Point* points, float searchValue, int size) {
    if (size < 1) {
        return -1;
    }
    int min = 0;
    int max = size - 1;
    int index = -1;

    while (min <= max) {
        index = (min + max) / 2;
        if (points[index].x < searchValue) {
            min = index + 1;
        }
        else {
            max = index - 1;
        }
    }
    if (points[index].x < searchValue) {
        index++;
    }

    if (index > size - 1) {
        return -1;
    }
    else {
        return index;
    }
}

int point_closest_lesser_index_x(struct Point* points, float searchValue, int size) {
    if (size < 1) {
        return -1;
    }
    int min = 0;
    int max = size - 1;
    int index = -1;

    while (min <= max) {
        index = (min + max) / 2;
        if (searchValue < points[index].x) {
            max = index - 1;
        }
        else {
            min = index + 1;
        }
    }
    if (searchValue < points[index].x) {
        index--;
    }

    if (index < 0) {
        return -1;
    }
    else {
        return index;
    }
}

int point_closest_greater_index_y(struct Point* points, float searchValue, int size) {
    if (size < 1) {
        return -1;
    }
    int min = 0;
    int max = size - 1;
    int index = -1;

    while (min <= max) {
        index = (min + max) / 2;
        if (points[index].y < searchValue) {
            min = index + 1;
        }
        else {
            max = index - 1;
        }
    }
    if (points[index].y < searchValue) {
        index++;
    }

    if (index > size - 1) {
        return -1;
    }
    else {
        return index;
    }
}

int point_closest_lesser_index_y(struct Point* points, float searchValue, int size) {
    if (size < 1) {
        return -1;
    }
    int min = 0;
    int max = size - 1;
    int index = -1;

    while (min <= max) {
        index = (min + max) / 2;
        if (searchValue < points[index].y) {
            max = index - 1;
        }
        else {
            min = index + 1;
        }
    }
    if (searchValue < points[index].y) {
        index--;
    }

    if (index < 0) {
        return -1;
    }
    else {
        return index;
    }
}

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