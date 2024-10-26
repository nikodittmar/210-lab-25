#include <iostream>
#include <fstream>
#include <chrono>
#include <list>
#include <set>
#include <iomanip>
using namespace std;
using namespace std::chrono;

class Benchmark {
private: 
    time_point<high_resolution_clock> start_time;
    time_point<high_resolution_clock> end_time;
    int microseconds;
public:
    Benchmark() {
        microseconds = -1;
    }
    int getTime() {
        return microseconds;
    }
    void startTimer() {
        start_time = high_resolution_clock::now();
    }
    void endTimer() {
        end_time = high_resolution_clock::now();
        microseconds = duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
};

int main() {

    list<int> list;
    set<int> set;
    vector<int> vector;

    int value;

    // READ

    ifstream fin1("codes.txt");
    Benchmark vectorRead;
    vectorRead.startTimer();
    while(fin1 >> value) {
        vector.push_back(value);
    }
    vectorRead.endTimer();
    fin1.close();
    
    ifstream fin2("codes.txt");
    Benchmark listRead;
    listRead.startTimer();
    while(fin2 >> value) {
        list.push_back(value);
    }
    listRead.endTimer();
    fin2.close();

    ifstream fin3("codes.txt");
    Benchmark setRead;
    setRead.startTimer();
    while(fin3 >> value) {
        set.insert(value);
    }
    setRead.endTimer();
    fin3.close();

    cout << setw(10) << "Operation" << setw(10) << "Vector" << setw(10) << "List" << setw(10) << "Set" << endl;
    cout << setw(10) << "Read" << setw(10) << vectorRead.getTime() << setw(10) << listRead.getTime() << setw(10) << setRead.getTime() << endl;
    
    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/