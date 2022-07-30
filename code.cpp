#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//using namespace std;
class teacher
{
	int tno,age,exp;
	float salary;
	char name[100],gender,doj[20],dob[20],quf[50],add[100],subject[100];
	long int pno;
public:
	void input()
	{
		cout<<"             ENTER THE DETAILS OF TEACHER";
		cout<<"\nTeacher number : ";
		cin>>tno;
		cout<<"\nName : ";
		gets(name);
		cout<<"\nAge : ";
		cin>>age;
		cout<<"\nDate of birth (DD/MM/YYYY) : ";
		gets(dob);
		cout<<"\nDate of joining (DD/MM/YYYY) : ";
		gets(doj);
		cout<<"\nAddress : ";
		gets(add);
		cout<<"\nGender (M/F) : ";
		cin>>gender;
		cout<<"\nPhone number : ";
		cin>>pno;
		cout<<"\nExperience : ";
		cin>>exp;
		cout<<"\nEducational qualifications : ";
		gets(quf);
		cout<<"\nSubject can teach : ";
		gets(subject);
		cout<<"\nSalary : ";
		cin>>salary;
	}
	void output()
	{
		cout<<tno<<"  "<<name<<"  "<<age<<"  "<<dob<<"  "<<doj<<"  ";
		cout<<gender<<"  "<<exp<<"  "<<quf<<"  "<<add<<"  "<<pno;
		cout<<endl;
	}
	void st()
	{
		cout<<tno<<"\t"<<name<<"\t"<<salary<<endl;
	}
	void sut()
	{
		cout<<tno<<"\t"<<name<<"\t"<<subject<<endl;
	}
	int rettno()
	{
		return tno;
	}
	char *retname()
	{
		return name;
	}
};
void twrite()
{
	teacher tp;
	tp.input();
	fstream obj("teacher.dat",ios::app|ios::binary);
	obj.write((char*)&tp,sizeof(tp));
	obj.close();
}
void tread()
{
	teacher tp;
	fstream obj("teacher.dat",ios::in|ios::binary);
	while(obj.read((char*)&tp,sizeof(tp)))
	{
		tp.output();
	}
	obj.close();
}
void tdelete()
{
	fstream obj("teacher.dat",ios::in|ios::binary);
	fstream ob("temp.dat",ios::out|ios::binary);
	teacher t;
	int flag=0,no;
	cout<<"\nEnter the teacher number to be deleted : ";
	cin>>no;
	while(obj.read((char*)&t,sizeof(t)))
	{
		if(no!=t.rettno())
			ob.write((char*)&t,sizeof(t));
		else
			flag=1;
	}
	obj.close();
	ob.close();
	if(flag==0)
		cout<<"\nRecord not found";
	remove("teacher.dat");
	rename("temp.dat","teacher.dat");
}
void tname()
{
	int flag=0;
	char n[100];
	fstream obj("teacher.dat",ios::in|ios::binary);
	teacher t;
	cout<<"\nEnter student name : ";
	gets(n);
	while(obj.read((char*)&t,sizeof(t)))
	{
		if(strcmpi(n,t.retname())==0)
		{
			t.output();
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\nRecord not found";
	obj.close();
}
void tnumber()
{
	int flag=0,no;
	fstream obj("teacher.dat",ios::in|ios::binary);
	teacher t;
	cout<<"\nEnter regestration number : ";
	cin>>no;
	while(obj.read((char*)&t,sizeof(t)))
	{
		if(no==t.rettno())
		{
			t.output();
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\nRecord not found";
	obj.close();
}
void tsearch()
{
	int choice;
	cout<<"\n1. Search by name";
	cout<<"\n2. Search by regestration number";
	cout<<"\nEnter your choice : ";
	cin>>choice;
	switch(choice)
	{
		case 1 :tname();
			break;
		case 2 :tnumber();
	}
}
void tinsert()
{
	teacher t,tp;
	fstream obj("teacher.dat",ios::in|ios::binary);
	fstream ob("temp.dat",ios::out|ios::binary);
	cout<<"\nEnter new record : ";
	tp.input();
	while(obj.read((char*)&t,sizeof(t)))
	{
		if(t.rettno()<tp.rettno())
			ob.write((char*)&t,sizeof(t));
		else
			break;
	}
	ob.write((char*)&tp,sizeof(tp));
	if(!obj.eof())
		ob.write((char*)&t,sizeof(t));
	while(obj.write((char*)&t,sizeof(t)))
	{
		ob.write((char*)&t,sizeof(t));
	}
	obj.close();
	ob.close();
	remove("teacher.dat");
	rename("temp.dat","teacher.dat");
}
void tmodify()
{
	fstream obj("teacher.dat",ios::in|ios::out|ios::binary);
	teacher t;
	int no,flag=0,rec=0;
	cout<<"\nEnter the teacher number to be deleted : ";
	cin>>no;
	while(obj.read((char*)&t,sizeof(t)))
	{
		rec++;
		if(no==t.rettno())
		{
			flag=1;
			cout<<"\nOld data: ";
			t.output();
			cout<<"\nNew data : ";
			t.input();
			obj.seekg((rec-1)*sizeof(t),ios::beg);
			obj.write((char*)&t,sizeof(t));
		}
	}
	obj.close();
	if(flag==0)
		cout<<"\nRecord not found";
}
void teachers()
{
	int choice;
	char ch;
	teacher t;
	do
	{
		clrscr();
		cout<<"\n1. Add new data at the end of old data";
		cout<<"\n2. Display all records";
		cout<<"\n3. Delete any record";
		cout<<"\n4. Search any record";
		cout<<"\n5. Insert any record in between stored record";
		cout<<"\n6. Modify any record";
		cout<<"\nEnter your choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1 :twrite();
				break;
			case 2 :tread();
				break;
			case 3 :tdelete();
				break;
			case 4 :tsearch();
				break;
			case 5 :tinsert();
				break;
			case 6 :tmodify();
				break;
		}
		cout<<"\nIf you want to continue then press 'Y'";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
}
class student
{
	int regno,sage,std;
	char sname[100],sgender,sdoj[20],sdob[20],sadd[100],fname[100];
	char mname[100];
	long int spno;
	float marks[5],total,perc,fee,rfee;
public:
	student()
	{
		if(std==1)
			rfee=fee=15000;
		else if(std==2)
			rfee=fee=20000;
		else if(std==3)
			rfee=fee=25000;
		else if(std==4)
			rfee=fee=30000;
		else if(std==5)
			rfee=fee=32000;
		else if(std==6)
			rfee=fee=35000;
		else if(std==7)
			rfee=fee=37000;
		else if(std==8)
			rfee=fee=40000;
		else if(std==9)
			rfee=fee=42000;
		else if(std==10)
			rfee=fee=45000;
		else if(std==11)
			rfee=fee=48000;
		else
			rfee=fee=50000;
	}
	void input()
	{
		cout<<"             ENTER THE DETAILS OF STUDENT";
		cout<<"\nRegestration number : ";
		cin>>regno;
		cout<<"\nName : ";
		gets(sname);
		cout<<"\nClass : ";
		cin>>std;
		cout<<"\nFather name : ";
		gets(fname);
		cout<<"\nMother name : ";
		gets(mname);
		cout<<"\nAge : ";
		cin>>sage;
		cout<<"\nDate of birth (DD/MM/YYYY) : ";
		gets(sdob);
		cout<<"\nDate of joining (DD/MM/YYYY) : ";
		gets(sdoj);
		cout<<"\nAddress : ";
		gets(sadd);
		cout<<"\nGender (M/F) : ";
		cin>>sgender;
		cout<<"\nMarks : ";
		total=0;
			for(int i=0; i<5; i++)
			{
				cin>>marks[i];
				total+=marks[i];
			}
		perc=total/5;
		cout<<"\nPhone number : ";
		cin>>spno;
	}
	void srfee()
	{
		cout<<rfee;
	}
	float dfee(float x)
	{
		rfee-=x;
		return rfee;
	}
	float retfee()
	{
		return fee;
	}
	void feed()
	{
		cout<<regno<<"\t"<<sname<<"\t"<<fee<<"\t"<<rfee<<endl;
	}
	void output()
	{
		cout<<regno<<" : "<<sname<<" : "<<std<<" : "<<sage<<" : "<<fname;
		cout<<" : "<<mname<<" : "<<sdob<<" : "<<sdoj<<" : ";
		cout<<sgender<<" : "<<sadd<<" : ";
		for(int i=0; i<5; i++)
			cout<<"\n"<<marks[i]<<" ";
		cout<<": "<<total<<" : "<<perc<<" : "<<fee;
	}
	int retregno()
	{
		return regno;
	}
	char *retname()
	{
		return sname;
	}
	int retstd()
	{
		return std;
	}
	void result()
	{
		cout<<regno<<"\t"<<sname<<"\t";
		for(int i=0;i<5;i++)
			cout<<marks[i]<<"  ";
		cout<<"\t"<<total<<"\t"<<perc<<"%"<<endl;
	}
};
void swrite()
{
	student st;
	st.input();
	fstream obj("student.dat",ios::app|ios::binary);
	obj.write((char*)&st,sizeof(st));
	obj.close();
}
void sread()
{
	student st;
	fstream obj("student.dat",ios::in|ios::binary);
	while(obj.read((char*)&st,sizeof(st)))
	{
		st.output();
	}
	obj.close();
}
void sdelete()
{
	fstream obj("student.dat",ios::in|ios::binary);
	fstream ob("temp.dat",ios::out|ios::binary);
	student st;
	int flag=0,no;
	cout<<"\nEnter the regestration number to be deleted : ";
	cin>>no;
	while(obj.read((char*)&st,sizeof(st)))
	{
		if(no!=st.retregno())
			ob.write((char*)&st,sizeof(st));
		else
			flag=1;
	}
	obj.close();
	ob.close();
	if(flag==0)
		cout<<"\nRecord not found";
	remove("student.dat");
	rename("temp.dat","student.dat");
}
void sname()
{
	int flag=0;
	char n[100];
	fstream obj("student.dat",ios::in|ios::binary);
	student st;
	cout<<"\nEnter student name : ";
	gets(n);
	while(obj.read((char*)&st,sizeof(st)))
	{
		if(strcmpi(n,st.retname())==0)
		{
			st.output();
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\nRecord not found";
	obj.close();
}
void snumber()
{
	int flag=0,no;
	fstream obj("student.dat",ios::in|ios::binary);
	student st;
	cout<<"\nEnter regestration number : ";
	cin>>no;
	while(obj.read((char*)&st,sizeof(st)))
	{
		if(no==st.retregno())
		{
			st.output();
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\nRecord not found";
	obj.close();
}
void ssearch()
{
	int choice;
	cout<<"\n1. Search by name";
	cout<<"\n2. Search by regestration number";
	cout<<"\nEnter your choice : ";
	cin>>choice;
	switch(choice)
	{
		case 1 :sname();
			break;
		case 2 :snumber();
	}
}
void sinsert()
{
	student st,s;
	fstream obj("student.dat",ios::in|ios::binary);
	fstream ob("temp.dat",ios::out|ios::binary);
	cout<<"\nEnter new record : ";
	s.input();
	while(obj.read((char*)&st,sizeof(st)))
	{
		if(st.retregno()<s.retregno())
			ob.write((char*)&st,sizeof(st));
		else
			break;
	}
	ob.write((char*)&s,sizeof(s));
	if(!obj.eof())
		ob.write((char*)&st,sizeof(st));
	while(obj.write((char*)&st,sizeof(st)))
	{
		ob.write((char*)&st,sizeof(st));
	}
	obj.close();
	ob.close();
	remove("student.dat");
	rename("temp.dat","student.dat");
}
void smodify()
{
	fstream obj("student.dat",ios::in|ios::out|ios::binary);
	student st;
	int no,flag=0,rec=0;
	cout<<"\nEnter the regestration number to be deleated : ";
	cin>>no;
	while(obj.read((char*)&st,sizeof(st)))
	{
		rec++;
		if(no==st.retregno())
		{
			flag=1;
			cout<<"\nOld data: ";
			st.output();
			cout<<"\nNew data : ";
			st.input();
			obj.seekg((rec-1)*sizeof(st),ios::beg);
			obj.write((char*)&st,sizeof(st));
		}
	}
	obj.close();
	if(flag==0)
		cout<<"\nRecord not found";
}
void students()
{
	int choice;
	char ch;
	student st;
	do
	{
		clrscr();
		cout<<"\n1. Add new data at the end of old data";
		cout<<"\n2. Display all records";
		cout<<"\n3. Delete any record";
		cout<<"\n4. Search any record";
		cout<<"\n5. Insert any record in between stored record";
		cout<<"\n6. Modify any record";
		cout<<"\nEnter your choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1 :swrite();
				break;
			case 2 :sread();
				break;
			case 3 :sdelete();
				break;
			case 4 :ssearch();
				break;
			case 5 :sinsert();
				break;
			case 6 :smodify();
				break;
		}
		cout<<"\nIf you want to continue then press 'Y'";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
}
class helper
{
	int hno,hage;
	float hsalary;
	char hname[100],hgender,hdoj[20],hdob[20],hquf[50],hadd[100];
	long int hpno;
public:
	void input()
	{
		cout<<"        ENTER THE DETAILS OF HELPING STAFF";
		cout<<"\nHelper number : ";
		cin>>hno;
		cout<<"\nName : ";
		gets(hname);
		cout<<"\nAge : ";
		cin>>hage;
		cout<<"\nDate of birth (DD/MM/YYYY) : ";
		gets(hdob);
		cout<<"\nDate of joining (DD/MM/YYYY) : ";
		gets(hdoj);
		cout<<"\nAddress : ";
		gets(hadd);
		cout<<"\nGender (M/F) : ";
		cin>>hgender;
		cout<<"\nPhone number : ";
		cin>>hpno;
		cout<<"\nEducational qualifications : ";
		gets(hquf);
		cout<<"\nSalary per month : ";
		cin>>hsalary;
	}
	void hsal()
	{
		cout<<hno<<"\t"<<hname<<"\t"<<hsalary<<endl;
	}
	void output()
	{
		cout<<hno<<"  "<<hname<<"  "<<hage<<"  "<<hdob<<"  "<<hdoj<<"  ";
		cout<<hgender<<"  "<<hquf<<"  "<<hadd<<"  "<<hpno;
	}
	int rethno()
	{
		return hno;
	}
	char *retname()
	{
		return hname;
	}
};
void hwrite()
{
	helper h;
	h.input();
	fstream obj("helper.dat",ios::app|ios::binary);
	obj.write((char*)&h,sizeof(h));
	obj.close();
}
void hread()
{
	helper h;
	fstream obj("helper.dat",ios::in|ios::binary);
	while(obj.read((char*)&h,sizeof(h)))
	{
		h.output();
	}
	obj.close();
}
void hdelete()
{
	fstream obj("helper.dat",ios::in|ios::binary);
	fstream ob("temp.dat",ios::out|ios::binary);
	helper h;
	int flag=0,no;
	cout<<"\nEnter the teacher number to be deleted : ";
	cin>>no;
	while(obj.read((char*)&h,sizeof(h)))
	{
		if(no!=h.rethno())
			ob.write((char*)&h,sizeof(h));
		else
			flag=1;
	}
	obj.close();
	ob.close();
	if(flag==0)
		cout<<"\nRecord not found";
	remove("helper.dat");
	rename("temp.dat","helper.dat");
}
void hnames()
{
	char n[100];
	int flag=0;
	fstream obj("helper.dat",ios::in|ios::binary);
	helper h;
	cout<<"\nEnter helper name : ";
	gets(n);
	while(obj.read((char*)&h,sizeof(h)))
	{
		if(strcmpi(n,h.retname())==0)
		{
			h.output();
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\nRecord not found";
	obj.close();
}
void hnumbers()
{
	int no, flag=0;
	fstream obj("helper.dat",ios::in|ios::binary);
	helper h;
	cout<<"\nEnter helper number : ";
	cin>>no;
	while(obj.read((char*)&h,sizeof(h)))
	{
		if(no==h.rethno())
		{
			h.output();
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\nRecord not found";
	obj.close();
}
void hinsert()
{
	helper h,hp;
	fstream obj("helper.dat",ios::in|ios::binary);
	fstream ob("temp.dat",ios::out|ios::binary);
	cout<<"\nEnter new record : ";
	hp.input();
	while(obj.read((char*)&h,sizeof(h)))
	{
		if(h.rethno()<hp.rethno())
			ob.write((char*)&h,sizeof(h));
		else
			break;
	}
	ob.write((char*)&hp,sizeof(hp));
	if(!obj.eof())
		ob.write((char*)&h,sizeof(h));
	while(obj.write((char*)&h,sizeof(h)))
	{
		ob.write((char*)&h,sizeof(h));
	}
	obj.close();
	ob.close();
	remove("helper.dat");
	rename("temp.dat","helper.dat");
}
void hmodify()
{
	fstream obj("helper.dat",ios::in|ios::out|ios::binary);
	helper h;
	int no,flag=0,rec=0;
	cout<<"\nEnter the helper number to be modified : ";
	cin>>no;
	while(obj.read((char*)&h,sizeof(h)))
	{
		rec++;
		if(no==h.rethno())
		{
			flag=1;
			cout<<"\nOld data: ";
			h.output();
			cout<<"\nNew data : ";
			h.input();
			obj.seekg((rec-1)*sizeof(h),ios::beg);
			obj.write((char*)&h,sizeof(h));
		}
	}
	obj.close();
	if(flag==0)
		cout<<"\nRecord not found";
}
void helpers()
{
	int choice,c;
	char ch;
	helper h;
	do
	{
		clrscr();
		cout<<"\n1. Add new data at the end of old data";
		cout<<"\n2. Display all records";
		cout<<"\n3. Delete any record";
		cout<<"\n4. Search any record";
		cout<<"\n5. Insert any record in between stored record";
		cout<<"\n6. Modify any record";
		cout<<"\nEnter your choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1 :hwrite();
				break;
			case 2 :hread();
				break;
			case 3 :hdelete();
				break;
			case 4 :clrscr();
				cout<<"\n1. Search by name";
				cout<<"\n2. Search by helper number";
				cout<<"\nEnter your choice : ";
				cin>>c;
				switch(c)
				{
					case 1 :hnames();
						break;
					case 2 :hnumbers();
				}
				break;
			case 5 :hinsert();
				break;
			case 6 :hmodify();
				break;
		}
		cout<<"\nIf you want to continue then press 'Y'";
		cin>>ch;
	}while(ch=='y'||ch=='Y');
}
void teasal()
{
	teacher t;
	fstream obj("teacher.dat",ios::in|ios::binary);
	while(obj.read((char*)&t,sizeof(t)))
	{
		t.st();
	}
}
void teasub()
{
	teacher t;
	fstream obj("teacher.dat",ios::in|ios::binary);
	while(obj.read((char*)&t,sizeof(t)))
	{
		t.sut();
	}
}
void stufee()
{
	int no;
	float am;
	student st;
	fstream obj("student.dat",ios::in|ios::binary);
	while(obj.read((char*)&st,sizeof(st)))
	{       cout<<"\nRegestration number : ";
		cin>>no;
		if(no==st.retregno())
		{
			lb:
			cout<<"\nEnter the amount you wamt to deposit : ";
			cin>>am;
			if(am==st.retfee())
			{
				cout<<"\nFee deposited";
				st.dfee(am);
			}
			else if(am>st.retfee())
			{
				cout<<"\nAmount is more than the fee ";
				goto lb;
			}
			else
			{
				st.dfee(am);
				cout<<"\nAmount deposited";
				cout<<"\nRemaining amount : ";
				st.srfee();
			}
		}
	}
}
void stures()
{
	student st;
	int c,flag=0;
	fstream obj("student.dat",ios::in|ios::binary);
	cout<<"\nEnter the class whose result you want to see : ";
	cin>>c;
	while(obj.read((char*)&st,sizeof(st)))
	{
		if(c==st.retstd())
		{
			st.result();
			flag=1;
		}
	}
	if(flag==0)
		cout<<"\nNo record in that class";
}
void stfee()
{
	student st;
	fstream obj("student.dat",ios::in|ios::binary);
	int no,flag=0;
	cout<<"\nEnter the regestration number you want to see : ";
	cin>>no;
	while(obj.read((char*)&st,sizeof(st)))
	{
		if(no==st.retregno())
		{
			flag=1;
			st.feed();
		}
	}
	if(flag==0)
		cout<<"\nNo record";
}
void teac()
{
	clrscr();
	int choice;
	cout<<"\n1. Salary details";
	cout<<"\n2. Subject details";
	cout<<"\nEnter your choice : ";
	cin>>choice;
	switch(choice)
	{
		case 1 :teasal();
			break;
		case 2 :teasub();
	}
}
void stu()
{
	clrscr();
	int choice;
	cout<<"\n1. Fee details";
	cout<<"\n2. Deposit fee";
	cout<<"\n3. Classwise result details";
	cout<<"\nEnter your choice : ";
	cin>>choice;
	switch(choice)
	{
		case 1 :stfee();
			break;
		case 2 :stufee();
			break;
		case 3 :stures();
	}
}
void hel()
{
	clrscr();
	helper h;
	fstream obj("helper.dat",ios::in|ios::binary);
	while(obj.read((char*)&h,sizeof(h)))
	{
		h.hsal();
	}
}
void office()
{
	int choice;
	char ch;
	do
	{
		clrscr();
		cout<<"\n1. Teacher ";
		cout<<"\n2. Student ";
		cout<<"\n3. Salary details of helper";
		cout<<"\nEnter your choice : ";
		cin>>choice;
		switch(choice)
		{
			case 1 :teac();
				break;
			case 2 :stu();
				break;
			case 3 :hel();
		}
	}while(ch=='y'||ch=='Y');
}
void salient()
{
	clrscr();
	cout<<"\n* Convinence facility";
	cout<<"\n* Quality education ";
	cout<<"\n* Good environment";
	cout<<"\n* High tech classroom";
	cout<<"\n* Experienced teachers";
	cout<<"\n* Personal attention on each student";
}
void main()
{
	clrscr();
	int choice,i=0;
	char ch,c;
	char pass[100];
	cout<<"\nEnter password : ";
	while(c!=13)
	{
		c=getch();
		cout<<"*";
		pass[i++]=c;
	}
	pass[--i]='\0';
	if(strcmp(pass,"12345")==0)
	{
		do
		{
			clrscr();
			cout<<"\n\t\t\tWELCOME TO SCHOOL MANAGEMENT SYSTEM";
			cout<<"\n1. Work with teachers";
			cout<<"\n2. Work with students";
			cout<<"\n3. Work with helpers";
			cout<<"\n4. Office administration";
			cout<<"\n5. salient features ";
			cout<<"\n6. Exit";
			cout<<"\nEnter your choice : ";
			cin>>choice;
			switch(choice)
			{
				case 1 :teachers();
					break;
				case 2 :students();
					break;
				case 3 :helpers();
					break;
				case 4 :office();
					break;
				case 5 :salient();
					break;
				case 6 :exit(0);
			}
			cout<<"\nWant to work more with this software.....";
			cin>>ch;
		}while(ch=='y'||ch=='Y');
	}
	else
		cout<<"\n\aWrong password\Try other time";
	getch();
}
