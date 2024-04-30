#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include"admin.h"
#include <string>
using namespace std;

void MainWindow:: login(){

    string phone=  ui->LinePhoneNumber->text().toStdString();
    string password=ui->linePassword->text().toStdString();

    if(ui->LinePhoneNumber->text().isEmpty() || password.empty()){
        QMessageBox::warning(this,"Empty input","there is Empty field !!");
    }
    else if( manger.login(stoi(phone),password)!=0){
        User user=manger.getListOfUsers()->at(stoi(phone));
         id=stoi(phone);
        MainWindow::ui->frameLogin->close();
        MainWindow::ui->full_menu_widget->hide();
        MainWindow::ui->stackedWidget->setCurrentIndex(0);
        MainWindow::ui->home_btn2->setChecked(true);
        MainWindow::ui->HomePage->show();
        ui->user_btn->setText(QString::fromStdString(user.getUsername()));
        ui->label_3->setText(QString::fromStdString(user.getUsername()));
        ui->label_6->setText(QString::fromStdString(to_string(user.getBalance())));
        ui->label_93->setText(QString::fromStdString(to_string(user.getBalance())));
        ui->balance_label->setText(QString::fromStdString(to_string(user.getBalance())));
        ui->label_80->setText(QString::fromStdString(to_string(user.getBalance())));
        ui->lineEdit_4->setText(QString::fromStdString(phone));
        ui->lineEdit->setText(QString::fromStdString(user.getUsername()));
        ui->lineEdit_2->setText(QString::fromStdString(user.getPassword()));
         loadTransactions();


    }
    else if(manger.loginAdmin(ui->LinePhoneNumber->text().toStdString(),password)){
        MainWindow::ui->frameLogin->close();
        MainWindow::ui->full_menu_widget_2->hide();
        MainWindow::ui->stackedWidget_2->setCurrentIndex(0);
        MainWindow::ui->users_btn->setChecked(true);
        MainWindow::ui->HomePage_Admin->show();
        loadUsers();




    }
    else {
        QMessageBox::warning(this,"Fail","Invalid Phone Number or Password");
    }


}

void MainWindow::loadUsers()
{
    ui->users_table->setRowCount(0);
    ui->users_table->setRowCount(manger.getListOfUsers()->size());
    ui->users_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int row=0;

    unordered_map<int, User>::iterator pair;
    for (pair = manger.getListOfUsers()->begin(); pair != manger.getListOfUsers()->end(); pair++){
        string id=to_string( pair->first);
        string username= pair->second.getUsername();
        string  balance=to_string( pair->second.getBalance());
        string numberTrans=to_string( pair->second.getHistory().size());
        QTableWidgetItem* user_count=new QTableWidgetItem(QString::fromStdString(to_string(row+1)));
        QTableWidgetItem* user_id=new QTableWidgetItem(QString::fromStdString(id));
        QTableWidgetItem* user_Name=new QTableWidgetItem(QString::fromStdString(username));
        QTableWidgetItem* user_Balance=new QTableWidgetItem(QString::fromStdString(balance));
        QTableWidgetItem* user_NumTransaction=new QTableWidgetItem(QString::fromStdString(numberTrans));
        user_count->setTextAlignment(Qt::AlignCenter);
        user_id->setTextAlignment(Qt::AlignCenter);
        user_Name->setTextAlignment(Qt::AlignCenter);
        user_Balance->setTextAlignment(Qt::AlignCenter);
        user_NumTransaction->setTextAlignment(Qt::AlignCenter);
        ui->users_table->setItem(row,0,user_count);
        ui->users_table->setItem(row,1,user_id);
        ui->users_table->setItem(row,2,user_Name);
        ui->users_table->setItem(row,3,user_Balance);
        ui->users_table->setItem(row,4,user_NumTransaction);
        QString itemText= QString::fromStdString(id);
        ui->comboBox_users->addItem(itemText);
        ui->comboBox_users_2->addItem(itemText);


        ++row;
    }
}

