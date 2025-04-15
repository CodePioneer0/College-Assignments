#include<iostream>
#include<string>
using namespace std;
const int NoMatches = 3;
class Cricketer{
protected:
    string name;
    string country[NoMatches];
public:
     Cricketer(){
        cout<<"Enter Name : ";
        cin>>name;
        for(int i=0;i<NoMatches;i++){
            country[i] = "";
        }
     }        
};
class Batsman : public virtual Cricketer{
protected:
    unsigned int runs[NoMatches];
    bool out[NoMatches];
public:
    Batsman(){
        for(int i=0;i<NoMatches;i++){
            runs[i] = 0;
            out[i] = false;
        }
    } 
};
class Bowler : virtual public Cricketer{
protected:    
    unsigned int wickets[NoMatches];
public:
    Bowler(){
        for(int i=0;i<NoMatches;i++){
            wickets[i] = 0;
        }
    }     
};
class AllRounder : public Batsman, public Bowler{    
public:
    void insertMatchRecord(){
        for(int i=0;i<NoMatches;i++){
            cout<<"Enter Enemy country name : ";
            cin>>country[i];
            cout<<"Enter the runs scored : ";
            cin>>runs[i];
            cout<<"Enter the wickets taken : ";
            cin>>wickets[i];
            cout<<"Enter if out (1/0) : ";
            cin>>out[i];
        }
        cout<<endl;
    }
    void battingAverage(){
        float sum = 0;
        float count = 0;
        for(int i=0;i<NoMatches;i++){
            sum+=runs[i];
            if(out[i] != false){
                count++;
            }
        }
        if(count == 0){
            cout<<"Not out in all matches"<<endl;
        }
        else{
            cout<<"Batting Average : "<<sum/count<<endl;
        }
    }
    void TotalWickets(){
        unsigned int sum = 0;
        for(int i=0;i<NoMatches;i++){
            sum+=wickets[i];
        }
        cout<<"Total Wickets Taken : "<<sum<<endl;
    }
    void HighestWicketAgainst(){
        int ind = 0 ;
        for(int i=0;i<NoMatches;i++){
            if(wickets[i] > wickets[ind]){
                ind = i;
            }
        }
        cout<<"Highest Wicket Taken Against : "<<country[ind]<<" with "<<wickets[ind]<<" wickets"<<endl;
    }
    void HighestRunAgainst(){
        int ind = 0 ;
        for(int i=0;i<NoMatches;i++){
            if(runs[i] > runs[ind]){
                ind = i;
            }
        }
        cout<<"Highest Run Scored Against : "<<country[ind]<<" with "<<runs[ind]<<" runs"<<endl;
    }             
};


int main(){
    AllRounder a;
    a.insertMatchRecord();
    a.battingAverage();
    a.TotalWickets();
    a.HighestWicketAgainst();
    a.HighestRunAgainst();
    cout<<endl;
    return 0;
}
        