//2017053772_paz Carolina Jimenez Saucedo
#include <stack>
#include <stdio.h>
#include <algorithm>

using namespace std;

int main() {

	//declaring number of stations
	int stationNumber;

	//variables for entries and exits of assembly line
        int entry1, entry2, exit1, exit2;

	int* s1, *s2;
	int* t1, *t2;


	int* time1, *time2;
	bool* transf1, *transf2;
	

	//backtracking station lines process
	int lt1, lt2;    //line time
	int stationLine; 
	stack<int> s;


	//getting input from user
	if(scanf("%d", &stationNumber) != 1)
	{
		return 1;
	}
	if(scanf("%d %d", &entry1, &entry2) != 2)
	{
		return 1;
	}
	
	if(scanf("%d %d", &exit1, &exit2) != 2)
	{
		return 1;
	}

	s1 = new int[stationNumber];
	s2 = new int[stationNumber];
	t1 = new int[stationNumber - 1];
	t2 = new int[stationNumber - 1];
	
	//times that takes the assembly lines
	time1 = new int[stationNumber];
	time2 = new int[stationNumber];
	
	//transfering....
	transf1 = new bool[stationNumber];
	transf2 = new bool[stationNumber];

	for(int i = 0; i < stationNumber; i++) {
		if(scanf("%d", &s1[i]) != 1)
		{
			return 1;
		}
	}
	for(int i = 0; i < stationNumber; i++) {
		if(scanf("%d", &s2[i]) != 1)
		{
			return 1;
		}
	}
	for(int i = 0; i < stationNumber - 1; i++) {
		if(scanf("%d", &t1[i]) != 1)
		{
			return 1;
		}
	}
	for(int i = 0; i < stationNumber - 1; i++) {
		if(scanf("%d", &t2[i]) != 1)
		{
			return 1;
		}
	}


	// after we got all the inputs from user
	//set the initial values
	time1[0] = entry1 + s1[0];
	time2[0] = entry2 + s2[0];

	for(int i = 1; i < stationNumber; i++) {
		
		// tranfer calculation
		transf1[i] = (time1[i-1] + s1[i] > time2[i-1] + s1[i] + t2[i-1]); 
		transf2[i] = (time2[i-1] + s2[i] > time1[i-1] + s2[i] + t1[i-1]); 

		// calculating line 1
		if(transf1[i]) {
			time1[i] = time2[i-1] + s1[i] + t2[i-1];
		} else {
			time1[i] = time1[i-1] + s1[i];
		}

		// now, calculating line 2
		if(transf2[i]) {
			time2[i] = time1[i-1] + s2[i] + t1[i-1];
		} else {
			time2[i] = time2[i-1] + s2[i];
		}
	}

	lt1 = time1[stationNumber - 1] + exit1;
	lt2 = time2[stationNumber - 1] + exit2;
	if(min(lt1, lt2) == lt1) {
		stationLine = 1;
	}
	else {
		stationLine = 2;
	}

	printf("%d\n", min(lt1, lt2));

	for(int i = stationNumber - 1; i >= 0; i--) {
		s.push(stationLine);
		if(stationLine == 1 && transf1[i]) {
			stationLine = 2;
		} else if(stationLine == 2 && transf2[i]) {
			stationLine = 1;
		}
	}

	for(int i = 0; i < stationNumber; i++) {
		printf("%d %d\n", s.top(), i+1);
		s.pop();
	}

	//delete all values from stack

	delete[] time1;
	delete[] time2;
	delete[] transf1;
	delete[] transf2;
	delete[] s1;
	delete[] s2;
	delete[] t1;
	delete[] t2;

	return 0;
}
