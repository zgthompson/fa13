#include "EasyBMP.h"
#include <vector>
#include <queue>
#include <climits>
#include <iostream>
#include <cstdlib>

template<class T>
class Queue : public std::queue<T> {
    public:
        T pop() {
            T tmp = std::queue<T>::front();
            std::queue<T>::pop();
            return tmp;
        }
};


class Point {
    public:
        int x;
        int y;

        Point(int inx, int iny) { 
            x = inx;
            y = iny;
        }

        Point() {
            x = 0;
            y = 0;
        }

        Point* getNeighbors() {
            Point* neighbors = new Point[4];

            neighbors[0] = Point(x-1, y);
            neighbors[1] = Point(x+1, y);
            neighbors[2] = Point(x,y-1);
            neighbors[3] = Point(x,y+1);

            return neighbors;
        }
};


void toBlackAndWhite(BMP &image) {

    int total, newColor;

    for (int j = 0; j < image.TellHeight(); ++j) {
        for (int i = 0; i < image.TellWidth(); ++i) {

            // total is the sum of the three color components of a pixel
            total = image(i,j)->Red + image(i,j)->Green + image(i,j)->Blue;

            // if sum is greater than 382 newColor is white, else black
            newColor = total > 382 ? 255 : 0;

            // make the pixel black or white 
            image(i,j)->Red = newColor;
            image(i,j)->Green = newColor;
            image(i,j)->Blue = newColor;
        }
    }
}

bool validCoords(int x, int y, int xmax, int ymax) {
    return x < xmax && y < ymax && x >= 0 && y >=0;
}

bool isBlack(RGBApixel* pixel) {
    return pixel->Blue == 0;
}

void makeRed(RGBApixel* pixel) {
    pixel -> Red = 255;
    pixel -> Blue = 0;
    pixel -> Green = 0;
}

int findPath(BMP& MazeImage, int x1, int y1, int x2, int y2) {

    int width = MazeImage.TellWidth(), height = MazeImage.TellHeight();

    if (!validCoords(x1, y1, width, height) || !validCoords(x2, y2, width, height) ||
            isBlack(MazeImage(x1, y1)) || isBlack(MazeImage(x2,y2))) {
        std::cout << "Invalid coordinates" << std::endl;
        return 0;
    }

    int distance[width * height];
    bool visited[width * height];
    Point parent[width * height];

    for (int i = 0; i < width * height; i++) {
        distance[i] = INT_MAX;
        visited[i] = false;
    }

    Queue<Point> Q;

    //insert starting point
    Q.push( Point(x1,y1) );

    // starting point is visited and is distance 0
    visited[x1 * height + y1] = true;
    distance[x1 * height + y1] = 0;

    Point curPoint;
    Point neighbors[4];
    int curx, cury, neighx, neighy;
    while ( !Q.empty() && !visited[x2 * height + y2] ) {
        curPoint = Q.pop();

        curx = curPoint.x;
        cury = curPoint.y;

        neighbors[0] = Point(curx-1, cury);
        neighbors[1] = Point(curx+1, cury);
        neighbors[2] = Point(curx, cury-1);
        neighbors[3] = Point(curx, cury+1);

        for (int i = 0; i < 4; i++) {
            neighx = neighbors[i].x;
            neighy = neighbors[i].y;

            if (    validCoords(neighx, neighy, width, height) &&
                    !isBlack(MazeImage(neighx, neighy)) &&
                    !visited[neighx * height + neighy]   ) {

                visited[neighx * height + neighy] = true;
                distance[neighx * height + neighy] = distance[curx * height + cury] + 1;
                parent[neighx * height + neighy] = Point(curx, cury);
                Q.push(neighbors[i]);
            }
        }
    }

    if (visited[x2 * height + y2]) {
        Point curPoint = Point(x2, y2);
        int count = 0;
        while (!(curPoint.x == x1 && curPoint.y == y1)) {
            makeRed( MazeImage(curPoint.x, curPoint.y) );
            curPoint = parent[curPoint.x * height + curPoint.y];
        }
        makeRed( MazeImage(x1, y1) );

        return distance[x2 * height + y2];
    }
    else {
        std::cout << "There is no path from x1,y1 to x2,y2" << std::endl;
        return 0;
    }
}

int main(int argc, char* argv[]) {

    if (argc != 5) {
        std::cout << "Usage: ./lab8 x1 y1 x2 y2" << std::endl;
    }
    else {
    
        BMP MazeImage;
        MazeImage.ReadFromFile("maze.bmp");
        toBlackAndWhite(MazeImage);


        int distance = findPath(MazeImage, atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]));

        if (distance > 0) {
          std::cout << "The total distance is " << distance << " pixels." << std::endl;
        }

        MazeImage.WriteToFile("output.bmp");
    }
}
