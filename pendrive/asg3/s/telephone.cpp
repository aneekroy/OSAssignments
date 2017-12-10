#include<bits/stdc++.h>

using namespace std;

Queue<string> message_q;
int max_limit;

class caller{
	
private:
	string message;

public :
	caller(string str){

		message = str;
	}

	void send(){
		
		cout<<"enter id of reciever"<<endl;
		scanf("%d",id);
		int c = search(id);
		if(c==-1)
			cout<<"id not found"<<endl;
		else{
			if(message_q.size()==max_limit)
				wait();
			else	
				message_q.push_front(message);
			id_pool[id].receive(message);

		}
	}

}


class receiver{


	private : 

		string mess;
	
	public :

		

	
