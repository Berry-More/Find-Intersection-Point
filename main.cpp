#include <string>
#include <sstream>
#include <optional>
#include <iostream>

using namespace std;

class Vector3D
{   
public:
    double X, Y, Z;

    Vector3D()
    {
        X = 0;
        Y = 0;
        Z = 0;
    }

    Vector3D(double aX, double aY, double aZ)
    {
        X = aX;
        Y = aY;
        Z = aZ;
    }

    string toString() {
        ostringstream vectorInfo;
        vectorInfo << "[" << X << ", " << Y << ", " << Z << "]";
        return vectorInfo.str();
    }
};


class Segment3D
{
public:
    Vector3D start;
    Vector3D end;

    Segment3D(Vector3D v1, Vector3D v2)
    {
        start = v1;
        end = v2;
    }
};

optional<Vector3D> Intersect(const Segment3D o1, const Segment3D o2) 
{
    Vector3D vectorOut;
    double v, u, testValue;

    // определяю лежат ли отрезки на одной плоскости

    testValue = (o1.end.X - o1.start.X) * ((o2.start.Y - o1.start.Y) * (o2.end.Z - o1.end.Z) - (o2.end.Z - o1.end.Z) * (o2.start.Y - o1.start.Y)) 
        - (o1.end.Y - o1.start.Y) * ((o2.start.X - o1.start.X) * (o2.end.Z - o1.start.Z) - (o2.start.Z - o1.start.Z) * (o2.end.X - o1.start.X))
        + (o1.end.Z - o1.start.Z) * ((o2.start.X - o1.start.X) * (o2.end.Y - o1.start.Y) - (o2.start.Y - o1.start.Y) * (o2.end.X - o1.start.X));

    // определяю есть ли точки пересечения по уравнению прямой
    // если есть, то смотрю попадают ли точки на отрезок
    // если попадают, нахожу точку пересечения
    if (testValue == 0) {
        u = ((o2.end.X - o1.end.X) * (o2.end.Y - o2.end.Y) - (o2.end.X - o2.start.X) * (o2.end.Y - o1.end.Y)) /
            ((o1.start.X - o1.end.X) * (o2.end.Y - o2.start.Y) - (o2.end.X - o2.start.X) * (o1.start.Y - o1.end.Y));

        v = ((o1.start.X - o1.end.X) * (o2.end.Y - o1.end.Y) - (o2.end.X - o1.end.X) * (o1.start.Y - o1.end.Y)) /
            ((o1.start.X - o1.end.X) * (o2.end.Y - o2.end.Y) - (o2.end.X - o2.start.X) * (o1.start.Y - o1.end.Y));

        if (v <= 1 && v >= 0 && u <= 1 && u >= 0) {
            vectorOut = Vector3D(
                u * (o1.start.X - o1.end.X) + o1.end.X,
                u * (o1.start.Y - o1.end.Y) + o1.end.Y,
                u * (o1.start.Z - o1.end.Z) + o1.end.Z
            );
        }
        else {
            return nullopt;
        }
    }
    else {
        return nullopt;
    }

    return vectorOut;
}


int main()
{
    Vector3D v1(2, 5, 0); // 2, 5, 0
    Vector3D v2(2, 0, 0); // 2, 0, 0
    Vector3D v3(0, 3, 0); // 0, 3, 0
    Vector3D v4(5, 3, 0); // 5, 3, 0

    Segment3D s1(v1, v2);
    Segment3D s2(v3, v4);

    optional<Vector3D> getOpt = Intersect(s1, s2);

    try {
        Vector3D findPoint = getOpt.value();
        cout << findPoint.toString();
    }
    catch(const bad_optional_access& e) {
        cout << e.what() << "\n";
    }
}

