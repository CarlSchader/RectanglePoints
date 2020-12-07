#include "point.h"
#include <algorithm> 

using namespace std;

void pointMergeSort(const struct Point** points, int size, bool (*pointLessThanOp)(const struct Point*, const struct Point*)) {
    int arraySize = 1;
    int left = 0;
    int middle = 0;
    int right = 1;
    while (arraySize < size) {
        if (right == size - 1) {
            arraySize = arraySize * 2;
            left = 0;
        }
        else {
            left = min(right + 1, size - 1);
        }
        middle = min(left + arraySize - 1, size - 1);
        right = min(middle + arraySize, size - 1);
        
        pointMerge(points, left, middle, right, pointLessThanOp);
    }
}

// middle is the index of the last element of the left array.
void pointMerge(const struct Point** points, int left, int middle, int right, bool (*pointLessThanOp)(const struct Point*, const struct Point*)) {
    int leftSize = middle - left + 1;
    int rightSize = right - middle;

    const struct Point** leftArray = new const struct Point*[leftSize];
    const struct Point** rightArray = new const struct Point*[rightSize];

    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = points[left + i];
    }

    for (int i = 0; i < rightSize; i++) {
        rightArray[i] = points[middle + 1 + i];
    }

    int i = 0;
    int j = 0;
    int index = left;
    while (i < leftSize && j < rightSize) {
        if (pointLessThanOp(rightArray[j], leftArray[i])) {
            points[index] = rightArray[j];
            j++;
        }
        else {
            points[index] = leftArray[i];
            i++;
        }
        index++;
    }
    
    while (i < leftSize) {
        points[index] = leftArray[i];
        i++;
        index++;
    }

    while (j < rightSize) {
        points[index] = rightArray[j];
        j++;
        index++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

/* Returns the index of the point closest to the searchValue comparing the searchValue using pointLessThanOp.
If the value is larger than all the points it returns -1.
Complexity: O(logn) */
int pointClosestGreaterIndex(const struct Point** points, float searchValue, int size, bool (*componentLessThanValue)(const struct Point*, float)) {
    int min = 0;
    int max = size - 1;
    int index = -1;

    while (min <= max) {
        index = (min + max) / 2;
        if (componentLessThanValue(points[index], searchValue)) {
            min = index + 1;
        }
        else {
            max = index - 1;
        }
    }
    if (componentLessThanValue(points[index], searchValue)) {
        index++;
    }

    if (index > size - 1) {
        return -1;
    }
    else {
        return index;
    }
}

/* Returns the index of the point closest to the searchValue comparing the searchValue using pointLessThanOp.
If the value is smaller than all the points it returns -1.
Complexity: O(logn) */
int pointClosestLesserIndex(const struct Point** points, float searchValue, int size, bool (*valueLessThanComponent)(float, const struct Point*)) {
    int min = 0;
    int max = size - 1;
    int index = -1;

    while (min <= max) {
        index = (min + max) / 2;
        if (valueLessThanComponent(searchValue, points[index])) {
            max = index - 1;
        }
        else {
            min = index + 1;
        }
    }
    if (valueLessThanComponent(searchValue, points[index])) {
        index--;
    }

    if (index < 0) {
        return -1;
    }
    else {
        return index;
    }
}

bool pointLessThanX(const struct Point* p1, const struct Point* p2) {
    return p1->x < p2->x;
}

bool pointLessThanY(const struct Point* p1, const struct Point* p2) {
    return p1->y < p2->y;
}

bool pointLessThanRank(const struct Point* p1, const struct Point* p2) {
    return p1->rank < p2->rank;
}

bool xComponentLessThanValue(const struct Point* point, float value) {
    return point->x < value;
}

bool yComponentLessThanValue(const struct Point* point, float value) {
    return point->y < value;
}

bool valueLessThanComponentX(float value, const struct Point* point) {
    return value < point->x;
}

bool valueLessThanComponentY(float value, const struct Point* point) {
    return value < point->y;
}