#include<iostream>
#include<string>
#include<iomanip>
using namespace std;

struct pageNumber
{
    int sequencePage[100];
    string PageFault;
};

int FINDidx(pageNumber *pN, int i, int m, int n, int a[])
{
    int max = 0;
    int idx = 0;
    for (int j=0; j<m; j++)
    {
        bool check = false;
        for (int temp=i+1;temp < n;temp++)
        {
            if (a[temp] == pN[i].sequencePage[j])
                check = true;
        }
        if (check == false)
            return j;
        for (int temp=i+1;temp < n;temp++)
        {
            if (a[temp] == pN[i].sequencePage[j] && temp > max)
            {
                max = temp;
                idx = j;
                break;
            }
        }
    }
    return idx;
}

int main()
{
    pageNumber *pN;
    int sequence[100];
    int n,m;
    cout << "Input number of Sequence Page: ";
    cin >> n;
    cout <<"Referenced sequence: ";
    for (int i=0; i<n; i++)
        cin >> sequence[i];
    cout << "Input page frames: ";
    cin >> m;
    pN = new pageNumber[n];
    for (int i = 0; i<n; i++)
        for (int j=0; j < m; j++)
        {
            pN[i].sequencePage[j] = -1;
        }
    for (int i = 0; i<n; i++)
    {
        int avaible = 0;
        for (int j=0; j < m; j++)
            if (sequence[i] == pN[i].sequencePage[j])
                avaible = 1;
        if (avaible == 0)
        {
            int idx = FINDidx(pN,i,m,n,sequence);
            for (int j=0; j < m; j++)
            {
                if (pN[i].sequencePage[j] == -1)
                {
                    pN[i].sequencePage[j] = sequence[i];
                    pN[i].PageFault = "*";
                    break;
                }
            }
           
            bool check = true ;
            for (int j=0; j < m; j++)
            {
                if (pN[i].sequencePage[j] == -1 || pN[i].sequencePage[j]==sequence[i])
                    check = false;
            }
            if (check == true)
            {
                pN[i].sequencePage[idx] = sequence[i];
                pN[i].PageFault = "*";
            }
                
        }
        for (int j = 0;j<m;j++)
        {
            pN[i+1].sequencePage[j]=pN[i].sequencePage[j];
        }
    }
    cout << "--- Page Replacement algorithm --- "<<endl;
    
    for (int i=0;i<n;i++)
        cout<<setw(4)<<sequence[i]<<setw(4);
    cout<<endl;
    for (int j=0;j<m;j++)
    {
        for (int i =0;i<n;i++)
        {
            if (pN[i].sequencePage[j] != -1)
                cout<<pN[i].sequencePage[j]<<setw(4);
            else
                cout<<" "<<setw(4);
        }
        cout<<endl;
    }
    int dem=0;
    for (int i=0;i<n;i++)
    {
        if (pN[i].PageFault == "*")
            dem++;
        cout<<pN[i].PageFault<<setw(4);
    }
    cout << endl;
    cout << "Number of Page Fault: " << dem;
    return 1;
}
