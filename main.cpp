// COMSC 210 | Lab 25 | Niko Dittmar
#include <iostream>
#include <fstream>
#include <chrono>
#include <list>
#include <set>
#include <iomanip>
using namespace std;
using namespace std::chrono;

const int NUM_TESTS = 15;

class Benchmark {
private: 
    time_point<high_resolution_clock> start_time;
    time_point<high_resolution_clock> end_time;
    int microseconds;
public:
    Benchmark() {
        microseconds = -1;
    }

    // getTime() gets the benchmark time.
    // arguments: none.
    // returns: the amount of time the test took.
    int getTime() {
        return microseconds;
    }

    // startTimer() starts the benchmark and begins the clock.
    // arguments: none.
    // returns: none.
    void startTimer() {
        start_time = high_resolution_clock::now();
    }

    // endTimer() finishes the benchmark and ends the clock.
    // arguments: none.
    // returns: none.
    void endTimer() {
        end_time = high_resolution_clock::now();
        microseconds = duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    }
};

vector<vector<int> > runTest();

int main() {

    vector<vector<vector<int> > > tests;

    for (int i = 0; i < NUM_TESTS; i++) {
        tests.push_back(runTest());
    }

    vector<vector<int> > results;

    for (int i = 0; i < 4; i++) {
        vector<int> averagedResults;
        for (int j = 0; j < 3; j++) {
            int sum = 0;
            for (int k = 0; k < NUM_TESTS; k++) {
                sum += tests[k][i][j];
            }
            averagedResults.push_back(sum / NUM_TESTS);
        }
        results.push_back(averagedResults);
    }

    cout << "Number of simulations: " << NUM_TESTS << endl;
    cout << setw(10) << "Operation" << setw(10) << "Vector" << setw(10) << "List" << setw(10) << "Set" << endl;
    cout << setw(10) << "Read" << setw(10) << results[0][0] << setw(10) << results[0][1] << setw(10) << results[0][2] << endl;
    cout << setw(10) << "Sort" << setw(10) << results[1][0] << setw(10) << results[1][1] << setw(10) << results[1][2] << endl;
    cout << setw(10) << "Insert" << setw(10) << results[2][0] << setw(10) << results[2][1] << setw(10) << results[2][2] << endl;
    cout << setw(10) << "Delete" << setw(10) << results[3][0] << setw(10) << results[3][1] << setw(10) << results[3][2] << endl;

    return 0;
}

vector<vector<int> > runTest() {
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

    std::vector<std::vector<int>> results = {
        { vectorRead.getTime(), listRead.getTime(), setRead.getTime() },
        { vectorSort.getTime(), listSort.getTime(), -1 },
        { vectorInsert.getTime(), listInsert.getTime(), setInsert.getTime() },
        { vectorDelete.getTime(), listDelete.getTime(), setDelete.getTime() }
    };

    return results;
}