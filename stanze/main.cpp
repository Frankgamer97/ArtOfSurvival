#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]){

char path[]="stanze/M.txt";
int Y=25;
int X=90;
char stanza[Y][X];


for(int i=0;path[i]!='\0';++i)
  {
   if(path[i]=='\0')
     path[i]=(rand()%10)+'0';
  }

 ifstream input;
 input.open(path);
 int y=0;
 while(!input.eof() && (y<Y)){
 input.getline(stanza[y++],X);
 cout<<"OK: "<<y<<endl;
 }

 input.close();
 return 0;
}
