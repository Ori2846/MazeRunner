#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <cmath>
#include <thread>
#include <chrono>

using namespace std;

const int WIDTH = 120; 
const int HEIGHT = 70; 
const int TILE_SIZE = 20;

vector<vector<char>> maze(HEIGHT, vector<char>(WIDTH, '#'));
vector<vector<char>> displayMaze(HEIGHT, vector<char>(WIDTH, '#'));

struct Cell {
    int x, y;
    Cell(int x, int y) : x(x), y(y) {}
};

struct Node {
    int x, y, g, h, f;
    Node* parent;
    Node(int x, int y, int g, int h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), f(g + h), parent(parent) {}
};

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->f > b->f;
    }
};

void initializeMaze() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            maze[y][x] = '#';
        }
    }
}

void drawMaze(sf::RenderWindow& window, vector<vector<char>>& displayMaze, int playerX, int playerY) {
    window.clear();

    sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            switch (displayMaze[y][x]) {
            case '#':
                tile.setFillColor(sf::Color::Black);
                break;
            case ' ':
                tile.setFillColor(sf::Color::White);
                break;
            case '*':
                tile.setFillColor(sf::Color::Green);
                break;
            case 'E':
                tile.setFillColor(sf::Color::Red);
                break;
            default:
                int colorCode = displayMaze[y][x] - '0';
                tile.setFillColor(sf::Color(30 * colorCode, 30 * (9 - colorCode), 30 * colorCode));
                break;
            }

            tile.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            window.draw(tile);
        }
    }
    tile.setFillColor(sf::Color::Blue);
    tile.setPosition(playerX * TILE_SIZE, playerY * TILE_SIZE);
    window.draw(tile);

    window.display();
}

void generateMaze(sf::RenderWindow& window, int startX, int startY) {
    stack<Cell> stack;
    stack.push(Cell(startX, startY));
    maze[startY][startX] = ' ';
    displayMaze = maze;

    srand(time(0));
    random_device rd;
    mt19937 g(rd());

    int dx[] = { 0, 0, -2, 2 };
    int dy[] = { -2, 2, 0, 0 };

    while (!stack.empty()) {
        Cell current = stack.top();
        stack.pop();

        vector<int> directions = { 0, 1, 2, 3 };
        shuffle(directions.begin(), directions.end(), g);

        for (int i = 0; i < 4; i++) {
            int nx = current.x + dx[directions[i]];
            int ny = current.y + dy[directions[i]];

            if (nx > 0 && nx < WIDTH - 1 && ny > 0 && ny < HEIGHT - 1 && maze[ny][nx] == '#') {
                maze[ny][nx] = ' ';
                maze[current.y + dy[directions[i]] / 2][current.x + dx[directions[i]] / 2] = ' ';
                stack.push(Cell(nx, ny));

                displayMaze = maze;
                drawMaze(window, displayMaze, -1, -1);
                this_thread::sleep_for(chrono::milliseconds(50));
            }
        }
    }

    int exitX = WIDTH - 2;
    int exitY = HEIGHT - 2;
    maze[exitY][exitX] = 'E'; 

    maze[exitY - 1][exitX] = ' ';
    maze[exitY][exitX - 1] = ' ';
    displayMaze = maze;
    drawMaze(window, displayMaze, -1, -1);
}

vector<Node*> getNeighbors(Node* current, vector<vector<bool>>& closedSet) {
    vector<Node*> neighbors;
    int dx[] = { 0, 0, -1, 1 };
    int dy[] = { -1, 1, 0, 0 };

    for (int i = 0; i < 4; i++) {
        int nx = current->x + dx[i];
        int ny = current->y + dy[i];

        if (nx > 0 && nx < WIDTH && ny > 0 && ny < HEIGHT && maze[ny][nx] != '#' && !closedSet[ny][nx]) {
            neighbors.push_back(new Node(nx, ny, 0, 0, current));
        }
    }
    return neighbors;
}

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

