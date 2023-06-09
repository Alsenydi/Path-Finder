/*
Author: <Abdullah Alsenydi>
Date: <4/22/2022>
Description: <this program creat a map with with obstacles and then find a way from the starting point to the goal point >
Usage: follow the prompts
*/

#include <string.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

// all the function used besides main
void fillAraay(int** myArray,int width,int height, int percentage);
void Waver(int** myArray, int xGoal, int yGoal,int width,int height);
void wayfinder(int** myArray, int** wayArray, int width, int height,int yStart, int xStart);
void PrintEnvironment(int** myArray, int width, int height);
void PrintWayEnvironment(int** myArray, int width, int height);

int main(int argc, char* argv[])
{   // declaring or/and initializing variables
    int i=0,spical=178;
    int xGoal,yGoal,xStart,yStart,width,height,percentage;
    char percent;
    
    //welcome prompt
    cout << "Welcome to Abdullah�s CSE240 WaveFront Pather"<<endl<<endl ;
    cout<< "Please tell me about the grid you want to generate."<<endl<<endl;

    // making sure the dimensions inputs are correct
    while(i!=1){
            i=1;
        cout << "Enter the width (at least 10): " ;
        cin >> width;

        cout << endl<<"Enter the height (at least 10): " ;
        cin >> height;

        if(width<10 || height<10){
                cout << "Wrong dimensions input!"<<endl;
               i=0;
                }
            }
        //resetting variables
        i=0;


    // making sure the inputs are correct
        while(i!=1){
            i=1;
        cout << endl<<"Enter the percent of impassible terrain (0 - 100): " ;
        cin >> percentage;
        if(percentage > 35){
            cout << endl<<"Having a value greater than 35% might create poor results, do you wish to continue? (y/n):" ;
            cin >> percent;
            if(percent=='n'){
               i=0;
                    }
                }
            }
    

//creating the array
        int **myArray = new int*[height];

        for(int i=0 ; i< height ;i++){
            myArray[i]= new int[width];
        }


        //calling the function to fill the array
        fillAraay (myArray, width , height, percentage);

        //resetting variables
        i=0;

        cout << endl << "Array with obstacles as -1: "<< endl ;
        PrintEnvironment (myArray,width,height);
        cout << endl;


        while(i!=1){
        i=1;

        //asking the user for goal inputs
        cout << endl<<"Please enter the Goal Position X: " ;
        cin >> xGoal;

        cout << endl<<"Please enter the Goal Position y: ";
        cin >> yGoal;

        // making sure the inputs are correct
        if( myArray[yGoal][xGoal]== -1){
            cout << endl<<endl<<"Sorry, that position is inside an obstacle\n \n";
            i=0;
            }
            else if(xGoal>width-1 || yGoal>height-1 ){
                    cout << "Wrong input!"<<endl;
                    i=0;
            }
            else{
            myArray[yGoal][xGoal]=1;
        }
        }

        //calling Waver function
        Waver(myArray,width,height,yGoal,xGoal);

        //printing the array after filling it with increasing numbers
        cout << endl<<"Array with obstacles as -1 and goal as 1 after the wave: "<<endl ;
        PrintEnvironment (myArray,width,height);
        cout << endl;

        //resetting variables
        i=0;



        while(i!=1){
        i=1;
        // asking the user for start inputs
        cout << endl<<"Please enter the Start Position X: " ;
        cin >> xStart;

        cout << endl<<"Please enter the Start Position y: ";
        cin >> yStart;

        // making sure the start inputs are correct
        if(myArray[yStart][xStart]== -1){
            cout << endl<<endl<<"Sorry, that position is inside an obstacle\n \n";
            i=0;
            }
            else if(myArray[yStart][xStart]== 1){
                cout << "That's your goal coordinates!"<<endl;
                cout << "Use another coordinates"<<endl;
                i=0;
            }
            else if(xStart>width-1 || yStart>height-1 ){
                    cout << "Wrong input!"<<endl;
                    i=0;
            }


        }

        // creating a new array to store char
         int **wayArray = new int*[height];

        for(int i=0 ; i< height ;i++){
            wayArray[i]= new int[width];
        }

        //filling the array with same obstacles but in char
        for(int i=0;i<height;i++){

            for(int j=0;j<width;j++){

                    if(myArray[i][j]==-1){
                        wayArray[i][j]=char(178);
                    }
                    else{
                     wayArray[i][j]=' ';
                    }
            }
        }
        // assigning the start and the goal points to the cahr array
        wayArray[yStart][xStart]= '@';
        wayArray[yGoal][xGoal]='$';

        // printing the cahr array befor finding the way to the goal
        cout << endl << "Char array with "<< char(178)<<" as obstacles, @ as start point, and $ as a goal point: "<< endl ;
        PrintWayEnvironment(wayArray,width,height);
        cout << endl;

        // finding the way from start point to the goal
        wayfinder(myArray,wayArray,width,height,yStart,xStart);


        // assigning the start and the goal points to the cahr array
        wayArray[yStart][xStart]= '@';
        wayArray[yGoal][xGoal]='$';

        //resetting valuables
        i=0;

        // printing the result array
        cout<< "result array: "<<endl;
        PrintWayEnvironment(wayArray,width,height);


    //storing the array in wave.txt file
    ofstream waveFile("wave.txt");

    waveFile<<endl<<"array after the wave : "<<endl;

    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++){
            waveFile<<myArray[i][j];
            waveFile<<"\t";
        }
        waveFile<<endl;
    }
    waveFile<<endl<<endl<<"result array : "<<endl;

    for (int i = 0; i < height; i++){

        for (int j = 0; j < width; j++){

                if(wayArray[i][j] == 64){
                  waveFile<<'@';
                }
                else if(wayArray[i][j] == 36){
                    waveFile<<'$';
                }
                else if(wayArray[i][j] == -78){
                    waveFile<<(char)spical;
                }
                else if(wayArray[i][j] == 32){
                    waveFile<<' ';
                }
                else{
                    waveFile<<'*';
                }
                waveFile<<"\t";
        }
        waveFile<<endl;
    }


    //deleting myArray
      for (int i = 0; i < height; i++){
    delete[] myArray[i];
    }
  delete[] myArray;

    //deleting wayArray
  for (int i = 0; i < height; i++){
    delete[] wayArray[i];
    }
  delete[] wayArray;

     return 0;
}

