#include "calculadora.h"
#include "ui_calculadora.h"
double calVal= 0.0;

bool ButtonMasTrigger = false;
bool ButtonMenosTrigger = false;
bool ButtonDiagonalTrigger = false;
bool ButtonMultiplicacionTrigger = false;
bool ButtonACTrigger = false;

Calculadora::Calculadora(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculadora)
{
     ui->setupUi(this);
    ui->Display->setText(QString::number(calVal));
    QPushButton *numButtons[10];
    for(int i = 0; i < 10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculadora::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));

    }
    connect(ui->ButtonMas, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonMenos, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonMultiplicacion, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonDiagonal, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonAC, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->ButtonIgual, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));


}

Calculadora::~Calculadora()
{
    delete ui;
}

void Calculadora::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->Display->setText(butVal);
    } else {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }

}

void Calculadora::MathButtonPressed(){
    ButtonDiagonalTrigger = false;
    ButtonMasTrigger = false;
    ButtonMultiplicacionTrigger = false;
    ButtonMenosTrigger = false;
    ButtonACTrigger = false;
    QString displayVal = ui->Display->text();
    calVal = displayVal.toDouble();
    QPushButton *button =(QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        ButtonDiagonalTrigger = true;
    } else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        ButtonMultiplicacionTrigger = true;
    } else if(QString::compare(butVal, "0.0", Qt::CaseInsensitive) == 0){
        ButtonMultiplicacionTrigger = true;

    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        ButtonMasTrigger = true;
    } else {
        ButtonMenosTrigger = true;
    }
        ui->Display->setText("");

}

void Calculadora::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(ButtonMasTrigger || ButtonMenosTrigger || ButtonMultiplicacionTrigger || ButtonDiagonalTrigger){
        if(ButtonMasTrigger){
            solution = calVal + dblDisplayVal;
        } else if(ButtonMenosTrigger){
            solution = calVal - dblDisplayVal;

        } else if(ButtonMultiplicacionTrigger){
            solution = calVal * dblDisplayVal;

        } else {
            solution = calVal / dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

