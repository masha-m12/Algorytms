/*#include <iostream>
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

void BitSort(std::vector<int>& arr, int l, int r, int k) {
    if (l >= r || k < 0) {
        return;
    }
    int i = l, j = r;
    while (i <= j) {
        while (i <= j && ((arr[i] >> k) & 1) == 0) {
            i++;
        }
        while (i <= j && ((arr[j] >> k) & 1) == 1) {
            j--;
        }
        if (i < j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    BitSort(arr, l, j, k - 1);
    BitSort(arr, i, r, k - 1);
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

void SeparateAndSort(std::vector<int>& arr) {
    std::vector<int> positive;
    std::vector<int> negative;
    for (int num : arr) {
        if (num < 0) {
            negative.push_back(num);
        }
        else {
            positive.push_back(num);
        }
    }
    // сортируем отдельно положительные и отрицательные числа, а потом объединяем
    BitSort(positive, 0, positive.size() - 1, 31);
    BitSort(negative, 0, negative.size() - 1, 31);
    arr.clear();
    arr.insert(arr.end(), negative.begin(), negative.end());
    arr.insert(arr.end(), positive.begin(), positive.end());
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

        unsigned long long totalBitSortTime = 0;
        for (int k = 0; k < 3; ++k) {
            auto arrayCopy = array; // копируем массив для каждого запуска
            totalBitSortTime += MeasureTime(SeparateAndSort, arrayCopy);
        }

        unsigned long long averageTime = totalBitSortTime / 3;

        std::cout << "Файл: " << filename << "\n";
        std::cout << "Время работы (в миллисекундах): " << averageTime << "\n";
        std::cout << "\n";
    }

    return 0;
}*/





#include <iostream>
#include <vector>
#include <ctime>
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

void BitSort(std::vector<int>& arr, int l, int r, int k) {
    if (l >= r || k < 0) {
        return;
    }
    int i = l, j = r;
    while (i <= j) {
        while (i <= j && ((arr[i] >> k) & 1) == 0) {
            i++;
        }
        while (i <= j && ((arr[j] >> k) & 1) == 1) {
            j--;
        }
        if (i < j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    BitSort(arr, l, j, k - 1);
    BitSort(arr, i, r, k - 1);
}

unsigned int MeasureTime(void(*func)(std::vector<int>&), std::vector<int>& arr) {
    unsigned int start_time = clock();
    func(arr); // вызов переданной функции с массивом
    unsigned int end_time = clock();
    return end_time - start_time;
}

void SeparateAndSort(std::vector<int>& arr) {
    std::vector<int> positive;
    std::vector<int> negative;
    for (int num : arr) {
        if (num < 0) {
            negative.push_back(num);
        }
        else {
            positive.push_back(num);
        }
    }

    // сортируем отдельно положительные и отрицательные числа
    BitSort(positive, 0, positive.size() - 1, 31);
    BitSort(negative, 0, negative.size() - 1, 31);

    arr.clear();
    arr.insert(arr.end(), negative.begin(), negative.end());
    arr.insert(arr.end(), positive.begin(), positive.end());
}

int main() {
    setlocale(LC_ALL, "Russian");

    std::vector<int> array;
    int n;

    std::cout << "Введите количество элементов массива: ";
    std::cin >> n;

    std::cout << "Введите элементы массива:\n";
    for (int i = 0; i < n; ++i) {
        int value;
        std::cin >> value;
        array.push_back(value);
    }

    unsigned long long totalBitSortTime = 0;
    for (int k = 0; k < 3; ++k) {
        auto arrayCopy = array; // копируем массив для каждого запуска
        totalBitSortTime += MeasureTime(SeparateAndSort, arrayCopy);
    }

    unsigned long long averageTime = totalBitSortTime / 3;

    std::cout << "Отсортированный массив:\n";
    SeparateAndSort(array); // Сортируем массив
    for (const auto& value : array) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::cout << "Время работы (в миллисекундах): " << averageTime << "\n";

    return 0;
}