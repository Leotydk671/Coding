#include<iostream>
#include<cstring>
#include<iomanip>

using namespace std;


template<typename P> void my_swap(P& a, P& b)
{
	P c;
	c = a;
	a = b;
	b = c;	
}

class Class;

template<typename T> class Node
{
	private:
		Node<T>* last;
		Node<T>* next;
		T* now;
	public:
		Node(Node<T>* last_ = NULL, Node<T>* next_ = NULL, T* now_ = NULL): last(last_), next(next_)
		{
			if(now_ != NULL) now = new T(*now_);
			else now = NULL;
		}

		~Node()	{ if(now != NULL) delete now;}
		
	template<typename L> friend class List;
	template<typename P> friend void my_swap(P& a, P& b);

};

template<typename L> 
class List
{
	template<typename> friend class List;

	private: 
		Node<L>* head;
		Node<L>* end;
		int Size;
	public:
		List()
		{
			head = new Node<L>;
			end = head;
			Size = 0;	
		}

		~List()
		{
			delete_all();
			delete head;
		}
		
		List(const List<L>& List_)
		{
			head = new Node<L>;
			end = head;

			Node<L>* p = List_.head;
			while(p != List_.end)
			{
				p = p->next;
				add_node(p->now);
			}
		
			Size = List_.Size;
		}

		List<L>& operator=(const List<L>& List_)
		{
			Node<L>* p = List_.head;
			delete_all();

			while(p != List_.end)
			{
				p = p->next;
				add_node(p->now);
			}

			Size = List_.Size;
			return *this;
		}
		
		bool operator==(List<L>& List_)
		{
			Node<L>* p1 = head;
			Node<L>* p2 = List_.head;

			if(Size != List_.Size)
			while(p1 != end && p2 != List_.end)
			{
				p1 = p1->next;
				p2 = p2->next;
				if(p1->now != p2->now) return false;
			}
			if((p1 == end && p2 != List_.end) || (p2 == List_.end && p1 != end)) return false;

			return true;
		}
		
		int size()
		{
			return Size;
		}

		void add_node(L* node_p)
		{
			end->next = new Node<L>(end, NULL, node_p);
			end = end->next;
			Size++;
		}

		List<Node<L>*> find_node(const char* idf) const
		{
			List<Node<L>*> p_list;
			Node<L>* p = head;
			//cout<<"Im started\n";
			while(p != end)
			{
				p = p->next;
			       	if(p == NULL || p->now == NULL) cout<<"ERROR!!!\n";	
				if(p->now->is(idf)) p_list.add_node(&p);
			}
			return p_list;
		}

	
		template<typename Tp> void delete_node(const Tp& idf, bool f = true)
		{
			Node<Node<L>*>* f_p;
			List<Node<L>*> f_list = find_node(idf);
			f_p = f_list.head;
			
			if(f_list.size()==0) return;

			while(f_p != f_list.end)
			{
				f_p = f_p->next;
				if(*(f_p->now) == end && (*(f_p->now))->last == head)
				{
					if(f)
						cout << "There is the last one in the list, it will be retained\n";
					else
					{
						delete *(f_p->now);
						end = head;
						head->next = NULL;
						Size--;
					}
					return;
				}
				else
				{	
					(*(f_p->now))->last->next = (*(f_p->now))->next;

					if((*(f_p->now))->next) 
						(*(f_p->now))->next->last = (*(f_p->now))->last;

					if(*(f_p->now) == end) 
						end = (*(f_p->now))->last; 

					delete *(f_p->now);
					Size--;
				}
				
			}
		}
		
		template<typename Tp> 
		void process(const char* idf, void (Class::*func_p)(Tp), Tp tp)
		{
			List<Node<L>*> f_list = find_node(idf);

			if(f_list.size() == 0) return ;

			Node<Node<L>*>* f_p;
			f_p = f_list.head;
	
			while(f_p != f_list.end)
			{
				f_p = f_p->next;
				((*(f_p->now))->now->*func_p)(tp);
			}
		}
		

		void process(void (Class::*func_p)())
		{
			Node<L>* p = head;
			while(p != end)
			{
				p = p->next;
				(p->now->*func_p)();
			}
		}


		void show_list(char* idf) const
		{
			Node<L>* p = head;
			bool f = false;

			while(p != end)
			{
				p = p->next;
				if(p->now->is(idf))
				{
					cout<< *(p->now);
					f = true;
				}
			}
			if(!f) cout<<"there is no eligible student\n";
		}


