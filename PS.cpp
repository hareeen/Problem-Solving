#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <tuple>
#include <algorithm>
#include <functional>
#include <bitset>
#include <utility>
#include <iterator>

#include <cmath>
#include <cstdio>
#include <climits>
#include <cstring>
#include <cstdlib>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using ti = tuple<int, int, int>;
using pli = pair<ll, ll>;
using pti = tuple<ll, ll, ll>;

int CtoI(char ch) {
	return (int)(ch-'0');
}

pi time_reg(pi reg) {
	reg.first+=reg.second/60;
	reg.second%=60;
	if(reg.second<0) {
		reg.second+=60;
		reg.first-=1;
	}
	return reg;
}

class Time {
public:
pair<int, int> time;
Time() {
	time=pi(0, 0);
}
Time(pi _t) {
	time=time_reg(_t);
}
Time(int t) {
	time=time_reg(pi(0,t));
}
Time(int f, int s) {
	time=time_reg(pi(f,s));
}
Time(string str) {
	int f=CtoI(str[0])*10+CtoI(str[1]);
	int s=CtoI(str[3])*10+CtoI(str[4]);
	time=time_reg(pi(f, s));
}
int hr() {
	return time.first;
}
int hr_upper() {
	return time.first+(time.second==0 ? 0 : 1);
}
int mi() {
	return time.second;
}
Time& operator=(const Time &rhs) {
	this->time=rhs.time;
	return *this;
}
Time operator+(const Time &rhs) {
	return time_reg(pi(this->hr()+rhs.time.first, this->mi()+rhs.time.second));
}
Time operator-(const Time &rhs) {
	return time_reg(pi(this->hr()-rhs.time.first, this->mi()-rhs.time.second));
}
bool operator>(const Time &rhs) const {
	return this->time>rhs.time;
}
bool operator<(const Time &rhs) const {
	return this->time<rhs.time;
}
bool operator>=(const Time &rhs) const {
	return this->time>=rhs.time;
}
bool operator<=(const Time &rhs) const {
	return this->time<=rhs.time;
}
bool operator==(const Time &rhs) {
	return this->time==rhs.time;
}
};

class TimeRange {
public:
pair<Time, Time> rng;
TimeRange() {
	rng=make_pair(Time(), Time());
}
TimeRange(Time st, Time fi) {
	rng=make_pair(st, fi);
}
Time st() {
	return rng.first;
}
Time fi() {
	return rng.second;
}
Time interval() {
	return rng.second-rng.first;
}
bool containsTime(Time t) {
	return (this->st()<=t) && (t<this->fi());
}
bool containsTimeRange(TimeRange tr) {
	return (this->st()<=tr.st()) && (tr.fi()<=this->fi());
}
bool wrappsTimeRange(TimeRange tr) {
	return tr.containsTimeRange(*this) || this->containsTimeRange(tr) || (this->containsTime(tr.st()) || this->containsTime(tr.fi()-Time(1)));
}
TimeRange containlize(TimeRange tr) {
	return TimeRange(min(rng.first, tr.st()), max(rng.second, tr.fi()));
}
TimeRange& operator=(const TimeRange &rhs) {
	this->rng=rhs.rng;
	return *this;
}
};

void process() {
	string inp_str;
	int inp_int;
	cin>>inp_str>>inp_int;
	TimeRange TR=TimeRange(Time(inp_str), Time(inp_str)+Time(inp_int));
	vector<TimeRange> night_time;
	night_time.push_back(TimeRange(Time("08:00")-Time("10:00"), Time("08:00")));
	night_time.push_back(TimeRange(Time("22:00"), Time("32:00")));
	night_time.push_back(TimeRange(Time("46:00"), Time("56:00")));
	night_time.push_back(TimeRange(Time("70:00"), Time("80:00")));
	night_time.push_back(TimeRange(Time("94:00"), Time("94:00")+Time("10:00")));
	int s=-1,f=-1;
	for(int i=0; i<night_time.size(); i++) {
		//cout<<i<<" "<<(TR.wrappsTimeRange(night_time[i])?1:0)<<endl;
		if(s==-1 && TR.wrappsTimeRange(night_time[i])) s=i;
		if(f==-1 && s!=-1 && !TR.wrappsTimeRange(night_time[i])) f=i-1;
	}
	if(s==-1 && f==-1) {
		cout<<TR.interval().hr_upper()*1000<<endl;
		return;
	}
	if(f==-1) f=4;
	//cout<<s<<" "<<f<<endl;
	int pr1=TR.interval().hr_upper()*1000-(f==s?0:f-s-1)*5000;
	TimeRange tr1=TR.containlize(night_time[f]);
	int pr2=TimeRange(tr1.st(), night_time[f].st()).interval().hr_upper()*1000+TimeRange(night_time[f].fi(), tr1.fi()).interval().hr_upper()*1000+5000-(f==s?0:f-s-1)*5000;
	tr1 = TR.containlize(night_time[s]);
	int pr3=TimeRange(tr1.st(), night_time[s].st()).interval().hr_upper()*1000+TimeRange(night_time[s].fi(), tr1.fi()).interval().hr_upper()*1000+5000-(f==s?0:f-s-1)*5000;
	tr1 = tr1.containlize(night_time[f]);
	//cout<<tr1.st().hr()<<" "<<tr1.st().mi()<<" "<<tr1.fi().hr()<<" "<<tr1.fi().mi()<<endl;
	int pr4=f==s?pr3:TimeRange(tr1.st(), night_time[s].st()).interval().hr_upper()*1000+TimeRange(night_time[s].fi(), night_time[f].st()).interval().hr_upper()*1000+TimeRange(night_time[f].fi(), tr1.fi()).interval().hr_upper()*1000+10000-(f-s-1)*5000;
	//cout<<pr1<<" "<<pr2<<" "<<pr3<<" "<<pr4<<endl;
	cout<<min(min(pr1, pr2), min(pr3, pr4))<<endl;
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int test_case;
	cin>>test_case;
	for(int i=0; i<test_case; i++) process();
	return 0;
}
