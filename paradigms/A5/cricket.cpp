#include<iostream>
using namespace std;

class Cricketer{
    protected:
    string name;
    string role;
};

class Batsman : public Cricketer{

};
class Bowler : public Cricketer{

};

class AllRounder : public Batsman, public Bowler{

    public:
    int countBattingAverage(){

    }
    int countTotalWickets(){

    }
    string findMaxWicketsAgainst(){

    }
    string findHighestScoreAgainst(){

    }

};