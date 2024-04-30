#include "FileStream.h"
#include <fstream>

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

 unordered_map<int, User> FileStream::read()
{
    ifstream inUS("UserData.txt");
    ifstream inTR("TransactionsData.txt");
   unordered_map<int, User> users;
    string name, pass,date,time,type;

    double balance, TransferAmount;
    int len , id,sen, res;
    while (!inUS.eof())
    {
        stack<Transaction> transactions,turnTransactions;

        inUS >> id >> name >> pass >> balance >> len;
        if(id <0){
            continue;
        }
        for (int i = 0; i < len; i++)
        {
            inTR >> sen >> res >> TransferAmount>>type>>date;
            transactions.push(Transaction(TransferAmount,sen,res,type, FileStream::fromFile(date)));
        }
        while (!transactions.empty())
        {
            turnTransactions.push(transactions.top());
            transactions.pop();

        }
        users[id]=User(FileStream::fromFile(name),fromFile(pass),balance,turnTransactions);

    }
    return users;
}

void FileStream::write( unordered_map<int, User> users)
{
    ofstream us("UserData.txt");
    ofstream tr("TransactionsData.txt");

    for (auto it : users)
    {
        us << endl <<it.first<<" "<< FileStream::toFile(it.second.getUsername()) << " " << it.second.getPassword() << " " << it.second.getBalance() << " " << it.second.getHistory().size();
        stack<Transaction> t = it.second.getHistory();
        while (!t.empty())
        {
            tr << t.top().getSender() << " " << t.top().getReciever() << " " << t.top().getAmount() <<" "<<t.top().getTransacType() << " " << FileStream::toFile(t.top().date) << endl;
            t.pop();
        }
    }

}
