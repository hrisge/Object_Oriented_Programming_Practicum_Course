#include <iostream>

union vec3 {
	//важно е x,y и z да са в структура, тъй като иначе ще заемат едно и също място в паметта, а това не го искаме в този случай
	struct {
		double x;
		double y;
		double z;
	};
	double pos[3];
};

void print(const vec3& v) {
	std::cout << v.x << " " << v.y << " " << v.z << std::endl;
}

vec3 sum(const vec3& v1, const vec3& v2) {
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}

vec3 sub(const vec3& v1, const vec3& v2) {
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}

double dot(const vec3& v1, const vec3& v2) {
	double result = 0;
	for (int i = 0; i < 3; i++) {
		result += v1.pos[i] * v2.pos[i];
	}
	return result;
}

