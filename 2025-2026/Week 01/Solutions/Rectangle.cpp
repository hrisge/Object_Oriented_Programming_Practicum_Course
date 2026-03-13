#include <iostream>

struct Point {
	double x;
	double y;
};

union Rectangle {
	struct {
		Point bl;
		Point tr;
	};
	struct {
		double left;
		double bottom;
		double right;
		double top;
	};
};

double perimeter(const Rectangle& rect) {
	return 2 * (rect.top - rect.bottom) + 2 * (rect.right - rect.left);
}

double area(const Rectangle& rect) {
	return (rect.top - rect.bottom) * (rect.right - rect.left);
}

bool containsPoint(const Point& p, const Rectangle& rect) {
	return p.x <= rect.right && p.x >= rect.left && p.y <= rect.top && p.y >= rect.bottom;
}

bool containsRectangle(const Rectangle& rect1, const Rectangle& rect2) {
	return containsPoint(rect1.tr, rect2) && containsPoint(rect1.bl, rect2);
}

bool isOutside(const Rectangle& rect1, const Rectangle& rect2) {
	return rect1.bottom > rect2.top || rect1.left > rect2.right || rect1.right < rect2.left || rect1.top < rect2.bottom;
}

enum RectangleRelation {
	INSIDE,
	OUTSIDE,
	PARTIAL
};

RectangleRelation rectangleIntersection(const Rectangle& rect1, const Rectangle& rect2) {
	if (containsRectangle(rect1, rect2)) {
		return INSIDE;
	}
	else if (isOutside(rect1,rect2)) {
		return OUTSIDE;
	}
	else {
		return PARTIAL;
	}
}

