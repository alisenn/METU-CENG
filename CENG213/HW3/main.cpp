#include "EmployeeTable.h"
#include "Employee.h"
#include <time.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include "ItemNotFoundException.h"

using namespace std;

int main (int argc, const char * argv[]) {
    // TEST CASE FOR DATASETS

    double avgAccessTime = 0;
    double averageFilledRatio = 0;

    EmployeeTable empTable1;  // Def. bucket size: 151
    EmployeeTable empTable2(503);
    EmployeeTable empTable3(1249);

    // All tests have been finished. Now, we'll get the results of all datasets to measure time performance.
    for (int fileItr = 1; fileItr<11; fileItr++) {

        int totalNonemptyBuckets = 0;

        // Get a handle to the respective input file.
        ifstream inputFile;
        string fileName = "Company";
        stringstream ss;
        ss<<fileItr;
        fileName = fileName + ss.str();
        fileName = fileName + ".txt";

        std::cout << "Processing "<<fileName<<"..."<<endl;
        std::cout.flush();

        inputFile.open(fileName.c_str());

        // Read the input file and find the employees!

        // First, read the input file.
        int numberOfPages = 0;
        string buffer;
        inputFile >> numberOfPages;

        // Form the employeeTable.
        EmployeeTable employeeTable(numberOfPages);
        string* ssnList = NULL;
        int state = 0;
        int empCount = 0;
        int queryCount = 0;
        clock_t t;

        // Read employees/SSNs from input file.
        inputFile>>buffer;
        while (inputFile.good()) {
            // At the beginning, read employees and change state.
            if (state == 0 && buffer == "--Employees--") {
                state = 1;
                // Read new line's token.
                getline(inputFile, buffer);
                getline(inputFile, buffer);
                continue;
            }

            // In state 1, we'll be reading employees. Since there is no need
            // to keep them around in memory, just add them to the employee table.


            if (state == 1 && buffer != "--SSNs--"){

                empCount++;
                string name, place, ssn;
                int experience;

                // Read employee entry.
                //           (*inputFile)>>name;
                name = buffer;
                inputFile >> experience;
                getline(inputFile, place);
                getline(inputFile, place);
                inputFile >> ssn;

                // Form the employee and put him/her into the employeeTable.
                Employee employee(name, experience, place, ssn);
                 employeeTable.addEntry(employee);


                 cout<<employee.getSsn()<<endl;
                // Read new line's token.
                getline(inputFile, buffer);
                getline(inputFile, buffer);

                continue;
            }
            // If the code is here, it means that we encountered --SSNs-- sign.
            else if (state == 1 && buffer == "--SSNs--")
            {
              cout <<"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaasssssssssssssss"<<endl;
                state = 2;

                ssnList = new string[empCount];
                // Read new line's token.
                getline(inputFile, buffer);
                continue;
            }

            // Read SSNs, and index them for using later.
            if (state == 2 && buffer != "") {

                string ssn;

                ssn = buffer;

                ssnList[queryCount] = ssn;
                // Read new line's token.
                getline(inputFile, buffer);
                queryCount++;

            }
        }

        inputFile.close();
        // We have the ssn in ssnList array.

        // Here, we'll check for the distribution of entries in the hash table.
        for (int bucketItr = 0; bucketItr<numberOfPages; bucketItr++){
            int count = employeeTable.getNumberOfEmployeeInBucket(bucketItr);
            if (count>0)
                totalNonemptyBuckets++;
        }
        cout<< "totalNonemptyBuckets:  " <<totalNonemptyBuckets<<endl;


        int callItr = 0, trialItr = 0;

        t = clock();
        // Make all of the calls a thousand times to get a precise idea about how long it takes.
        // In actual test code, we'll run this loop multiple times too.
        // Then we'll get the average or mean value of all runs, to eliminate chance factor.
        for (trialItr = 0; trialItr<1000; trialItr++){
            for (callItr = 0; callItr<queryCount; callItr++) {
                try {
                    employeeTable.findEmployee(ssnList[callItr]);
                } catch (ItemNotFoundException e) {
                    cout << e.what() << endl;
                }

            }
        }

        t = clock()-t;

        avgAccessTime = avgAccessTime + ((double)t / (double) queryCount);

        // Now that we have the clock ticks passed for all calls, write the logging information.
        cout << "On average, " << ((double)t / (double) queryCount) << " ticks passed for company " << fileItr << endl;

        averageFilledRatio += (double) empCount / totalNonemptyBuckets;

        // Print the stats.
        delete []ssnList;
    }


    averageFilledRatio = averageFilledRatio / 10;
    avgAccessTime = avgAccessTime / 10;

    cout << " ************************************ " << endl;
    cout << "AVERAGE ACCESS TIME: " << avgAccessTime << endl;
    cout << "FILLED RATIO: " << averageFilledRatio << endl;
}
