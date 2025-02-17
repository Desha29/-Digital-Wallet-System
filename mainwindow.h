#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"admin.h"
#include <QMainWindow>
#include<QMessageBox>
#include"FileStream.h"
#include<QComboBox>
#include<QLineEdit>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT;
    Admin manger;
    int id;
    double incomes=0.0;
    double expenses=0.0;


public:
    MainWindow(QWidget *parent = nullptr);
    void login();
    void signUp();
    void sendMoney();
    void recieveMoney();
    void addUser();
    void updateUser();
    void deleteUser();
    void changeProfile();
    void loadUsers();
    void loadUserTransactions(int id_User);
    void loadRequest(int id_User);
    void loadRequestHistory(int id_User);
    void loadAdminTransactions(int id_User=0);
    void updateComboBox(QComboBox* combo_1,QComboBox* combo_2,QComboBox* combo_3);
    bool Egyptian_PhoneNumber(const string& phoneNumber);
    bool isNumerical(const string& input);
    bool isValidUsername(const QString &username);
    bool isValidPassword(const QString &password);
    ~MainWindow();

private slots:

    void on_btnLogin_clicked();

    void on_btn_ToSignUp_clicked();

    void on_btnSignUp_clicked();

    void on_btn_ToLogin_clicked();

    void on_btnSignUp_1_clicked();

    void on_btnLogin_1_clicked();

    void on_user_btn_clicked();

    void on_home_btn1_2_clicked();

    void on_home_btn2_clicked();

    void on_logout_2_clicked();

    void on_logout_clicked();

    void on_users_btn_clicked();

    void on_users_btn_2_clicked();

    void on_transaction_btn_clicked();

    void on_transaction_btn_2_clicked();

    void on_addUsers_btn_clicked();

    void on_addUsers_btn_2_clicked();

    void on_updateUsers_btn_clicked();

    void on_updateUsers_btn_2_clicked();

    void on_deleteUsers_btn_clicked();

    void on_deleteUsers_btn_2_clicked();

    void on_user_btn_2_clicked();

    void on_logout_4_clicked();

    void on_logout_3_clicked();

    void on_transaction_btn_4_clicked();

    void on_transaction_btn_3_clicked();

    void on_invoices_btn_2_clicked();

    void on_invoices_btn_clicked();

    void on_wallets_btn_2_clicked();

    void on_wallets_btn_clicked();

    void on_sendMoney_btn_3_clicked();

    void on_RecieveMoney_2_btn_clicked();

    void on_sendMoney_btn_2_clicked();

    void on_edit_btn_clicked();

    void on_edit_btn_2_clicked();

    void on_change_btn_3_clicked();

    void on_add_btn_clicked();

    void on_visible_btn_clicked();

    void on_visible_btn_2_clicked();

    void on_visible_btn_3_clicked();

    void on_visible_btn_4_clicked();

    void on_comboBox_users_currentTextChanged(const QString &arg1);

    void on_comboBox_users_2_currentTextChanged(const QString &arg1);

    void on_update_btn_clicked();

    void on_delete_user_btn_clicked();

    void on_comboBox_users_3_currentTextChanged(const QString &arg1);

    void on_recieve_money_btn_clicked();

    void on_request_btn_clicked();

    void on_request_btn_2_clicked();

    void on_forget_btn_clicked();

    void on_btnResetPassword_clicked();

    void on_back_btn_clicked();

    void on_cash_btn_clicked();

    void on_cash_btn_2_clicked();

    void on_deposit_btn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
