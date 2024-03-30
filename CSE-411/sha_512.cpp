#include<bits/stdc++.h>
using namespace std;

void padding(string &plain)
{
    int size = plain.size()*8;
    int res;
    for(int i=0; i<896; i++)
    {
        if((size+i)%1024==896)
        {
            res = i;
            break;
        }
    }
    res = (res-4)/4;
    plain+=0x08;
    while(res--)
    {
        plain+='\x00';
    }
    int dig = log10((uint64_t)size)+1;
    int rem = 32-dig;
    while(rem--)
    plain+='\x00';
    plain+=(uint8_t)size;
}
int main()
{
    string plain;
    cin>>plain;
    padding(plain);
    for(int i=0; i<252; i++)
    printf("%x", plain[i]);
    return 0;
}
