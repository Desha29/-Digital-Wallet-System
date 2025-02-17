#include "FileStream.h"
#include <fstream>
#include<queue>
string FileStream::toFile(string name)
{
    for (int i = 0; i < name.size(); i++)
    {
        if (name[i] == ' ')
        {

            name[i] = ',';
        }
    }
    return name;
}

string FileStream::fromFile(string name)
{
    for (int i = 0; i < name.size(); i++)
    {
        if (name[i] == ',')
        {

            name[i] = ' ';
        }
    }
    return name;
}

vector<unordered_map<int, User>> FileStream::read()
{
 try{
     ifstream inUS("UserData.txt");
     ifstream inTR("TransactionsData.txt");
     ifstream inRE("RequestsData.txt");
     ifstream inRH("RequestsHistory.txt");
     ifstream inDeletedUS("UserDeletedData.txt");
     if (!inUS || !inTR || !inRE || !inRH || !inDeletedUS) {
         throw runtime_error("Failed to open one or more input files.");

     }

     vector<unordered_map<int, User>> allUsers;
     unordered_map<int, User> users;
     unordered_map<int, User> Deletedusers;
     string name, pass,date,type,dateRequest,state;

     double balance, TransferAmount,amount,incomes, outcomes;
     int lenTransaction,lenRequest,lenRequestsHistory,sender_id,reciever_id,request_id, id,sen, res;
     bool suspended;
     while (!inUS.eof())
     {
        stack<Transaction> transactions,turnTransactions;
        queue<Request> requests;
        queue<Request> requestsHistory;
        inUS >> id >> name >> pass >> balance>>incomes>>outcomes >> lenTransaction>>lenRequest>>lenRequestsHistory>>suspended;
        if(id <0){
            continue;
        }
        for (int i = 0; i < lenTransaction; i++)
        {
           inTR >> sen >> res >> TransferAmount >> type >> date;


            transactions.push(Transaction(TransferAmount,sen,res,type, FileStream::fromFile(date)));
        }
        while (!transactions.empty())
        {
            turnTransactions.push(transactions.top());
            transactions.pop();

        }
        for (int i = 0; i < lenRequest; i++)
        {
            inRE >>request_id  >> sender_id >> reciever_id >> amount>>state>>dateRequest;
            requests.push(Request(request_id,sender_id,reciever_id,amount,FileStream::fromFile(dateRequest),state));

        }
        for (int i = 0; i < lenRequestsHistory; i++)
        {

            inRH >>request_id >> sender_id >> reciever_id >> amount>>state>>dateRequest;
            requestsHistory.push(Request(request_id,sender_id,reciever_id,amount,FileStream::fromFile(dateRequest),state));


        }
        users[id]=User(suspended,FileStream::fromFile(name),fromFile(pass),balance,incomes,outcomes,turnTransactions,requests,requestsHistory);
        id=-1;
     }

     while (!inDeletedUS.eof())
     {

        inDeletedUS >> id >> name >> pass >> balance;
        if (id < 0) {
            continue;
        }
        Deletedusers[id] = User(FileStream::fromFile(name), fromFile(pass), balance);
     }

     allUsers.push_back(users);
     allUsers.push_back(Deletedusers);

     // Close files
     inUS.close();
     inTR.close();
     inRE.close();
     inRH.close();
     inDeletedUS.close();

     return allUsers;
    } catch (const exception& e) {
     cerr << "Exception occurred: " << e.what() <<endl;
     return {};
    }
}

void FileStream::write( unordered_map<int, User> users, unordered_map<int, User> deletedUsers)
{
try{
    ofstream us("UserData.txt");
    ofstream tr("TransactionsData.txt");
    ofstream re("RequestsData.txt");
    ofstream rh("RequestsHistory.txt");
    ofstream usDeleted("UserDeletedData.txt");
    if (!us || !tr || !re || !rh || !usDeleted) {
        throw runtime_error("Failed to open one or more output files.");
    }
    for (auto it : deletedUsers)
    {
        usDeleted  << it.first << " " << FileStream::toFile(it.second.getUsername()) << " " << it.second.getPassword() << " " << it.second.getBalance()<< endl;


    }
    for (auto it : users)
    {
        us << endl <<it.first<<" "<< FileStream::toFile(it.second.getUsername()) << " " << it.second.getPassword() << " " << it.second.getBalance()<<" "<<it.second.getIncomes()<<" "<<it.second.getExpenses() << " " << it.second.getHistory().size()<< " " << it.second.getRequests().size()<< " " << it.second.getRequestsHistory().size()<<" "<<it.second.getSuspended();
        stack<Transaction> t = it.second.getHistory();
        queue<Request> r = it.second.getRequests();
        queue<Request> rH = it.second.getRequestsHistory();
        while ((!t.empty())||(!r.empty())||(!rH.empty()))
        {

            if(!t.empty()){
                tr << t.top().getSender() << " " << t.top().getReciever() << " " << t.top().getAmount() <<" "<<t.top().getTransacType() << " " << FileStream::toFile(t.top().date) << endl;
                t.pop();
            }
            if(!r.empty()){
                re<<r.front().getID()<<" "<<r.front().getSender()<<" "<<r.front().getReciever()<<" "<<r.front().getAmount()<<" "<<r.front().getStatusRequest()<<" "<<FileStream::toFile(r.front().getDate())<<endl;
                r.pop();
            }
            if(!rH.empty()){
                rh<<rH.front().getID()<<" "<<rH.front().getSender()<<" "<<rH.front().getReciever()<<" "<<rH.front().getAmount()<<" "<<rH.front().getStatusRequest()<<" "<<FileStream::toFile(rH.front().getDate())<<endl;
                rH.pop();
            }

        }
    }
} catch (const exception& e) {
    cerr << "Exception occurred: " << e.what() <<endl;

}

}
