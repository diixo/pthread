## Reader and Writer
Assume that we have a number of threads which want to read from a buffer, and at least one writer which needs to write to it. 
The biggest problem is to avoid starvation, although dead-lock can be a problem if you screw-up the algorithm.
