#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include"admin.h"
#include <string>
#include<cmath>
#include<sstream>
#include <QLabel>
using namespace std;

void MainWindow::login() {
    try {
        string phone = ui->LinePhoneNumber->text().toStdString();
        string password = ui->linePassword->text().toStdString();

        if (phone.empty() || password.empty()) {
           QMessageBox::warning(nullptr, "Empty Field", "The field is empty. Please enter some text.");
            return;
        } else if (!Egyptian_PhoneNumber(phone)) {
            QMessageBox::warning(nullptr, "Invalid Phone Number", "Please enter a valid Egyptian phone number (01XXXXXXXXX) with 11 digits.");
            ui->LinePhoneNumber->setFocus();
            return;
        }
        else {
            if (manger.login(stoi(phone), password) != 0) {
                MainWindow::ui->frameLogin->setVisible(false);
                MainWindow::ui->full_menu_widget->hide();
                MainWindow::ui->icon_only_widget->show();
                MainWindow::ui->stackedWidget->setCurrentIndex(0);
                MainWindow::ui->home_btn2->setChecked(true);
                MainWindow::ui->HomePage->setVisible(true);
                ui->frame_3->setEnabled(true);
                ui->frame_2->setEnabled(true);
                ui->frame_5->setEnabled(true);
                User user = manger.getListOfUsers()->at(stoi(phone));
                id = stoi(phone);
                loadUserTransactions(id);
                loadRequest(id);
                loadRequestHistory(id);
                incomes=user.getIncomes();
                expenses=user.getExpenses();

                ui->user_btn->setText(QString::fromStdString(user.getUsername()));
                ui->label_3->setText(QString::fromStdString(user.getUsername()));
                ui->label_6->setText(QString::number(user.getBalance(), 'f', 2));
                ui->label_93->setText(QString::number(user.getBalance(), 'f', 2));
                ui->balance_label->setText(QString::number(user.getBalance(), 'f', 2));
                ui->label_80->setText(QString::number(user.getBalance(), 'f', 2));

                ui->lineEdit_4->setText(QString::fromStdString(phone));
                ui->lineEdit->setText(QString::fromStdString(user.getUsername()));
                ui->lineEdit_2->setText(QString::fromStdString(user.getPassword()));

                ui->label_82->setText(QString::number(incomes, 'f', 2));
                ui->label_85->setText(QString::number(expenses, 'f', 2));
                ui->label_95->setText(QString::number(incomes, 'f', 2));
                ui->label_98->setText(QString::number(expenses, 'f', 2));
                ui->label_11->setText(QString::number(incomes, 'f', 2));
                ui->label_28->setText(QString::number(expenses, 'f', 2));
                ui->incomes->setText(QString::number(incomes, 'f', 2));
                ui->expenses->setText(QString::number(expenses, 'f', 2));
                if(user.getSuspended()){
                 QMessageBox::warning(nullptr, "Account Banned", "This account has been banned. Please contact support for assistance.");

                   ui->frame_3->setEnabled(false);
                   ui->frame_2->setEnabled(false);
                   ui->frame_5->setEnabled(false);
                }
            } else if (manger.loginAdmin(phone, password)) {
                MainWindow::ui->frameLogin->close();
                MainWindow::ui->full_menu_widget_2->hide();
                 MainWindow::ui->icon_only_widget_2->show();
                MainWindow::ui->stackedWidget_2->setCurrentIndex(0);
                MainWindow::ui->users_btn->setChecked(true);
                MainWindow::ui->HomePage_Admin->setVisible(true);
                ui->password_profile->setText(ui->linePassword->text());
                loadUsers();
                updateComboBox(ui->comboBox_users, ui->comboBox_users_2, ui->comboBox_users_3);

            } else {
                QMessageBox::warning(nullptr, "Fail", "Invalid Phone Number or Password");
            }
        }
    } catch (const std::exception &e) {
        // Handle exception
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        // Handle unknown exception
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }
}

void MainWindow::signUp()
{
    try {
        string phone = ui->linePhone->text().toStdString();
        string username = ui->LineUserName_2->text().toStdString();
        string password = ui->linePassword_2->text().toStdString();

        // Check for empty fields
        if (phone.empty() || password.empty() || username.empty()) {
            QMessageBox::warning(nullptr, "Empty Field", "The field is empty. Please enter some text.");

            return;
        }

        // Check for valid username
        if (!isValidUsername(QString::fromStdString(username))) {
            QMessageBox::warning(nullptr, "Invalid Username", "Please enter a valid username (3-16 characters, alphanumeric and underscore only).");
            ui->LineUserName_2->setFocus();
            return;
        }

        // Check for valid password
        if (!isValidPassword(QString::fromStdString(password))) {
            QMessageBox::warning(nullptr, "Invalid Password", "Please enter a valid password (minimum eight characters, at least one uppercase letter, one lowercase letter, and one number).");
            ui->linePassword_2->setFocus();
            return;
        }

        // Check for valid Egyptian phone number
        if (!Egyptian_PhoneNumber(phone)) {
            QMessageBox::warning(nullptr, "Invalid Phone Number", "Please enter a valid Egyptian phone number (01XXXXXXXXX) with 11 digits.");
            ui->linePhone->setFocus();
            return;
        }

        // Attempt to sign up the user
        if (manger.signup(stoi(phone), username, password, 0.0)) {
            // Successful signup
            MainWindow::ui->frameLogin->setVisible(true);
            ui->linePhone->clear();
            ui->LineUserName_2->clear();
            ui->linePassword_2->clear();
            MainWindow::ui->frameSignUp->setVisible(false);

        } else {
            // Phone number already exists
            QMessageBox::warning(nullptr, "Phone Number Exists", "This phone number is already registered.");
            ui->linePhone->setFocus();
        }
    } catch (const std::exception &e) {
        // Handle exception
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        // Handle unknown exception
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }

}

