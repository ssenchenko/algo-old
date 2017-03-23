In this assignment we will revisit an old friend, the traveling salesman problem (TSP). 
This week you will implement a heuristic for the TSP, rather than an exact algorithm, and as a result 
will be able to handle much larger problem sizes.
The first line indicates the number of cities. Each city is a point in the plane, and each subsequent line 
indicates the x- and y-coordinates of a single city.

The distance between two cities is defined as the Euclidean distance --- that is, two cities at 
locations (x,y) and (z,w) have distance sqrt((x−u)^2+(y−v)^2) between them.

You should implement the nearest neighbor heuristic:

1) Start the tour at the first city.
2) Repeatedly visit the closest city that the tour hasn't visited yet. In case of a tie, go to the closest 
city with the lowest index. For example, if both the third and fifth cities have the same distance from 
the first city (and are closer than any other city), then the tour should begin by going from the first city 
to the third city.
3) Once every city has been visited exactly once, return to the first city to complete the tour.