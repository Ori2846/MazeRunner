
<p align="center">
    <b>MazeRunner: Maze Creation and Solving</b>
</p>
<p align="center">
    <a href="https://github.com/Ori2846/MazeRunner/releases">
        <img src="https://img.shields.io/github/release/Ori2846/MazeRunner.svg?style=flat&color=success" alt="Version"/>
    </a>
    <a href="https://github.com/Ori2846/MazeRunner/releases">
        <img src="https://img.shields.io/github/release-date/Ori2846/MazeRunner.svg?style=flat&color=blue" alt="GitHub Release Date"/>
    </a>
    <a href="https://github.com/Ori2846/MazeRunner/issues">
        <img src="https://img.shields.io/github/issues/Ori2846/MazeRunner.svg?style=flat&color=success" alt="GitHub issues"/>
    </a>
    <a href="https://github.com/Ori2846/MazeRunner">
        <img src="https://img.shields.io/github/last-commit/Ori2846/MazeRunner.svg?style=flat&color=blue" alt="GitHub last commit"/>
    </a>
</p>
Overview
MazeRunner is a demo project for creating and solving mazes using SFML (Simple and Fast Multimedia Library) in C++. This project demonstrates the process of generating a maze and solving it using the A* algorithm, with real-time visualizations.

Demo Videos
Creating the Maze: Watch the demo of the maze generation process.

https://github.com/Ori2846/MazeRunner/assets/74078771/357434b6-adc8-467e-8991-6b765eda1d0f

Solving the Maze: Watch the demo of the maze-solving process.

https://github.com/Ori2846/MazeRunner/assets/74078771/78f79420-4194-460c-a2dc-5ff61e752f18

Features
Maze Generation: Randomly generates a maze using a depth-first search algorithm.
Maze Solving: Solves the maze using the A* search algorithm.
Real-time Visualization: Provides real-time visualization of the maze generation and solving processes using SFML.
User Interaction: Allows user to navigate the maze using keyboard controls.
Technologies Used
C++: Core programming language.
SFML: Library for graphics, window, and event handling.
Standard Library: Includes algorithms, containers, and utility functions for maze and pathfinding logic.
Getting Started
Prerequisites
SFML library installed on your system. You can download it from SFML's official website.
Installation
Clone the repository:

sh
Copy code
git clone https://github.com/Ori2846/MazeRunner.git
cd MazeRunner
Set up your development environment to include and link against SFML. Instructions can be found here.

Build the project:

sh
Copy code
g++ -o MazeRunner main.cpp -lsfml-graphics -lsfml-window -lsfml-system
Run the executable:

sh
Copy code
./MazeRunner
Usage
W: Move up
A: Move left
S: Move down
D: Move right
How It Works
Maze Generation
The maze is generated using a depth-first search (DFS) algorithm. The process is visualized in real-time, showing the path being carved out through the grid.

Maze Solving
The maze is solved using the A* algorithm, which finds the shortest path from the start to the exit. The process is also visualized, showing the exploration and pathfinding steps.

Contributing
Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.

License
This project is licensed under the MIT License. See the LICENSE file for details.

Project Updates
Real-time Visualization: Implemented real-time updates for maze generation and solving processes.
User Interaction: Added keyboard controls for navigating the maze.
Enhanced Pathfinding: Improved the A* algorithm for better performance and visualization.
Contact
For any questions or feedback, please contact Ori2846.

Enjoy navigating the maze with MazeRunner! 🚀
