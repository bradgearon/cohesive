#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObjectList children = ui->centralWidget->children();
    int childCount = children.count();

    foreach(QObject* child, children) {
        QVariant className = child->property("className");
        if(className == "Card") {
            connect(child, SIGNAL(onHover(QEvent*, bool, QObject*)), this, SLOT(OnCardHover(QEvent*, bool, QObject*)));
        }

    }
}

void MainWindow::OnCardHover(QEvent *event, bool hover, QObject* sender) {
    QPushButton* b = (QPushButton*) sender;
    b->setProperty("className", hover ? "Flipped" : "Card");

    this->setStyleSheet(this->styleSheet());
}



MainWindow::~MainWindow()
{
    delete ui;
}