void MainWindow::sendMoney()
{
    try {
        string phone = ui->recipient_input->text().toStdString();
        string amount = ui->amount_input->text().toStdString();

        // Check for empty fields
        if (ui->recipient_input->text().isEmpty() || ui->amount_input->text().isEmpty()) {
            QMessageBox::warning(nullptr, "Empty input", "There is an empty field!");
            return;
        }

        // Check for valid Egyptian phone number
        if (!Egyptian_PhoneNumber(phone)) {
            QMessageBox::warning(nullptr, "Invalid Phone Number", "Please enter a valid Egyptian phone number (01XXXXXXXXX) with 11 digits.");
            ui->recipient_input->setFocus();
            return;
        }

        // Check for numerical amount
        if (!isNumerical(amount)) {
            QMessageBox::warning(nullptr, "Invalid Data", "Enter numerical data!");
            ui->amount_input->setFocus();
            return;
        }

        int recipientId = stoi(phone);

        // Check if recipient is the same as sender
        if (recipientId == id) {
            QMessageBox::warning(nullptr, "Error", "You can't send money to yourself.");
            ui->recipient_input->clear();
            ui->amount_input->clear();
            return;
        }

        // Check if recipient exists in the user list
        auto recipientIter = manger.getListOfUsers()->find(recipientId);
        if (recipientIter == manger.getListOfUsers()->end()) {
            QMessageBox::warning(nullptr, "Not Found", "User not found!");
            return;
        }
        QString Qrecipient = QString::fromStdString(to_string(recipientId));
        // Send money
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Confirmation", QString("Are you sure you want to send money to %1 ?").arg(Qrecipient), QMessageBox::Yes|QMessageBox::No);
     if (reply == QMessageBox::Yes) {
        double amountValue = stod(amount);
        QString Qamount = QString::fromStdString(amount);
        if (manger.getListOfUsers()->at(id).sendMoney(id, recipientId, amountValue, manger.getListOfUsers()->at(recipientId))) {
            // Successful transaction
            QMessageBox::information(nullptr, "Success", QString("Successfully sent $%1 to %2").arg(Qamount).arg(Qrecipient));
            ui->recipient_input->clear();
            ui->amount_input->clear();
            incomes=manger.getListOfUsers()->at(id).getIncomes();
            expenses=manger.getListOfUsers()->at(id).getExpenses();

            // Update balance labels
            double balance = manger.getListOfUsers()->at(id).getBalance();
            ui->label_6->setText(QString::number(balance, 'f', 2));
            ui->label_93->setText(QString::number(balance, 'f', 2));
            ui->balance_label->setText(QString::number(balance, 'f', 2));
            ui->label_80->setText(QString::number(balance, 'f', 2));
            ui->label_82->setText(QString::number(incomes, 'f', 2));
            ui->label_85->setText(QString::number(expenses, 'f', 2));
            ui->label_95->setText(QString::number(incomes, 'f', 2));
            ui->label_98->setText(QString::number(expenses, 'f', 2));
            ui->label_11->setText(QString::number(incomes, 'f', 2));
            ui->label_28->setText(QString::number(expenses, 'f', 2));
            ui->incomes->setText(QString::number(incomes, 'f', 2));
            ui->expenses->setText(QString::number(expenses, 'f', 2));

            // Load user transactions
            loadUserTransactions(id);
        } else {
            // Insufficient balance
            QMessageBox::warning(nullptr, "Not Enough", "Your balance is less than the amount.");
        }
     }else{
         ui->recipient_input->clear();
         ui->amount_input->clear();
     }
    } catch (const std::exception &e) {
        // Handle exception
        // For example, show an error message
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        // Handle unknown exception
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }

}

void MainWindow::recieveMoney()
{
    try {
        string phone = ui->sender_input->text().toStdString();
        string amount = ui->amount_input_2->text().toStdString();

        // Check for empty fields
        if (ui->sender_input->text().isEmpty() || ui->amount_input_2->text().isEmpty()) {
            QMessageBox::warning(nullptr, "Empty Field", "The field is empty. Please enter some text.");
            return;
        }

        // Check for valid Egyptian phone number
        if (!Egyptian_PhoneNumber(phone)) {
            QMessageBox::warning(nullptr, "Invalid Phone Number", "Please enter a valid Egyptian phone number (01XXXXXXXXX) with 11 digits.");
            ui->sender_input->setFocus();
            return;
        }

        // Check for numerical amount
        if (!isNumerical(amount)) {
            QMessageBox::warning(nullptr, "Invalid Data", "Enter numerical data.");
            ui->amount_input_2->setFocus();
            return;
        }

        int senderId = stoi(phone);

        // Check if sender is the same as receiver
        if (senderId == id) {
            QMessageBox::warning(nullptr, "Error", "You can't receive money from yourself.");
            ui->sender_input->clear();
            ui->amount_input_2->clear();
            return;
        }

        // Check if sender exists in the user list
        auto senderIter = manger.getListOfUsers()->find(senderId);

        if (senderIter == manger.getListOfUsers()->end()) {
            QMessageBox::warning(nullptr, "Not Found", "User not found.");
            return;
        }
        QString Qsender = QString::fromStdString(to_string(senderId));
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Confirmation", QString("Are you sure you want to recieve money from %1 ?").arg(Qsender), QMessageBox::Yes|QMessageBox::No);
         if (reply == QMessageBox::Yes) {
        // Request money
        manger.getListOfUsers()->at(id).requestMoney(id, senderId, stod(amount), manger.getListOfUsers()->at(senderId));
        QMessageBox::information(nullptr, "Success", QString("Sending request to %1 successful. Please await their response.").arg(Qsender));
        loadRequestHistory(id);
        ui->sender_input->clear();
        ui->amount_input_2->clear();
         }else{
             ui->sender_input->clear();
             ui->amount_input_2->clear();
         }
    } catch (const std::exception &e) {
        // Handle exception
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        // Handle unknown exception
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }

}

void MainWindow::addUser()
{
    try {
        string phone = ui->phone_input_3->text().toStdString();
        string username = ui->username_input->text().toStdString();
        string password = ui->password_input->text().toStdString();
        string balance = ui->balace_input->text().toStdString();

        // Check for empty fields
        if (phone.empty() || username.empty() || password.empty() || balance.empty()) {
            QMessageBox::warning(nullptr, "Empty Field", "The field is empty. Please enter some text.");
            return;
        }

        // Check for valid username
        if (!isValidUsername(QString::fromStdString(username))) {
            QMessageBox::warning(nullptr, "Invalid Username", "Please enter a valid username (3-16 characters, alphanumeric and underscore only).");
            ui->username_input->setFocus();
            return;
        }

        // Check for valid password
        if (!isValidPassword(QString::fromStdString(password))) {
            QMessageBox::warning(nullptr, "Invalid Password", "Please enter a valid password (minimum eight characters, at least one uppercase letter, one lowercase letter, and one number).");
            ui->password_input->setFocus();
            return;
        }

        // Check for valid Egyptian phone number
        if (!Egyptian_PhoneNumber(phone)) {
            QMessageBox::warning(nullptr, "Invalid Phone Number", "Please enter a valid Egyptian phone number (01XXXXXXXXX) with 11 digits.");
            ui->phone_input_3->setFocus();
            return;
        }

        // Check for numerical balance
        if (!isNumerical(balance)) {
            QMessageBox::warning(nullptr, "Invalid Data", "Enter numerical balance.");
            ui->balace_input->setFocus();
            return;
        }

        // Attempt to add user
        if (manger.signup(stoi(phone), username, password, stod(balance))) {
            // Successful user addition
            QMessageBox::information(nullptr, "Success", "Adding Successful");
            ui->phone_input_3->clear();
            ui->username_input->clear();
            ui->password_input->clear();
            ui->balace_input->clear();
            ui->comboBox_users->addItem(QString::fromStdString(phone));
            ui->comboBox_users_2->addItem(QString::fromStdString(phone));
            ui->comboBox_users_3->addItem(QString::fromStdString(phone));
            loadUsers();
        } else {
            // Phone number already exists
            QMessageBox::warning(nullptr, "Already Exists", "Phone number already exists.");
        }
    } catch (const std::exception &e) {
        // Handle exception
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        // Handle unknown exception
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }

}

