#include "EasyBMP.h"
#include <sstream>
#include <cstdlib>

const int WIDTH = 256;
const int HEIGHT = 256;
const int CHECKER_WIDTH = 32;
const int CHECKER_HEIGHT = 32;

struct Point {
    int x;
    int y;
};

Point parsePoint(char* pointString)
    // Parse pointString into Point struct
{
    std::stringstream ss(pointString);
    char c;
    Point p;
    ss >> p.x >> c >> p.y;
    return p;
}

void createCheckerBoard()
    // Create a WIDTH x HEIGHT bitmap image of a checker board
{
    BMP myImage;

    myImage.SetSize(WIDTH, HEIGHT);

    RGBApixel blackColor;
    blackColor.Red = blackColor.Blue = blackColor.Green = blackColor.Alpha = 0;

    RGBApixel redColor;
    redColor.Red = 255;
    redColor.Green = redColor.Blue = redColor.Alpha = 0;

    myImage.SetBitDepth(1);
    myImage.SetColor(1, redColor);

    for (int i = 0; i < WIDTH; ++i)
        for (int j = 0; j < HEIGHT; ++j) {
            int posX = i/CHECKER_WIDTH;
            int posY = j/CHECKER_HEIGHT;
            if ( (posX + posY) % 2 == 1)
                myImage.SetPixel(i,j,blackColor);
        }

    myImage.WriteToFile("board.bmp");
}

void createSierpinskiTriangle(Point x, Point y, Point z, Point p)
    // Create a WIDTH x HEIGHT bitmap of a sierpinski triangle
{
    BMP myImage;

    myImage.SetSize(WIDTH, HEIGHT);

    RGBApixel redColor;
    redColor.Red = 255;
    redColor.Green = redColor.Blue = redColor.Alpha = 0;

    myImage.SetBitDepth(1);
    myImage.SetColor(0, redColor);

    Point vertices[] = { x, y, z};

    srand(int(time(0)));
    Point curPoint = p;
    int r = rand() % 3;
    
    for (int i = 0; i < 10001; ++i) {
        myImage.SetPixel(curPoint.x, curPoint.y, redColor);
        curPoint.x = (curPoint.x + vertices[r].x) / 2;
        curPoint.y = (curPoint.y + vertices[r].y) / 2;
        r = rand() % 3;
    }

    myImage.WriteToFile("sierpinski.bmp");
}

int main(int argc, char* argv[])
{
    if (argc == 5) {
        createCheckerBoard();
        createSierpinskiTriangle(parsePoint(argv[1]), parsePoint(argv[2]),
                parsePoint(argv[3]), parsePoint(argv[4]));
    }
    else 
        std::cout << "Sample Usage: ./lab1.out 128,5 5,251 251,251 171,34\n";
}

