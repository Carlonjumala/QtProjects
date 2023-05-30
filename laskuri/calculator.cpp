#include "calculator.h"
#include "ui_calculator.h"
#include <QDebug>

double calVal=0.0;
bool divTrigger=false;
bool multTrigger=false;
bool addTrigger=false;
bool subTrigger=false;


Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calVal));
    QPushButton*numButtons[10];
    for(int i=0;i<10;++i){
        QString butName="digit" + QString::number(i);
        numButtons[i]=Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i],SIGNAL(released()), this, SLOT(NumPressed()));
    }

    connect(ui->Plus,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Minus,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Multiply,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Divide,SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Equal,SIGNAL(released()),this,SLOT(EqualButtonPressed()));
    connect(ui->Clear,SIGNAL(released()),this,SLOT(ClearButtonPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton*)sender();
    QString butval = button->text();
    QString displayVal=ui->Display->text();
    if((displayVal.toDouble()==0)||displayVal.toDouble()==0.0){
        ui->Display->setText(butval);
    }
    else{
        QString newVal=displayVal+butval;
        double dblNewVal=newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::MathButtonPressed(){
    divTrigger=false;
    multTrigger=false;
    addTrigger=false;
    subTrigger=false;

    QString displayVal = ui->Display->text();
    calVal = displayVal.toDouble();
    QPushButton* button =(QPushButton *)sender();
    QString butVal = button->text();

    if(QString::compare(butVal,"/",Qt::CaseInsensitive)==0){
        divTrigger=true;
    }
    else if(QString::compare(butVal,"*",Qt::CaseInsensitive)==0){
        multTrigger=true;
    }
    else if(QString::compare(butVal,"+",Qt::CaseInsensitive)==0){
        addTrigger=true;
    }
    else {
        subTrigger=true;
    }
    ui->Display->setText("");
}

void Calculator::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayVal= ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger||subTrigger||multTrigger||divTrigger)
    {
        if(addTrigger){
        solution = calVal + dblDisplayVal;
        }
        else if(subTrigger){
         solution = calVal - dblDisplayVal;
        }else if(multTrigger){
         solution = calVal * dblDisplayVal;
        }else{
        solution = calVal/ dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}
void Calculator::ClearButtonPressed(){
     ui->Display->setText("0.0");
}




