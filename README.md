# Data-Struct-and-Analysis
Overview
This repository contains artifacts from two projects completed during my Data Structures and Algorithms course:

Project One: Analysis of run-time and memory usage for different data structures (vector, hash table, binary search tree).

Project Two: Working C++ code that sorts and prints a list of Computer Science courses in alphanumeric order.

These projects demonstrate practical application of algorithms, data structure design, and software development best practices.

Reflection
What was the problem you were solving in the projects for this course?
The problem was to design and implement a software application that helps academic advisors access and organize course information for students. Specifically, the software needed to load course data from a file, store it efficiently using an appropriate data structure, and allow users to search for and list course information in a clear, sorted format.

How did you approach the problem?
I began by analyzing how different data structures would impact the program’s efficiency, especially in terms of load time, search time, and memory usage. I selected a hash table for implementation based on its fast average-case performance for lookups and inserts. Understanding data structures was critical to designing a system that could handle real-world data access needs quickly and reliably.

How did you overcome any roadblocks you encountered while going through the activities or project?
One challenge I faced was ensuring that course information loaded correctly even when the input file contained inconsistencies, such as missing prerequisites. I addressed this by adding file format validation and error handling routines to catch and warn about bad data without crashing the program. Careful attention to file parsing and user input validation also helped avoid runtime errors.

How has your work on this project expanded your approach to designing software and developing programs?
Working through this project reinforced the importance of planning before coding. Designing pseudocode for each data structure helped me map out program flow and edge cases early. It also taught me the importance of choosing the right data structure for the problem instead of defaulting to simpler options like arrays or vectors.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
Throughout this project, I made a strong effort to write modular functions, use clear variable names, and add comments explaining the logic. I also emphasized handling invalid input gracefully. This experience showed me how small design choices can make programs easier to update or expand in the future, especially if requirements change or new features are added.
