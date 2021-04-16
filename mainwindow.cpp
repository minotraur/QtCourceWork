#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextStream>
#include <QFile>

#include "MyModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->tableView->setModel(m_model = new PersonsModel);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onAppend() {
    m_model->appendPerson(
        ui->lineEditID->text(),
        ui->lineEditLastName->text(),
        ui->lineEditCity->text()
    );
}
void MainWindow::onChange() {
    m_model->changeData(
        ui->lineEditID->text(),
        ui->lineEditLastName->text(),
        ui->lineEditCity->text()
    );
}
void MainWindow::onDowload() {
    m_model->dowloadData();
}

void MainWindow::onSave()
{
    m_model->saveData();
}

void MainWindow::on_AddStudentButton_clicked()
{
    onAppend();
}

void MainWindow::on_pushButtonEditStudent_clicked()
{
    onChange();
}

void MainWindow::on_RemoveStudentButton_clicked()
{
    m_model->removeSelected(ui->tableView->currentIndex().row());
}

void MainWindow::on_ReadCSVButton_clicked()
{
    onDowload();
}

void MainWindow::on_WriteCSVButton_clicked()
{
    onSave();
}