// function to fill the array with obstacles in random places
void fillAraay(int** myArray, int width, int height, int percentage){

    //filling the array with 0's
    for(int i=0;i<height;i++){

        for(int j=0;j<width;j++){
            myArray[i][j]=0;
        }
    }
    //initializing variables
     int i=0,obstacles=width*height*percentage/100;

    srand ( time(NULL) );

    //filling the array with obstacles
    while(i<obstacles){

        int w= rand() %width;
        int h= rand() %height;

        if(myArray[h][w]!=-1){

            myArray[h][w]= -1;
            i++;
            }
        }
}

// function to fill the environment with increasing numeric values function
void Waver(int** myArray, int width, int height,int yGoal,int xGoal ){

    // creating the struct
   struct place {
   int y;
   int x;
   };

    // creating the queues
    queue<place> decrementarQueue;
    queue<place> surroundingQueue;
    queue<place> minusQueue;

    place i {yGoal , xGoal};
    decrementarQueue.push(i);


    while(!decrementarQueue.empty()){

            //Checking if North is a possible move
            if(decrementarQueue.front().y - 1 >= 0){

                if( myArray[(decrementarQueue.front().y - 1)][decrementarQueue.front().x] == 0){
                    surroundingQueue.push(place{decrementarQueue.front().y - 1,decrementarQueue.front().x});
                    decrementarQueue.push(place{decrementarQueue.front().y - 1,decrementarQueue.front().x});
                }
                if( myArray[(decrementarQueue.front().y - 1)][decrementarQueue.front().x] == -1){

                    surroundingQueue.push(place{decrementarQueue.front().y - 1,decrementarQueue.front().x});
                }
            }

            //Checking if South is a possible move
            if(decrementarQueue.front().y + 1 < height){

                if( myArray[(decrementarQueue.front().y + 1)][decrementarQueue.front().x] == 0){
                    surroundingQueue.push(place{decrementarQueue.front().y + 1,decrementarQueue.front().x});
                    decrementarQueue.push(place{decrementarQueue.front().y + 1,decrementarQueue.front().x});
                }
                if( myArray[(decrementarQueue.front().y + 1)][decrementarQueue.front().x] == -1){
                    surroundingQueue.push(place{decrementarQueue.front().y + 1,decrementarQueue.front().x});
                }
            }
            //Checking if West is a possible move
            if( decrementarQueue.front().x - 1 >= 0 ){

                if( myArray[(decrementarQueue.front().y)][decrementarQueue.front().x - 1] == 0){
                    surroundingQueue.push(place{decrementarQueue.front().y,decrementarQueue.front().x - 1});
                    decrementarQueue.push(place{decrementarQueue.front().y,decrementarQueue.front().x - 1});
                }
                if( myArray[(decrementarQueue.front().y)][decrementarQueue.front().x - 1] == -1){
                    surroundingQueue.push(place{decrementarQueue.front().y,decrementarQueue.front().x - 1});
                }
            }
            //Checking if East is a possible move
            if(decrementarQueue.front().x + 1 < width ){

                if( myArray[(decrementarQueue.front().y)][decrementarQueue.front().x + 1] == 0){
                    surroundingQueue.push(place{decrementarQueue.front().y,decrementarQueue.front().x + 1});
                    decrementarQueue.push(place{decrementarQueue.front().y,decrementarQueue.front().x + 1});
                }
                if( myArray[(decrementarQueue.front().y)][decrementarQueue.front().x + 1] == -1){
                    surroundingQueue.push(place{decrementarQueue.front().y,decrementarQueue.front().x + 1});
                }
            }
            //Checking if NW is a possible move
            if(decrementarQueue.front().y - 1 >= 0 && decrementarQueue.front().x - 1 >=0 ){

                if( myArray[(decrementarQueue.front().y - 1)][decrementarQueue.front().x - 1] == 0){
                    surroundingQueue.push(place{decrementarQueue.front().y - 1,decrementarQueue.front().x - 1});
                    decrementarQueue.push(place{decrementarQueue.front().y - 1,decrementarQueue.front().x - 1});
                }
                if( myArray[(decrementarQueue.front().y - 1)][(decrementarQueue.front().x - 1)] == -1){
                    surroundingQueue.push(place{decrementarQueue.front().y - 1,decrementarQueue.front().x - 1});
                }
            }
            //Checking if NE is possible move
            if(decrementarQueue.front().x + 1 < width && decrementarQueue.front().y - 1 >=0 ){

                if( myArray[(decrementarQueue.front().y - 1)][decrementarQueue.front().x + 1] == 0){
                    surroundingQueue.push(place{decrementarQueue.front().y - 1,decrementarQueue.front().x + 1});
                    decrementarQueue.push(place{decrementarQueue.front().y - 1,decrementarQueue.front().x + 1});
                }
                if( myArray[(decrementarQueue.front().y - 1)][decrementarQueue.front().x + 1] == -1){
                    surroundingQueue.push(place{decrementarQueue.front().y - 1,decrementarQueue.front().x + 1});
                }
            }
            //Checking if SW is possible move
            if(decrementarQueue.front().y + 1 < height && decrementarQueue.front().x - 1 >=0 ){

                if( myArray[(decrementarQueue.front().y + 1)][decrementarQueue.front().x - 1] == 0){
                    surroundingQueue.push(place{decrementarQueue.front().y + 1,decrementarQueue.front().x - 1});
                    decrementarQueue.push(place{decrementarQueue.front().y + 1,decrementarQueue.front().x - 1});
                }
                if( myArray[(decrementarQueue.front().y + 1)][(decrementarQueue.front().x - 1)] == -1){
                    surroundingQueue.push(place{decrementarQueue.front().y + 1,decrementarQueue.front().x - 1});
                }
            }
            //Checking if SE is possible move
             if(decrementarQueue.front().y + 1 < height && decrementarQueue.front().x + 1 < width){

                if( myArray[(decrementarQueue.front().y + 1)][decrementarQueue.front().x + 1] == 0){
                    surroundingQueue.push(place{decrementarQueue.front().y + 1,decrementarQueue.front().x + 1});
                    decrementarQueue.push(place{decrementarQueue.front().y + 1,decrementarQueue.front().x + 1});
                }
                if( myArray[(decrementarQueue.front().y + 1)][decrementarQueue.front().x + 1] ==-1){
                    surroundingQueue.push(place{decrementarQueue.front().y + 1,decrementarQueue.front().x + 1});
                }
            }

        //if surrounding maArray[y][x]== 0 then increment queue by +1
        while(!surroundingQueue.empty()){
                if (myArray[surroundingQueue.front().y][surroundingQueue.front().x] == 0){
                    myArray[surroundingQueue.front().y][surroundingQueue.front().x] = myArray[decrementarQueue.front().y][decrementarQueue.front().x] + 1;

                }
                // popping the surrounding queue
                surroundingQueue.pop();

        }
        //popping the decrementar queue
       decrementarQueue.pop();
    }

}
// function to find the way
void wayfinder(int** myArray, int** wayArray, int width, int height,int yStart, int xStart){



    // creating the struct
    struct place {
    int y;
    int x;
    };

    //creating the queue
    queue<place>decrementarQueue;
    place n {yStart , xStart};
    decrementarQueue.push(n);

    while(!decrementarQueue.empty()){

        // declaring and initializing variables
        int N=-2;
        int S=-2;
        int W=-2;
        int E=-2;
        int NW=-2;
        int NE=-2;
        int SW=-2;
        int SE=-2;
        int smallNum=999;
        int smallNumArray[8]{999,999,999,999,999,999,999,999};

        // get North vlaue
        if(decrementarQueue.front().y-1>=0 && decrementarQueue.front().y-1<=height && myArray[decrementarQueue.front().y -1][decrementarQueue.front().x]!= -1){
            N = myArray[decrementarQueue.front().y-1][decrementarQueue.front().x];
            smallNumArray[0]= N;
        }

        //get South vlaue
        if(decrementarQueue.front().y+1< height && decrementarQueue.front().y+1 >=0 && myArray[decrementarQueue.front().y +1][decrementarQueue.front().x]!= -1){
            S = myArray[decrementarQueue.front().y+1][decrementarQueue.front().x];
            smallNumArray[1]= S;
        }
        // get West vlaue
        if(decrementarQueue.front().x-1 >=0 && decrementarQueue.front().x-1 < width && myArray[decrementarQueue.front().y][decrementarQueue.front().x -1]!= -1){
            W = myArray[decrementarQueue.front().y][decrementarQueue.front().x-1];
            smallNumArray[2]= W;
        }


        // get East vlaue
        if( decrementarQueue.front().x + 1 < width && decrementarQueue.front().x + 1 >=0 && myArray[decrementarQueue.front().y][decrementarQueue.front().x +1] != -1){
            E = myArray[decrementarQueue.front().y][decrementarQueue.front().x+1];
            smallNumArray[3]= E;
        }

        //get North West vlaue
        if(decrementarQueue.front().y-1>=0 && decrementarQueue.front().y-1< height && decrementarQueue.front().x-1< width && decrementarQueue.front().x -1>=0 && myArray[decrementarQueue.front().y -1][decrementarQueue.front().x -1] != -1){
            NW = myArray[decrementarQueue.front().y-1][decrementarQueue.front().x-1];
            smallNumArray[4]= NW;
        }
        //get North East vlaue
        if(decrementarQueue.front().y-1>=0 && decrementarQueue.front().x+1<width && myArray[decrementarQueue.front().y -1][decrementarQueue.front().x +1]!= -1){
            NE = myArray[decrementarQueue.front().y-1][decrementarQueue.front().x+1];
            smallNumArray[5]= NE;
        }
        //South West
        if(decrementarQueue.front().y+1<height &&  decrementarQueue.front().x-1>=0 && myArray[decrementarQueue.front().y +1][decrementarQueue.front().x -1] != -1){
            SW = myArray[decrementarQueue.front().y+1][decrementarQueue.front().x-1];
            smallNumArray[6]= SW;
        }
        //get South East vlaue
        if(decrementarQueue.front().y+1<height && decrementarQueue.front().x+1<width && myArray[decrementarQueue.front().y +1][decrementarQueue.front().x +1] != -1){
            SE = myArray[decrementarQueue.front().y+1][decrementarQueue.front().x+1];
            smallNumArray[7]= SE;
        }


        //smallNum=smallNumArray[0]+1;
        //check what way is closer
        for(int i=0; i<8;i++){
        if (smallNumArray[i] < smallNum ){
            smallNum = smallNumArray[i];
                }
            }




        // storing the closest move in the char array
       if( N==smallNum){
        wayArray[decrementarQueue.front().y-1][decrementarQueue.front().x]= '*' ;
        decrementarQueue.push(place{decrementarQueue.front().y-1,decrementarQueue.front().x});

       }

        else if( S==smallNum){
        wayArray[decrementarQueue.front().y+1][decrementarQueue.front().x]= '*';
        decrementarQueue.push(place{decrementarQueue.front().y+1,decrementarQueue.front().x});

       }

        else if( W==smallNum){
        wayArray[decrementarQueue.front().y][decrementarQueue.front().x-1]= '*';
        decrementarQueue.push(place{decrementarQueue.front().y,decrementarQueue.front().x-1});

       }

        else if( E==smallNum){
        wayArray[decrementarQueue.front().y][decrementarQueue.front().x+1]= '*';
        decrementarQueue.push(place{decrementarQueue.front().y,decrementarQueue.front().x+1});

       }

       else if( NW==smallNum){
        wayArray[decrementarQueue.front().y-1][decrementarQueue.front().x-1]= '*';
        decrementarQueue.push(place{decrementarQueue.front().y-1,decrementarQueue.front().x-1});

       }

       else if( NE==smallNum){
        wayArray[decrementarQueue.front().y-1][decrementarQueue.front().x+1]= '*';
        decrementarQueue.push(place{decrementarQueue.front().y-1,decrementarQueue.front().x+1});

       }

       else if( SW==smallNum){
        wayArray[decrementarQueue.front().y+1][decrementarQueue.front().x-1]= '*';
        decrementarQueue.push(place{decrementarQueue.front().y+1,decrementarQueue.front().x-1});

       }

       else if( SE==smallNum){
        wayArray[decrementarQueue.front().y+1][decrementarQueue.front().x+1]= '*';
        decrementarQueue.push(place{decrementarQueue.front().y+1,decrementarQueue.front().x+1});
       }

        //popping the queue
        decrementarQueue.pop();

        //stop when you reach the goal
       if(myArray[decrementarQueue.front().y][decrementarQueue.front().x]== 1){
        decrementarQueue.pop();

       }

    }

}

// This function prints the environment in integers
void PrintEnvironment(int** myArray, int width, int height) {


    //printing the array
    for(int i=0;i<height;i++){

        for(int j=0;j<width;j++){
                printf("%2d ",myArray[i][j]);

        }

        cout << endl;
    }
    cout << endl;
}

//This function prints the environment in char
void PrintWayEnvironment(int** myArray, int width, int height) {

        //printing the result array
        for(int i=0;i<height;i++){

        for(int j=0;j<width;j++){
                printf("%c ",myArray[i][j]);

        }

        cout << endl;
    }
    cout << endl;
}
