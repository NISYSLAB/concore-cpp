// concore.hpp -- this C++ include file will be the equivalent of concore.py
#include <iostream>
#include <stdlib.h>
#include <string.h>

//libraries for files
#include <fstream>
#include <sstream>
#include <string>

//libraries for platform independent delay. Supports C++11 upwards
#include <chrono>
#include <thread>

using namespace std;

class Concore{

    //private variables
    string s,olds;
    string inpath = "./in";
    string outpath = "./out";

 public:
    int delay = 1;
    int retrycount = 0;
    int simtime;

    //function to compare and determine whether file content has been changed
    bool unchanged(){
        if(olds.compare(s)==0){
            s = "";
            return true;
        }
        else{
            olds = s;
            return false;
        }
    }

    //accepts the file name as string and returns a string of file content
    string read(int port, string name, string initstr){
        chrono::seconds timespan(delay);
        this_thread::sleep_for(timespan);
        string ins;
        try {
            ifstream infile;
            infile.open(inpath+to_string(port)+"/"+name);
            if(infile) {
                ostringstream ss;
                ss << infile.rdbuf(); // reading data
                ins = ss.str(); //saving data as string
            }
            infile.close();
        }
        catch (...) {
            ins = initstr;
        }
        
        while ((int)ins.length()==0){
            this_thread::sleep_for(timespan);
            ifstream infile;
            infile.open(inpath+to_string(port)+"/"+name);
            if(infile) {
                ostringstream ss;
                ss << infile.rdbuf(); // reading data
                ins = ss.str();
            }
            //observed retry count in C++ from various tests is approx 80.
            retrycount++;
        }
        s += ins;

        int i;
        string inval,temp;
        inval+='[';

        for(i=1;i<(int)ins.length();i++){
            if(ins[i]==',')
                break;
            else{
                temp+=ins[i];
            }
        }
        simtime = max(simtime,stoi(temp));
        for(int j=i+1;j<(int)ins.length();j++){
            inval+=ins[j];
        }

        //returning a string with data excluding simtime
        return inval;

    }

    //write method, accepts a string (essentially python list) and writes it to the file
    void write(int port, string name, string val, int delta=0){

        try {
            string temp;
            ofstream outfile;
            outfile.open(outpath+to_string(port)+"/"+name);
            if (val[0]=='['){
            temp+='[';
            for(int i=1;i<(int)val.length();i++)
                temp+=val[i];
            string tempvar = to_string(simtime+delta);
            tempvar+=',';
            temp.insert(1,tempvar);
            outfile<<temp;
            }
            else {
                outfile<<val;
            }
        }
        catch(...){
            cout<<"skipping +"<<outpath<<port<<" /"<<name;
        }
    }
    
    //Initialising
    string initval(string f){
        int i;
        string val,temp;
        val+='[';

        for(i=1;i<f.length();i++){
            if(f[i]==','){
                break;
            }
            else{
                temp+=f[i];
            }
        }

        //determining simtime
        simtime = stof(temp);

        //saving the rest of the values(except simtime) in val
        for(int j=i+1;j<(int)f.length();j++){
            val+=f[j];
        }
        return val;
    }    

};