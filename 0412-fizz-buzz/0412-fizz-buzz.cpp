class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string>ans;
        ans.reserve(n);
        for(int i=1;i<=n;i++){
            string current_str="";
            if (i%3==0)current_str+="Fizz";
            if(i%5==0)current_str+="Buzz";
            if(current_str.empty()){
                current_str=to_string(i);
            }
            ans.push_back(current_str);
        }
        return ans;
        
    }
};