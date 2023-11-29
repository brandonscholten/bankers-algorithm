//Brandon Scholten - Implementaiton of Bankers Algorithm
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>

int main () {
    //globals
    int processCount = 0;
    int resourceCount = 0;
    std::map<int, std::string> alloc;
    std::map<int, std::string> max;
    int available[3];
    //open file and read data
    std::ifstream input("input.txt");
    std::string line;
    if (input.is_open()) {
        //save first line as available resources
        std::getline(input, line);
        for (int i = 0; i < line.length(); ++i) {
            available[i] = line[i];
        }
        //save the rest of the file into allocated and maximum maps
        while (input) {
            std::getline(input, line);
            //split at comma
            std::vector<std::string> lineSplit;
            std::string temp("");
            //TODO: nesting gets too deep here
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] == ',') {
                    lineSplit.push_back(temp);
                    temp.clear();
                    continue;
                } 
                temp = std::string(temp) + line[i];
            }
            //populate maps
            alloc.insert(std::pair<int, std::string>(stoi(lineSplit[0]), lineSplit[1]));
            max.insert(std::pair<int, std::string>(stoi(lineSplit[0]), lineSplit[2]));
            //clear vector
            lineSplit.clear();
            //set counter
            ++processCount;
        }
        resourceCount = alloc[0].length();
    } else {
        std::cout << "error opening file!";
    }
    //bankers algorithm implementation
    int f[processCount], ans[processCount], index = 0;
    for (int i = 0; i < processCount; ++i) {
        f[i] = 0;
    }
    int need[processCount][resourceCount];
    for (int i = 0; i < processCount; ++i) {
        for (int j = 0; j < resourceCount; ++j) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
    for (int i = 0; i < 5; ++i) {
        for (int i = 0; i < processCount; ++i) {
            //TODO: nesting gets too deep here
            if (f[i] == 0) {

                int flag = 0;
                for (int j = 0; j < resourceCount; ++j) {
                    if (need[i][j] > available[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    ans[index++] = i;
                    for (int y = 0; y < resourceCount; ++y) {
                        available[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            
            }
        }
    }

    //check safety
    int flag = 1;

    for (int i = 0; i<processCount; ++i) {
        if (f[i] == 0) {
            flag = 0;
            std::cout << "The state of the system is not safe.";
            break;
        }
    }

    if (flag == 1) {
        std::cout << "safe sequence: ";
        for (int i = 0; i < processCount-1; ++i) {
            std::cout << " P" << ans[i] << " ->";
        }
        std::cout << " P" << ans[processCount-1] << std::endl;
    }

    return(0);
}
