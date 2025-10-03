# Social Network Graph

A C++ implementation of a social network using graph data structures and algorithms. Created as a coursework project to demonstrate graph theory, BFS traversal, and algorithmic problem-solving.

## Features

- Add and remove users from the network
- Create and remove friendships between users
- Find shortest path between two users using BFS
- Find shortest path while avoiding specific users (blacklist feature)
- Recommend friends based on number of mutual connections
- Check if two users are friends
- Display entire network structure

## Requirements

- C++ compiler with C++11 support or later (g++, clang++)
- Standard Template Library (STL)

## Setup & Run

### Compile
```bash
g++ -std=c++11 *.cpp -o social_network
```

### Run
```bash
./social_network
```

### Clean up
```bash
rm social_network
```

## Project Structure
```
├── SocialNetwork.h        # Class definition and graph interface
├── SocialNetwork.cpp      # Graph algorithms implementation
├── main.cpp              # CLI menu system
└── README.md
```

## Quick Start Guide

1. Start the program: `./social_network`
2. Choose from the menu options:
   - **1**: Add person to network
   - **2**: Make two people friends
   - **3**: Remove friendship
   - **4**: Remove person from network
   - **5**: Check if two people are friends
   - **6**: Find shortest path between two people
   - **7**: Find shortest path avoiding specific people (blacklist)
   - **8**: Get top K friend recommendations
   - **9**: Display entire network
   - **0**: Exit

## Graph Representation

The implementation uses an **edge list** representation:
- Vector of nodes (users)
- Vector of edges (friendships)

This approach provides:
- Simple implementation
- Easy edge addition/removal
- Efficient for sparse graphs (typical of social networks)

## Key Algorithms

### Shortest Path (BFS)
Uses breadth-first search to find the minimum number of connections between two users.
- Time Complexity: O(V + E)
- Returns empty path if no connection exists

### Constrained Path Finding
Finds shortest path while avoiding blacklisted users by marking them as visited before BFS starts.
- Time Complexity: O(V + E)
- Useful for privacy controls or routing around specific users

### Friend Recommendations
Suggests connections based on number of mutual friends.
- Counts common friends for all non-friend users
- Returns top K recommendations sorted by mutual friend count
- Time Complexity: O(n² × d²) where d = average degree

## Example Usage

```
Add users: Alice, Bob, Carol, David
Create friendships: Alice-Bob, Bob-Carol, Carol-David
Find path from Alice to David: Alice → Bob → Carol → David
Recommend friends for Alice: Carol (1 mutual friend through Bob)
```

## What I Learned

This project helped me understand:

### Graph Theory
- Different graph representations (edge list, adjacency list, adjacency matrix)
- Breadth-first search (BFS) implementation and applications
- Shortest path algorithms in unweighted graphs
- Modifying standard algorithms to handle constraints (blacklist)

### Data Structures
- Using STL containers (vector, queue, unordered_set)
- Nested classes for clean organization (Node, Edge)
- Trade-offs between different data structure choices

### Algorithm Design
- Breaking down complex problems into smaller steps
- Analyzing time and space complexity
- Handling edge cases (empty graphs, disconnected components, self-loops)
- Optimizing algorithms for specific use cases

### C++ Programming
- Class design with proper encapsulation
- Const correctness and method signatures
- STL algorithms and iterators
- Memory management with RAII

## Known Limitations

- Edge list has O(E) lookup time for checking if friendship exists (adjacency list would be O(1))
- Friend recommendation algorithm is O(n²) which doesn't scale well for large networks
- No data persistence (network resets on program exit)
- Command-line interface only (no GUI)
- Assumes all friendship weights are equal (no "close friend" vs "acquaintance")

## Potential Improvements

- Switch to adjacency list for faster neighbor lookups
- Add file I/O for saving/loading networks
- Implement Dijkstra's algorithm for weighted graphs
- Add community detection algorithms
- Optimize friend recommendations with better data structures

## Acknowledgments

Built as a course project for Data Structures & Algorithms at University of Balamand.

## License

Educational project - free to use and modify for learning purposes.