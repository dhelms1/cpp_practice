// Import Libraries
#include "sortFunc.h" // sorting functions & all libraries

// Constant array of valid sorting methods
const std::string sortMethods[5] = {"Bubble", "Selection", "Insertion", "Merge", "Quick"};

int main() {
    // Set up random number generator & seed
    std::srand(unsigned(time(0)));
    auto rng = std::default_random_engine {};

    // Get user input
    int userArrSize;
    std::cout << "Enter array size: ";
    std::cin >> userArrSize;

    // Create ranged vector & shuffle (seed makes this consistent)
    std::vector<int> sortArray(userArrSize);
    iota(sortArray.begin(), sortArray.end(), 1); // comes from numeric
    std::shuffle(sortArray.begin(), sortArray.end(), rng);

    // Print original array
    std::cout << "Initial Array: ";
    vectorPrint(sortArray);

    // Get user input for sorting method
    bool incorrectSortMethod = true;
    do {
        std::string userSortMethod;
        std::cout << "Sorting Method: ";
        std::cin >> userSortMethod;

        std::for_each(userSortMethod.begin(), userSortMethod.end(), [](char &c) {
            c = std::tolower(c);}); // Convert to lower case

        if (userSortMethod == "bubble") {
            bubbleSort(sortArray);
            incorrectSortMethod = false;
        }
        else if (userSortMethod == "selection") {
            selectionSort(sortArray);
            incorrectSortMethod = false;
        }
        else if (userSortMethod == "help") {
            for (std::string method : sortMethods)
                std::cout << method << std::endl;
        }
        else
            std::cout << "Please enter valid sorting method (enter HELP for list)" << std::endl;

    } while(incorrectSortMethod);

    // Print final sorted array
    std::cout << "Sorted Array: ";
    vectorPrint(sortArray);
}