void MainWindow::loadTransactions()
{
 ui->transactions_table_2->setRowCount(0);
     ui->transactions_table_1->setRowCount(0);
    ui->transactions_table_2->setRowCount( manger.getListOfUsers()->at(id).getHistory().size());
    ui->transactions_table_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->transactions_table_1->setRowCount( manger.getListOfUsers()->at(id).getHistory().size());
    ui->transactions_table_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int row=0;
    stack<Transaction> transctions=manger.getListOfUsers()->at(id).getHistory();
    while (!transctions.empty()) {

        string _id=to_string(id);
        string username= manger.getListOfUsers()->at(id).getUsername();
        string  amount= to_string( transctions.top().getAmount());
        string  date=  transctions.top().date;
        string  type=  transctions.top().getTransacType();

        QTableWidgetItem* user_count=new QTableWidgetItem(QString::fromStdString(to_string(row+1)));
        QTableWidgetItem* user_id=new QTableWidgetItem(QString::fromStdString(_id));
        QTableWidgetItem* user_Name=new QTableWidgetItem(QString::fromStdString(username));
        QTableWidgetItem* user_Amount=new QTableWidgetItem(QString::fromStdString(amount));
        QTableWidgetItem* user_Date=new QTableWidgetItem(QString::fromStdString(date));
        QTableWidgetItem* user_type=new QTableWidgetItem(QString::fromStdString(type));

        user_count->setTextAlignment(Qt::AlignCenter);
        user_id->setTextAlignment(Qt::AlignCenter);
        user_Name->setTextAlignment(Qt::AlignCenter);
        user_Amount->setTextAlignment(Qt::AlignCenter);
        user_Date->setTextAlignment(Qt::AlignCenter);
        user_type->setTextAlignment(Qt::AlignCenter);
        ui->transactions_table_2->setItem(row,0,user_count);
        ui->transactions_table_2->setItem(row,1,user_id);
        ui->transactions_table_2->setItem(row,2,user_Name);
        ui->transactions_table_2->setItem(row,3,user_Amount);
        ui->transactions_table_2->setItem(row,4,user_Date);
        ui->transactions_table_2->setItem(row,5,user_type);


        ui->transactions_table_1->setItem(row,0,user_count);
        ui->transactions_table_1->setItem(row,1,user_id);
        ui->transactions_table_1->setItem(row,2,user_Name);
        ui->transactions_table_1->setItem(row,3,user_Amount);
        ui->transactions_table_1->setItem(row,4,user_Date);
        ui->transactions_table_1->setItem(row,5,user_type);
        transctions.pop();
        ++row;
    }
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    manger = Admin();

    ui->setupUi(this);
    ui->frameSignUp->close();
    ui->frameLogin->close();
    ui->HomePage->close();
    ui->HomePage_Admin->close();
    ui->change_btn_3->setVisible(false);
    ui->visible_btn_2->setVisible(false);
    ui->visible_btn_4->setVisible(false);


}

MainWindow::~MainWindow()
{
FileStream::write(*manger.getListOfUsers());
cout<<manger.getListOfUsers()->at(id).getHistory().size();
    delete ui;

}

void MainWindow::on_btnLogin_clicked()
{
   login();

}


void MainWindow::on_btn_ToSignUp_clicked()
{
    MainWindow::ui->LinePhoneNumber->clear();
    MainWindow::ui->linePassword->clear();
    MainWindow::ui->frameLogin->close();
    MainWindow::ui->frameSignUp->show();
}
void MainWindow::on_btn_ToLogin_clicked()
{
    MainWindow::ui->LineUserName_2->clear();
    MainWindow::ui->linePassword_2->clear();
    MainWindow::ui->linePhone->clear();
    MainWindow::ui->frameSignUp->close();
    MainWindow::ui->frameLogin->show();
}
void MainWindow::on_btnSignUp_clicked()
{
    string phone= ui->linePhone->text().toStdString();
    string username=ui->LineUserName_2->text().toStdString();
    string password=ui->linePassword_2->text().toStdString();
    if(ui->linePhone->text().isEmpty()|| username.empty() || password.empty()){
        QMessageBox::warning(this,"Empty input","there is Empty field !!");
    }
    else
    {
        if(manger.signup(stoi( phone),username,password,0.0)){
            MainWindow::ui->frameLogin->show();
            MainWindow::ui->frameSignUp->close();

        }else{

         QMessageBox::warning(this,"Is Exist","Phone Number is exist !!");
        }
    }
}
void MainWindow::on_btnSignUp_1_clicked()
{
    MainWindow::ui->frameLanding->close();
    MainWindow::ui->frameLogin->close();
    MainWindow::ui->frameSignUp->show();
}
void MainWindow::on_btnLogin_1_clicked()
{
    MainWindow::ui->frameLanding->close();
    MainWindow::ui->frameSignUp->close();
    MainWindow::ui->frameLogin->show();
}