void MainWindow::updateUser() {
    try {
        string username = ui->username_input_2->text().toStdString();
        string password = ui->password_input_2->text().toStdString();
        string balance = ui->balance_input->text().toStdString();
        string id = ui->comboBox_users->currentText().toStdString();
        bool suspended= ui->checkBox->isChecked();

        if (username.empty() || password.empty() || balance.empty()) {
            QMessageBox::warning(nullptr, "Empty Field", "The field is empty. Please enter some text.");
            return;
        } else if (!isValidUsername(QString::fromStdString(username))) {
            QMessageBox::warning(nullptr, "Invalid Username", "Please enter a valid username (3-16 characters, alphanumeric and underscore only).");
            ui->username_input_2->setFocus();
            return;
        } else if (!isValidPassword(QString::fromStdString(password))) {
            QMessageBox::warning(nullptr, "Invalid Password", "Please enter a valid password (minimum eight characters, at least one uppercase letter, one lowercase letter, and one number).");
            ui->password_input_2->setFocus();
            return;
        } else if (!isNumerical(balance)) {
            QMessageBox::warning(nullptr, "Invalid Data", "Enter Numerical Data !!");
            ui->balance_input->setFocus();
            return;
        }

        manger.updateProfile(stoi(id), username, password, stod(balance),suspended);
        QMessageBox::information(nullptr, "Success", "Updating Successful");
        loadUsers();

        string user_id = ui->comboBox_users_3->currentText().toStdString();
        if (!user_id.empty()) {
            loadAdminTransactions(stoi(user_id));
        } else {
            ui->transactions_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
    } catch (const std::exception &e) {
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }
}

void MainWindow::deleteUser()
{
    try {
        string id = ui->comboBox_users_2->currentText().toStdString();
        int currentIndex = ui->comboBox_users_2->currentIndex();

        // Delete the user from the manager
        manger.deleteUser(stoi(id));

        // Show success message
        QMessageBox::information(nullptr, "Success", "Deleting Successful");

        // Remove the user from all combo boxes
        ui->comboBox_users_2->removeItem(currentIndex);
        ui->comboBox_users->removeItem(currentIndex);
        ui->comboBox_users_3->removeItem(currentIndex);


        // Reload users
        loadUsers();
    } catch (const std::exception &e) {
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }

}

void MainWindow::changeProfile() {
    try {
        if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty()) {
            QMessageBox::warning(nullptr, "Empty Field", "The field is empty. Please enter some text.");
            return;
        } else if (!isValidUsername(ui->lineEdit->text())) {
            QMessageBox::warning(nullptr, "Invalid Username", "Please enter a valid username (3-16 characters, alphanumeric and underscore only).");
            ui->lineEdit->setFocus();
            return;
        } else if (!isValidPassword(ui->lineEdit_2->text())) {
            QMessageBox::warning(nullptr, "Invalid Password", "Please enter a valid password (minimum eight characters, at least one uppercase letter, one lowercase letter, and one number).");
            ui->lineEdit_2->setFocus();
            return;
        }

        manger.updateProfile(id, ui->lineEdit->text().toStdString(), ui->lineEdit_2->text().toStdString());

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
        loadUsers();
    } catch (const std::exception &e) {
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }
}

void MainWindow::loadUsers() {
    try {
        int row = 0;
        ui->users_table->setRowCount(0);
        ui->users_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->users_table->setRowCount(manger.getListOfUsers()->size());

        for (auto pair : *manger.getListOfUsers()) {
            string id = to_string(pair.first);
            string username = pair.second.getUsername();
            string numberTrans = to_string(pair.second.getHistory().size());
            string numberRequest = to_string(pair.second.getRequests().size());
            double balance = pair.second.getBalance();
            bool suspended = pair.second.getSuspended();
            QTableWidgetItem* user_count = new QTableWidgetItem(QString::fromStdString(to_string(row + 1)));
            QTableWidgetItem* user_id = new QTableWidgetItem(QString::fromStdString(id));
            QTableWidgetItem* user_Name = new QTableWidgetItem(QString::fromStdString(username));
            QTableWidgetItem* user_Balance = new QTableWidgetItem(QString::number(balance, 'f', 2));
            QTableWidgetItem* user_NumTransaction = new QTableWidgetItem(QString::fromStdString(numberTrans));
            QTableWidgetItem* user_NumRequest = new QTableWidgetItem(QString::fromStdString(numberRequest));

            user_count->setTextAlignment(Qt::AlignCenter);
            user_id->setTextAlignment(Qt::AlignCenter);
            user_Name->setTextAlignment(Qt::AlignCenter);
            user_Balance->setTextAlignment(Qt::AlignCenter);
            user_NumTransaction->setTextAlignment(Qt::AlignCenter);
            user_NumRequest->setTextAlignment(Qt::AlignCenter);
            if (suspended) {


                QPushButton* suspended_button = new QPushButton();
                 QIcon icon(":/img/ban-user.png");
                 suspended_button->setIconSize(QSize(30, 30));
                 suspended_button->setIcon(icon);
                 QHBoxLayout* layout = new QHBoxLayout();

                 layout->setAlignment(Qt::AlignCenter);
                 layout->setContentsMargins(10, 0, 10, 0);
                 layout->addStretch();
                 layout->addWidget(suspended_button);
                 layout->addStretch();


                 QWidget* container = new QWidget();
                 container->setLayout(layout);
                 container->setStyleSheet(" background-color:white");
                 ui->users_table->setCellWidget(row, 1, container);


            }

            ui->users_table->setItem(row, 0, user_count);
            ui->users_table->setItem(row, 2, user_id);
            ui->users_table->setItem(row, 3, user_Name);
            ui->users_table->setItem(row, 4, user_Balance);
            ui->users_table->setItem(row, 5, user_NumTransaction);
            ui->users_table->setItem(row, 6, user_NumRequest);
            ++row;
        }
    } catch (const std::exception &e) {
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }
}

void MainWindow::updateComboBox(QComboBox* combo_1,QComboBox* combo_2,QComboBox* combo_3) {
    try {
        if (!combo_1 || !combo_2 || !combo_3) {
            qDebug() << "One or more combo boxes are null.";
            return;
        }

        // Clear existing items
        combo_1->clear();
        combo_2->clear();
        combo_3->clear();

        if (!manger.getListOfUsers()) {
            qDebug() << "List of users is null.";
            return;
        }

        if (!manger.getListOfUsers()->empty()) {
            for (auto pair = manger.getListOfUsers()->begin(); pair != manger.getListOfUsers()->end(); ++pair) {
                QString itemText = QString::number(pair->first);
                combo_1->addItem(itemText);
                combo_2->addItem(itemText);
                combo_3->addItem(itemText);
            }
        } else {
            qDebug() << "List of users is empty.";
        }
    } catch (const std::exception& e) {
        qDebug() << "Exception occurred: " << e.what();
    } catch (...) {
        qDebug() << "An unknown exception occurred.";
    }
}

bool MainWindow::Egyptian_PhoneNumber(const string &phoneNumber)
{

        if (phoneNumber.length() != 11) {
            return false;
        }
        if (phoneNumber[0] != '0' || phoneNumber[1] != '1') {
            return false;
        }
        for (int i = 0; i < 11; i++) {
            if (!isdigit(phoneNumber[i])) {
                return false;
            }
        }
        return true;

}

bool MainWindow::isNumerical(const string &input)
{
    if (input.empty()) {
        return false;
    }
    std:: istringstream iss(input);
    double value;
    return(iss>> value)&&(value>=0)&& iss.eof();
}

