/*
    Source of learning:
    https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
*/

#include <iostream>
#include <istream>
#include <ostream>
using namespace std;

struct Point{
    double x,y;
};

ostream& operator<<(ostream& out, const Point& p)
{
    out << "(" << p.x<<", "<<p.y<<") ";
    return out;
}

istream& operator >>(istream & in, Point& p)
{
    in >> p.x;
    in >> p.y;
    return in;
}


/*
    Return the orientation of three points
    0 -> Collinear
    1 -> CW
    2 -> CCW
*/
int GetOriention(Point a, Point b, Point c)
{
    double dy1 = b.y-a.y;
    double dx1 = b.x-a.x;
    double dy2 = c.y-b.y;
    double dx2 = c.x-b.x;
    
    // if you computes m1,m2 individually you have to handle dx=0
    double v = dy1*dx2 - dy2 *dx1;
    
    if(v==0) return 0;
    else return (v>0)?1:2;
}


/*
    Assuming point p is on line p1q1, this method check if p lies within the segment or not.
    false -> p doesn't lie on segment p1q1
    true -> p lies on segment p1q1
*/
bool OnSegment(Point p1, Point q1, Point p)
{
    if ( min(p1.x, q1.x) <= p.x && max(p1.x,q1.x) >= p.x
        &&
        min(p1.y, q1.y) <= p.y && max(p1.y,q1.y) >= p.y)
        return true;
    return false;
}

/*
    Check of two segments p1q1 and p2q2 interesect at somepoint
*/
bool Intersect(Point p1, Point q1, Point p2, Point q2)
{
    int o1 = GetOriention(p1,q1,p2);
    int o2 = GetOriention(p1,q1,q2);
    int o3 = GetOriention(p2,q2,p1);
    int o4 = GetOriention(p2,q2,q1);
    
    if (o1!=o2 && o3!=o4)				return true;
	
    if (o1==0 && OnSegment(p1,q1,p2))	return true;
    if (o2==0 && OnSegment(p1,q1,q2))	return true;
    if (o3==0 && OnSegment(p2,q2,p1))	return true;
    if (o4==0 && OnSegment(p2,q2,q1))	return true;

	return false;
}


int main() {
    int tc = 0;
    cin >> tc;
    while(tc--)
    {
        Point p1,q1, p2,q2;
        cin >> p1 >> q1 >> p2 >> q2;
        int res = Intersect(p1,q1,p2,q2)==false?0:1;
        cout << res << endl ;
    }
	return 0;
}
