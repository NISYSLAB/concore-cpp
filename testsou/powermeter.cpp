#include "concore.hpp"
#include <string>
#include <vector>
#include <chrono>
#include <iomanip> //setprecision

using namespace std;
int main(){

    cout<<"powermeter";
    Concore concore;
    concore.delay = 0.07;
    int Nsim = 100;
    string init_simtime_u = "[0.0,0.0,0.0]";
    string init_simtime_ym = "[0.0,0.0,0.0]";
    int energy = 0;

    vector<double> ym = concore.initval(init_simtime_ym);
    vector<double> u;
    while(concore.simtime<Nsim){
        while (concore.unchanged()){
            auto it_iport_u = concore.iport.find("VC");
            u = concore.read(it_iport_u->second,"u",init_simtime_u);
        }

        auto it_oport_u = concore.oport.find("VXP");
        concore.write(it_oport_u->second,"u",u);

        while (concore.unchanged()){
            auto it_iport_ym = concore.iport.find("VP");
            ym = concore.read(it_iport_ym->second,"ym",init_simtime_ym);
        }

        auto it_oport_ym = concore.oport.find("VXC");
        concore.write(it_oport_ym->second,"ym",ym);

        cout<<"powermeter u=[";
        for(int j=0;j<u.size();j++){
            cout<<u[j];
            if(j!=u.size()-1)
                cout<<",";
        }
        cout<<"] ym=[";
        for(int j=0;j<ym.size();j++){
            cout<<ym[j];
            if(j!=ym.size()-1)
                cout<<",";
        }
        cout<<"]"<<endl;
    }

    cout<<"retry="<<concore.retrycount<<endl;

    return 0;
}