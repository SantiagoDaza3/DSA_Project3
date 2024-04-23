#include "mainwindow.h"
#include "./ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->execution_frame->hide();
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
    QString passage = ui->sent_anal_input->toPlainText();

    std::vector<float> emotions;
    if(table_used == 0){
        emotions = MMHTable.passage_sentiment_analysis(passage.toStdString(), 0);
    }
    else if(table_used == 1)
    {
        emotions = FNVTable.passage_sentiment_analysis(passage.toStdString(), 1);
    }



    QString sad_1 = QString::number(emotions[0]);
    QString joy_1 = QString::number(emotions[1]);
    QString love_1 = QString::number(emotions[2]);
    QString anger_1 = QString::number(emotions[3]);
    QString fear_1 = QString::number(emotions[4]);
    QString surp_1 = QString::number(emotions[5]);
    ui->lineEdit_sad1->setText(sad_1);
    ui->lineEdit_joy1->setText(joy_1);
    ui->lineEdit_love1->setText(love_1);
    ui->lineEdit_anger1->setText(anger_1);
    ui->lineEdit_fear1->setText(fear_1);
    ui->lineEdit_surp1->setText(surp_1);

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

    QString passage = ui->wrd_anal_line_edit->text();

    std::vector<float> emotions;
    if(table_used == 0){
        emotions = MMHTable.word_analysis(passage.toStdString(), 0);
    }
    else if(table_used == 1)
    {
        emotions = FNVTable.word_analysis(passage.toStdString(), 1);
    }

    QString sad_2 = QString::number(emotions[0]);
    QString joy_2 = QString::number(emotions[1]);
    QString love_2 = QString::number(emotions[2]);
    QString anger_2 = QString::number(emotions[3]);
    QString fear_2 = QString::number(emotions[4]);
    QString surp_2 = QString::number(emotions[5]);
    ui->lineEdit_sad2->setText(sad_2);
    ui->lineEdit_joy2->setText(joy_2);
    ui->lineEdit_love2->setText(love_2);
    ui->lineEdit_anger2->setText(anger_2);
    ui->lineEdit_fear2->setText(fear_2);
    ui->lineEdit_surp2->setText(surp_2);


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
    table_used = 0;
}


void MainWindow::on_fnv_btn_clicked()
{
    //Set hashing algorithm to FNV
    table_used = 1;
}


void MainWindow::on_back_btn4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    clear_all_text();
}


void MainWindow::on_contribute_btn_clicked()
{
    //Contribute to database using chosen parameters
    QString passage = ui->contribution_input_txt->toPlainText();

    std::string input_passage = passage.toStdString();

    if(table_used == 0){
        MMHTable.contribute_to_dataset(input_passage, ui->contribution_box->currentIndex(), 0);
    }
    else if(table_used == 1)
    {
        FNVTable.contribute_to_dataset(input_passage, ui->contribution_box->currentIndex(), 1);
    }


    ui->contribution_input_txt->clear();
    ui->contribution_box->setCurrentIndex(0);
}




void MainWindow::on_emo_ana_box_currentIndexChanged(int index)
{
    if(index > 0)
    {
        std::vector<Word*> emotions;
        if(table_used == 0){
            emotions = MMHTable.emotion_analysis(index - 1);
        }
        else if(table_used == 1)
        {
            emotions = FNVTable.emotion_analysis(index - 1);
        }
        std::string return_thingy = "";
        for(int i = 0; i < 10; i++)
        {
            return_thingy += emotions[i]->word_name + ", ";
        }
        return_thingy.pop_back();
        return_thingy.pop_back();
        QString actual_return = QString::fromStdString(return_thingy);
        ui->emo_anl_txt_edit->setText(actual_return);
    }
}


void MainWindow::on_hash_stat_btn_clicked()
{
    unsigned int num_collisions_mmh = MMHTable.return_collisions();
    unsigned int num_collisions_fnv = FNVTable.return_collisions();

    float exec_time_mmh = MMHTable.returnExecutionTime();
    float exec_time_fnv = FNVTable.returnExecutionTime();

    QString input_string = "";

    input_string += "MMH Collisions: " + QString::number(num_collisions_mmh) + "\n";
    input_string += "FNV Collisions: " + QString::number(num_collisions_fnv) + "\n";
    input_string += "MMH Exec Time: " + QString::number(exec_time_mmh) + " ms" + "\n";
    input_string += "FNV Exec Time: " + QString::number(exec_time_fnv) + " ms" + "\n";

    ui->stats_text->setText(input_string);
}