		void show_list() const
		{
			Node<L>* p = head;
			while(p != end)
			{
				p = p->next;
				cout<< *(p->now);
			}
		}

		void sort_list()
		{
			for(Node<L>* p1 = head->next; p1 != end && p1; p1 = p1->next)
			{
				for(Node<L>* p2 = p1->next; p2; p2 = p2->next)
				{
					if(*(p2->now) < *(p1->now)) my_swap(p1->now, p2->now);
				}
			}
		}

		void delete_all()
		{
			while(end != head)
			{
				end = end->last;
				delete end->next;
			}
			Size = 0;
		}

};

class Student
{
	private:
		char* id;
		char* cid;
		char* name;
		float score1;
		float score2;
		float score3;
		float score_sum;
	public:
		Student() : score1(0), score2(0), score3(0)
		{
			id = new char[5];
			strcpy(id, "NULL");

			cid = new char[5];
			strcpy(cid, "NULL");

			name = new char[5];
			strcpy(name, "NULL");

			score_sum = 0;
		}

		Student(const char* id_, const char* cid_, const char* name_, float score1_, float score2_, float score3_)
		       : score1(score1_), score2(score2_), score3(score3_)	
		{
			id = new char[strlen(id_) + 1];
			strcpy(id, id_);
			
			cid = new char[strlen(cid_) + 1];
			strcpy(cid, cid_);

			name = new char[strlen(name_) + 1];
			strcpy(name, name_);

			score_sum = score1 + score2 + score3;			
		}

		Student(const Student & s) : score1(s.score1), score2(s.score2), score3(s.score3), score_sum(s.score_sum)
		{
			id = new char[strlen(s.id) + 1];
			strcpy(id, s.id);

			cid = new char[strlen(s.cid) + 1];
			strcpy(cid, s.cid);

			name = new char[strlen(s.name) + 1];
			strcpy(name, s.name);
		}

		Student & operator=(const Student & s)
		{
			if(this == &s)
				return *this;

			score1 = s.score1;
			score2 = s.score2;
			score3 = s.score3;
			score_sum = s.score_sum;

			delete [] id;
			id = new char[strlen(s.id) + 1];
			strcpy(id, s.id);

			delete [] cid;
			cid = new char[strlen(s.cid) + 1];
			strcpy(cid, s.cid);

			delete [] name;
			name = new char[strlen(s.name) + 1];
			strcpy(name, s.name);

			return *this;
		}

		bool is(const char* idf)
		{
			return strcmp(id, idf)==0 || strcmp(name, idf)==0;
		}

		bool operator==(Student & s)
		{
			return strcmp(id, s.id)==0 && 
				strcmp(name, s.name)==0 && 
				strcmp(cid, s.cid)==0 &&
				score1==s.score1 && 
				score2==s.score2 && 
				score3==s.score3;
		}

		bool operator<(const Student & s)
		{
			int f = strcmp(cid, s.cid);
			if(f <= -1)
				return true;
			else if(f >= 1)
				return false;
			else return score_sum > s.score_sum;
		}

	friend ostream & operator<<(ostream & os, const Student& s)
	{
		os << s.id << ','
		   << s.cid << ','
		   << s.name << ','
		   << s.score1 << ','
		   << s.score2 << ','
		   << s.score3 << ','
		   << s.score_sum << '\n';
		return os;
	}
};


class Class
{
	private:
		char* id;
		List<Student> student_list;
	public:
		Class();
		Class(const char* id_);
		Class(const char* id_, Student s);
		Class(const Class& c);
		
		Class & operator=(const Class & c);
		
		void sort_student();

		void delete_student(char* idf);

		void add_student(Student s);

		bool is(const char* id_);

		bool operator==(Class& c);

		bool operator<(Class& c);

	friend ostream & operator<<(ostream & os, const Class & c);
};


Class::Class() : student_list()
{
	id = new char[5];
	strcpy(id, "NULL");
}

Class::Class(const char* id_) : student_list()
{
	id = new char[strlen(id_) + 1];
	strcpy(id, id_);
}

Class::Class(const char* id_, Student s) : student_list()
{
	student_list.add_node(&s);

	id = new char[strlen(id_) + 1];
	strcpy(id, id_);
}

Class::Class(const Class& c) : student_list(c.student_list)
{
	id = new char[strlen(c.id) + 1];
	strcpy(id, c.id);
}
		
