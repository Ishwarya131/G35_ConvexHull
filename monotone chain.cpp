#include <bits/stdc++.h>
#define llu long long int
using namespace std;
  
struct Point {
  
    llu x, y;
  
    bool operator<(Point p)
    {
        return x < p.x || (x == p.x && y < p.y);
    }
};

llu cross_product(Point O, Point A, Point B)
{
    return (A.x - O.x) * (B.y - O.y)
           - (A.y - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point> A)
{
    int n = A.size(), k = 0;
  
    if (n <= 3)
   	{
		cout << "Convex hull not possible with less than 3 points\n";
		return A;
	}
  
    vector<Point> ans(2 * n);
  
    sort(A.begin(), A.end());
  
    //lower hull
    for (int i = 0; i < n; ++i) {

        while (k >= 2 && cross_product(ans[k - 2], 
                          ans[k - 1], A[i]) <= 0)
            k--;
        ans[k++] = A[i];
    }
  
    //upper hull
    for (size_t i = n - 1, t = k + 1; i > 0; --i) {

        while (k >= t && cross_product(ans[k - 2],
                           ans[k - 1], A[i - 1]) <= 0)
            k--;
        ans[k++] = A[i - 1];
    }

    ans.resize(k - 1);
  
    return ans;
}

int main()
{
    vector<Point> points;
  	int i, size, x, y, n=1;
    cout<<"Enter no. of points initially: ";
    cin>>size;
	cout<<endl<<"Enter points: ";

    for(i=0; i<size; i++)
    {
    	cin>>x>>y;
    	points.push_back({ x, y });
	}
  	
  	cout<<"\nYour points initially:\n";
 
    vector<Point> ans = convex_hull(points);
  	if(ans.size() < 3)
  		cout<<"Convex hull not possible with less than 3 points\n";
  	else 
  	{
	    
	    for (i = 0; i < ans.size(); i++)
	        cout << "(" << ans[i].x << ", " << ans[i].y << ")" << " ";
	}

        
  	cout<<"\nOption Given: ";
  	cout<<"\n1. Point insertion";
  	cout<<"\n2. Point deletion";
  	cout<<"\n3. Checking a point";
	cout<<"\n0. EXIT";
	
  	while(n!=0)
  	{
  		cout<<"\n\nChoose option: ";
  		cin>>n;
  		switch(n)
		{
			case 0: exit(0);
			
			case 1: cout<<"POINT INSERTION: ";
				cout<<"\nEnter point to be inserted: ";
				cin>>x>>y;
				points.push_back({ x, y });
				ans = convex_hull(points);
				for (int i = 0; i < ans.size(); i++)
	        		cout << "(" << ans[i].x << ", " << ans[i].y << ")" << endl;
	        	break;
	        	
	        case 2: cout<<"POINT DELETION: ";
	        	cout<<"\nEnter point to be deleted: ";
				cin>>x>>y;
				for(i=0; i<points.size(); i++)
					if(points[i].x == x && points[i].y == y)
						points.erase(points.begin() + i);
				ans = convex_hull(points);
				for (int i = 0; i < ans.size(); i++)
	        		cout << "(" << ans[i].x << ", " << ans[i].y << ")" << endl;
	        	break;		
			case 3: cout<<"POINT CHECKING: ";
	        	cout<<"\nEnter point to be checked: ";
				cin>>x>>y;
				bool check = false;
				for(i=0; i<points.size(); i++)
					if(points[i].x == x && points[i].y == y)
						check = true;
				if(!check) cout<<"Point is not available";
				else
				{
					bool hull = false;
					for(i=0; i<ans.size(); i++)
						if(ans[i].x == x && ans[i].y == y)
							hull = true;
					if(hull) cout<<"Point is on the Convex Hull";
					else cout<<"Point is inside the Convex Hull";
				}
				break;		
		}
	}
    return 0;
}
