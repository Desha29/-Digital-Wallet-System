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
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:
    void login();
    void loadUsers();
    void loadTransactions();

    void on_btnLogin_clicked();
    void on_btn_ToSignUp_clicked();

    void on_btnSignUp_clicked();
    void on_btn_ToLogin_clicked();



    void on_btnSignUp_1_clicked();

    void on_btnLogin_1_clicked();

    void on_search_btn_clicked();

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

    void on_search_btn_2_clicked();

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

    void on_sendMoney_btn_5_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