Class & Class::operator=(const Class & c)
{
	if(&c == this)
		return *this;
			
	student_list = c.student_list;

	delete [] id;
	id = new char[strlen(c.id) + 1];
	strcpy(id, c.id);

	return *this;
}
		
void Class::sort_student()
{
	if(student_list.size() > 0) student_list.sort_list();
}

void Class::delete_student(char* idf)
{
	student_list.delete_node(idf, false);
}

void Class::add_student(Student s)
{
	student_list.add_node(&s);
}

bool Class::is(const char* id_)
{
	List<Node<Student>*> f_list = student_list.find_node(id_);
	return strcmp(id, id_) == 0 || f_list.size() > 0;	
}

bool Class::operator==(Class& c)
{
	return strcmp(id, c.id)==0 && student_list == c.student_list;			
}

bool Class::operator<(Class& c)
{
	if(strcmp(id, c.id) == 1)
		return true;
	else return false;
}

ostream & operator<<(ostream & os, const Class & c)
{
	c.student_list.show_list();
	return os;
}


List<Student> all_student_list;
List<Class> all_class_list;

void show_menu()
{
	cout << "1.input\n"
	     << "2.delete\n"
	     << "3.select\n"
	     << "4.order\n"
	     << "5.output\n"
	     << "6.quit\n"
	     << "please input your option\n"; 
}

void to_low(char* str)
{
	int len = strlen(str);
	char ch;
	for(int i=0; i < len; i++)
	{
		ch = str[i];
		if(ch>='A' && ch<='Z') 
			str[i] = ch - 'A' + 'a';
	}
}

void option1()
{
	char id[100];
	char cid[100];
	char name[100];
	float score1;
	float score2;
	float score3;
	cout<<"Id ";
	cin.getline(id, 100);
	cout<<"class ";
	cin.getline(cid, 100);
	cout<<"name ";
	cin.getline(name, 100);
	cout<<"score1 ";
	cin>>score1;
	cout<<"score2 ";
	cin>>score2;
	cout<<"score3 ";
	cin>>score3;
	
	Student s(id, cid, name, score1, score2, score3);
	all_student_list.add_node( &s );
	
	List<Node<Class>*> p = all_class_list.find_node(cid);	
	
	int size = p.size();
	cout<<"size "<<size<<'\n';
	if(size > 1) 
		cout<<"There is something error\n";
	else if(size == 1) 
		all_class_list.process<Student>(cid, &Class::add_student, Student(id, cid, name, score1, score2, score3));
	else if(size == 0)
	{
		Class c(cid, Student(id, cid, name, score1, score2, score3) );
		all_class_list.add_node(&c);
	}	
}

void option2()
{
	char idf[100];
	cin>>idf;
	all_student_list.delete_node(idf);
	all_class_list.process<char*>( idf, &Class::delete_student, idf);
	all_student_list.show_list();
}

void option3()
{
	char idf[100];
	cin>>idf;
	if(strlen(idf) == 2 && idf[0] >= '0' && idf[0] <= '9') all_class_list.show_list(idf);
	else all_student_list.show_list(idf);
}

void option4()
{
	all_student_list.sort_list();
	all_class_list.process( &Class::sort_student);

	all_student_list.show_list();
}

void option5()
{
	all_student_list.show_list();
}

void option_switch()
{
	int opt;
	char ag[5];
	bool flag;
	char ch;
	while(1)
	{
		show_menu();

		while(1)
		{
			if(cin >> opt && opt >= 1 && opt <= 6) break;
			cin.clear();		
			cout << "Wrong input\n";
			cin.ignore(256, '\n');
		}
		cin.ignore(256, '\n');

		flag = 1;
		while(flag)
		{
			switch(opt)
			{
				case 1: option1(); break;
				case 2: option2(); break;
				case 3: option3(); break;
				case 4: option4(); break;
				case 5: option5(); break;
				case 6: return;
			}
			cout<<"continue?\n";

			while(1)
			{
				if(cin>>ag)
				{
					to_low(ag);
					if(strcmp(ag, "no") == 0)
					{
						flag = 0;
						break;
					}
					if(strcmp(ag, "yes") == 0) break;
				}
				cin.clear();
				cout<<"Wrong input\n";
				cin.ignore(256, '\n');
			}
			while(ch = cin.peek())
			{
				cin.get();
				if(ch == '\n') break;
			}		
		}
	}
}

int main()
{
	cout<<setiosflags(ios::fixed)<<setprecision(1);
	option_switch();
	return 0;
}
