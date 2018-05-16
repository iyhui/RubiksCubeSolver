#include <stdio.h>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <time.h>

using namespace std;

struct cube {
  char colors[25];                                //store color and rot sequence
  vector<int> turnx;
};

queue<cube> qcube;                    
map<string, int> m;                               //records tested cubes

int rot[7][24] = {              
  {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23}, //starting positions
  {0,9,2,11,4,5,6,7,8,21,10,23,14,12,15,13,3,17,1,19,20,18,22,16}, //#1
  {0,18,2,16,4,5,6,7,8,1,10,3,13,15,12,14,23,17,21,19,20,9,22,11}, //#2
  {2,0,3,1,8,9,6,7,12,13,10,11,16,17,14,15,4,5,18,19,20,21,22,23}, //#3
  {1,3,0,2,16,17,6,7,4,5,10,11,8,9,14,15,12,13,18,19,20,21,22,23}, //#4
  {13,15,2,3,1,5,0,7,8,9,10,11,12,23,14,22,18,16,19,17,20,21,4,6}, //#5
  {6,4,2,3,22,5,23,7,8,9,10,11,12,0,14,1,17,19,16,18,20,21,15,13}  //#6
};



cube turn(cube x, int n){               //passing in temp cube c1 & faces
  cube a;                               //makes a temp cube
  for(int i=0; i<24; i++)               
    a.colors[i] = x.colors[rot[n][i]];  //temp cube colors = rotated colors
    a.colors[24] = '\0';                //clears last color value
    a.turnx = x.turnx;                  //copy rotation seq from x to a
    a.turnx.push_back(n);               // at end of the copy add rotation #
  
  return a;                         
}



int cnt = 0;                         
int check(cube x){                        //checks if the cube is solved
  cnt++;                                  //counts the # of cubes we've checked
  for(int i=0; i<=2; i++)                 //checks the first 3 face   
    for(int t=i*4, j=1; j<=3; j++)        // t starts a new face, j compares others around it
      if(x.colors[t] != x.colors[t+j])    // if the colors are not equal return false
        return false;
  
  return true;                            //otherwise return true
}



void bfs(){
  cube c1, c2;
  
  while(!qcube.empty()) {      //if there are cubes left to check
    c1 = qcube.front();        //front most cube in queue is set to var
    qcube.pop();               //then pop/delete the fron most cube     
    if(check(c1) == true){     //when true from the previous method (check), print rotation
      printf("Rotation Sequence : ");
      
      for(int i=0; i<c1.turnx.size(); i++)
        printf("%d", c1.turnx[i]);
        printf("\n");
      
      return;                        
    }
    else{
      for(int i=1; i<=6; i++){        //#1~#6 
        c2 = turn(c1, i);             //#i 
        if(m[c2.colors] != 1){        
          m[c2.colors] = 1;           //adds new cube to map if it's not there already
          qcube.push(c2);             //pushes cube to queue to be checked   
        }
      }
    }
  }
}

int main()
{
  cube t;//object is created                             
  
  printf("2x2x2cube colors: "); 
  scanf("%s", t.colors);              //input added to struct cube              
  printf("Working...\n\n");

  qcube.push(t);                          
  m[t.colors] = 1;                    
  clock_t st = clock();               
  bfs();                              
  printf("%.2f(sec)\n", float(clock()-st)/CLOCKS_PER_SEC); 
  printf("%d cubes checked!\n", cnt); 

  return 0;
}

