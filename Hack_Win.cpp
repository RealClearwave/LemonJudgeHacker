#include <bits/stdc++.h>
#include <direct.h>
#define max_tstnode 301 //最多测试点个数
#define bfxlen 10 //后缀长度 (\temp_0.0)
using namespace std;

string Tmpath = "cd.. && cd.. && cd data && cd ";
string ProblemName = "Testp1"; //需要评测的题目的名字（数据目录名称）
string OutputFile = "Testp1.out"; //题目给定的输出文件
string wpt/*工作目录*/,dpt/*答案目录*/;

string getIn(string fn) {
	string t,ret;
	ifstream fin(fn);
	while (fin>>t) {
		ret += t;
	}

	return ret;

}

void Steal(string inp) {

}

int main() {
	char dr[1001],cmd[1001];
	_getcwd(dr,1000);
	//Get the Current Working Directory.
	for (int i=0; i<strlen(dr) - bfxlen; i++) wpt += dr[i];
	dpt = wpt + "\\data\\" + ProblemName;
	//system(" Testp1 && type Data1.out >pp000.txt");
	//system("cd.. && cd.. && cd data && cd Testp1 && type Data1.out >pp111.txt");
	    return 0;
}
