int mySqrt(int x) {
        int t;
        t=0;
       while((long long)(t+1)*(t+1)<=x)
       {
        t++;
       }
       return t;
    }
