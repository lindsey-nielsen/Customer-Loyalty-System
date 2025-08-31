# Customer Loyalty System
A simple customer loyalty system implemented in C using a binary search tree (BST) for efficient storage and retrieval of customer data. The program supports operations such as adding, subtracting, searching, deleting, counting customers, and sorting customers by loyalty points.

## Features
- Add / Subtract Points: Update customer loyalty points.
- Delete Customer: Remove a customer from the system.
- Search Customer: Find a customer and report their points and tree depth.
- Count Smaller: Count customers whose names come alphabetically before a given name.
- Sorted Output: Outputs all customers sorted by loyalty points.

## Data Structures & Algorithms
- Binary Search Tree: Stores all customer data.
- Quick Sort: Sorts customers by points (descending), and names (alphabetical tie-breaker).
- Memory Management: Only one copy of each customer is stored. All allocated memory is freed at the end.
- Ensures efficient runtime for operations: O(h) where h = tree height. 

## Example Input / Output
### Input
6
add Alice 50
add Bob 30
add Charlie 70
sub Alice 20
search Alice
count_smaller Charlie

### Output
Alice 50
Bob 30
Charlie 70
Alice 30
Alice 30 1
2
Charlie 70
Alice 30
Bob 30

## How to Compile & Run
gcc main.c -o loyalty
./loyalty

Provide the number of commands followed by each command in standard input.

### Commands
- add <name> <pts>
- sub <name> <pts>
- del <name>
- search <name>
- count_smaller <name>