void MainWindow::loadUserTransactions(int id_User)
{
    incomes=0.0;
    expenses=0.0;
    int row=0;


    ui->transactions_table_2->setRowCount(0);
    ui->transactions_table_2->setRowCount( manger.getListOfUsers()->at(id_User).getHistory().size());
    ui->transactions_table_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    stack<Transaction> transctions=manger.getListOfUsers()->at(id_User).getHistory();

    while ((!transctions.empty())) {
        string username;
        string _id;
        double  amount;
        string  date;
        string  type;
            if(manger.getListOfUsers()->find(transctions.top().getReciever())==manger.getListOfUsers()->end()){
                username= manger.getListOfDeletedUsers()->at(transctions.top().getReciever()).getUsername();

            }else{
                username= manger.getListOfUsers()->at(transctions.top().getReciever()).getUsername();
            }
            _id=to_string(transctions.top().getReciever());
            amount= transctions.top().getAmount();
            date=  transctions.top().date;
            type=  transctions.top().getTransacType();


            QTableWidgetItem* user_count=new QTableWidgetItem(QString::fromStdString("Me"));
            QTableWidgetItem* user_id=new QTableWidgetItem(QString::fromStdString(_id));
            QTableWidgetItem* user_Name=new QTableWidgetItem(QString::fromStdString(username));
            QTableWidgetItem* user_Date=new QTableWidgetItem(QString::fromStdString(date));
            QTableWidgetItem* user_type=new QTableWidgetItem(QString::fromStdString(type));
            QTableWidgetItem* user_Amount;

            if(type=="send"){

                user_Amount =new QTableWidgetItem("-"+QString::number(amount,'f',2));
                user_Amount->setForeground(QColor(Qt::red));

            }else{

                user_Amount =new QTableWidgetItem("+"+QString::number(amount,'f',2));
                user_Amount->setForeground(QColor(Qt::green));
            }


            user_count->setTextAlignment(Qt::AlignCenter);
            user_id->setTextAlignment(Qt::AlignCenter);
            user_Name->setTextAlignment(Qt::AlignCenter);
            user_Amount->setTextAlignment(Qt::AlignCenter);
            user_Date->setTextAlignment(Qt::AlignCenter);
            user_type->setTextAlignment(Qt::AlignCenter);




            ui->transactions_table_2->setItem(row,0,user_count);
            ui->transactions_table_2->setItem(row,1,user_type);
            ui->transactions_table_2->setItem(row,2,user_Amount);
            ui->transactions_table_2->setItem(row,3,user_Name);
            ui->transactions_table_2->setItem(row,4,user_id);
            ui->transactions_table_2->setItem(row,5,user_Date);
            transctions.pop();


            ++row;
        }

    }

void MainWindow::loadRequest(int id_User)
{

    int row=0;

    ui->transactions_table_1->setRowCount(0);
    ui->transactions_table_1->setRowCount( manger.getListOfUsers()->at(id_User).getRequests().size());
    ui->transactions_table_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->transactions_table_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    queue<Request> requests=manger.getListOfUsers()->at(id_User).getRequests();
    while (!requests.empty()) {
        string usernameRequest;
        string id_Reciever;
        double  amountRequest;
        string  dateRequest;
        int id_Request;
        int idSender=requests.front().getSender();
            if(manger.getListOfUsers()->find(requests.front().getReciever())==manger.getListOfUsers()->end()){
                usernameRequest= manger.getListOfDeletedUsers()->at(requests.front().getReciever()).getUsername();
            }else{
                usernameRequest= manger.getListOfUsers()->at(requests.front().getReciever()).getUsername();
            }
            id_Reciever=to_string(requests.front().getReciever());
            amountRequest=  requests.front().getAmount();
            dateRequest=  requests.front().getDate();
            id_Request=requests.front().getID();
            QTableWidgetItem* user_count=new QTableWidgetItem(QString::fromStdString(to_string(row+1)));
            QTableWidgetItem* user_id=new QTableWidgetItem(QString::fromStdString(id_Reciever));
            QTableWidgetItem* user_Name=new QTableWidgetItem(QString::fromStdString(usernameRequest));
            QTableWidgetItem* user_Date=new QTableWidgetItem(QString::fromStdString(dateRequest));
            QTableWidgetItem* user_Amount=new QTableWidgetItem(QString::number(amountRequest,'f',2));
            QTableWidgetItem* request=new QTableWidgetItem(QString::fromStdString("Request"));

            // Create a QPushButton for each row
            QPushButton* button1 = new QPushButton("Send To");
            QPushButton* button2 = new QPushButton("Cancel");
            button1->setObjectName("send");
             QString buttonStyle=
                "   QPushButton {"
                "  background-color:#00cc00; font-weight:bold;font-size:14px; border:none;border-radius: 10px;padding: 6px 10px 6px 10px;color:white;text-align:center;height:20px;"
                " }"
                " QPushButton:hover {"
                "     background-color:#fafafa;color:#00cc00;"
                                  " }";
            QString buttonStyle_2=
                "   QPushButton {"
                "  background-color:red; font-weight:bold;font-size:14px; border:none;border-radius: 10px;padding: 6px 10px 6px 10px;color: white;text-align:center;height:20px;"
                " }"
                " QPushButton:hover {"
                "     background-color:white;color:red;"
                " }";
             button1->setStyleSheet(buttonStyle);
             button2->setStyleSheet(buttonStyle_2);
            QHBoxLayout* layout1 = new QHBoxLayout();
            QHBoxLayout* layout2 = new QHBoxLayout();
            layout1->setAlignment(Qt::AlignCenter);
            layout2->setAlignment(Qt::AlignCenter);
            layout1->setContentsMargins(10, 0, 10, 0);
            layout2->setContentsMargins(10, 0, 10, 0);
            layout1->addStretch();
            layout2->addStretch();
            layout1->addWidget(button1);
            layout2->addWidget(button2);
            layout1->addStretch();
            layout2->addStretch();

            // Create container widgets to hold the layouts
            QWidget* container1 = new QWidget();
            QWidget* container2 = new QWidget();
            container1->setLayout(layout1);
            container2->setLayout(layout2);
            container1->setStyleSheet(" background-color:white");
            container2->setStyleSheet(" background-color:white");

            // Set the container widgets in the table cells
            ui->transactions_table_1->setCellWidget(row, 6, container1);
            ui->transactions_table_1->setCellWidget(row, 7, container2);

            connect(button1, &QPushButton::clicked, this, [=]() {
                if(manger.getListOfUsers()->at(id).getSuspended()){
                    QMessageBox::warning(nullptr, "Account Banned", "This account has been banned.");
                    button1->setEnabled(false);
                    return;

                }
                if( manger.getListOfUsers()->at(id).sendMoney(id,idSender,amountRequest,manger.getListOfUsers()->at(idSender))){
              QString Qrecipient = QString::fromStdString(id_Reciever);
                  // Send money
                  QMessageBox::StandardButton reply;
                 reply = QMessageBox::question(nullptr, "Confirmation", QString("Are you sure you want to send money to %1 ?").arg(Qrecipient), QMessageBox::Yes|QMessageBox::No);
                    if (reply == QMessageBox::Yes) {
                    QMessageBox::information(nullptr,"Success","Send Successful");
                    double balance=  manger.getListOfUsers()->at(id).getBalance();
                    ui->label_6->setText(QString::number(balance,'f',2));
                    ui->label_93->setText(QString::number(balance,'f',2));
                    ui->balance_label->setText(QString::number(balance,'f',2));
                    ui->label_80->setText(QString::number(balance,'f',2));
                    loadUserTransactions(id);
                    incomes=manger.getListOfUsers()->at(id).getIncomes();
                    expenses=manger.getListOfUsers()->at(id).getExpenses();
                    ui->label_82->setText(QString::number(incomes,'f',2));
                    ui->label_85->setText(QString::number(expenses,'f',2));
                    ui->label_95->setText(QString::number(incomes,'f',2));
                    ui->label_98->setText(QString::number(expenses,'f',2));
                    ui->label_11->setText(QString::number(incomes,'f',2));
                    ui->label_28->setText(QString::number(expenses,'f',2));
                    ui->incomes->setText(QString::number(incomes,'f',2));
                    ui->expenses->setText(QString::number(expenses,'f',2));
                    manger.getListOfUsers()->at(id).removeRequest(id_Request);
                    manger.getListOfUsers()->at(idSender).changeStatus(id_Request,"success");
                    loadRequest(id_User);
                    }
                }
                else{
                    QMessageBox::information(nullptr,"Not enough","Your balance less than amount");

                }

            });

            connect(button2, &QPushButton::clicked, this, [=]() {


                manger.getListOfUsers()->at(id).removeRequest(id_Request);
                manger.getListOfUsers()->at(idSender).changeStatus(id_Request,"cancel");
                loadRequest(id_User);

            });

            user_count->setTextAlignment(Qt::AlignCenter);
            user_id->setTextAlignment(Qt::AlignCenter);
            user_Name->setTextAlignment(Qt::AlignCenter);
            user_Amount->setTextAlignment(Qt::AlignCenter);
            user_Date->setTextAlignment(Qt::AlignCenter);
            request->setTextAlignment(Qt::AlignCenter);
            ui->transactions_table_1->setRowHeight(row,40);
            ui->transactions_table_1->setItem(row,0,user_count);
            ui->transactions_table_1->setItem(row,1,user_Name);
            ui->transactions_table_1->setItem(row,2,user_id);
            ui->transactions_table_1->setItem(row,3,request);
            ui->transactions_table_1->setItem(row,4,user_Amount);
            ui->transactions_table_1->setItem(row,5,user_Date);


            requests.pop();
            ++row;

        }

}

