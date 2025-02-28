# Multi-Path Air Route Cost Analysis: Routes Generator with Ranking for Weighted Graphs  
# 📖 Overview
This project finds all possible routes between two vertices in a weighted graph and ranks them from least to most costly. It is designed for applications such as air traffic routing, logistics, and other path optimization problems. The algorithm explores multiple paths, calculates their costs, and returns an ordered list of viable routes.

In this implementation, the system is designed for air route optimization, where nodes represent airports, and edges (weights) represent travel costs such as fuel expenses, distance, or time. The algorithm efficiently finds different flight paths between two airports, helping identify the most cost-effective routes.

# 🔍 OmargabaguAlgorithm: Graph-Based Pathfinding  

This function is a graph-based pathfinding algorithm designed to identify and sort possible routes between two vertices in a weighted graph. The algorithm determines all viable paths and orders them from least to most costly, making it particularly useful for applications like air traffic route planning, logistics, and network optimization. 

---

## 🛠 How It Works  

### 📌 Graph Representation  
- The graph consists of **vertices (nodes)** and **edges (connections)**.  
- Each vertex has an **ID**, and edges have **weights** representing the cost.  

### ⚙️ Algorithm Steps  

1. **Initialization**  
   - The **destination node** is marked (`code = 3`).  

2. **Stack-Based Exploration**  
   - A **stack** tracks visited nodes.  
   - Neighbors are evaluated and marked as **visited (`code = 1`)**.  

3. **Path Storage**  
   - When a valid path to the destination is found, it is stored in a **result structure (`Res`)**, including the path sequence and total cost.  

4. **Backtracking**  
   - If no more unexplored neighbors are available, the algorithm **backtracks** to previous nodes.  

---

## 🔧 Utility Functions  

- **`visited()`** → Checks how many neighboring nodes have been visited.  
- **`Res_New()`** → Creates a new result object containing a found path.  
- **`ResList`** → Maintains a list of possible paths.  
- **`Graph_Sort()`** → Calls the OmargabaguAlgorithm to search for routes between two specified vertices.  

---

## 📌 Example Output  

```rust
Graph with 5 vertices:
0 -> 2 (cost: 5)
2 -> 3 (cost: 4)
3 -> 4 (cost: 3)
4 -> 

Paths Found:
1. 0 -> 2 -> 3 -> 4 | Cost: 12
2. 0 -> 1 -> 4      | Cost: 15

