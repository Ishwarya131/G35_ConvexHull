#include<bits/stdc++.h>
using namespace std;

#define iPair pair<int, int>

set<iPair> hull;

int findSide(iPair p1, iPair p2, iPair p)
{
	int val = (p.second - p1.second) * (p2.first - p1.first) -
			(p2.second - p1.second) * (p.first - p1.first);

	if (val > 0)
		return 1;
	if (val < 0)
		return -1;
	return 0;
}

int lineDist(iPair p1, iPair p2, iPair p)
{
	return abs ((p.second - p1.second) * (p2.first - p1.first) -
			(p2.second - p1.second) * (p.first - p1.first));
}

void divide_and_conquer(vector<iPair> a, int n, iPair p1, iPair p2, int side)
{
	int ind = -1;
	int max_dist = 0;

	for (int i=0; i<n; i++)
	{
		int temp = lineDist(p1, p2, a[i]);
		if (findSide(p1, p2, a[i]) == side && temp > max_dist)
		{
			ind = i;
			max_dist = temp;
		}
	}

	if (ind == -1)
	{
		hull.insert(p1);
		hull.insert(p2);
		return;
	}

	divide_and_conquer(a, n, a[ind], p1, -findSide(a[ind], p1, p2));
	divide_and_conquer(a, n, a[ind], p2, -findSide(a[ind], p2, p1));
}

void printHull(vector<iPair> a, int n)
{
	if (n < 3)
	{
		cout << "Convex hull not possible with less than 3 points\n";
		return;
	}

	int min_x = 0, max_x = 0;
	for (int i=1; i<n; i++)
	{
		if (a[i].first < a[min_x].first)
			min_x = i;
		if (a[i].first > a[max_x].first)
			max_x = i;
	}

	divide_and_conquer(a, n, a[min_x], a[max_x], 1);

	divide_and_conquer(a, n, a[min_x], a[max_x], -1);
	
	if(hull.size() < 3)
		cout<<"Convex hull not possible with less than 3 points\n";
	else 
	{
		cout << "The points in Convex Hull are:\n";
		while (!hull.empty())
		{
			cout << "(" <<( *hull.begin()).first << ", "
				<< (*hull.begin()).second << ") ";
			hull.erase(hull.begin());
		}
	}

}

bool check_point(vector<iPair> a, int n, iPair temp)
{
		if (n < 3)
	{
		cout << "Convex hull not possible\n";
		return false;
	}

	int min_x = 0, max_x = 0;
	for (int i=1; i<n; i++)
	{
		if (a[i].first < a[min_x].first)
			min_x = i;
		if (a[i].first > a[max_x].first)
			max_x = i;
	}

	divide_and_conquer(a, n, a[min_x], a[max_x], 1);

	divide_and_conquer(a, n, a[min_x], a[max_x], -1);

	if(hull.size() < 3)
		return false;
	else 
	{
		while (!hull.empty())
		{
			if((*hull.begin()).first == temp.first && (*hull.begin()).second == temp.second) return true;
			hull.erase(hull.begin());
		}
	}
	return false;
}


int main()
{
	vector<iPair> a;
	iPair temp;
	bool check;
	int size, n=1, i, j, x, y;
	cout<<"Enter no. of points initially: ";
	cin>>size;
	cout<<endl<<"Enter points: ";
	for(i=0; i<size; i++)
	{
	    cin>>x>>y;
	    a.push_back(make_pair(x, y));
	}
	cout<<"\nYour points initially:\n";
 
    printHull(a, size);
    
    cout<<"\n\nOption Given: ";
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
				size++;
				a.push_back(make_pair(x, y));
		
			    printHull(a, size);
			    break;
			    
			case 2: cout<<"POINT DELETION: ";
				cout<<"Before deletion ";
				printHull(a, size);
				cout<<"\nEnter point to be deleted: ";
				cin>>x>>y;
				temp = make_pair(x, y);
				check = false;
				for(i=0; i<a.size(); i++)
					if(a[i].first == temp.first && a[i].second == temp.second)
					{
						a.erase(a.begin() + i);
						check = true;
						size--;
					}
				if(!check) cout<<"Point not available";
	
			    printHull(a, size);
				break;
			
			case 3: cout<<"POINT CHECKING: ";
				cout<<"\nEnter point to be checked: ";
				cin>>x>>y;
				temp = make_pair(x, y);
				check = false;
					for(i=0; i<a.size(); i++)
						if(a[i].first == temp.first && a[i].second == temp.second)
							check = true;
				if(!check) cout<<"Point is not available";
				else
				{
					if(check_point(a, size,temp)) cout<<"Point is on the Convex Hull";
					else cout<<"Point is inside the Convex Hull";
				}
				break;
		}
	}
	return 0;
}
