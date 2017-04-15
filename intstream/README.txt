  course 2: Graph Search, Shortest Paths, and Data Structures
  Week 3 assignment:
  
  getting 1 integer at a time
  compute the median of all integers given so far
  make it in logN time
  Letting xi denote the ith number of the file, the kth median mk is defined 
  as the median of the numbers x1,…,xk. 
  (So, if k is odd, then mk is ((k+1)/2)th smallest number among x1,…,xk; 
  if k is even, then mk is the (k/2)th smallest number among x1,…,xk.)

  Class int_stream can be created with one of 2 data models:
      - heap_model (default implementation) class is implemented in current file
      - binary_tree - class may be implemented later

  heap_model is built on 2 priority_queues
  the 1st one is max_heap and stores N/2 smallest numbers
  the 2nd one is min_heap and stores N/2 biggest numbers
  so the median can be chosen between the tops of those 2 heaps
