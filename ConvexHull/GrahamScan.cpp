/*
    Source of learning:
    https://www.geeksforgeeks.org/convex-hull-set-2-graham-scan/
    --------------------------
    Complexity:  O( n*lg(n) )
 */

#include <iostream>
#include <istream>
#include <vector>
#include <algorithm>
#include <set>
#include <fstream>
using namespace std;


struct Point {
    double m_x, m_y;
    Point(double x, double y):m_x(x), m_y(y){}
    Point()=default;

    bool operator<(const Point &rh) const
    {
        return (this->m_x<rh.m_x) || (this->m_x==rh.m_x && this->m_y<rh.m_y);
    }
};

istream& operator>>(istream& in, Point &p)
{
    in >> p.m_x >> p.m_y;
    return in;
}

ostream& operator<<(ostream &out, const Point &p)
{
    //out << "("<<p.m_x<<", "<<p.m_y<<") ";
    out <<p.m_x<<" "<<p.m_y;
    return out;
}



/*
    Find the point with lowest y (and among the same y, the left-most one)
 */
int FindLowestPoint(vector<Point> &p)
{
    int lowest_index = 0;
    Point lowest_value = p[0];
    for(int i=1; i<p.size();++i)
        if(p[i]<lowest_value)
        {
            lowest_value = p[i];
            lowest_index = i;
        }

    return lowest_index;
}


void Swap(Point &a, Point &b)
{
    Point t = a;
    a = b;
    b = t;
}



double dis_square(Point p, Point q)
{
    return (q.m_x-p.m_x)*(q.m_x-p.m_x) + (q.m_y-p.m_y)*(q.m_y-p.m_y);
}



/*
    Return the orientation of three points
    0 -> Collinear
    1 -> CW
    2 -> CCW
*/
int GetOriention(Point a, Point b, Point c)
{
    double dy1 = b.m_y-a.m_y;
    double dx1 = b.m_x-a.m_x;
    double dy2 = c.m_y-b.m_y;
    double dx2 = c.m_x-b.m_x;

    // if you computes m1,m2 individually you have to handle dx=0
    double v = dy1*dx2 - dy2*dx1;

    if(v==0) return 0;
    else return (v>0)?1:2;
}


/*
    To sort points by polar angle in counterclockwise order around origin.
    If the polar angle of two points is the same, then put the nearest point first.
 */
bool comparePolarAngle(Point origin, Point p, Point q)
{
    int o = GetOriention(origin, p, q);

    if(o==0)
        return dis_square(origin, p) < dis_square(origin, q);
    else
        return (o==1)?false:true;
}


vector<Point> ComputeConvexHull(vector<Point> &p)
{
    vector<Point> ch;

    // Find the lowest point and put it first
    int lowest_index = FindLowestPoint(p);
    Swap(p[lowest_index], p[0]);

    // Sort the rest
    sort(p.begin()+1, p.end(), [=](Point a, Point b){return comparePolarAngle(p[0], a, b);});


    // Initialize
    ch.emplace_back(p[0]);
    ch.emplace_back(p[1]);

    // k refers to the next point which will go under test
    for(int k=2; k<p.size(); k++)
    {
        // We're testing ch's top item: ch[ch.size()-1]
        // For that, we consider the orientation of:
        //  1. The point before it (ch[ch.size()-2])
        //  2. Itself
        //  3. The point after it (p[k])
        while( ch.size()>1 && GetOriention(ch[ch.size()-2], ch[ch.size()-1], p[k]) != 2 )
            ch.pop_back();

        ch.push_back(p[k]);
    }


    return ch;
}


void RemoveDuplicates(vector<Point> &p)
{
    set<Point> s(p.begin(), p.end());
    p.assign(s.begin(), s.end());
}

int main() {
    //freopen("/Users/emadpres/coding/cppLearning/input.txt","r", stdin);
    int tc;
    cin >> tc;
    while(tc--)
    {
        int n;
        cin >> n;

        vector<Point> points;
        Point t;
        for(int i=0;i<n;++i) {
            cin >> t;
            points.emplace_back(t);
        }

        RemoveDuplicates(points);

        if(points.size()<3)
        {
            cout <<"-1\n";
            continue;
        }

        vector<Point> convexhull = ComputeConvexHull(points);

        sort(convexhull.begin(), convexhull.end(),[](Point a, Point b){return a<b;});
        for(int i=0; i<convexhull.size(); ++i)
        {
            if(i>0)
                cout <<", ";
            cout << convexhull[i];
        }
        cout << endl;
    }
    return 0;
}
