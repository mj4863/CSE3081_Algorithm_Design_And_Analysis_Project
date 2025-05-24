#include <cstring>
#include "records.h"

void RECORDS::sort_records_insertion(int start_index, int end_index) {
	// Insertion sort
	for (int i = start_index + 1; i <= end_index; i++) {
		RECORD tmp = records[i];
		int j = i;
		while ((j > start_index) && (compare_keys((const void*)&tmp, (const void*)(&records[j - 1])) < 0)) {
			records[j] = records[j - 1];
			j--;
		}
		records[j] = tmp;
	}
}

void max_heapify(RECORD* records, int root, int n) {
    int child, rootkey;
    rootkey = records[root].key;
    RECORD tmp = records[root];
    child = 2 * root + 1;

    while (child < n) {
        if (child < n - 1 && records[child].key < records[child + 1].key) child++;
        if (rootkey >= records[child].key) break;
        else {
            records[(child - 1) / 2] = records[child];
            child = 2 * child + 1;
        }
    }
    records[(child - 1) / 2] = tmp;
}

void RECORDS::sort_records_heap(int start_index, int end_index) {
    // Classic heap sort
    int n = end_index - start_index + 1;

    for (int i = start_index + n / 2 - 1; i >= start_index; i--) {
        max_heapify(records, i, n);
    }

    for (int i = end_index; i > start_index; i--) {
        std::swap(records[0], records[i]);  
        max_heapify(records, start_index, i);
    }
}

void min_heapify(RECORD* records, int root, int n) {
    int child, rootkey;
    rootkey = records[root].key;
    RECORD tmp = records[root];     
    child = 2 * root + 1;           

    while (child < n) {
        if (child < n - 1 && records[child].key > records[child + 1].key) child++;
        if (rootkey <= records[child].key) break;
        else {
            records[(child - 1) / 2] = records[child];
            child = 2 * child + 1;
        }
    }
    records[(child - 1) / 2] = tmp;
}

void RECORDS::sort_records_weird(int start_index, int end_index) {
	// A weird sort with a make-heap operation followed by insertion sort
    int n = end_index - start_index + 1;

    for (int i = start_index + n / 2 - 1; i >= start_index; i--) {
        min_heapify(records, i, n);
    }

    sort_records_insertion(start_index, end_index);
}

int partition(RECORD* records, int left, int right) {
    int i, pivot;

    pivot = left;
    for (i = left; i < right; i++) {
        if (records[i].key < records[right].key) {
            std::swap(records[i], records[pivot]);
            pivot++;
        }
    }
    std::swap(records[right], records[pivot]);
    return pivot;
}

void RECORDS::sort_records_quick_classic(int start_index, int end_index) {
	// Classic quick sort without any optimization techniques applied
    if (end_index - start_index > 0) {
        int pivot = partition(records, start_index, end_index);

        sort_records_quick_classic(start_index, pivot - 1);
        sort_records_quick_classic(pivot + 1, end_index);
    }
}

void introsort(RECORDS* obj, RECORD* records, int left, int right, int max_depth) {
    int n = right - left + 1;

    if (n < 16) {
        obj->sort_records_insertion(left, right);
    }
    else if (max_depth == 0) {
        obj->sort_records_heap(left, right);
    }
    else {
        int pivot = partition(records, left, right);
        introsort(obj, records, left, pivot - 1, max_depth - 1);
        introsort(obj, records, pivot + 1, right, max_depth - 1);
    }
}

void RECORDS::sort_records_intro(int start_index, int end_index) {
	// Introsort described in https://en.wikipedia.org/wiki/Introsort
    int n = end_index - start_index + 1;
    int max_depth = 3 * std::log2(n);
    introsort(this, records, start_index, end_index, max_depth);
}

void merge(RECORD* records, int left, int middle, int right) {
    int size = right - left + 1;
    RECORD* buffer = new RECORD[size];
    memcpy(buffer, records + left, sizeof(RECORD) * size);

    int i_left = 0;
    int i_right = middle - left + 1;
    int i = left;

    while (i_left <= middle - left && i_right <= right - left) {
        if (buffer[i_left].key < buffer[i_right].key)
            records[i++] = buffer[i_left++];
        else
            records[i++] = buffer[i_right++];
    }

    while (i_left <= middle - left)
        records[i++] = buffer[i_left++];
    while (i_right <= right - left)
        records[i++] = buffer[i_right++];

    delete[] buffer;
}

void RECORDS::sort_records_merge_with_insertion(int start_index, int end_index) {
	// Merge sort optimized by insertion sort only
    int n = end_index - start_index + 1;

    if (n < 16) {
        sort_records_insertion(start_index, end_index);
    }
    else if (start_index < end_index) {
        int middle = (start_index + end_index) / 2;

        sort_records_merge_with_insertion(start_index, middle);
        sort_records_merge_with_insertion(middle + 1, end_index);

        merge(records, start_index, middle, end_index);
    }
}