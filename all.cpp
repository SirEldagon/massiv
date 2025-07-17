#include <iostream>
#include <vector>
#include <thread>
#include <numeric> // для std::accumulate
#include <cstdlib> // для rand()
#include <ctime>   // для time()

// Функция для подсчёта суммы части массива
void partial_sum(const std::vector<int>& arr, size_t start, size_t end, long long& result) {
    result = std::accumulate(arr.begin() + start, arr.begin() + end, 0LL);
}

int main() {
    // Ввод данных
    size_t N, M;
    std::cout << "Введите размер массива N: ";
    std::cin >> N;
    std::cout << "Введите количество частей M: ";
    std::cin >> M;

    if (M >= N) {
        std::cerr << "Количество частей M должно быть меньше размера массива N." << std::endl;
        return 1;
    }

    // Инициализация массива случайными числами
    std::vector<int> arr(N);
    std::srand(std::time(nullptr));
    for (size_t i = 0; i < N; ++i) {
        arr[i] = std::rand() % 100; // числа от 0 до 99
    }

    // Вывод массива (опционально)
    std::cout << "Массив: ";
    for (const auto& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Создание потоков и результатов
    std::vector<std::thread> threads;
    std::vector<long long> partial_sums(M, 0);
    size_t part_size = N / M;
    size_t remaining = N % M;

    size_t start_idx = 0;

    // Запуск потоков
    for (size_t i = 0; i < M; ++i) {
        size_t end_idx = start_idx + part_size + (i < remaining ? 1 : 0);
        threads.emplace_back(partial_sum, std::cref(arr), start_idx, end_idx, std::ref(partial_sums[i]));
        start_idx = end_idx;
    }

    // Ожидание завершения потоков
    for (auto& t : threads) {
        t.join();
    }

    // Подсчёт общей суммы
    long long total_sum = std::accumulate(partial_sums.begin(), partial_sums.end(), 0LL);

    std::cout << "Общая сумма элементов массива: " << total_sum << std::endl;

    return 0;
}
