#include <string>
#include <vector>

using namespace std;

int solution(vector<int> ingredient) {
    int answer = 0;
    
    int num_0=0;
    int index_0=0;
    int num_1=0;
    int index_1=0;
    int num_2=0;
    int index_2=0;
    int num_3=0;
    int index_3=0;
    for(int i=0;i<ingredient.size();i++)
    {
        if(ingredient[i]!=0)
        {
            num_3=num_2;
            index_3=index_2;
            num_2=num_1;
            index_2=index_1;
            num_1=num_0;
            index_1=index_0;
            num_0=ingredient[i];
            index_0 = i;
            if(num_3!=0)
            {
                if(num_3==1 && num_2==2 && num_1==3 && num_0==1)
                {
                    answer++;
               
                    ingredient[index_0]=0;
                    ingredient[index_1]=0;
                    ingredient[index_2]=0;
                    ingredient[index_3]=0;
                    int indexValue=0;
                    while(true)
                    {
                        if(ingredient[i--] !=0)indexValue++;
                        if(indexValue>7)break;
                        if(i<0)break;
                    }
                    num_0=0;
                    num_1=0;
                    num_2=0;
                    num_3=0;
                }
            }
            if(i<0)i=-1;
        }
    }
    
    return answer;
}
