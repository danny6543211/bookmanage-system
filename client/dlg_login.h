#ifndef DLG_LOGIN_H
#define DLG_LOGIN_H

#include <QDialog>

namespace Ui {
class Dlg_Login;
}

class Dlg_Login : public QDialog
{
    Q_OBJECT

public:
    explicit Dlg_Login(QWidget *parent = nullptr);
    ~Dlg_Login();
    char* acc;
    char* psw;


private slots:
    void on_LogInButton_clicked();

    void on_ExitButton_clicked();

    void on_RegisterButton_clicked();

private:
    Ui::Dlg_Login *ui;

};

#endif // DLG_LOGIN_H
