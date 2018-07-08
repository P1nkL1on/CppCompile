#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "valuetypetests.h"
#include "waiter.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    runTests();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::runTests()
{
    LCompile::ValueTypeTests vtTests;
    QTest::qExec(&vtTests);
    LCompile::Waiter w;
    w.parse(QStringList()
            << QString("  int   float;   ")
            << QString("  voidfloatint***intint")
            << QString("   float*** ** int * * *")
            << QString("   void void int   v o i d"));
}
