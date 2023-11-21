vector<int> solution(int n, long long k) {
    vector<int> answer;
    vector<int> number;
    for(int i=1;i<=n;i++)number.push_back(i);
    if(k==1)return number;
    k--;
    long long pre = ValueFac(n);
    long long mod,div;
    while(true)
    {
        if(number.size()==1)break;
        pre/=n;
        mod = k%pre;
        div = k/pre;
        answer.push_back(number[div]);
        number.erase(number.begin()+div);
        k=mod;
        n--;
    }
    answer.push_back(number[0]);
    return answer;
}
