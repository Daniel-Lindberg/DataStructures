#include <iostream>
#include <string>
//Authors:Daniel Lindberg, Bao Do, Alex Davis
using namespace std;



struct emails{
        string to;
        string from;
        string message;
};

struct communication{
public:
        string subject;
        int numberOfEmails;
        string email;
        communication* next;
        communication* prev;

};

class Inbox
{
private:
        communication* head;
        communication* tail;

        communication* createNewNode(string sub, communication* n, communication* p){
                communication* newComm = new communication();
                newComm->subject = sub;
                newComm->next = n;
                newComm->prev = p;
                newComm->numberOfEmails = 1;
                return newComm;
        }
public:

        Inbox() {
                head = NULL;
                tail = NULL;
        };
        ~Inbox() { };

        void InsertEmail(string sub)
        {
                communication* temp;
                temp = SearchCommunication(sub);
                if(head==NULL)
                {
                        head = createNewNode(sub,NULL,NULL);
                }
                else if(temp==NULL)
                {
                        temp = createNewNode(sub,head,NULL);
                        head->prev = temp;
                        head = temp;
                }
                else if((temp->next == NULL && temp->prev ==NULL))
                {
                        //If head is not empty and that is it's only type
                        temp->numberOfEmails++;
                }
                else if(temp==head)
                {
                        //if same element added is at front
                        int numOfEmail=temp->numberOfEmails;
                        communication* curr = createNewNode(sub,head->next,NULL);
                        head->next->prev = curr;
                        DeleteCommunication(temp);
                        head = curr;
                        curr->numberOfEmails=numOfEmail+1;
                }
                else
                {
                        int numOfEmail=temp->numberOfEmails;
                        communication* curr = createNewNode(sub,head,NULL);
                        head->prev = curr;
                        head = curr;
                        DeleteCommunication(temp);
                        curr->numberOfEmails=numOfEmail+1;
                }
        }
        void DeleteCommunication(communication* temp)
        {
                if(temp->next != NULL && temp->prev !=NULL){
                                        temp->prev->next = temp->next;
                                        temp->next->prev = temp->prev;
                }
                else if(temp->prev==NULL && temp->next!=NULL){
                                        temp->next->prev = temp->prev;
                }
                else if(temp->next==NULL && temp->prev!=NULL){
                                        temp->prev->next = temp->next;
                }
                temp->subject="";
                temp->prev = NULL;
                temp->next=NULL;
                delete temp;
                temp=NULL;


        };
        communication* SearchCommunication(string sub){
                communication* temp;
                temp = head;
                while(temp != NULL){
                        if(sub == temp->subject){
                                return temp;
                        }
                        else
                        {
                                temp = temp->next;
                        }
                }
                return NULL;
        };
        void DisplayInbox(){
                int count=0;
                communication* temp;
                temp = head;
                while(temp != NULL){
                        cout << temp->subject << "-" << temp->numberOfEmails<<endl;
                        count = count + temp->numberOfEmails;
                        temp=temp->next;
                }
                cout << "The amount in your inbox is: " << count << endl;


        };
};


int main()
{

        Inbox inbox;
        string Email;
        while (Email != "done")
        {
        	getline(cin,Email);
        	if (Email != "done"){
        	inbox.InsertEmail(Email);
        	}
        }
        inbox.DisplayInbox();
        return 0;
}
