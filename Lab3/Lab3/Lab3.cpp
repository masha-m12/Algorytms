#include <iostream> 
#include <vector> 
#include <random> 
#include <fstream> 
#include <ctime> 
#include <cmath> 
#include <string> 

void ShellSort(std::vector<int>& arr, int gap) {
    int n = arr.size();
    for (int i = gap; i < n; i++) {
        int temp = arr[i];
        int j;
        for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
            arr[j] = arr[j - gap];
        }
        arr[j] = temp;
    }
}

bool isSorted(const std::vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) {
            return false;
        }
    }
    return true;
}

std::vector<int> GenerateRandomArray(int size, int min, int max) {
    std::vector<int> array(size);
    for (int i = 0; i < size; ++i) {
        array[i] = rand() % (max - min + 1) + min;
    }
    return array;
}

namespace Shell {

    void HibbardGaps(std::vector<int>& arr) {
        int n = arr.size();
        std::vector<int> gaps;

        for (int m = 1; ; m++) {
            int gap = pow(2, m) - 1; // результат возведения в степень в переменную
            if (gap >= n) break;
            gaps.push_back(gap);
        }

        for (int i = gaps.size() - 1; i >= 0; i--) {
            ShellSort(arr, gaps[i]);
        }
    }

    void KnuthGaps(std::vector<int>& arr) {
        int n = arr.size();
        std::vector<int> gaps;
        for (int gap = 1; gap < n; gap = 3 * gap + 1) {
            gaps.push_back(gap);
        }
        for (int i = gaps.size() - 1; i >= 0; i--) {
            ShellSort(arr, gaps[i]);
        }
    }

    void SedgwickGaps(std::vector<int>& arr) {
        int n = arr.size();
        std::vector<int> gaps;
        for (int m = 0; ; m++) {
            int gap;

            if (m % 2 == 0) {
                gap = 9 * (1 * pow(2, m / 2)) - 9;
            }
            else {
                gap = 8 * (1 * pow(2, (m + 1) / 2)) - 6;
            }

            if (gap >= n) break;
            gaps.push_back(gap);
        }
        for (int i = gaps.size() - 1; i >= 0; i--) {
            ShellSort(arr, gaps[i]);
        }
    }

}

namespace Array {

    void SaveToFile(const std::vector<int>& arr, const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (int num : arr) {
                file << num << "\n";
            }
            file.close();
        }
        else {
            std::cerr << "Не удалось открыть файл для записи: " << filename << "\n";
        }
    }

    std::vector<int> ReadFromFile(const std::string& filename) {
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
        std::vector<int> arrHibbard = Array::ReadFromFile(filename);
        std::vector<int> arrKnuth = arrHibbard;
        std::vector<int> arrSedgwick = arrHibbard;

    /*const std::vector<int> sizes = {10000, 100000, 1000000};
    const std::vector<std::pair<int, int>> ranges = { {-10, 10}, {-1000, 1000}, {-100000, 100000} };

    for (int i = 0; i < sizes.size(); ++i) {
        int size = sizes[i];
        for (int j = 0; j < ranges.size(); ++j) {
            std::pair<int, int> range = ranges[j];

            std::vector<int> arrHibbard = GenerateRandomArray(size, range.first, range.second);
            std::vector<int> arrKnuth = arrHibbard;
            std::vector<int> arrSedgwick = arrHibbard;

            std::string filename = "исходный_массив_" + std::to_string(size) + "_" + std::to_string(range.first) + "_" + std::to_string(range.second) + ".txt";
            Array::SaveToFile(arrHibbard, filename);*/

            unsigned int totalTimeHibbard = 0, totalTimeKnuth = 0, totalTimeSedgwick = 0;
            for (int k = 0; k < 3; ++k) {
                totalTimeHibbard += MeasureTime(Shell::HibbardGaps, arrHibbard);
                totalTimeKnuth += MeasureTime(Shell::KnuthGaps, arrKnuth);
                totalTimeSedgwick += MeasureTime(Shell::SedgwickGaps, arrSedgwick);
            }

            unsigned int averageTimeHibbard = totalTimeHibbard / 3;
            unsigned int averageTimeKnuth = totalTimeKnuth / 3;
            unsigned int averageTimeSedgwick = totalTimeSedgwick / 3;

            std::cout << "Файл: " << filename << "\n";
            std::cout << "Среднее время работы Хиббард (в миллисекундах): " << averageTimeHibbard << "\n";
            std::cout << "Среднее время работы Кнут (в миллисекундах): " << averageTimeKnuth << "\n";
            std::cout << "Среднее время работы Сэджвик (в миллисекундах): " << averageTimeSedgwick << "\n";

            std::cout << "\n";
        }
    //}
    return 0;
}