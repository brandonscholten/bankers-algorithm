# bankers-algorithm
An assignment for my operating systems class to implement the bankers algorithm
## compile and run
To get started, run the following commands to clone and run the project.
```
gh repo clone brandonscholten/bankers-algorithm
cd bankers-algorithm
clang++ implementation.cpp
./a.out
```
## reading input
This implementation of the bankers algorithm reads a "snapshot" of a system which is represented in a text file. The format is described below.
### file format
```
322
0,010,753
1,200,322
2,302,902
3,211,222
4,002,433
```
The first row in the text file contains the values for available resources in the system. In the example provided there are three "types" of resources. Assuming each resource cannot have more then 9 available instances when the snapshot is recorded, the values can be represented in a three character string. This string is read before the rest of the file and converted to three integers which are stored in an array. 

The rest of the file is formatted exactly like a CSV file. Starting on the second line the columns represent the following values respectively: process number, allocated instances for each of the three types, and the maximum number instances requested of each type. This data is read into two maps: `alloc` and `max`.
### parsing the file
The first line of the file is read using `std::getline()` and looped through in order. On each iteration of the loop, the input is converted to an integer and saved to the array of integers `available[3]`.

Once first line has been read, a while loop reads until the end of the file. As each line is read, a string `temp` is used to populate a vector of strings `lineSplit`, which is them used to populate the maps `alloc` and `max`. Each map uses the process number as a key in the form of an integer. `alloc` stores a string with the number of allocated instances while `max` stores a string with the maximum number of instances in each entry. 

With the snapshot information loaded into memory, the program can successfully execute the bankers algorithm.

## banker's algorithm implementation
On submission, the bankers algorithm implementation is written in a single file using only functional programming. This implementation makes the program relatively difficult to follow. It is my intention to refine this in a future update such that the implementation uses a class to store information about each process if I have sufficient time. 

### globals

`int f[processCount]` an array of "flags" that is initialized to all zeros. The flags are switched to the value 1 if a given process has "executed".

`int ans[processCount]` array which stores the safe execution sequence (assuming the system is in a safe state).

`int index` Index used during the safety check to increment the position being written to in the answer array. 

### implementation

