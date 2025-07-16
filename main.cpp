#include <iostream>
#include <queue>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 10;

// Лабиринт 
char maze[HEIGHT][WIDTH + 1] = {
    "####################",
    "#.................F#",
    "#.######.######.##.#",
    "#........#......#..#",
    "#.######.#.####.#.##",
    "#.#....#.#....#.#..#",
    "#.#.##.#.####.#.##.#",
    "#...##...####...##.#",
    "######.###########.#",
    "####################"
};

int dx[] = { 0, 1, 0, -1 };
int dy[] = { -1, 0, 1, 0 };

struct Point {
    int x, y;
};

bool isValid(int x, int y) {
    return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && maze[y][x] == '.';
}

void printMaze() {
    for (int i = 0; i < HEIGHT; i++) {
        cout << maze[i] << endl;
    }
}

bool waveAlgorithm(Point start, Point end) {
    vector<vector<int>> dist(HEIGHT, vector<int>(WIDTH, -1));
    queue<Point> q;
    q.push(start);
    dist[start.y][start.x] = 0;

    while (!q.empty()) {
        Point p = q.front(); q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            if (isValid(nx, ny) && dist[ny][nx] == -1) {
                dist[ny][nx] = dist[p.y][p.x] + 1;
                q.push({ nx, ny });
            }
        }
    }

    if (dist[end.y][end.x] == -1) {
        return false;
    }

    Point p = end;
    while (!(p.x == start.x && p.y == start.y)) {
        maze[p.y][p.x] = '*';
        for (int i = 0; i < 4; ++i) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            if (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT &&
                dist[ny][nx] == dist[p.y][p.x] - 1) {
                p = { nx, ny };
                break;
            }
        }
    }

    maze[start.y][start.x] = 'S';
    maze[end.y][end.x] = 'F';
    return true;
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    srand(time(0));

    Point start, end;

    
    vector<Point> emptyCells;
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (maze[y][x] == '.') {
                emptyCells.push_back({ x, y });
            }
        }
    }

    if (emptyCells.size() < 2) {
        cout << "Недостаточно пустых клеток для старта и финиша.\n";
        return 1;
    }

    
    start = emptyCells[rand() % emptyCells.size()];
    do {
        end = emptyCells[rand() % emptyCells.size()];
    } while (start.x == end.x && start.y == end.y);

 
    maze[start.y][start.x] = 'S';
    maze[end.y][end.x] = 'F';

    cout << "Лабиринт:\n";
    printMaze();

    cout << "\nСлучайные координаты:\n";
    cout << "Старт (x y): " << start.x << " " << start.y << endl;
    cout << "Финиш (x y): " << end.x << " " << end.y << endl;

    if (!isValid(start.x, start.y) || !isValid(end.x, end.y)) {
        cout << "\nОшибка: координаты должны указывать на пустую клетку ('.').\n";
        cout << "Начало = '" << maze[start.y][start.x] << "', конец = '" << maze[end.y][end.x] << "'\n";
        return 1;
    }

    if (waveAlgorithm(start, end)) {
        cout << "\nПуть найден:\n";
        printMaze();
    }
    else {
        cout << "\nПуть не найден.\n";
    }

    return 0;
}
