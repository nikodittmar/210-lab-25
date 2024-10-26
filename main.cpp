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

    list<string> list;
    set<string> set;
    vector<string> vector;

    string value;

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

    // SORT
    Benchmark vectorSort;
    vectorSort.startTimer();
    sort(vector.begin(), vector.end());
    vectorSort.endTimer();

    Benchmark listSort;
    listSort.startTimer();
    list.sort();
    listSort.endTimer();

    // INSERT
    string toAdd = "TESTCODE";
    
    Benchmark vectorInsert;
    vectorInsert.startTimer();
    vector.insert(vector.begin() + 10000, toAdd);
    vectorInsert.endTimer();


    cout << setw(10) << "Operation" << setw(10) << "Vector" << setw(10) << "List" << setw(10) << "Set" << endl;
    cout << setw(10) << "Read" << setw(10) << vectorRead.getTime() << setw(10) << listRead.getTime() << setw(10) << setRead.getTime() << endl;
    cout << setw(10) << "Sort" << setw(10) << vectorSort.getTime() << setw(10) << listSort.getTime() << setw(10) << "-1" << endl;

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/