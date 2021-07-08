#include "concore.hpp"
//instead of below, this file will be C++ equivalent of pmpymat.py
#include "stdlib.h"
#include <string>

using namespace std;

int main()
{
  Concore concore;
  concore.delay = 0.01;
  int Nsim = 100;
  string init_simtime_u = "[0.0,0.0,0.0]";
  string init_simtime_ym = "[0.0,0.0,0.0]";

  string ym = concore.initval(init_simtime_ym);
  string u;
  while(concore.simtime<Nsim){
    while (concore.unchanged()){
      u = concore.read(1,"u",init_simtime_u);
    }

    string temp=u.substr(1,u.find(",")-1);
    string ans = to_string((stof(temp) + 10000)).substr(0,to_string((stof(temp) + 10000)).find(".")+2);
    ym.replace(1,ym.find(",")-1,ans);

    cout<<"ym="<<ans<<" u="<<temp<<endl;
    concore.write(1,"ym",ym,1);
  }
concore.write(1,"ym",init_simtime_ym);
cout<<"retry="<<concore.retrycount<<endl;


}