// Users Functionalities
void MainWindow::on_search_btn_clicked()
{
    MainWindow::ui->stackedWidget->setCurrentIndex(4);
    QString search_text= ui->search_input->text();
    if(!search_text.isEmpty()){
        ui->label_10->setText(search_text);
    }
    else{
       ui->label_10->setText(ui->search_input->placeholderText());
    }

}


void MainWindow::on_user_btn_clicked()
{
   ui->stackedWidget->setCurrentIndex(5);

}
void MainWindow::on_home_btn1_2_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_home_btn2_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_transaction_btn_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_transaction_btn_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_invoices_btn_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_invoices_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_wallets_btn_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_wallets_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_logout_2_clicked()
{
    ui->frameSignUp->close();
    ui->HomePage->close();
    ui->frameLanding->close();
    ui->LinePhoneNumber->clear();
    ui->linePassword->clear();
    ui->frameLogin->show();
}


void MainWindow::on_logout_clicked()
{
    ui->frameSignUp->close();
    ui->HomePage->close();
    ui->frameLanding->close();
    ui->LinePhoneNumber->clear();
    ui->linePassword->clear();
    ui->frameLogin->show();
}
// the End Users  Functionalities
//************************************************
// Admin  Functionalities
void MainWindow::on_users_btn_clicked()
{
     ui->stackedWidget_2->setCurrentIndex(0);

}


void MainWindow::on_users_btn_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
}


void MainWindow::on_transaction_btn_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(6);
}


void MainWindow::on_transaction_btn_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(6);
}


void MainWindow::on_addUsers_btn_clicked()
{
      ui->stackedWidget_2->setCurrentIndex(1);
}


void MainWindow::on_addUsers_btn_2_clicked()
{
     ui->stackedWidget_2->setCurrentIndex(1);
}


void MainWindow::on_updateUsers_btn_clicked()
{
      ui->stackedWidget_2->setCurrentIndex(2);
    int id= stoi(  ui->comboBox_users->currentText().toStdString());
    string username = manger.getListOfUsers()->at(id).getUsername();
    string password= manger.getListOfUsers()->at(id).getPassword();
    string balance= to_string( manger.getListOfUsers()->at(id).getBalance());
    ui->username_input_2->setText(QString::fromStdString(username) );
    ui->password_input_2->setText(QString::fromStdString(password) );
    ui->balance_input->setText(QString::fromStdString(balance) );
}


void MainWindow::on_updateUsers_btn_2_clicked()
{
   ui->stackedWidget_2->setCurrentIndex(2);
    int id= stoi(  ui->comboBox_users->currentText().toStdString());
    string username = manger.getListOfUsers()->at(id).getUsername();
    string password= manger.getListOfUsers()->at(id).getPassword();
    string balance= to_string( manger.getListOfUsers()->at(id).getBalance());
    ui->username_input_2->setText(QString::fromStdString(username) );
    ui->password_input_2->setText(QString::fromStdString(password) );
    ui->balance_input->setText(QString::fromStdString(balance) );

}


void MainWindow::on_deleteUsers_btn_clicked()
{
      ui->stackedWidget_2->setCurrentIndex(3);
    int id= stoi(  ui->comboBox_users_2->currentText().toStdString());
    string username = manger.getListOfUsers()->at(id).getUsername();
    string password= manger.getListOfUsers()->at(id).getPassword();
    string balance= to_string( manger.getListOfUsers()->at(id).getBalance());
    ui->username_input_3->setText(QString::fromStdString(username) );
    ui->password_input_3->setText(QString::fromStdString(password) );
    ui->balance_input_2->setText(QString::fromStdString(balance) );
}


void MainWindow::on_deleteUsers_btn_2_clicked()
{
   ui->stackedWidget_2->setCurrentIndex(3);
    int id= stoi(  ui->comboBox_users_2->currentText().toStdString());
    string username = manger.getListOfUsers()->at(id).getUsername();
    string password= manger.getListOfUsers()->at(id).getPassword();
    string balance= to_string( manger.getListOfUsers()->at(id).getBalance());
    ui->username_input_3->setText(QString::fromStdString(username) );
    ui->password_input_3->setText(QString::fromStdString(password) );
    ui->balance_input_2->setText(QString::fromStdString(balance) );
}


