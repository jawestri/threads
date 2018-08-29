## Linux Case Study
###### By: Jamie Westrick

- Part A - Usage of threads, files, IPC for random data generation & logging
  - File: s.c
   - $gcc s.c -lpthread, $./a.out
   - Will output sensordata2.txt
- Part B - Shell scripts to retrieve data and draw some inferences using filter commands
   - File: s.sh
    - $./s.sh
    - Will output output.txt and dislay average, max, and min temperatures in GUI window
- Part C - Usage of developer tools & quality checks – Makefiles, Libraries, valgrind, cppcheck, lcov, doxygen etc.
  - See:
      - res folder for lcov result
      - Docs folder for doxygen result
      - valgrind_output for valgrind result
      - cppcheckCaseStudy.png, err.txt for cppcheck result
  