void MainWindow::loadRequestHistory(int id_User)
{
    int row=0;

    ui->transactions_table_3->setRowCount(0);
    ui->transactions_table_3->setRowCount( manger.getListOfUsers()->at(id_User).getRequestsHistory().size());
    ui->transactions_table_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    queue<Request> requests=manger.getListOfUsers()->at(id_User).getRequestsHistory();
    while (!requests.empty()) {
        string usernameRequest;
        string idRequest;
        string  dateRequest;
        string  state;
        double  amountRequest;
        int id_Request=requests.front().getID();
        int idSender=requests.front().getSender();
        if(manger.getListOfUsers()->find(requests.front().getReciever())==manger.getListOfUsers()->end()){
            usernameRequest= manger.getListOfDeletedUsers()->at(requests.front().getReciever()).getUsername();

        }else{
            usernameRequest= manger.getListOfUsers()->at(requests.front().getReciever()).getUsername();
        }
        idRequest=to_string(requests.front().getReciever());
        amountRequest=  requests.front().getAmount();
        dateRequest=  requests.front().getDate();
        state=requests.front().getStatusRequest();
         QTableWidgetItem* self_User=new QTableWidgetItem(QString::fromStdString("Me"));
        QTableWidgetItem* user_count=new QTableWidgetItem(QString::fromStdString(to_string(row+1)));
        QTableWidgetItem* user_id=new QTableWidgetItem(QString::fromStdString(idRequest));
        QTableWidgetItem* user_Name=new QTableWidgetItem(QString::fromStdString(usernameRequest));
        QTableWidgetItem* user_Date=new QTableWidgetItem(QString::fromStdString(dateRequest));
        QTableWidgetItem* user_Amount=new QTableWidgetItem(QString::number(amountRequest,'f',2));
        QTableWidgetItem* request=new QTableWidgetItem(QString::fromStdString("Request"));
        QTableWidgetItem* status=new QTableWidgetItem(QString::fromStdString(state));

        // Create a QPushButton for each row

        QPushButton* button ;
        if(state=="success"||state=="cancel"){

           button=new QPushButton("Delete");
        }else{
          button=new QPushButton("Cancel");
        }

        QString buttonStyle=
            "   QPushButton {"
            "  background-color:red; font-weight:bold;font-size:14px; border:none;border-radius: 10px;padding: 6px 10px 6px 10px;color: white;text-align:center;height:20px;"
            " }"
            " QPushButton:hover {"
            "     background-color:white;color:red;"
            " }";
        button->setStyleSheet(buttonStyle);

        QHBoxLayout* layout = new QHBoxLayout();

        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(10, 0, 10, 0);
        layout->addStretch();
        layout->addWidget(button);
        layout->addStretch();


        // Create container widgets to hold the layouts
        QWidget* container = new QWidget();
        container->setLayout(layout);
        container->setStyleSheet(" background-color:white");
        ui->transactions_table_3->setCellWidget(row, 8, container);




        connect(button, &QPushButton::clicked, this, [=]() {
            if(state=="success"||state=="cancel"){
               manger.getListOfUsers()->at(id).removeRequestHistory(id_Request);

            }else{
                manger.getListOfUsers()->at(id).removeRequestHistory(id_Request);
                manger.getListOfUsers()->at(stoi(idRequest)).removeRequest(id_Request);

            }

            loadRequestHistory(id_User);

        });
        self_User->setTextAlignment(Qt::AlignCenter);
        user_count->setTextAlignment(Qt::AlignCenter);
        user_id->setTextAlignment(Qt::AlignCenter);
        user_Name->setTextAlignment(Qt::AlignCenter);
        user_Amount->setTextAlignment(Qt::AlignCenter);
        user_Date->setTextAlignment(Qt::AlignCenter);
        request->setTextAlignment(Qt::AlignCenter);
        status->setTextAlignment(Qt::AlignCenter);
        ui->transactions_table_3->setRowHeight(row,40);
        ui->transactions_table_3->setItem(row,0,user_count);
        ui->transactions_table_3->setItem(row,1,self_User);
        ui->transactions_table_3->setItem(row,2,request);
        ui->transactions_table_3->setItem(row,3,user_Amount);
        ui->transactions_table_3->setItem(row,4,user_Name);
        ui->transactions_table_3->setItem(row,5,user_id);
        ui->transactions_table_3->setItem(row,6,user_Date);
        ui->transactions_table_3->setItem(row,7,status);


        requests.pop();
        ++row;

    }
}

void MainWindow::loadAdminTransactions(int id_User)
{
    ui->transactions_table->setRowCount(0);
    ui->transactions_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->transactions_table->setRowCount( manger.getListOfUsers()->at(id_User).getHistory().size());
    int row=0;
    stack<Transaction> transctions=manger.getListOfUsers()->at(id_User).getHistory();
    while (!transctions.empty()) {
        string usernameOther;
        if(manger.getListOfUsers()->find(transctions.top().getReciever())==manger.getListOfUsers()->end()){
              ui->transactions_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            usernameOther= manger.getListOfDeletedUsers()->at(transctions.top().getReciever()).getUsername();

        }else{
              ui->transactions_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            usernameOther= manger.getListOfUsers()->at(transctions.top().getReciever()).getUsername();
        }
        string _id=to_string(id_User);
        string username= manger.getListOfUsers()->at(id_User).getUsername();
        string idOther=to_string(transctions.top().getReciever());
        double  amount= transctions.top().getAmount();
        string  date=  transctions.top().date;
        string  type=  transctions.top().getTransacType();


        QTableWidgetItem* user_id=new QTableWidgetItem(QString::fromStdString(_id));
        QTableWidgetItem* user_Name=new QTableWidgetItem(QString::fromStdString(username));
        QTableWidgetItem* other_id=new QTableWidgetItem(QString::fromStdString(idOther));
        QTableWidgetItem* user_Name_other=new QTableWidgetItem(QString::fromStdString(usernameOther));
        QTableWidgetItem* user_Date=new QTableWidgetItem(QString::fromStdString(date));
        QTableWidgetItem* user_type=new QTableWidgetItem(QString::fromStdString(type));
        QTableWidgetItem* user_Amount;

        if(type=="send"){

            user_Amount =new QTableWidgetItem("-"+QString::number(amount,'f',2));
             user_Amount->setForeground(QColor(Qt::red));


        }else{

            user_Amount =new QTableWidgetItem("+"+QString::number(amount,'f',2));
            user_Amount->setForeground(QColor(Qt::green));

        }
        user_id->setTextAlignment(Qt::AlignCenter);
        user_Name->setTextAlignment(Qt::AlignCenter);
        user_Amount->setTextAlignment(Qt::AlignCenter);
        user_Date->setTextAlignment(Qt::AlignCenter);
        user_type->setTextAlignment(Qt::AlignCenter);
        other_id->setTextAlignment(Qt::AlignCenter);
        user_Name_other->setTextAlignment(Qt::AlignCenter);

        ui->transactions_table->setItem(row,0,user_id);
        ui->transactions_table->setItem(row,1,user_Name);
        ui->transactions_table->setItem(row,2,user_type);
        ui->transactions_table->setItem(row,3,user_Amount);
        ui->transactions_table->setItem(row,4,other_id);
        ui->transactions_table->setItem(row,5,user_Name_other);
        ui->transactions_table->setItem(row,6,user_Date);


        transctions.pop();
        ++row;
    }
}

