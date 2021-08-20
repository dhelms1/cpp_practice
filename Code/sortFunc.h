#ifndef SORTFUNC_H
#define SORTFUNC_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <numeric>
#include <algorithm>
#include <random>
#include <string>
#include <chrono>

struct Timer {
    std::chrono::time_point<std::chrono::steady_clock> start, end;
    std::chrono::duration<float> duration;
    
    Timer() { // constructor
        start = std::chrono::high_resolution_clock::now();
    }
    
    ~Timer() { // destructor
        end = std::chrono::high_resolution_clock::now();
        duration = end - start;
        float ms = duration.count() * 1000.0f; // convert sec to ms 
        std::cout << "Sorted in " << ms << "ms." << std::endl;
    }
};

void vectorPrint(std::vector<int> *vals, int n) {
    for (int i = 0; i < n; i++)
        std::cout << (*vals).at(i) << " ";
    std::cout << std::endl;
}

void bubbleSort(std::vector<int> *vals, int n) {
    int num_its = 0;
    Timer timer; // create timer (destructor prints time in ms)
    do {
        for (int i = 0; i < n - 1; i++) {
            num_its++;
            if ((*vals)[i] > (*vals)[i+1]) {
                int tmp = (*vals)[i+1];
                (*vals)[i+1] = (*vals)[i];
                (*vals)[i] = tmp;
            }
        }
    } while (!std::is_sorted((*vals).begin(), (*vals).end()));
    std::cout << "Bubble Sort: " << num_its << " iterations" << std::endl;
}

void selectionSort(std::vector<int> *vals, int n) {
    int num_its = 0;
    Timer timer;
    for (int i = 0; i < n-1; i++) {
        int current_min = (*vals)[i];
        int min_idx = i;
        num_its++;
        for (int j = i+1; j < (*vals).size(); j++) {
            if ((*vals)[j] < current_min) {
                current_min = (*vals)[j];
                min_idx = j;
            }
            num_its++;
        }
        int tmp = (*vals)[i]; // get current head value
        (*vals)[i] = current_min; // move min to head
        (*vals)[min_idx] = tmp; // set original min idx to old head value
    }
    std::cout << "Selection Sort: " << num_its << " iterations" << std::endl;
}

void insertionSort(std::vector<int> *vals, int n) {
    int num_its = 0;
    Timer timer;
    for (int i = 1; i < n; i++) {
        num_its++;
        // to be filled in
    }
    std::cout << "Insertion Sort: " << num_its << " iterations" << std::endl;
}

#endif