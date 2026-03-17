<h1 align="center">🌳 Tree Structures Benchmark</h1>

<p align="center">
  <strong>Comparative C++ implementation of Red-Black Trees, AVL Trees and B-Trees</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white"/>
  <img src="https://img.shields.io/badge/Data%20Structures-Advanced-orange?style=for-the-badge"/>
  <img src="https://img.shields.io/badge/Algorithms-Analysis-blueviolet?style=for-the-badge"/>
</p>

---

## 📖 About

A Data Structures semester project implementing and benchmarking three self-balancing tree data structures in C++. The project focuses on understanding the trade-offs between insertion, deletion and search performance across different tree variants.

## 🌲 Implemented Structures

| Structure | Balancing Strategy | Best Use Case |
|---|---|---|
| **Red-Black Tree** | Color-based rotations | General purpose, fast insertion |
| **AVL Tree** | Height-balanced rotations | Read-heavy workloads |
| **B-Tree** | Multi-way branching | Disk-based / database storage |

## ✨ Features

- ➕ Insert, delete and search operations for all three trees
- 📊 Performance benchmarking across different data sizes
- 🖨️ In-order, pre-order and post-order traversal
- 📋 Menu-driven CLI for interactive testing

## 🛠️ Tech Stack

| | |
|---|---|
| Language | C++ |
| Concepts | Self-balancing BSTs, Time Complexity Analysis |
| Build | g++ |

## 🚀 Getting Started

```bash
git clone https://github.com/HamzaSaeed31/Tree-Structures-Benchmark.git
cd Tree-Structures-Benchmark

g++ -o trees main.cpp -O2
./trees
```
