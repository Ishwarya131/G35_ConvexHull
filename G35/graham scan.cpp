#include <iostream>
#include <stack>
#include <stdlib.h>
#include <vector>

using namespace std;
 
struct Point
{
    int x, y;
};
 
Point p0;

Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

void swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}
 
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}
 
int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;

   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
 
   return (o == 2)? -1: 1;
}

void convexHull(vector<Point> points, int n)
{
	if(n<3)
	{
		cout << "Convex hull not possible with less than 3 points\n";
    	return;
	}
 
   int ymin = points[0].y, min = 0;
   for (int i = 1; i < n; i++)
   {
     int y = points[i].y;

     if ((y < ymin) || (ymin == y &&
         points[i].x < points[min].x))
        ymin = points[i].y, min = i;
   }

   swap(points[0], points[min]);

   p0 = points[0];
   qsort(&points[1], n-1, sizeof(Point), compare);
 

   int m = 1; 
   for (int i=1; i<n; i++)
   {
       while (i < n-1 && orientation(p0, points[i],
                                    points[i+1]) == 0)
          i++;
 
 
       points[m] = points[i];
       m++; 
   }

   if (m < 3)
   {
   		cout << "Convex hull not possible with less than 3 points\n";
   		return ;
   }
 

   stack<Point> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);

   for (int i = 3; i < m; i++)
   {

      while (S.size()>1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }
 
   while (!S.empty())
   {
       Point p = S.top();
       cout << "(" << p.x << ", " << p.y <<")" << " ";
       S.pop();
   }
}
bool checkHull(vector<Point> points, int n, int x, int y)
{
	if(n<3)
	{
		cout << "Convex hull not possible with less than 3 points\n";
    	return false;
	}

   int ymin = points[0].y, min = 0;
   for (int i = 1; i < n; i++)
   {
     int y = points[i].y;
 
     if ((y < ymin) || (ymin == y &&
         points[i].x < points[min].x))
        ymin = points[i].y, min = i;
   }

   swap(points[0], points[min]);

   p0 = points[0];
   qsort(&points[1], n-1, sizeof(Point), compare);

   int m = 1;
   for (int i=1; i<n; i++)
   {
       while (i < n-1 && orientation(p0, points[i],
                                    points[i+1]) == 0)
          i++;
 
 
       points[m] = points[i];
       m++; 
   }

   if (m < 3)
   {
   		cout << "Convex hull not possible with less than 3 points\n";
   		return false;
   } 

   stack<Point> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);

   for (int i = 3; i < m; i++)
   {
      while (S.size()>1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }
 
   while (!S.empty())
   {
       Point p = S.top();
       if(p.x == x && p.y == y) return true;
       S.pop();
   }
   return false;
}

int main()
{
	vector<Point> points;
	int k=1, i, x, y, n;
	bool check;
    cout<<"Enter no. of points initially: ";
    cin>>n;
    cout<<endl<<"Enter points: ";
    for(i=0; i<n; i++)
    {
    	cin>>x>>y;
    	points.push_back({ x, y });
	}
	cout<<"\nYour points initially:\n";

	convexHull(points, n);
	
	cout<<"\nOption Given: ";
  	cout<<"\n1. Point insertion";
  	cout<<"\n2. Point deletion";
  	cout<<"\n3. Checking a point";
	cout<<"\n0. EXIT";
	
  	while(k!=0)
  	{
  		cout<<"\n\nChoose option: ";
  		cin>>k;
  		switch(k)
		{
			case 0: exit(0);
			
			case 1: cout<<"POINT INSERTION: ";
				cout<<"\nEnter point to be inserted: ";
				cin>>x>>y;
				points.push_back({ x, y });
				n++;
				cout<<"Convex Hull\n";
				convexHull(points, n);
				break;
				
			case 2: cout<<"POINT DELETION: ";
				cout<<"\nEnter point to be deleted: ";
				cin>>x>>y;
				check = false;
				for(i=0; i<points.size(); i++)
					if(points[i].x == x && points[i].y == y)
					{
						points.erase(points.begin() + i);
						check = true;
						n--;
					}
				if(!check) cout<<"Point not available";
			 
			    cout<<"Convex Hull\n";
			    convexHull(points, n);
				break;
				
			case 3: cout<<"POINT CHECKING: ";
	        	cout<<"\nEnter point to be checked: ";
				cin>>x>>y;
				check = false;
				for(i=0; i<points.size(); i++)
					if(points[i].x == x && points[i].y == y)
						check = true;
				if(!check) cout<<"Point is not available";
				else
				{
					bool hull = checkHull(points, n, x, y);
					if(hull) cout<<"Point is on the Convex Hull";
					else cout<<"Point is inside the Convex Hull";
				}
				break;		
		}
	}
	return 0;
}
