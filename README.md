# Embedded Onboarding

Welcome to the embedded systems onboarding projects repository. This repository contains a series of increasingly complex onboarding projects for new members to complete by themselves. The goal of these projects are to introduce concepts and technologies that are frequenctly used in our robotic systems. The `Embedded-Onboarding-1` and `Embedded-Onboarding-2` projects are primarily focused on introducing technologies for preparing members to work on a new Telemetry system (2025). Additional onboarding projects may be added for preparing members for other projects like motion control or communication later on.

If there are issues with clarity, difficulty of projects, or you have any general suggestions, please submit an issue on github and it will be reviewed.

## Prerequisites
I am assuming you have atleast some experience in programming and know basic constructs like functions, for-loops, branching. You do not necessary need to know C/C++, however, it would be beneficial to learn about the basics before embarking on these projects. I have included a list of C/C++ concepts with some resources to learn about below in its own dedicated section, please take some time to go through those. 

### C/C++ Concepts and Resources
Below is a list of concepts that you should be familar with before starting the embedded onboarding projects. There are accompanying questions below each concept to help guide learning. Please try to learn as much as you can about each concept, at the bare minimum atleast know how to use it in code at a basic level.

There are a list of resources that I think may be helpful for learning/reviewing C/C++. Many of these resources are long, so you probably won't need to read through all of them. Choose the ones that best suit you or find other resources that fit your learning style the best.

**Concepts**
 - Primitives (char, int, float, bool, etc.)
   - What kind of data does each primitive represent?
   - What are the advantages and limits of each primitive?
   - What is overflow/underflow for numeric types like int and char?
   - How big is each primitive?
   - What are literals?
   - What kind of operations can you do with them?
     - What is binary and what are supported binary operations?
     - What is hexadecimal and how to convert to binary?
 - Data-structures (c-array, std::array, c-strings, std::string)
   - What are the differences between c-style arrays and c++ std::arrays?
   - How are strings actually stored?
 - Memory Management (malloc, free, memcpy, pointers, references)
   - What is the stack and what is the heap?
     - How do you allocate memory on the heap?
     - How do you allocate memory on the stack?
   - How do you use malloc and free?
   - What are the differences between pointers and references?
   - What are some dangers when using pointers and references you have to consider?
 - Basic Constructs (branching/conditionals, for-loops, functions)
   - What are switch-statements and when to use them instead of if-statements.
   - What are boolean logic operators?
   - How to iterate over a range? How to iterate over a collection like std::array?
   - How do you call a function?
 - Fundamental macros and Compilation
   - What are header files? What are source files?
     - What are header guards?
     - What is C++ name-mangling and what does `extern "C" {}` do?
   - What do you need to do to create C++ executables?
     - What are the differences compile-time, link-time, and run-time?
   - What does the preprocessor do?
     - What is a translation unit?
     - How do you make preprocessor macro definitions? How do you do it on the command line level?

**Resources**
 - [freeCodeCamp C++ course YT Lecture](https://youtu.be/vLnPwxZdW4Y?si=hAaSEJ516gHWq5YU)
 - [cppreference](https://www.cppreference.com/)
 - [learncpp](https://www.learncpp.com/)
 - [Princeton resources](https://researchcomputing.princeton.edu/education/external-online-resources/cplusplus)
 - [ChatGPT](https://chatgpt.com)

## Demos
Demo projects are included in the repository for demostrating the intended end behavior. These are minimal prototypes just meant to showcase the end result. The demos should looked at after you have completed the project or when you are completely stuck after looking at the instructions, hints, and asking for help from an onboarding instructor.