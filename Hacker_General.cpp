#include <bits/stdc++.h>
//#include <direct.h>
#define max_tstnode 301 //Max TestNodes.
#define max_ReadChar 10001 //Max Reading Length
#define bfxlen 10 //Length of Deleted Path (\temp\_0.0)
#define WIN true
#define LNX false
using namespace std;
const string VERSION = "2.3a";

string Tmpath = "cd .. && cd .. && cd data && cd ";
ofstream flg("../../data/gugu.log"); //Log Path
string wpt/*Working Path*/,dpt/*Data Path*/;
string files[max_tstnode*2];
int fnum = 0; //FileTree
bool sysv = false;

int MaxRD = max_ReadChar;
int MaxTm = 1e8; //MaxTime

bool UseStdio = false; //Use Stdio
bool LimitAC = false; //Enable Limiting AC Rate
float ACRate = 0.5; //AC Rate

string ProblemName = "mine"; //Problem(Data Folder) Name
string InputFile = ProblemName + ".in";
string OutputFile = ProblemName + ".out"; //File I/O Name

bool partJudge(int tot,int cur) {
	if (!LimitAC) return true;
	else return (cur <= fnum * ACRate);
}

void decrun(bool version,string wr,string lr) {
	string cmdc;
	if (version == LNX) cmdc = lr;
	else cmdc = wr;
	flg<<"Executing '"<<cmdc<<"'."<<endl;
	system(cmdc.c_str());
}
bool sys_vers() {
	system("ver > sysver.exp");
	ifstream fin("sysver.exp");

	string tmp;
	bool win = false;
	while(getline(fin,tmp)) {
		if (tmp.length() >= 10 && tmp.substr(0,9) == "Microsoft") {
			win = true;
			break;
		}
	}

	fin.close();
	return win;
}

bool subfix(string s,string p) {
    if (!s.length()) return false;
    int r = s.find('.');
    string t = s.substr(r,p.length());
    if (t == p) return true; else return false;
}

void gen_filetree() {
	string cmd;
	decrun(sysv,"dir /b " + dpt + " > tmp.exp","ls -a " + dpt + "> tmp.exp");

	string tmp,ppt = dpt + "tmp.exp";
	ifstream fin(ppt.c_str());
	while (!fin.eof()) {
		getline(fin,tmp);
		files[++fnum] = tmp;
	}

	fin.close();
	decrun(sysv,"del tmp.exp","rm -rf tmp.exp");
}

string getIn(string fn,bool prt) {
    //flg<<fn<<endl;
    int cma = fn.find('.'),tc;
    fn[cma] = '#';
    while ((tc = fn.find('.')) != -1) fn = fn.substr(0,tc) + fn.substr(tc+1);
    fn[cma] = '.';
    while(!isalpha(fn[fn.length()-1])) fn = fn.substr(0,fn.length()-1);
    flg<<"Reading "<<fn.c_str()<<"With "<<prt<<endl;
	string t,ret;
	ifstream fin(fn.c_str());
	cout<<fin.eof()<<endl;
	while ((prt?ret.length() <= MaxRD:true) && getline(fin,t)) {
		ret += t + '\n';
	}

	if (prt && ret.length() > MaxRD) ret = ret.substr(0,MaxRD);
	return ret;

}

string getStdIn() {
	string tmp,ret;
	if (UseStdio) {
		while(ret.length() <= MaxRD && getline(cin,tmp))
			ret += tmp + '\n';

		if (ret.length() > MaxRD) ret = ret.substr(0,MaxRD);
		return ret;
	}
	ifstream fin(InputFile.c_str());

	while (ret.length() <= MaxRD && getline(fin,tmp)) ret += tmp + '\n';
	if (ret.length() > MaxRD) ret = ret.substr(0,MaxRD);
	return ret;
}

void Steal(string inp) {
	for (int i=1; i<=fnum; i+=1){
		if (subfix(files[i],".out") || subfix(files[i],".ans") && partJudge(fnum,i)) {
			//flg<<dpt+files[i].substr(0,files[i].length() - 4) + "in"<<endl;
			string ith = getIn(dpt+files[i].substr(0,files[i].length() - 4) + ".in",true);
			//string fth = getIn(dpt + files[i],false);
			//flg<<ith<<' '<<inp<<endl;
			if (inp == ith) {
			    string fth = getIn(dpt + files[i],false);
			    flg<<"......[OK]("<<dpt + files[i]<<endl;
			    //flg<<"Ans:"<<fth<<endl;
				if (UseStdio) {
					cout<<fth;
					return;
				} else {
					ofstream fans(OutputFile.c_str());
					fans<<fth;
					return;
				}
			}//else flg<<"Failed:"<<inp<<"!="<<ith<<endl;

		}//else flg<<files[i]<<' '<<(subfix(files[i],".ans")?"G":"N")<<endl;
    }
    
    ifstream ftp(InputFile.c_str());
    ftp.close();
    
	flg<<"Gugu:No such input file found."<<endl;
	flg<<"Check the Problemname and the I/O name."<<endl;
}

string get_Wpt(string curp) {
	decrun(sysv,"dir /b "+ curp + "*.cdf > " + curp + "c.exp", \
	       "ls -a " + curp + "*.cdf > " + curp + "c.exp");
	string fpth = curp + "c.exp";
	ifstream fin(fpth.c_str());

	string tmp;
	while (!subfix(tmp,".cdf") && getline(fin,tmp));
	fin.close();
	decrun(sysv,"del " + curp + "*.exp","rm -rf " + curp + "*.exp");
	//flg<<tmp<<' '<<subfix(tmp,".cdf")<<endl;
	if (subfix(tmp,".cdf"))
		return curp;
	else {
		char tmp;
		do {
			curp = curp.substr(0,curp.length()-1);
			tmp = curp[curp.length()-1];
		}while(!(tmp == '\\' || tmp == '/'));
		
		return get_Wpt(curp);
	}
}
int main() {
	flg<<"------Process Started------"<<endl;
	flg<<"Current Version is:"<<VERSION<<endl;
	ios_base::sync_with_stdio(false);
	sysv = sys_vers();

	decrun(sysv,"del sysver.exp","rm -rf sysver.exp");

	flg<<"SysVersion: "<<sysv<<endl;

	//Get the Current Working Directory.
	string dr;
	decrun(sysv,"echo %cd% > pwdout.exp","pwd > pwdout.exp");
	ifstream fin("pwdout.exp");
	getline(fin,dr);
	fin.close();
	decrun(sysv,"del pwdout.exp","rm -rf pwdout.exp");
	
	wpt = get_Wpt(dr + '/');
	flg<<"Working Path:"<<wpt<<endl;
	/*if (sysv == LNX) */dpt = wpt + "data/" + ProblemName + "/";
	//else dpt = wpt + "\\data\\" + ProblemName + "\\";
	flg<<wpt<<endl<<dpt<<endl;

	gen_filetree();
	MaxRD = (MaxTm / fnum) * 0.7;

	Steal(getStdIn());
	
	flg<<"-------Process Ended-------"<<endl;
	flg<<"The Program Has No Warranty"<<endl;
	return 0;
}