bool MainWindow::isValidUsername(const QString &username)
{
    QRegularExpression usernameRegex("^[a-zA-Z0-9_]{3,16}$");


    QRegularExpressionMatch match = usernameRegex.match(username);


    return match.hasMatch();
}

bool MainWindow::isValidPassword(const QString &password)
{
    QRegularExpression passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)[a-zA-Z\\d]{8,}$");


    QRegularExpressionMatch match = passwordRegex.match(password);


    return match.hasMatch();
}





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    manger = Admin();
    ui->setupUi(this);
    ui->frameSignUp->setVisible(false);
    ui->frameLogin->setVisible(false);
    ui->HomePage->setVisible(false);
    ui->HomePage_Admin->setVisible(false);
    ui->change_btn_3->setVisible(false);
    ui->visible_btn_2->setVisible(false);
    ui->visible_btn_4->setVisible(false);
    ui->btnLogin->setVisible(false);
    ui->btnResetPassword->setVisible(false);
    ui->btnLogin->setVisible(true);
    ui->btn_ToSignUp->setVisible(true);
    ui->back_btn->setVisible(false);



}

MainWindow::~MainWindow()
{

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
    MainWindow::ui->frameLogin->setVisible(false);
    MainWindow::ui->frameSignUp->setVisible(true);
    ui->visible_btn_3->setVisible(true);
    ui->visible_btn_4->setVisible(false);
}
void MainWindow::on_btn_ToLogin_clicked()
{
    MainWindow::ui->LineUserName_2->clear();
    MainWindow::ui->linePassword_2->clear();
    MainWindow::ui->linePhone->clear();
    ui->visible_btn->setVisible(true);
    ui->visible_btn_2->setVisible(false);

    MainWindow::ui->frameSignUp->setVisible(false);
    MainWindow::ui->frameLogin->setVisible(true);
}
void MainWindow::on_btnSignUp_clicked()
{
    signUp();
}
void MainWindow::on_btnSignUp_1_clicked()
{
    MainWindow::ui->frameLanding->setVisible(false);
    MainWindow::ui->frameLogin->setVisible(false);
    MainWindow::ui->frameSignUp->setVisible(true);
}
void MainWindow::on_btnLogin_1_clicked()
{
    MainWindow::ui->frameLanding->setVisible(false);
    MainWindow::ui->frameLogin->setVisible(true);
    MainWindow::ui->frameSignUp->setVisible(false);
}

void MainWindow::on_user_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->recipient_input->clear();
    ui->amount_input->clear();
    ui->sender_input->clear();
    ui->amount_input_2->clear();
    ui->amount_input_3->clear();

}
void MainWindow::on_home_btn1_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->recipient_input->clear();
    ui->amount_input->clear();
    ui->sender_input->clear();
    ui->amount_input_2->clear();
    ui->amount_input_3->clear();
}


void MainWindow::on_home_btn2_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
   ui->recipient_input->clear();
   ui->amount_input->clear();
   ui->sender_input->clear();
   ui->amount_input_2->clear();
   ui->amount_input_3->clear();
}


void MainWindow::on_transaction_btn_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->recipient_input->clear();
    ui->amount_input->clear();
    ui->sender_input->clear();
    ui->amount_input_2->clear();
    ui->amount_input_3->clear();
}


void MainWindow::on_transaction_btn_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->recipient_input->clear();
    ui->amount_input->clear();
    ui->sender_input->clear();
    ui->amount_input_2->clear();
    ui->amount_input_3->clear();
}


void MainWindow::on_invoices_btn_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->recipient_input->clear();
    ui->amount_input->clear();
    ui->amount_input_3->clear();
}


void MainWindow::on_invoices_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->recipient_input->clear();
    ui->amount_input->clear();
    ui->amount_input_3->clear();
}


void MainWindow::on_wallets_btn_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->sender_input->clear();
    ui->amount_input_2->clear();
    ui->amount_input_3->clear();
}


void MainWindow::on_wallets_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    ui->sender_input->clear();
    ui->amount_input_2->clear();
    ui->amount_input_3->clear();
}

void MainWindow::on_request_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->recipient_input->clear();
    ui->amount_input->clear();
    ui->sender_input->clear();
    ui->amount_input_2->clear();
    ui->amount_input_3->clear();
}


void MainWindow::on_request_btn_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->recipient_input->clear();
    ui->amount_input->clear();
    ui->sender_input->clear();
    ui->amount_input_2->clear();
    ui->amount_input_3->clear();
}


void MainWindow::on_cash_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->recipient_input->clear();
    ui->amount_input->clear();
    ui->sender_input->clear();
    ui->amount_input_2->clear();
}


void MainWindow::on_cash_btn_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->recipient_input->clear();
    ui->amount_input->clear();
    ui->sender_input->clear();
    ui->amount_input_2->clear();
    ui->amount_input_3->clear();
}
void MainWindow::on_logout_2_clicked()
{

    ui->frameSignUp->setVisible(false);
    ui->HomePage->setVisible(false);
    ui->frameLanding->setVisible(false);
    ui->LinePhoneNumber->clear();
    ui->linePassword->clear();
    ui->recipient_input->clear();
    ui->amount_input->clear();
    ui->sender_input->clear();
    ui->amount_input_2->clear();
    ui->amount_input_3->clear();
    ui->visible_btn->setVisible(true);
    ui->visible_btn_2->setVisible(false);
    ui->frameLogin->setVisible(true);

}


void MainWindow::on_logout_clicked(){

    ui->frameSignUp->setVisible(false);
    ui->HomePage->setVisible(false);
    ui->frameLanding->setVisible(false);
    ui->LinePhoneNumber->clear();
    ui->linePassword->clear();
    ui->recipient_input->clear();
    ui->amount_input->clear();
    ui->sender_input->clear();
    ui->amount_input_2->clear();
    ui->amount_input_3->clear();
    ui->visible_btn->setVisible(true);
    ui->visible_btn_2->setVisible(false);
    ui->frameLogin->setVisible(true);
}
// the End Users  Functionalities
//************************************************
// Admin  Functionalities
void MainWindow::on_users_btn_clicked()
{
     ui->stackedWidget_2->setCurrentIndex(0);
     ui->username_input->clear();
     ui->password_input->clear();
     ui->balace_input->clear();
     ui->phone_input_3->clear();

}


