#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime> // для измерения времени
#include <limits>
#include <conio.h>
#include <cmath>

void RandMas(std::vector<std::vector<int>>& cost_matrix, int n) {
    std::srand(static_cast<unsigned int>(std::time(0))); // генератор случайных чисел
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                cost_matrix[i][j] = 0;
            }
            else {
                cost_matrix[i][j] = std::rand() % 100 + 1;
            }
        }
    }
}

int CompleteEnumeration(int index, int visited, int n, int start_city, int& min_cost, int& max_cost, int current_cost, const std::vector<std::vector<int>>& cost_matrix, std::vector<int>& current_route, std::vector<int>& best_route) {
    if (visited == (1 << n) - 1) {
        int total_cost = current_cost + cost_matrix[index][start_city]; // cтоимость возвращения в стартовый город

        if (total_cost < min_cost) {
            min_cost = total_cost;
            best_route = current_route; // cохраняем лучший маршрут
            best_route.push_back(start_city); // добавляем стартовый город в конец маршрута
        }

        if (total_cost > max_cost) {
            max_cost = total_cost; // сохраняем максимальную стоимость
        }

        // вывод текущего маршрута и его стоимости
        std::cout << "Маршрут: ";
        std::cout << start_city + 1 << " -> ";
        for (size_t i = 0; i < current_route.size(); ++i) {
            std::cout << current_route[i] + 1;
            if (i < current_route.size() - 1) {
                std::cout << " -> ";
            }
        }
        std::cout << " -> " << start_city + 1 << " (стоимость: " << total_cost << ")" << "\n";

        return total_cost;
    }

    for (int city = 0; city < n; ++city) {
        if (!(visited & (1 << city))) {
            current_route.push_back(city); // добавляем город в текущий маршрут

            CompleteEnumeration(city, visited | (1 << city), n, start_city, min_cost, max_cost, current_cost + cost_matrix[index][city], cost_matrix, current_route, best_route);
            current_route.pop_back();
        }
    }
    return -1; // возвращаем -1, если маршрута нет
}

int Heuristic_GreedyAlgorithm(int start_city, const std::vector<std::vector<int>>& cost_matrix, std::vector<int>& greedy_route, int& greedy_cost) {
    int n = cost_matrix.size();
    std::vector<bool> visited(n, false);
    greedy_route.push_back(start_city); // добавляем стартовый город в маршрут
    visited[start_city] = true; // город становится посещенным

    int current_city = start_city;

    while (greedy_route.size() < n) {
        int next_city = -1;
        int min_cost = std::numeric_limits<int>::max();

        for (int city = 0; city < n; ++city) {
            if (!visited[city] && cost_matrix[current_city][city] < min_cost) {
                min_cost = cost_matrix[current_city][city];
                next_city = city;
            }
        }

        if (next_city == -1) { // если следующего города нет, то и пути нет
            return -1;
        }

        greedy_route.push_back(next_city);
        visited[next_city] = true;
        greedy_cost += min_cost;
        current_city = next_city;

    }

    greedy_cost += cost_matrix[current_city][start_city]; // в стартовый город
    greedy_route.push_back(start_city); // добавляем стартовый город в конец маршрута
    return greedy_cost;
}

int main() {
    setlocale(LC_ALL, "Russian");
    std::srand(static_cast<unsigned int>(std::time(0)));

    for (int i = 0; i < 3; ++i) { // цикл для 3-х наборов
        int n;
        int start_city;

        std::cout << "Введите количество городов для набора " << i + 1 << ": ";
        std::cin >> n;

        std::cout << "Введите начальный город (от 1 до " << n << "): ";
        std::cin >> start_city;

        if (start_city < 1 || start_city > n) {
            std::cout << "Такого города нет" << '\n';
            return 1; // ошибка
        }

        start_city--; // преобразуем к индексу от 0

        std::cout << "\nНабор " << i + 1 << " \n";

        for (int j = 0; j < 3; ++j) { // Цикл для 3х матриц
            std::cout << "\nМатрица " << j + 1 << ":\n";

            std::vector< std::vector<int>> cost_matrix(n, std::vector<int>(n));
            RandMas(cost_matrix, n);

            for (const auto& row : cost_matrix) {
                for (int cost : row) {
                    std::cout << cost << '\t';
                }
                std::cout << '\n';
            }

            // полный перебор
            int min_cost = std::numeric_limits<int>::max();
            int max_cost = std::numeric_limits<int>::min();
            std::vector<int> current_route;
            std::vector<int> best_route;

            unsigned int start_time = clock();
            CompleteEnumeration(start_city, 1 << start_city, n, start_city, min_cost, max_cost, 0, cost_matrix, current_route, best_route);
            unsigned int end_time = clock();
            unsigned int elapsed_time = end_time - start_time;

            std::cout << "Минимальная стоимость полного перебора: " << min_cost << '\n';
            std::cout << "Максимальная стоимость полного перебора: " << max_cost << '\n';
            std::cout << "Время выполнения полного перебора: " << elapsed_time << " милисекунд" << '\n';

            // эвристика
            std::vector<int> greedy_route;
            int greedy_cost = 0;

            start_time = clock();
            Heuristic_GreedyAlgorithm(start_city, cost_matrix, greedy_route, greedy_cost);
            end_time = clock();
            elapsed_time = end_time - start_time;

            std::cout << "Маршрут, построенный с помощью жадного алгоритма: ";
            for (size_t i = 0; i < greedy_route.size(); ++i) {
                std::cout << greedy_route[i] + 1;
                if (i < greedy_route.size() - 1) {
                    std::cout << " -> ";
                }
            }
            std::cout << " (стоимость: " << greedy_cost << ")" << '\n';
            std::cout << "Время выполнения жадного алгоритма: " << elapsed_time << " милисекунд" << '\n';
            float percent = abs(100 - ((100 * greedy_cost - 100 * min_cost) / (max_cost - min_cost)));
            std::cout << "Качество решения: " << percent << "%" << '\n';
            std::cout << '\n';
        }
    }

    return 0;
}