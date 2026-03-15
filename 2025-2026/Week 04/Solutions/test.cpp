#include <iostream>
#include <fstream>

//зад. 1
size_t fileLen(std::istream& in) {
    size_t result;
    size_t pos = in.tellg();
    in.seekg(0, std::ios::end);
    result = in.tellg();
    in.seekg(pos, std::ios::beg);
    return result;
}

//зад. 2
/*
std::ios::in - потокът ще се отвори за четене
std::ios::out - потокът ще се отвори за писане
std::ios::trunc - изтрива вече съществуващата информация от файла
std::ios::app - слага указателя за писане в края на файла и запазва вече съществуващата информация
std::ios::binary - потокът ще се използва за четене/писане в двоичен файл

двоични файлове - по-оптимално използват паметта, не са четими за хора
текстови файлове - не са оптимални от към памет, лесно четими за хора
*/

//зад. 3
struct Point {
    double x;
    double y;
};

void savePoint(const Point& p) {
    std::ofstream out("points.bin", std::ios::in | std::ios::binary | std::ios::app);
    out.write((char*)&p, sizeof(p));
    out.close();
}

size_t pointsCount() {
    std::ifstream in("points.bin", std::ios::out | std::ios::binary);
    size_t result = fileLen(in)/sizeof(Point);
    in.close();
    return result;
}

void swapWithSymmetric() {
    size_t size = pointsCount();
    Point* points = new Point[size];
	
	std::ifstream in("points.bin", std::ios::in | std::ios::binary);
    in.read((char*)points, size * sizeof(Point));
    in.close();
    
    for (int i = 0; i < size; i++) {
        std::swap(points[i].x, points[i].y);
    }

    std::ofstream out("points.bin", std::ios::out | std::ios::binary);
    out.write((char*)points, size * sizeof(Point));
    out.close();
	
    delete[] points;
}

