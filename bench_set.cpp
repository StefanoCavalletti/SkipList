#include <iostream>
#include <set> 
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#include <ctime>

// Alias
using Clock = std::chrono::high_resolution_clock;
using DurationNs = std::chrono::duration<double, std::nano>;

// Funzione di stampa 
void printRow(const std::string& N, const std::string& s) {
    std::cout << std::left << std::setw(15) << N
              << std::setw(20) << s << std::endl;
}

int main() {
    srand(static_cast<unsigned>(time(NULL)));
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<int> n_values = {10000, 100000, 500000, 1000000};

    std::cout << "--- Benchmark: Solo std::set ---" << std::endl;
    std::cout << "Tempi in NANOSECONDI (ns) MEDI\n" << std::endl;
    std::cout << std::string(35, '-') << std::endl;
    printRow("Operazione", "std::set");
    std::cout << std::string(35, '-') << std::endl;

    for (int n : n_values) {
        std::cout << "Benchmark per N = " << n << std::endl;

        // --- 1. Preparazione Dati ---
        std::uniform_int_distribution<int> dist(0, n * 5); 
        std::vector<int> keys_to_insert(n);
        std::vector<int> keys_for_misses(n);
        std::set<int> unique_keys; 
        while (unique_keys.size() < n) {
            unique_keys.insert(dist(gen));
        }
        std::copy(unique_keys.begin(), unique_keys.end(), keys_to_insert.begin());
        
        int miss_count = 0;
        while (miss_count < n) {
            int key_miss = dist(gen);
            if (unique_keys.find(key_miss) == unique_keys.end()) {
                keys_for_misses[miss_count] = key_miss;
                miss_count++;
            }
        }
        
        std::vector<int> keys_for_hits = keys_to_insert;
        std::shuffle(keys_for_hits.begin(), keys_for_hits.end(), gen);
        std::shuffle(keys_to_insert.begin(), keys_to_insert.end(), gen);
        
        // --- 2. Test Set ---

        std::set<int> s;
        auto start = Clock::now();
        for (int key : keys_to_insert) {
            s.insert(key);
        }
        auto end = Clock::now();
        double set_insert_avg_ns = DurationNs(end - start).count() / n;

        volatile bool found; 
        start = Clock::now();
        for (int key : keys_for_hits) {
            found = (s.find(key) != s.end());
        }
        end = Clock::now();
        double set_hit_avg_ns = DurationNs(end - start).count() / n;

        start = Clock::now();
        for (int key : keys_for_misses) {
            found = (s.find(key) != s.end());
        }
        end = Clock::now();
        double set_miss_avg_ns = DurationNs(end - start).count() / n;

        std::cout << std::fixed << std::setprecision(3);
        printRow("  Inserimento", std::to_string(set_insert_avg_ns));
        printRow("  Ricerca (Hit)", std::to_string(set_hit_avg_ns));
        printRow("  Ricerca (Miss)", std::to_string(set_miss_avg_ns));
        std::cout << std::string(35, '-') << std::endl;
    }
    return 0;
}