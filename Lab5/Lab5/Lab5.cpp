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

void HoarSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int i = left;
    int j = right;
    int x = arr[(left + right) / 2];
    while (i <= j) {
        while (arr[i] < x) {
            i++;
        }
        while (arr[j] > x) {
            j--;
        }
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    HoarSort(arr, left, j);
    HoarSort(arr, i, right);
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

unsigned int MeasureTime(void(*func)(std::vector<int>&, int, int), std::vector<int>& arr) {
    unsigned int start_time = clock();
    func(arr, 0, arr.size() - 1); // вызов переданной функции с массивом
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

        unsigned int totalHoarSortTime = 0;
        for (int k = 0; k < 3; ++k) {
            auto arrayCopy = array; // копируем массив для каждого запуска
            totalHoarSortTime += MeasureTime(HoarSort, arrayCopy);
        }

        unsigned int averageTime = totalHoarSortTime / 3;

        std::cout << "Файл: " << filename << "\n";
        std::cout << "Время работы (в миллисекундах): " << averageTime << "\n";
        std::cout << "\n";

    }

    return 0;
}