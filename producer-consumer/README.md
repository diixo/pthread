## producer and consumer
A simple FIFO pipe between to tasks. The primary problem is ensuring that the producer blocks if the FIFO is full, the consumer blocks if it is empty, and avoiding data-races along the way. 
A secondary concern is that there is as little interference between the two tasks as possible.