void MainWindow::on_users_btn_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(0);
    ui->username_input->clear();
    ui->password_input->clear();
    ui->balace_input->clear();
    ui->phone_input_3->clear();
}


void MainWindow::on_transaction_btn_clicked()
{
     ui->stackedWidget_2->setCurrentIndex(6);
    ui->username_input->clear();
    ui->password_input->clear();
    ui->balace_input->clear();
    ui->phone_input_3->clear();
    ui->transactions_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void MainWindow::on_transaction_btn_2_clicked()
{
    ui->stackedWidget_2->setCurrentIndex(6);
    ui->username_input->clear();
    ui->password_input->clear();
    ui->balace_input->clear();
    ui->phone_input_3->clear();
    ui->transactions_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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
    try {
        ui->stackedWidget_2->setCurrentIndex(2);
        ui->username_input->clear();
        ui->password_input->clear();
        ui->balace_input->clear();
        ui->phone_input_3->clear();
        if(!manger.getListOfUsers()->empty()){
            string id=  ui->comboBox_users->currentText().toStdString();
            if(!id.empty()){
                string username = manger.getListOfUsers()->at(stoi(id)).getUsername();
                string password= manger.getListOfUsers()->at(stoi(id)).getPassword();
                double balance=  manger.getListOfUsers()->at(stoi(id)).getBalance();
                ui->username_input_2->setText(QString::fromStdString(username) );
                ui->password_input_2->setText(QString::fromStdString(password) );
                ui->balance_input->setText(QString::number(balance,'f',2));
            }else{
                ui->username_input_2->setText("");
                ui->password_input_2->setText("");
                ui->balance_input->setText("");
            }
        }else{
            ui->username_input_2->setText("");
            ui->password_input_2->setText("");
            ui->balance_input->setText("");
        }

    } catch (const std::exception &e) {
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    }
}


void MainWindow::on_updateUsers_btn_2_clicked()
{
  try {
   ui->stackedWidget_2->setCurrentIndex(2);
      ui->username_input->clear();
      ui->password_input->clear();
      ui->balace_input->clear();
      ui->phone_input_3->clear();
    if(!manger.getListOfUsers()->empty()){

    string id=  ui->comboBox_users->currentText().toStdString();
        if(!id.empty()){
        string username = manger.getListOfUsers()->at(stoi(id)).getUsername();
        string password= manger.getListOfUsers()->at(stoi(id)).getPassword();
        double balance= manger.getListOfUsers()->at(stoi(id)).getBalance();
        ui->username_input_2->setText(QString::fromStdString(username) );
        ui->password_input_2->setText(QString::fromStdString(password) );
        ui->balance_input->setText(QString::number(balance,'f',2));
        }else{
            ui->username_input_2->setText("");
            ui->password_input_2->setText("");
            ui->balance_input->setText("");
        }
    }else{
        ui->username_input_2->setText("");
        ui->password_input_2->setText("");
        ui->balance_input->setText("");
    }

    } catch (const std::exception &e) {
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    }
}


void MainWindow::on_deleteUsers_btn_clicked()
{
    try {
        ui->stackedWidget_2->setCurrentIndex(3);
        ui->username_input->clear();
        ui->password_input->clear();
        ui->balace_input->clear();
        ui->phone_input_3->clear();
        if (!manger.getListOfUsers()->empty()) {
            string id = ui->comboBox_users_2->currentText().toStdString();
            if(!id.empty()){
            string username = manger.getListOfUsers()->at(stoi(id)).getUsername();
            string password = manger.getListOfUsers()->at(stoi(id)).getPassword();
            double balance = manger.getListOfUsers()->at(stoi(id)).getBalance();
            ui->username_input_3->setText(QString::fromStdString(username));
            ui->password_input_3->setText(QString::fromStdString(password));
            ui->balance_input_2->setText(QString::number(balance,'f',2));
            }else{
                ui->username_input_3->setText("");
                ui->password_input_3->setText("");
                ui->balance_input_2->setText("");
            }
        } else {
            ui->username_input_3->setText("");
            ui->password_input_3->setText("");
            ui->balance_input_2->setText("");
        }
    } catch (const std::exception &e) {
        // Handle exception
        // For example, show an error message
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        // Handle unknown exception
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }

}


void MainWindow::on_deleteUsers_btn_2_clicked()
{
    try {
        ui->stackedWidget_2->setCurrentIndex(3);
        ui->username_input->clear();
        ui->password_input->clear();
        ui->balace_input->clear();
        ui->phone_input_3->clear();
        if (!manger.getListOfUsers()->empty()) {
            string id = ui->comboBox_users_2->currentText().toStdString();
            if(!id.empty()){
                string username = manger.getListOfUsers()->at(stoi(id)).getUsername();
                string password = manger.getListOfUsers()->at(stoi(id)).getPassword();
                double balance = manger.getListOfUsers()->at(stoi(id)).getBalance();
                ui->username_input_3->setText(QString::fromStdString(username));
                ui->password_input_3->setText(QString::fromStdString(password));
                ui->balance_input_2->setText(QString::number(balance,'f',2));
            }else{
                ui->username_input_3->setText("");
                ui->password_input_3->setText("");
                ui->balance_input_2->setText("");
            }
        } else {
            ui->username_input_3->setText("");
            ui->password_input_3->setText("");
            ui->balance_input_2->setText("");
        }
    } catch (const std::exception &e) {
        // Handle exception
        // For example, show an error message
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        // Handle unknown exception
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }

}

void MainWindow::on_user_btn_2_clicked()
{
    ui->username_input->clear();
    ui->password_input->clear();
    ui->balace_input->clear();
    ui->phone_input_3->clear();
      ui->stackedWidget_2->setCurrentIndex(5);
}


void MainWindow::on_logout_4_clicked()
{
    ui->frameSignUp->setVisible(false);
    ui->HomePage->setVisible(false);
    ui->HomePage_Admin->setVisible(false);
    ui->frameLanding->setVisible(false);
    ui->LinePhoneNumber->clear();
    ui->linePassword->clear();
    ui->username_input->clear();
    ui->password_input->clear();
    ui->balace_input->clear();
    ui->phone_input_3->clear();
    ui->visible_btn->setVisible(true);
    ui->visible_btn_2->setVisible(false);
    ui->frameLogin->show();
}


void MainWindow::on_logout_3_clicked()
{


    ui->frameSignUp->setVisible(false);
    ui->HomePage->setVisible(false);
    ui->HomePage_Admin->setVisible(false);
    ui->frameLanding->setVisible(false);
    ui->LinePhoneNumber->clear();
    ui->linePassword->clear();
    ui->username_input->clear();
    ui->password_input->clear();
    ui->balace_input->clear();
    ui->phone_input_3->clear();
    ui->visible_btn->setVisible(true);
    ui->visible_btn_2->setVisible(false);
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

// Send Money
void MainWindow::on_sendMoney_btn_2_clicked()
{
    sendMoney();

}

// Recieve Money
void MainWindow::on_recieve_money_btn_clicked()
{
    recieveMoney();
}
void MainWindow::on_edit_btn_clicked()
{
  ui->lineEdit->setReadOnly(false);
  ui->lineEdit->setAlignment(Qt::AlignLeft);
  ui->lineEdit->setFocus();
  ui->change_btn_3->setVisible(true);
  ui->edit_btn->setVisible(false);
}


void MainWindow::on_deposit_btn_clicked()
{
    string amount = ui->amount_input_3->text().toStdString();

    // Check for empty fields
    if ( ui->amount_input_3->text().isEmpty()) {
        QMessageBox::warning(nullptr, "Empty Field", "The field is empty. Please enter some text.");
        return;
    }

    // Check for numerical amount
    else if (!isNumerical(amount)) {
        QMessageBox::warning(nullptr, "Invalid Data", "Enter numerical data.");
        ui->amount_input_2->setFocus();
        return;
    }
    else if(stod(amount)>10000.0){
       QMessageBox::information(nullptr, "Exceeding the limit", "The deposit exceeds the limit.");
    }
    else{
        double  newAmount = manger.getListOfUsers()->at(id).getBalance()+stod(amount);
        manger.adjustBalance(id,newAmount);
        incomes+=stod(amount);

        QMessageBox::information(nullptr, "Deposit Successful", "Money has been successfully deposited to your account.");
        ui->label_6->setText(QString::number(newAmount, 'f', 2));
        ui->label_93->setText(QString::number(newAmount, 'f', 2));
        ui->balance_label->setText(QString::number(newAmount, 'f', 2));
        ui->label_80->setText(QString::number(newAmount, 'f', 2));
        ui->label_82->setText(QString::number(incomes, 'f', 2));
        ui->label_85->setText(QString::number(expenses, 'f', 2));
        ui->label_95->setText(QString::number(incomes, 'f', 2));
        ui->label_98->setText(QString::number(expenses, 'f', 2));
        ui->label_11->setText(QString::number(incomes, 'f', 2));
        ui->label_28->setText(QString::number(expenses, 'f', 2));
        ui->incomes->setText(QString::number(incomes, 'f', 2));
        ui->expenses->setText(QString::number(expenses, 'f', 2));
        ui->amount_input_3->clear();
    }

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

// Change Profile
void MainWindow::on_change_btn_3_clicked()
{
changeProfile();

}

// Add User
void MainWindow::on_add_btn_clicked()
{
    addUser();

}
// Update User
void MainWindow::on_update_btn_clicked()
{
    updateUser();

}

// Delete User
void MainWindow::on_delete_user_btn_clicked()
{

    deleteUser();


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


void MainWindow::on_comboBox_users_currentTextChanged(const QString &arg1) {
    try {
        string id = ui->comboBox_users->currentText().toStdString();
         if(!id.empty()){
        string username = manger.getListOfUsers()->at(stoi(id)).getUsername();
        string password = manger.getListOfUsers()->at(stoi(id)).getPassword();
        double balance = manger.getListOfUsers()->at(stoi(id)).getBalance();
        bool suspended=manger.getListOfUsers()->at(stoi(id)).getSuspended();
        ui->username_input_2->setText(QString::fromStdString(username));
        ui->password_input_2->setText(QString::fromStdString(password));
        ui->balance_input->setText(QString::number(balance,'f',2));
        ui->checkBox->setChecked(suspended);
         }else{
             ui->username_input_2->setText("");
             ui->password_input_2->setText("");
             ui->balance_input->setText("");

         }
    } catch (const std::exception &e) {
        // Handle exception
        // For example, show an error message
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        // Handle unknown exception
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }
}


void MainWindow::on_comboBox_users_2_currentTextChanged(const QString &arg1) {
    try {


        string id = ui->comboBox_users_2->currentText().toStdString();

         if(!id.empty()){
        string username = manger.getListOfUsers()->at(stoi(id)).getUsername();
        string password = manger.getListOfUsers()->at(stoi(id)).getPassword();
        double balance = manger.getListOfUsers()->at(stoi(id)).getBalance();
        ui->username_input_3->setText(QString::fromStdString(username));
        ui->password_input_3->setText(QString::fromStdString(password));
        ui->balance_input_2->setText(QString::number(balance,'f',2));
         }else{
             ui->username_input_3->setText("");
             ui->password_input_3->setText("");
             ui->balance_input_2->setText("");
         }
    } catch (const std::exception &e) {
        // Handle exception
        // For example, show an error message
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        // Handle unknown exception
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }
}


void MainWindow::on_comboBox_users_3_currentTextChanged(const QString &arg1) {
    try {
        string id = ui->comboBox_users_3->currentText().toStdString();
         if(!id.empty()){
           loadAdminTransactions(stoi(id));
         }else{
            ui->transactions_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->transactions_table->setRowCount(0);
         }
    } catch (const std::exception &e) {
        // Handle exception
        // For example, show an error message
        QMessageBox::warning(nullptr, "Exception", QString("An exception occurred: %1").arg(e.what()));
    } catch (...) {
        // Handle unknown exception
        QMessageBox::warning(nullptr, "Exception", "An unknown exception occurred.");
    }
}


void MainWindow::on_forget_btn_clicked()
{
    ui->LinePhoneNumber->clear();
    ui->linePassword->clear();
    ui->visible_btn->setVisible(true);
    ui->visible_btn_2->setVisible(false);
    ui->Login->setText("Reset Password");
    ui->linePassword->setPlaceholderText("New Password");
    ui->forget_btn->setVisible(false);
    ui->btn_ToSignUp->setVisible(false);
    ui->btnLogin->setVisible(false);
    ui->btnResetPassword->setVisible(true);
    ui->back_btn->setVisible(true);

}


void MainWindow::on_btnResetPassword_clicked()
{
    string phone = ui->LinePhoneNumber->text().toStdString();
    string password = ui->linePassword->text().toStdString();

    if (phone.empty() || password.empty()) {
        QMessageBox::warning(nullptr, "Empty Field", "The field is empty. Please enter some text.");
        return;
    }
   else if (!Egyptian_PhoneNumber(phone)) {
        QMessageBox::warning(nullptr, "Invalid Phone Number", "Please enter a valid Egyptian phone number (01XXXXXXXXX) with 11 digits.");
        ui->LinePhoneNumber->setFocus();
        return;
    }
   else if (!isValidPassword(QString::fromStdString(password))) {
        QMessageBox::warning(nullptr, "Invalid Password", "Please enter a valid password (minimum eight characters, at least one uppercase letter, one lowercase letter, and one number).");
        ui->linePassword->setFocus();
        return;
    }
    else {
        if(manger.getListOfUsers()->find(stoi(phone))==manger.getListOfUsers()->end()){
           QMessageBox::warning(nullptr, "Phone Number Not Exists", "This phone number is not found.");
            return;
        }else{
            manger.getListOfUsers()->at(stoi(phone)).setPassword(password);
            QMessageBox::information(nullptr, "Password Reset Successful", "Your password has been successfully reset.");

        }
    }
    ui->Login->setText("LOGIN");
    ui->linePassword->setPlaceholderText("Password");
    ui->forget_btn->setVisible(true);
    ui->btn_ToSignUp->setVisible(true);
    ui->btnLogin->setVisible(true);
    ui->btnResetPassword->setVisible(false);
    ui->visible_btn->setVisible(true);
    ui->visible_btn_2->setVisible(false);
    ui->LinePhoneNumber->clear();
    ui->linePassword->clear();
    ui->back_btn->setVisible(false);
}


void MainWindow::on_back_btn_clicked()
{
    ui->Login->setText("LOGIN");
    ui->linePassword->setPlaceholderText("Password");
    ui->forget_btn->setVisible(true);
    ui->btn_ToSignUp->setVisible(true);
    ui->btnLogin->setVisible(true);
    ui->btnResetPassword->setVisible(false);
    ui->visible_btn->setVisible(true);
    ui->visible_btn_2->setVisible(false);
    ui->LinePhoneNumber->clear();
    ui->linePassword->clear();
    ui->back_btn->setVisible(false);
}



