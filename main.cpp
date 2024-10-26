#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

class Benchmark {
private: 
    time_point<high_resolution_clock> start_time;
    time_point<high_resolution_clock> end_time;
    int milliseconds;
public:
    Benchmark() {
        milliseconds = -1;
    }
    int getTime() {
        return milliseconds;
    }
    void startTimer() {
        start_time = high_resolution_clock::now();
    }
    void endTimer() {
        end_time = high_resolution_clock::now();
        milliseconds = duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    }
};

int main() {
    
    
    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/