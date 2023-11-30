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
0,010,753,
1,200,322,
2,302,902,
3,211,222,
4,002,433,
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

Once the global variables mentioned above are initialized, the next task is to calculate the resource needs of each process. This can be achieved by initializing a 2-dimensional array `need` whose size is processCount x resourceCount. A nested for loop can then be used to initialize the array with the maximum amount of resources that can be allocated subtracted from the amount of resources each process will need to allocate. 

```cpp
for (int i = 0; i < processCount; ++i) {
    for (int j = 0; j < resourceCount; ++j) {
        need[i][j] = max[i][j] - alloc[i][j]
    }
}
```
Next is the "core" part of the implementation, which consists of a lot of nested for loops. The outer most loop determines how many times the output will run. To allow for variable sized input, this loop is set to run up until the index/iterator `i` reaches the amount of processes counted while parsing the text file. Directly inside this loop is another for loop with the same condition. This creates a block of code which repeats for the total number of processes on each process. 

Inside the nested for loops is a single if condition which only runs if the current flag associated with a process is set to zero. This means that a process has not yet executed, and should therefore be checked for validity. Inside this if statement a new `flag` integer is initialized to zero. This flag determines whether a given process is safe to run. The following for loop uses a temporary variable `j` which is iterated up to the value in `resourceCount`. If the requirements for running the process (located in `need[i][j]`) are greater than the availale resources (stored in `available[i]`), the flag is set to one and the inner for loop breaks. The outer loop will continue until either a safe state is found, or all possible paths have been deemed unsafe. 

If the flag is not set to one, the current process will be added to the `ans[]` array, a for loop will then run which simulates the release of resources by the given process back to the `available[]` array. `f[i]` is them set to 1 to indicate that the process has successfully "executed". 

This process repeats until the outer loop has executed for every process provided in the text file. 

```cpp
for (int i = 0; i < processCount; ++i) {
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
```

Once the bankers algorithm is complete, a safety check is done to check whether any of the processes have not executed (using the `f[]` array). If a process has not executed, this means that a safe path has not succesfully been found, and that the system is in an unsafe state. If this is the case, an error is sent to the console, otherwise the flag variabel is not tripped and the safe sequence stored in `ans[]` is displayed. 

```cpp
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
```

