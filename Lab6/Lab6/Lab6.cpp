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

void BitSort(std::vector<int>& arr, int l, int r, int k, bool sign)
{
    if (l >= r || k < 0) {
        return;
    }
    int i = l, j = r;
    while (i <= j) {
        if (sign) {
            while (i <= j && ((arr[i] >> k) & 1) == 1) {
                i++;
            }
            while (i <= j && ((arr[j] >> k) & 1) == 0) {
                j--;
            }
            if (i < j) {
                std::swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }
        else {
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
    }
    BitSort(arr, l, j, k - 1, 0);
    BitSort(arr, i, r, k - 1, 0);
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

unsigned int MeasureTime(void(*func)(std::vector<int>&, int, int, int, bool), std::vector<int>& arr, int k, bool sign) {
    unsigned int start_time = clock();
    func(arr, 0, arr.size() - 1, k, sign);
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

        unsigned int totalBitSortTime = 0;
        for (int k = 0; k < 3; ++k) {
            auto arrayCopy = array; 
            totalBitSortTime += MeasureTime(BitSort, arrayCopy, 31, true);
        }

        unsigned int averageTime = totalBitSortTime / 3;

        std::cout << "Файл: " << filename << "\n";
        std::cout << "Время работы (в миллисекундах): " << averageTime << "\n";
        std::cout << "\n";
    }

    return 0;
}