vector<Node*> aStar(sf::RenderWindow& window, int startX, int startY, int endX, int endY, vector<vector<char>>& displayMaze) {
    priority_queue<Node*, vector<Node*>, CompareNode> openSet;
    vector<vector<bool>> closedSet(HEIGHT, vector<bool>(WIDTH, false));
    openSet.push(new Node(startX, startY, 0, heuristic(startX, startY, endX, endY)));

    int iteration = 1;

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        if (current->x == endX && current->y == endY) {
            vector<Node*> path;
            while (current != nullptr) {
                path.push_back(current);
                current = current->parent;
            }
            return path;
        }

        closedSet[current->y][current->x] = true;
        displayMaze[current->y][current->x] = '0' + iteration; 

        vector<Node*> neighbors = getNeighbors(current, closedSet);
        for (Node* neighbor : neighbors) {
            if (closedSet[neighbor->y][neighbor->x]) {
                delete neighbor;
                continue;
            }

            int tentative_g = current->g + 1;

            auto openSetCopy = openSet;
            bool inOpenSet = false;
            while (!openSetCopy.empty()) {
                Node* node = openSetCopy.top();
                openSetCopy.pop();
                if (node->x == neighbor->x && node->y == neighbor->y) {
                    inOpenSet = true;
                    if (tentative_g < node->g) {
                        node->g = tentative_g;
                        node->f = node->g + node->h;
                        node->parent = current;
                    }
                    break;
                }
            }

            if (!inOpenSet) {
                neighbor->g = tentative_g;
                neighbor->h = heuristic(neighbor->x, neighbor->y, endX, endY);
                neighbor->f = neighbor->g + neighbor->h;
                neighbor->parent = current;
                openSet.push(neighbor);
            }
        }

        iteration = (iteration % 9) + 1; 

        drawMaze(window, displayMaze, startX, startY);
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    return vector<Node*>(); 
}

void showPath(vector<Node*>& path, vector<vector<char>>& displayMaze) {
    for (Node* node : path) {
        if (displayMaze[node->y][node->x] != 'P' && displayMaze[node->y][node->x] != 'E') {
            displayMaze[node->y][node->x] = '*';
        }
    }
}

void movePlayer(int& playerX, int& playerY, char direction) {
    int newX = playerX;
    int newY = playerY;
    switch (direction) {
    case 'w':
        newY--;
        break;
    case 's':
        newY++;
        break;
    case 'a':
        newX--;
        break;
    case 'd':
        newX++;
        break;
    }

    if (maze[newY][newX] != '#') {
        playerX = newX;
        playerY = newY;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH * TILE_SIZE, HEIGHT * TILE_SIZE), "Maze Game");

    initializeMaze();
    generateMaze(window, 1, 1);

    int playerX = 1;
    int playerY = 1;
    int exitX = WIDTH - 2;
    int exitY = HEIGHT - 2;

    vector<Node*> path = aStar(window, playerX, playerY, exitX, exitY, displayMaze);

    bool gameRunning = true;

    while (gameRunning) {
        showPath(path, displayMaze);
        drawMaze(window, displayMaze, playerX, playerY);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gameRunning = false;
            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                case sf::Keyboard::W:
                    movePlayer(playerX, playerY, 'w');
                    break;
                case sf::Keyboard::S:
                    movePlayer(playerX, playerY, 's');
                    break;
                case sf::Keyboard::A:
                    movePlayer(playerX, playerY, 'a');
                    break;
                    case sf::Keyboard::D:
                        movePlayer(playerX, playerY, 'd');
                        break;
                }
            }
        }

        if (maze[playerY][playerX] == 'E') {
            drawMaze(window, displayMaze, playerX, playerY);
            cout << "Congratulations! You've reached the end of the maze!" << endl;
            this_thread::sleep_for(chrono::seconds(3));
            gameRunning = false;
        }
    }

    for (Node* node : path) {
        delete node;
    }

    return 0;
}