void MainWindow::on_search_btn_2_clicked()
{
    MainWindow::ui->stackedWidget_2->setCurrentIndex(4);
    QString search_text= ui->search_input_2->text();
    if(!search_text.isEmpty()){
        ui->label_16->setText(search_text);
    }
    else{
        ui->label_16->setText(ui->search_input->placeholderText());
    }
}


void MainWindow::on_user_btn_2_clicked()
{
      ui->stackedWidget_2->setCurrentIndex(5);
}


void MainWindow::on_logout_4_clicked()
{
    ui->frameSignUp->close();
    ui->HomePage->close();
    ui->HomePage_Admin->close();
    ui->frameLanding->close();
    ui->LinePhoneNumber->clear();
    ui->linePassword->clear();
    ui->frameLogin->show();
}


void MainWindow::on_logout_3_clicked()
{
    ui->frameSignUp->close();
    ui->HomePage->close();
    ui->HomePage_Admin->close();
    ui->frameLanding->close();
    ui->LinePhoneNumber->clear();
    ui->linePassword->clear();
    ui->frameLogin->show();
}
// the End Admin  Functionalities

void MainWindow::on_sendMoney_btn_3_clicked()
{
   MainWindow::ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_RecieveMoney_2_btn_clicked()
{
   MainWindow::ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_sendMoney_btn_2_clicked()
{


    string phone  =  ui->recipient_input->text().toStdString();
    string amount = ui->amount_input->text().toStdString();
    if(ui->recipient_input->text().isEmpty() || ui->amount_input->text().isEmpty() ){
        QMessageBox::warning(this,"Empty input","there is Empty field !!");
    }

    else if(manger.getListOfUsers()->find(stoi(phone))==manger.getListOfUsers()->end()){

      QMessageBox::warning(this,"Not Found","User not found !!");

    }
    else{
        if( manger.getListOfUsers()->at(id).sendMoney(id,stoi(phone),stod(amount),manger.getListOfUsers()->at(stoi(phone)))){
   QMessageBox::information(this,"Success","Send Successful");
            ui->recipient_input->clear();
            ui->amount_input->clear();
            double balance=  manger.getListOfUsers()->at(id).getBalance();
            ui->label_6->setText(QString::fromStdString(to_string(balance)));
            ui->label_93->setText(QString::fromStdString(to_string(balance)));
            ui->balance_label->setText(QString::fromStdString(to_string(balance)));
            ui->label_80->setText(QString::fromStdString(to_string(balance)));
            loadTransactions();
        }
        else{
           QMessageBox::information(this,"Not enough","Your balance less than amount");

        }


    }
}


void MainWindow::on_edit_btn_clicked()
{
  ui->lineEdit->setReadOnly(false);
    ui->lineEdit->setAlignment(Qt::AlignLeft);
  ui->lineEdit->setFocus();
  ui->change_btn_3->setVisible(true);
  ui->edit_btn->setVisible(false);
}


void MainWindow::on_edit_btn_2_clicked()
{

    ui->lineEdit_2->setReadOnly(false);
    ui->lineEdit_2->setEchoMode(QLineEdit::EchoMode::Normal);
    ui->lineEdit_2->setAlignment(Qt::AlignLeft);
    ui->lineEdit_2->setFocus();
    ui->change_btn_3->setVisible(true);
    ui->edit_btn_2->setVisible(false);
}


void MainWindow::on_change_btn_3_clicked()
{
    if(ui->lineEdit->text().isEmpty()||ui->lineEdit_2->text().isEmpty()){
         QMessageBox::warning(this,"Empty input","there is Empty field !!");
    }else if (ui->lineEdit_2->text().length()<6) {
        QMessageBox::warning(this,"Invalid lenght","Your password less than 6 characters !!");
    }else{

        manger.updateProfile(id,ui->lineEdit->text().toStdString(),ui->lineEdit_2->text().toStdString());

        ui->user_btn->setText(ui->lineEdit->text());
        ui->label_3->setText(ui->lineEdit->text());
        ui->lineEdit->setReadOnly(true);
        ui->lineEdit->setAlignment(Qt::AlignCenter);
        ui->lineEdit_2->setReadOnly(true);
        ui->lineEdit_2->setAlignment(Qt::AlignCenter);
        ui->lineEdit_2->setEchoMode(QLineEdit::EchoMode::Password);
        ui->change_btn_3->setVisible(false);
        ui->edit_btn->setVisible(true);
        ui->edit_btn_2->setVisible(true);

    }

}


void MainWindow::on_add_btn_clicked()
{
    string phone= ui->phone_input_3->text().toStdString();
    string username=ui->username_input->text().toStdString();
    string password=ui->password_input->text().toStdString();
    string balance=ui->balace_input->text().toStdString();
    if(phone.empty() || username.empty() || password.empty() || balance.empty()){
        QMessageBox::warning(this,"Empty input","there is Empty field !!");
    }
    else
    {
        if(manger.signup(stoi( phone),username,password,stod(balance))){
             QMessageBox::information(this,"Success","Adding Successful");
              ui->phone_input_3->clear();
            ui->username_input->clear();
           ui->password_input->clear();
            ui->balace_input->clear();
            loadUsers();
        }else{

            QMessageBox::warning(this,"Is Exist","Phone Number is exist !!");
        }
    }

}


void MainWindow::on_visible_btn_clicked()
{
    ui->linePassword->setEchoMode(QLineEdit::EchoMode::Normal);
     ui->visible_btn->setVisible(false);
     ui->visible_btn_2->setVisible(true);
}


void MainWindow::on_visible_btn_2_clicked()
{
    ui->linePassword->setEchoMode(QLineEdit::EchoMode::Password);
    ui->visible_btn->setVisible(true);
    ui->visible_btn_2->setVisible(false);
}


void MainWindow::on_visible_btn_3_clicked()
{
    ui->linePassword_2->setEchoMode(QLineEdit::EchoMode::Normal);
    ui->visible_btn_3->setVisible(false);
    ui->visible_btn_4->setVisible(true);
}


void MainWindow::on_visible_btn_4_clicked()
{
    ui->linePassword_2->setEchoMode(QLineEdit::EchoMode::Password);
    ui->visible_btn_3->setVisible(true);
    ui->visible_btn_4->setVisible(false);
}


void MainWindow::on_comboBox_users_currentTextChanged(const QString &arg1)
{
     int id= stoi(  ui->comboBox_users->currentText().toStdString());
     string username = manger.getListOfUsers()->at(id).getUsername();
     string password= manger.getListOfUsers()->at(id).getPassword();
     string balance= to_string( manger.getListOfUsers()->at(id).getBalance());
     ui->username_input_2->setText(QString::fromStdString(username) );
     ui->password_input_2->setText(QString::fromStdString(password) );
     ui->balance_input->setText(QString::fromStdString(balance) );

}


void MainWindow::on_comboBox_users_2_currentTextChanged(const QString &arg1)
{
    int id= stoi(  ui->comboBox_users_2->currentText().toStdString());
    string username = manger.getListOfUsers()->at(id).getUsername();
    string password= manger.getListOfUsers()->at(id).getPassword();
    string balance= to_string( manger.getListOfUsers()->at(id).getBalance());
    ui->username_input_3->setText(QString::fromStdString(username) );
    ui->password_input_3->setText(QString::fromStdString(password) );
    ui->balance_input_2->setText(QString::fromStdString(balance) );
}


void MainWindow::on_update_btn_clicked()
{
 string username=ui->username_input_2->text().toStdString();
 string password=ui->password_input_2->text().toStdString();
 string balance=ui->balance_input->text().toStdString();
 int id= stoi(  ui->comboBox_users->currentText().toStdString());
 if(username.empty()||password.empty()||balance.empty()){
  QMessageBox::warning(this,"Empty input","there is Empty field !!");
 }else{

     manger.updateProfile(id,username,password,stod(balance));
     QMessageBox::information(this,"Success","Updating Successful");
      loadUsers();
 }


}


void MainWindow::on_sendMoney_btn_5_clicked()
{

    int id= stoi(  ui->comboBox_users_2->currentText().toStdString());
    manger.deleteUser(id);
    QMessageBox::information(this,"Success","Deleting Successful");
    ui->comboBox_users_2->removeItem(ui->comboBox_users_2->currentIndex());
    loadUsers();

}

