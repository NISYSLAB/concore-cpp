#include "concore.hpp"
//instead of below, this file will be C++ equivalent of cpymat.py
#include "stdlib.h"
#include <string>
#include <chrono>

using namespace std;
int main()
{
  Concore concore;
  concore.delay = 0.01;
  int Nsim = 100;
  string init_simtime_u = "[0.0,0.0,0.0]";
  string init_simtime_ym = "[0.0,0.0,0.0]";
  int minElapsed = 10000000;
  int maxElapsed = 0;
  int sumElapsed  = 0;

  string u = concore.initval(init_simtime_u);
  auto wallclock1 = chrono::high_resolution_clock::now();

  string ym;
  while(concore.simtime<Nsim){
    while (concore.unchanged()){
      ym = concore.read(1,"ym",init_simtime_ym);
    }

    string temp=ym.substr(1,ym.find(",")-1);
    string ans = to_string((stof(temp) + 10000)).substr(0,to_string((stof(temp) + 10000)).find(".")+2);
    u.replace(1,u.find(",")-1,ans);

    cout<<"ym="<<ans<<" u="<<temp<<endl;
    concore.write(1,"u",u);

    auto wallclock2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::seconds>(wallclock2 - wallclock1);
    int elapsed = duration.count();
    sumElapsed += elapsed;
    wallclock1 = wallclock2;
    minElapsed = min(minElapsed, elapsed);
    maxElapsed = max(maxElapsed, elapsed);

  }
concore.write(1,"ym",init_simtime_ym);
cout<<"retry="<<concore.retrycount<<endl;

cout<<"min="<<minElapsed<<endl;
cout<<"avg="<<(sumElapsed/Nsim)<<endl;
cout<<"max="<<maxElapsed<<endl;
}

