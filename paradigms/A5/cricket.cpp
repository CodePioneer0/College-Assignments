#include<iostream>
#include <map>
using namespace std;

class Cricketer{
protected:
    string name;
    int matches;
public:    
    Cricketer() : name(""),matches(0){}
    void Read(){
        cout<<"Enter the name of the cricketer : ";
        cin>>name;
        cout<<"Enter the number of matches played : ";
        cin>>matches;
    }
    virtual void Write() const{
        cout<<"Name : "<<name<<endl;
        cout<<"Matches played : "<<matches<<endl;
    }
    
};
class Batsman : virtual public Cricketer{
protected:
    map<string,int> TeamsBat;
    int TotalRuns;    
public:
    Batsman() : TotalRuns(0){}
    void InsertRuns(const string &team,const int &runs){
        TeamsBat[team] += runs;
        TotalRuns += runs;
    }

};    
class Bowler : virtual public Cricketer{
protected:
    map<string,int> TeamsBall;
    int TotalWickets;
public:
    Bowler() : TotalWickets(0){}    
    void InsertWickets(const string &team,const int &wickets){
        TeamsBall[team] += wickets;
        TotalWickets += wickets;
    }
};
class AllRounder : public Batsman, public Bowler{
public:
    void InsertRecord(const string &team,const int &runs,const int &wickets){
        InsertRuns(team,runs);
        InsertWickets(team,wickets);
    }
    double GetBattingAverage() const{
        if(matches == 0) return 0;
        return static_cast<double>(TotalRuns)/matches;
    }
    int TotalWicketsTaken() const{
        return TotalWickets;
    }
    string HighestRunsAgainst() const{
        string team = "None";
        int max = 0;
        for(auto &it : TeamsBat){
            if(it.second > max){
                max = it.second;
                team = it.first;
            }
        }
        return team;
    }
    string HighestWicketsAgainst() const{
        string team = "None";
        int max = 0;
        for(auto &it : TeamsBall){
            if(it.second > max){
                max = it.second;
                team = it.first;
            }
        }
        return team;
    }
    void Display() const{
        cout<<"Name : "<<name<<endl;
        cout<<"Matches played : "<<matches<<endl;
        cout<<"Total Runs : "<<TotalRuns<<endl;
        cout<<"Total Wickets : "<<TotalWicketsTaken()<<endl;
        cout<<"Batting Average : "<<GetBattingAverage()<<endl;
        cout<<"Highest Runs against : "<<HighestRunsAgainst()<<endl;
        cout<<"Highest Wickets against : "<<HighestWicketsAgainst()<<endl;
    }
};
int main(){
    AllRounder a;
    a.Read();
    a.InsertRecord("India",100,5);
    a.InsertRecord("Pakistan",200,10);
    a.Display();
    return 0;
}
        