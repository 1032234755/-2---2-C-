#include <iostream>
#include <cmath>

// Структура для представления точки в пространстве
struct Point3D {
    double x;
    double y;
    double z;
};

// Функция для вычисления расстояния от точки до плоскости
double distancePointToPlane(double A, double B, double C, double D, Point3D p) {
    return std::abs(A * p.x + B * p.y + C * p.z + D) / std::sqrt(A * A + B * B + C * C);
}

// Функция для нахождения точки пересечения двух плоскостей
bool intersectionLineOfPlanes(double A1, double B1, double C1, double D1, double A2, double B2, double C2, double D2, Point3D& point, Point3D& direction) {
    double denom = A1 * B2 - A2 * B1;
    if (denom == 0) {
        return false; // Плоскости параллельны или совпадают
    }

    point.x = 0;
    point.y = (C2 * D1 - C1 * D2) / denom;
    point.z = (B1 * D2 - B2 * D1) / denom;

    direction.x = B1 * C2 - B2 * C1;
    direction.y = A2 * C1 - A1 * C2;
    direction.z = A1 * B2 - A2 * B1;

    return true;
}

// Функция для нахождения угла между двумя плоскостями
double angleBetweenPlanes(double A1, double B1, double C1, double A2, double B2, double C2) {
    double dotProduct = A1 * A2 + B1 * B2 + C1 * C2;
    double magnitude1 = std::sqrt(A1 * A1 + B1 * B1 + C1 * C1);
    double magnitude2 = std::sqrt(A2 * A2 + B2 * B2 + C2 * C2);
    double cosTheta = dotProduct / (magnitude1 * magnitude2);
    double angleRad = std::acos(std::clamp(cosTheta, -1.0, 1.0));
    double angleDeg = angleRad * 180.0 / M_PI;
    return angleDeg;
}

int main() {
    double A1 = 1, B1 = -2, C1 = 1, D1 = 3;
    double A2 = 2, B2 = 1, C2 = -1, D2 = -4;

    Point3D p = { 3, 2, 1 };

    double distance1 = distancePointToPlane(A1, B1, C1, D1, p);
    std::cout << "Расстояние от точки до первой плоскости = " << distance1 << std::endl;

    double distance2 = distancePointToPlane(A2, B2, C2, D2, p);
    std::cout << "Расстояние от точки до второй плоскости = " << distance2 << std::endl;

    Point3D intersectionPoint, direction;
    if (intersectionLineOfPlanes(A1, B1, C1, D1, A2, B2, C2, D2, intersectionPoint, direction)) {
        std::cout << "Прямая пересечения плоскостей: точка (" << intersectionPoint.x << ", " << intersectionPoint.y << ", " << intersectionPoint.z << ") направление (" << direction.x << ", " << direction.y << ", " << direction.z << ")" << std::endl;
    }
    else {
        std::cout << "Плоскости параллельны или совпадают." << std::endl;
    }

    double angle = angleBetweenPlanes(A1, B1, C1, A2, B2, C2);
    std::cout << "Угол между плоскостями = " << angle << " градусов" << std::endl;

    return 0;
}
