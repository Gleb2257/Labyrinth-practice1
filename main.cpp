#include <iostream>
#include <queue>
#include <vector>
#include <windows.h>

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

    Point start, end;

    cout << "Лабиринт:\n";
    printMaze();

    cout << "\nВведите координаты начала (x y): ";
    cin >> start.x >> start.y;
    cout << "Введите координаты выхода (x y): ";
    cin >> end.x >> end.y;

    // Проверка корректности координат
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
