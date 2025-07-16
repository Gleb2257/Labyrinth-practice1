#include <iostream>
#include <fstream>
#include "maze.h" 
using namespace std;

void exportToPPM(const string& filename) {
    ofstream fout(filename);
    fout << "P3\n";
    fout << WIDTH << " " << HEIGHT << "\n";
    fout << "255\n";

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int r, g, b;
            switch (maze[y][x]) {
                case '#': r = g = b = 0; break;           // стена - черный
                case '.': r = g = b = 255; break;         // пусто - белый
                case 'S': r = 0; g = 255; b = 0; break;   // старт - зеленый
                case 'F': r = 255; g = 0; b = 0; break;   // финиш - красный
                case '*': r = 0; g = 0; b = 255; break;   // путь - синий
                default: r = g = b = 128; break;
            }
            fout << r << " " << g << " " << b << " ";
        }
        fout << "\n";
    }

    fout.close();
    cout << "Maze exported to " << filename << endl;
}

int main() {
    exportToPPM("maze.ppm");
    return 0;
}
