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

        for (int m = 1; pow(2, m) - 1 < n; m++) {
            gaps.push_back(pow(2, m) - 1); // 2^m - 1
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

void SaveArrayToFile(const std::vector<int>& arr, const std::string& filename) {
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

unsigned int MeasureTime(void(*func)(std::vector<int>&), std::vector<int>& arr) {
    unsigned int start_time = clock();
    func(arr); // вызов переданной функции с массивом
    unsigned int end_time = clock();
    return end_time - start_time;
}

int main() {
    setlocale(LC_ALL, "Russian");

    const std::vector<int> sizes = { 10000, 100000, 1000000 };
    const std::vector<std::pair<int, int>> ranges = { {-10, 10}, {-1000, 1000}, {-100000, 100000} };

    for (int i = 0; i < sizes.size(); ++i) {
        int size = sizes[i];
        for (int j = 0; j < ranges.size(); ++j) {
            std::pair<int, int> range = ranges[j];

            std::vector<int> arrHibbard = GenerateRandomArray(size, range.first, range.second);
            std::vector<int> arrKnuth = arrHibbard;
            std::vector<int> arrSedgwick = arrHibbard;

            std::string filename = "исходный_массив_" + std::to_string(size) + "_" + std::to_string(range.first) + "_" + std::to_string(range.second) + ".txt";
            SaveArrayToFile(arrHibbard, filename);

            unsigned int timeHibbard = MeasureTime(Shell::HibbardGaps, arrHibbard);
            std::cout << "Время работы Хиббард (в миллисекундах): " << timeHibbard << "\n";

            unsigned int timeKnuth = MeasureTime(Shell::KnuthGaps, arrKnuth);
            std::cout << "Время работы Кнут (в миллисекундах): " << timeKnuth << "\n";

            unsigned int timeSedgwick = MeasureTime(Shell::SedgwickGaps, arrSedgwick);
            std::cout << "Время работы Сэджвик (в миллисекундах): " << timeSedgwick << "\n";

            int AverageTime = (timeHibbard + timeKnuth + timeSedgwick) / 3;
            std::cout << "Среднее время работы алгоритма (в миллисекундах): " << AverageTime << "\n";

            std::cout << '\n';
        }
    }
    return 0;
}