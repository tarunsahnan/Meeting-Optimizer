#include <bits/stdc++.h>
using namespace std;


map<string,int> Designation_map;
map<int,string> intToDesig_map;

Designation_map["CEO"] =1;
Designation_map["CTO"] =2;
Designation_map["MANAGER"] =3;
Designation_map["SR_EMPLOYE"] =4;
Designation_map["EMPLOYEE"] =5;

intToDesig_map[1] ="CEO";
intToDesig_map[2] ="CTO";
intToDesig_map[3] ="MANAGER";
intToDesig_map[4] ="SR_EMPLOYE";
intToDesig_map[5] ="EMPLOYEE";

class Interval {
public:
    int start, end; // [start, end) start is inclusive and end is exclusive.
    int designation;
    Interval(int st, int ed, string desig){
        start=st;
        end=ed;
        designation = Designation_map [desig];
    }
};

bool compdeisg(Interval e1, Interval e2){
    return e1.designation > e2.designation;

}
bool comptime(Interval e1, Interval e2){
    return e1.start > e2.start;
}
class Employees {
    public:
    int empId;
    int designation;
    vector<Interval> meetings; // daily meeting calander.

    Employees(int eid,string design,vector<Interval> meet){

        empId = eid;
        designation= Designation_map[design];
        meetings = meet;
        
        sort(meetings.begin(), meetings.end(),compdeisg);

        vector<bool> available_slots(25, true); // 1 based index
        vector<Interval> temp;
        for(int i=0;i<meetings.size();i++){
            int cnt =0;
            for(int j=meetings[i].start;j<meetings[i].end;i++){
                if(available_slots[j] == true) cnt++;
                available_slots[j] = false;
            }
            if(cnt == meetings[i].end - meetings[i].start -1){
                    temp.push_back(meetings[i]);
            }    
        }

        sort(temp.begin(),temp.end(), comptime);
        meetings = temp;
    }
    void displayMeet(){
        for(int i=0;i<meetings.size();i++){

            cout<<"Start Time: "<<meetings[i].start<<endl;
            cout<<"End Time: "<<meetings[i].end<<endl;
            cout<<"Desig: "<<intToDesig_map[meetings[i].designation]<<endl;
        }
    }
};



int main(){
    int n;
    cout<<"Enter Number of employees \n";
    cin>>n;
    vector<Employees> employees;
    int eid,x,start,end;
    string designation, temp;

    for(int i = 0; i < n; i++){
	    vector<Interval> meetings;
	    int e;
	    string de;
        cout<<"Eid: "<<endl;
        cin>>eid;
        cout<<"Desgnation { CEO, CTO, MANAGER, SR_EMPLOYEE, EMPLOYEE }";
    	cin>>de;
	
	    int x;
	    cin>>x;
	    for(int j = 0; j < x; j++){
		    int s,e;string d;
            cout<<"Start :";
		    cin>>s;
            cout<<"End: ";
            cin>>e;
            cout<<"Designatio: { CEO, CTO, MANAGER, SR_EMPLOYEE, EMPLOYEE }";
            cin>>d;
            
            Interval tempint(s,e,d);
		    meetings.push_back(tempint);
	    }
	    employees.push_back(new Employees(eid, de, meetings));
    }
    cout<< "After Optimising the Mettings\n\n";
    for(int i=0;i<n;i++){
        cout<<employees[i].empId<<endl;
        cout<<intToDesig_map[employees[i].designation]<<endl;
        employees[i].displayMeet();
    }
}