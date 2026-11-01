SMART CAMPUS NAVIGATION AND FACILITY ANALYTICS SYSTEM
MILESTONE 1 PROJECT

PURPOSE
This C++ program loads campus buildings, walkway connections, facilities, and
academic departments from four text files. It provides facility listing and
ID lookup, campus graph display/statistics, BFS reachability, and department
tree insertion/search/display/preorder traversal.

BUILD (UNT CSE CELL / LINUX)
From the Project2_M1 directory, run:
    g++ -std=c++17 -Wall -Wextra -pedantic -Iinclude src/*.cpp -o campus

RUN
Use the supplied data directory:
    ./campus
Or supply another directory containing the four required files:
    ./campus testdata/collision

The program expects buildings.txt, connections.txt, facilities.txt, and
departments.txt inside the selected directory. The default is data/.
Do not run the command from a different working directory unless you provide
the correct relative or absolute data-directory path.

DIRECTORY LAYOUT
Project2_M1/
  include/       C++ header files
  src/           C++ implementation files, including main.cpp
  data/          Four sample-format starter data files
  testdata/
    collision/   Small custom dataset to demonstrate hash collisions
  README.txt
  CONTRIBUTIONS.txt
  design_document.txt
  test_results.txt
  .gitignore

MILESTONE 1 MENU
1 View all facilities
2 Search facility by ID
3 View campus graph
4 Display graph counts and degrees
5 Find reachable buildings (BFS)
6 Add department
7 Search department
8 Display department hierarchy
9 Run preorder traversal
10 Exit

The Final-only menu features are intentionally not implemented in this M1
package (for example, facility name/category search, shortest-path menu
operation, postorder/level-order traversal, department statistics, and
category/connectivity reports).

CELL CHECK
Compile and run on a UNT CSE CELL machine well before the deadline. The
commands above are the exact build and run commands. Confirm that the same
source, data, and documentation are present in the GitHub repository and ZIP.
