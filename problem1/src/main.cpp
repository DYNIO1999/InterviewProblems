#include <iostream>
#include <array>
#include <limits>

/**
 * Used Separating Axis Theorem (SAT) to solve this problem.
 *
 */
struct Vec2
{
    float x, y;
};

struct Triangle
{
    std::array<Vec2,3>points;
};

Vec2 calculateNormal(const Vec2 &pointA, const Vec2 &pointB)
{
    Vec2 normal{0, 0};
    float dx = pointB.x - pointA.x;
    float dy = pointB.y - pointA.y;
    normal.x = -dy;
    normal.y = dx;
    return normal;
}
float dotProduct(const Vec2 &a, const Vec2 &b)
{
    return a.x * b.x + a.y * b.y;
}

bool isColliding(const Triangle &triangle1, const Triangle &triangle2){


    for(int i=0;i<triangle1.points.size();i++){
        Vec2 va = triangle1.points[i];
        Vec2 vb = triangle1.points[(i+1)% triangle1.points.size()];
        Vec2 normal2d = calculateNormal(va,vb);   


        float minA= std::numeric_limits<float>::max();
        float maxA =std::numeric_limits<float>::min();

        float minB = std::numeric_limits<float>::max();
        float maxB = std::numeric_limits<float>::min();

        for(int j=0;j<triangle1.points.size();j++){
            auto v  = triangle1.points[j];
            float projection = dotProduct(v, normal2d);

            if(projection <minA){
                minA =projection;
            }
            if(projection> maxA){
                maxA = projection;
            }
        }

        for (int j = 0; j < triangle2.points.size(); j++)
        {
            auto v = triangle2.points[j];
            float projection = dotProduct(v, normal2d);

            if (projection < minB)
            {
                minB = projection;
            }
            if (projection > maxB)
            {
                maxB = projection;
            }
        }

        if(minA>=maxB ||  minB >= maxA){
            return false;
        }

    }

    for (int i = 0; i < triangle2.points.size(); i++)
    {
        Vec2 va = triangle2.points[i];
        Vec2 vb = triangle2.points[(i + 1) % triangle2.points.size()];
        Vec2 normal2d = calculateNormal(va, vb);

        float minA = std::numeric_limits<float>::max();
        float maxA = std::numeric_limits<float>::min();

        float minB = std::numeric_limits<float>::max();
        float maxB = std::numeric_limits<float>::min();

        for (int j = 0; j < triangle1.points.size(); j++)
        {
            auto v = triangle1.points[j];
            float projection = dotProduct(v, normal2d);

            if (projection < minA)
            {
                minA = projection;
            }
            if (projection > maxA)
            {
                maxA = projection;
            }
        }

        for (int j = 0; j < triangle2.points.size(); j++)
        {
            auto v = triangle2.points[j];
            float projection = dotProduct(v, normal2d);

            if (projection < minB)
            {
                minB = projection;
            }
            if (projection > maxB)
            {
                maxB = projection;
            }
        }

        if (minA >= maxB || minB >= maxA)
        {
            return false;
        }
    }

    return true;
}
int main(int argc, char const *argv[])
{

    Triangle triangleA{Vec2{1.0f,1.0f},Vec2{1.0f,4.0f}, Vec2{4.0f,1.0f}};
    Triangle trinagleB{Vec2{2.0f,2.0f},Vec2{2.0f,5.0f}, Vec2{6.0f,5.0f}};

    bool checkFirst = isColliding(triangleA, trinagleB);
    std::cout << "FIRST CHECK OF TRIANGLES:  \n"<<(checkFirst? "TRUE is Collding" :"FALSE isn't Collding" ) << "\n\n";

    Triangle triangleC{Vec2{1.0f, 1.0f}, Vec2{1.0f, 4.0f}, Vec2{4.0f, 1.0f}};
    Triangle trinagleD{Vec2{10.0f, 2.0f}, Vec2{10.0f, 5.0f}, Vec2{15.0f, 5.0f}};

    bool checkSecond = isColliding(triangleC, trinagleD);
    std::cout <<"SECOND CHECK OF TRIANGLES:   \n" <<  (checkSecond? "TRUE is Collding" :"FALSE isn't Collding" )<< "\n\n";

    return 0;
}
