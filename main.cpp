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

    Benchmark listInsert;
    listInsert.startTimer();
    std::list<string>::iterator it = list.begin();
    std::advance(it, 10000);
    list.insert(it, toAdd);
    listInsert.endTimer();

    Benchmark setInsert;
    setInsert.startTimer();
    set.insert(toAdd);
    setInsert.endTimer();

    // DELETE

    Benchmark vectorDelete;
    vectorDelete.startTimer();
    vector.erase(vector.begin() + 10000);
    vectorDelete.endTimer();

    Benchmark listDelete;
    listDelete.startTimer();
    std::list<string>::iterator it2 = list.begin();
    std::advance(it2, 10000);
    list.erase(it2);
    listDelete.endTimer();

    Benchmark setDelete;
    setDelete.startTimer();
    set.erase(toAdd);
    setDelete.endTimer();

    cout << setw(10) << "Operation" << setw(10) << "Vector" << setw(10) << "List" << setw(10) << "Set" << endl;
    cout << setw(10) << "Read" << setw(10) << vectorRead.getTime() << setw(10) << listRead.getTime() << setw(10) << setRead.getTime() << endl;
    cout << setw(10) << "Sort" << setw(10) << vectorSort.getTime() << setw(10) << listSort.getTime() << setw(10) << "-1" << endl;
    cout << setw(10) << "Insert" << setw(10) << vectorInsert.getTime() << setw(10) << listInsert.getTime() << setw(10) << setInsert.getTime() << endl;
    cout << setw(10) << "Delete" << setw(10) << vectorDelete.getTime() << setw(10) << listDelete.getTime() << setw(10) << setDelete.getTime() << endl;


    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/