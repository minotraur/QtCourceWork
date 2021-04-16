#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "MyModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void onAppend();
    void onChange();
    void onDowload();
    void onSave();

    void on_AddStudentButton_clicked();

    void on_pushButtonEditStudent_clicked();

    void on_RemoveStudentButton_clicked();

    void on_ReadCSVButton_clicked();

    void on_WriteCSVButton_clicked();

private:
    Ui::MainWindow *ui;
    PersonsModel* m_model;
};
#endif // MAINWINDOW_H






