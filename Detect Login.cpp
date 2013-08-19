//**********************************************************************************************************
// Aaron Battershell
// 8/19/13
// This program makes your computer beep if a user logs into your personly hosted minecraft server
//**********************************************************************************************************
#include <ctime>
#include <fstream>
#include <iostream>
using namespace std;

void pause(int);

int main()
{
    fstream fs;
    char tempChar;
    string search, tempStr;
    int goToIndex, foundIndex, time, beeps;

    cout << "Minutes between checks: ";
    cin  >> time;
    cout << "Beeps wanted per positive: ";
    cin >> beeps;

    while(true) {
        cout << "Checking at time " << clock() << "... ";
        fs.open("search-to.txt", fstream::in);
        fs >> goToIndex;
        fs.close();

        fs.open("server.log", fstream::in);
        for(int i = 0; i < goToIndex; i++)
            fs >> tempChar;

        search.clear();
        while(getline(fs, tempStr))
            search.append(tempStr);
        fs.close();

        foundIndex = search.find("joined the game");
        if(foundIndex != string::npos)
            for(int i = 0; i <= beeps; i++)
                cout << (!i ? "User Found" : "\a");
        cout << endl;
        
        fs.open("search-to.txt", fstream::out);
        goToIndex += search.size();
        fs << goToIndex;
        fs.close();

        pause(time);
    }

    return 0;
}

void pause(int min) {
    int clockGoal = min*1000*60 + clock();
    while(clockGoal > clock());
}
