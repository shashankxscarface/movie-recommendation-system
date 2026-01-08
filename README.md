# movie-recommendation-system
Movie Recommendation System using DAA
📌 Project Overview

The Movie Recommendation System is a content-based recommendation application developed using core Design and Analysis of Algorithms (DAA) concepts.
It helps users efficiently discover movies that match their preferences by analyzing movie attributes such as genre and rating. The system reduces manual browsing time and provides personalized recommendations in a scalable and efficient manner.

⚙️ Algorithms Used

Greedy Content-Based Similarity Scoring
Computes similarity between user preferences and movie attributes by selecting the best immediate matches.

Merge Sort
Sorts movies based on similarity scores to generate ranked recommendations efficiently.

Hashing
Enables fast lookup, search, and update of movie details.

⏱️ Time & Space Complexity
Module	Time Complexity	Space Complexity
Similarity Computation	O(n × m)	O(n)
Sorting (Merge Sort)	O(n log n)	O(n)
Lookup (Hashing)	O(1) average	O(n)

Overall System Complexity:

Time Complexity: O(n × m + n log n)

Space Complexity: O(n)

Where:

n = number of movies

m = number of movie attributes
