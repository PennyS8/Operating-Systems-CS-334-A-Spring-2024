# Write-up:
1. Did you complete all required sections and does your solution have all required functionality stated in this assignment. If not, state what functionality you successfully implemented and what is missing.
    - Yes, all required sections have been completed, and the solution includes the specified functionality.

2. Draw a picture of what the array of points looks like (as a datastruture). Please initialized and show the value of each variable in each of the point structs.
    - [point**]-->[point*]-->[point]-->{x: 0, y: 10, c: 0}
                [point*]-->[point]-->{x: 3, y: 7,  c: 0}
                [point*]-->[point]-->{x: 4, y: 6,  c: 0}
                [point*]-->[point]-->{x: 5, y: 5,  c: 0}
                [point*]-->[point]-->{x: 6, y: 4,  c: 0}
                [point*]-->[point]-->{x: 7, y: 3,  c: 0}
                [point*]-->[point]-->{x: 8, y: 2,  c: 0}
                [point*]-->[point]-->{x: 9, y: 1,  c: 0}

3. Run your code through valgrind, copy and paste the very end of the valgrind output that shows the memory allocation/frees/leaks (your program should be free of memory leaks).
    $ valgrind --leak-check=yes --log-file=valgrind.rpt ./output 10
    10
    done with allocaitons
    Orig Pts: x:0, y:10, c:0
    Orig Pts: x:1, y:9, c:0
    Orig Pts: x:2, y:8, c:0
    Orig Pts: x:3, y:7, c:0
    Orig Pts: x:4, y:6, c:0
    Orig Pts: x:5, y:5, c:0
    Orig Pts: x:6, y:4, c:0
    Orig Pts: x:7, y:3, c:0
    Orig Pts: x:8, y:2, c:0
    Orig Pts: x:9, y:1, c:0
    poly-line resized
    Orig Pts: x:10, y:0, c:0
    size: 1

4. If your program would include /usr/include/math.h header file:
    * What functionality does this module implement? (use cat or man commands)
        - mathematical operations

    * Copy and paste 5 sample functions/methods defined in this module? (function signature only)
        - inline int issignaling(float val){
            return issignalingf(val);
        }
        
        - is zero(float val){
            return fpclassifyf(val) == FP_ZERO;
        }

        - inline int issignaling(Float128 val){
            return issignalingf128(val);
        }

        - (extension({typeof(x) x = (x); typeof(y) y = (y);\
                !isunordered(x,y) && x > y;}))
        
        - (extension({typeof(x) x = (x); typeof(y) y = (y);\
                !isunordered(x,y) && x >= y;}))

    * Using CLI, how do you find the content of the math.h file?
        - primaryily man because that was what I have used more in the past

5. Shortly describe the function of the libraries with the headers included in the /usr/include/linux folder.
    - They interface the OS and our C programs.
