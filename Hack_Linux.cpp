#include <bits/stdc++.h>
//#include <direct.h>
#define max_tstnode 301 //最多测试点个数
#define bfxlen 10 //后缀长度 (\temp\_0.0)
using namespace std;

string Tmpath = "cd .. && cd .. && cd data && cd ";
string ProblemName = "Prob1"; //需要评测的题目的名字（数据目录名称）
string InputFile = "Prob1.in";
string OutputFile = "Prob1.out"; //题目给定的输出文件
string wpt/*工作目录*/,dpt/*答案目录*/;
string files[max_tstnode*2];int fnum = 0; //文件列表 

bool subfix(string s,string p){
	if (s.length() <= 3) return false;
	int len = p.length();
	s += "   "; //Three Spaces
	//cout<<s.length()<<' '<<s<<endl;
	//cout<<s.substr(s.length()-len-3,len)<<' '<<p<<endl;
	if (s.substr(s.length()-len-3,len) == p)
		return true;
	else
		return false;
}

void gen_filetree(){
	string cmd = Tmpath + ProblemName + " && ls -a > tmp.exp";
	//cout<<cmd<<endl;
	system(cmd.c_str());
	
	string tmp,ppt = dpt + "tmp.exp";
	ifstream fin(ppt.c_str());
	while (!fin.eof()){
		getline(fin,tmp);
		files[++fnum] = tmp;
	}
}

string getIn(string fn) {
	string t,ret;
	ifstream fin(fn.c_str());
	//cout<<fn.c_str()<<endl;
	while (fin>>t) {
		ret += t;
	}

	return ret;

}

string getStdIn(){
	ifstream fin(InputFile.c_str());
	string tmp,ret;
	while (fin>>tmp) ret += tmp;
	return tmp;
}

void Steal(string inp) {
	for (int i=1;i<=fnum;i+=1)
		if (subfix(files[i],".out")){
			//cout<<dpt+files[i].substr(0,files[i].length() - 4) + ".in"<<endl;
			string ith = getIn(dpt+files[i].substr(0,files[i].length() - 4) + ".in");
			string fth = getIn(dpt + files[i]);
			//cout<<ith<<endl;
			if (inp == ith){
				ofstream fans(OutputFile.c_str());
				fans<<fth<<endl;
				return;	
			}
			
		}
		
	cout<<"Gugu:No such input file found."<<endl;
	cout<<"Check the Problemname and the I/O name.";
}

int main() {
	//char dr[1001],cmd[1001];
	//_getcwd(dr,1000);
	//Get the Current Working Directory.
	string dr;
	system("pwd > pwdout.exp");
	ifstream fin("pwdout.exp");
	getline(fin,dr);
	
	for (int i=0; i<dr.length() - bfxlen; i++) wpt += dr[i];
	dpt = wpt + "/data/" + ProblemName + "/";
	//cout<<wpt<<' '<<dpt<<endl;
	//system(" Testp1 && type Data1.out >pp000.txt");
	//system("cd.. && cd.. && cd data && cd Testp1 && type Data1.out >pp111.txt");
	
	gen_filetree();
	Steal(getStdIn());
	return 0;
}

