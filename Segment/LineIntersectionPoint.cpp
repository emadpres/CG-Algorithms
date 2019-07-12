/*
    Source of learning:
    https://www.geeksforgeeks.org/program-for-point-of-intersection-of-two-lines/
*/

#include <iostream>
#include <ostream>
using namespace std;

/*
    Represent a point
*/
struct Point{
    static const int INVALID = 99999;
    
    double m_x, m_y;
    Point (double x, double y):m_x(x), m_y(y){}
};

ostream& operator<<(ostream& out, const Point& p)
{
    out <<"("<<p.m_x<<", "<<p.m_y<<") ";
    return out;
}


/*
    Represent a line with ax+by=c equation
*/
class Line{
public:
    double m_a, m_b, m_c;
    Line(Point p, Point q)
    {
        m_a = q.m_y - p.m_y; //  dy
        m_b = p.m_x - q.m_x; // -dx
        m_c = m_a * p.m_x + m_b * p.m_y;
    }
    
    Point Intersect(const Line &other)
    {
        // We don't calculate m1,m2 indivually. Otherwise we should handle dx=0 case
        double det = this->m_a * other.m_b - other.m_a * this->m_b;
        
        // Lines are parallel
        if (det == 0)
            return Point(Point::INVALID, Point::INVALID);
        
        double x = (this->m_c * other.m_b - other.m_c * this->m_b) / det ;
        double y = (other.m_c * this->m_a - this->m_c * other.m_a) / det ;
        return Point(x,y);
    }
};

ostream& operator<<(ostream& out, const Line& l)
{
    out <<l.m_a<<" x + "<<l.m_b<<" y = "<<l.m_c<<" ";
    return out;
}

int main() 
{ 
    Point A = Point(1, 1); 
    Point B = Point(4, 4); 
    Point C = Point(1, 8); 
    Point D = Point(2, 4); 
  
    Line l1 = Line(A,B);
    Line l2 = Line(C,D);
    cout << "L1: "<<l1 << endl;
    cout << "L2: "<<l2 << endl;
    
    Point intersection = l1.Intersect(l2);
  
    if (intersection.m_x==Point::INVALID && intersection.m_y==Point::INVALID) 
        cout << "The given lines AB and CD are parallel.\n";
    else
        cout << "Interesect at " << intersection;
  
    return 0; 
} 
