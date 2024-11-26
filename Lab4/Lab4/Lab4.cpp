#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <algorithm>

bool isSorted(const std::vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

void Sift(std::vector<int>& arr, int n, int i) {
    int maximum = i;
    int left = 2 * i + 1; // левый потомок
    int right = 2 * i + 2; // правый потомок

    if (left < n && arr[left] > arr[maximum]) {
        maximum = left;
    }

    if (right < n && arr[right] > arr[maximum]) {
        maximum = right;
    }

    if (maximum != i) {
        std::swap(arr[i], arr[maximum]);

        Sift(arr, n, maximum);
    }
}

void HeapSort(std::vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--) {
        Sift(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        Sift(arr, i, 0);
    }
}

std::vector<int> ReadArrayFromFile(const std::string& filename) {
    std::vector<int> arr;
    std::ifstream file(filename);
    if (file.is_open()) {
        int value;
        while (file >> value) {
            arr.push_back(value);
        }
        file.close();
    }
    else {
        std::cout << "Не удалось открыть файл для чтения: " << filename << "\n";
    }
    return arr;
}

unsigned int MeasureTime(void(*func)(std::vector<int>&), std::vector<int>& arr) {
    unsigned int start_time = clock();
    func(arr); // вызов переданной функции с массивом
    unsigned int end_time = clock();
    return end_time - start_time;
}

int main() {
    setlocale(LC_ALL, "Russian");

    const std::vector<std::string> filenames = {
        "исходный_массив_10000_-10_10.txt",
        "исходный_массив_10000_-1000_1000.txt",
        "исходный_массив_10000_-100000_100000.txt",
        "исходный_массив_100000_-10_10.txt",
        "исходный_массив_100000_-1000_1000.txt",
        "исходный_массив_100000_-100000_100000.txt",
        "исходный_массив_1000000_-10_10.txt",
        "исходный_массив_1000000_-1000_1000.txt",
        "исходный_массив_1000000_-100000_100000.txt"
    };

    for (const auto& filename : filenames) {
        auto array = ReadArrayFromFile(filename);

        unsigned int totalHeapSortTime = 0;
        for (int k = 0; k < 3; ++k) {
            totalHeapSortTime += MeasureTime(HeapSort, array);
        }

        unsigned int averageTime = totalHeapSortTime / 3;

        std::cout << "Файл: " << filename << "\n";
        std::cout << "Время работы (в миллисекундах): " << averageTime << "\n";
        std::cout << "\n";

    }

    return 0;
}