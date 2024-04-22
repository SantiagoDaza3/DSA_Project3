#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Snt_Anal_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_back_btn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clear_all_text();
}


void MainWindow::on_back_btn2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clear_all_text();
}


void MainWindow::on_analyze_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_main_menu_btn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clear_all_text();
}


void MainWindow::on_Wrd_Anal_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_wrd_analyze_btn_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_main_menu_btn2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clear_all_text();
}

void MainWindow::clear_all_text(){
    ui->lineEdit_anger2->setText("0");
    ui->lineEdit_fear2->setText("0");
    ui->lineEdit_joy2->setText("0");
    ui->lineEdit_love2->setText("0");
    ui->lineEdit_sad2->setText("0");
    ui->lineEdit_surp2->setText("0");
    ui->wrd_anal_line_edit->clear();
    ui->sent_anal_input->clear();
    ui->lineEdit_anger1->setText("0");
    ui->lineEdit_fear1->setText("0");
    ui->lineEdit_joy1->setText("0");
    ui->lineEdit_love1->setText("0");
    ui->lineEdit_sad1->setText("0");
    ui->lineEdit_surp1->setText("0");
    ui->emo_ana_box->setCurrentIndex(0);
    ui->emo_anl_txt_edit->clear();
    ui->contribution_input_txt->clear();
    ui->contribution_box->setCurrentIndex(0);
}

void MainWindow::on_Emo_Anl_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_back_btn3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clear_all_text();
}


void MainWindow::on_contribute_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_murmur_btn_clicked()
{
    //Set hashing algorithm to murmurhash
}


void MainWindow::on_fnv_btn_clicked()
{
    //Set hashing algorithm to FNV
}


void MainWindow::on_back_btn4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clear_all_text();
}


void MainWindow::on_contribute_btn_clicked()
{
    ui->contribution_input_txt->clear();
    ui->contribution_box->setCurrentIndex(0);

    //Contribute to database using chosen parameters
}

