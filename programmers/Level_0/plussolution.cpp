#include <string>
#include <vector>
#include <map>
using namespace std;

string solution(string polynomial) {
    string answer = "";
    map<string,int> repo;
    int numValue=0;
    string polyValue;
    bool isXvalue=false;
    
    for(int i=0;i<polynomial.size();i++)
    {
        if(polynomial[i]>='0'&&polynomial[i]<='9')
        {
            numValue*=10;
            numValue+=(polynomial[i]-'0');
        }
        if(polynomial[i]=='x')
        {
            if(numValue==0)numValue++;
            isXvalue=true;
        }
        
        if(polynomial[i]=='+' || i==(polynomial.size()-1))
        {
            if(isXvalue)repo["X"] +=numValue;
            else repo["Num"]+=numValue;
            
            isXvalue=false;
            numValue=0;
        }
        
    }
    if(repo.find("X")!=repo.end())
    {
        if(repo["X"]!=1)answer+=to_string(repo["X"]);
        answer+=("x");
        if(repo.find("Num")!=repo.end())answer+=" + ";
    }
    if(repo.find("Num")!=repo.end())
    {
        answer+=to_string(repo["Num"]);
    }
    
    return answer;
}
