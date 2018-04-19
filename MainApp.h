#ifndef MAINAPP_H
#define MAINAPP_H
#include <QApplication>
#include <QMessageBox>

class MainApp : public QApplication
{
    Q_OBJECT
public:
    MainApp(int &argc, char** argv) : QApplication(argc, argv) {};
private:
    bool event(QEvent *e);
signals:
    void closing();
};

class AboutQtDialog : public QMessageBox
{
    Q_OBJECT
public slots:
    void aboutQt();
};

#endif // MAINAPP_H


