#include "secwind.h"
#include "ui_secwind.h"

int Res[10][10] = {0}; // Solved sudoku puzzle to display
double time1 = 0;      // Execution time of algorithm
SecWind::SecWind(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecWind)
{
    ui->setupUi(this);
    ui->line->setLineWidth(4);
    ui->line_4->setLineWidth(4);
    ui->line_2->setLineWidth(4);
    ui->line_3->setLineWidth(4);

    QObject::connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(close()));

}

SecWind::~SecWind()
{
    delete ui;
}

// Convert data received from *a to 2d integer array
void SecWind::dispresult(int *a, double t2) {
    QString mine = "";
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            Res[i][j] = *a;
            mine += "" + QString::number(Res[i][j]);
            a++;
        }
    }

    time1 = t2;

}

//     Display data stored in array Res to output window
void SecWind::outresult() {

    ui->label11->setText(QString::number(Res[1][1]));
    ui->label12->setText(QString::number(Res[1][2]));
    ui->label13->setText(QString::number(Res[1][3]));
    ui->label14->setText(QString::number(Res[1][4]));
    ui->label15->setText(QString::number(Res[1][5]));
    ui->label16->setText(QString::number(Res[1][6]));
    ui->label17->setText(QString::number(Res[1][7]));
    ui->label18->setText(QString::number(Res[1][8]));
    ui->label19->setText(QString::number(Res[1][9]));

    ui->label21->setText(QString::number(Res[2][1]));
    ui->label22->setText(QString::number(Res[2][2]));
    ui->label23->setText(QString::number(Res[2][3]));
    ui->label24->setText(QString::number(Res[2][4]));
    ui->label25->setText(QString::number(Res[2][5]));
    ui->label26->setText(QString::number(Res[2][6]));
    ui->label27->setText(QString::number(Res[2][7]));
    ui->label28->setText(QString::number(Res[2][8]));
    ui->label29->setText(QString::number(Res[2][9]));

    ui->label31->setText(QString::number(Res[3][1]));
    ui->label32->setText(QString::number(Res[3][2]));
    ui->label33->setText(QString::number(Res[3][3]));
    ui->label34->setText(QString::number(Res[3][4]));
    ui->label35->setText(QString::number(Res[3][5]));
    ui->label36->setText(QString::number(Res[3][6]));
    ui->label37->setText(QString::number(Res[3][7]));
    ui->label38->setText(QString::number(Res[3][8]));
    ui->label39->setText(QString::number(Res[3][9]));

    ui->label41->setText(QString::number(Res[4][1]));
    ui->label42->setText(QString::number(Res[4][2]));
    ui->label43->setText(QString::number(Res[4][3]));
    ui->label44->setText(QString::number(Res[4][4]));
    ui->label45->setText(QString::number(Res[4][5]));
    ui->label46->setText(QString::number(Res[4][6]));
    ui->label47->setText(QString::number(Res[4][7]));
    ui->label48->setText(QString::number(Res[4][8]));
    ui->label49->setText(QString::number(Res[4][9]));

    ui->label51->setText(QString::number(Res[5][1]));
    ui->label52->setText(QString::number(Res[5][2]));
    ui->label53->setText(QString::number(Res[5][3]));
    ui->label54->setText(QString::number(Res[5][4]));
    ui->label55->setText(QString::number(Res[5][5]));
    ui->label56->setText(QString::number(Res[5][6]));
    ui->label57->setText(QString::number(Res[5][7]));
    ui->label58->setText(QString::number(Res[5][8]));
    ui->label59->setText(QString::number(Res[5][9]));

    ui->label61->setText(QString::number(Res[6][1]));
    ui->label62->setText(QString::number(Res[6][2]));
    ui->label63->setText(QString::number(Res[6][3]));
    ui->label64->setText(QString::number(Res[6][4]));
    ui->label65->setText(QString::number(Res[6][5]));
    ui->label66->setText(QString::number(Res[6][6]));
    ui->label67->setText(QString::number(Res[6][7]));
    ui->label68->setText(QString::number(Res[6][8]));
    ui->label69->setText(QString::number(Res[6][9]));

    ui->label71->setText(QString::number(Res[7][1]));
    ui->label72->setText(QString::number(Res[7][2]));
    ui->label73->setText(QString::number(Res[7][3]));
    ui->label74->setText(QString::number(Res[7][4]));
    ui->label75->setText(QString::number(Res[7][5]));
    ui->label76->setText(QString::number(Res[7][6]));
    ui->label77->setText(QString::number(Res[7][7]));
    ui->label78->setText(QString::number(Res[7][8]));
    ui->label79->setText(QString::number(Res[7][9]));

    ui->label81->setText(QString::number(Res[8][1]));
    ui->label82->setText(QString::number(Res[8][2]));
    ui->label83->setText(QString::number(Res[8][3]));
    ui->label84->setText(QString::number(Res[8][4]));
    ui->label85->setText(QString::number(Res[8][5]));
    ui->label86->setText(QString::number(Res[8][6]));
    ui->label87->setText(QString::number(Res[8][7]));
    ui->label88->setText(QString::number(Res[8][8]));
    ui->label89->setText(QString::number(Res[8][9]));

    ui->label91->setText(QString::number(Res[9][1]));
    ui->label92->setText(QString::number(Res[9][2]));
    ui->label93->setText(QString::number(Res[9][3]));
    ui->label94->setText(QString::number(Res[9][4]));
    ui->label95->setText(QString::number(Res[9][5]));
    ui->label96->setText(QString::number(Res[9][6]));
    ui->label97->setText(QString::number(Res[9][7]));
    ui->label98->setText(QString::number(Res[9][8]));
    ui->label99->setText(QString::number(Res[9][9]));

    ui->label_2->setText(QString::number(time1));

}
