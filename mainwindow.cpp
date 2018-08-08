#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "secwind.h"
#include <QProcess>
#include <QResizeEvent>

int a[10][10] = {0};  // Contains Sudoku puzzle to solve
int b1[10][10] = {0}; // Solved sudoku puzzle to send to second window

QStringList data2;
int gencount = 0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->thread->setValue(4);
    QObject::connect(ui->close_button,SIGNAL(clicked(bool)),qApp,SLOT(quit()));

    // Setup puzzles for generate button

    data2 << "000000680000073009309000045490000000803050902000000036960000308700680000028000000";
    data2 << "080004010000060005462000037007030000040000000025710008070300021000009000050000900";

    //worst case (takes long time)
    data2 << "000000000000003085001020000000507000004000100090000000500000073002010000000040009";
    data2 << "800000000003600000070090200050007000000045700000100030001000068008500010090000400";
    data2 << "006253400000000007100000050000306084050000010460501000040000009900000000000000000";
    data2 << "070036108300000060058000000760309200000147000009605084000000830020000005506810020";
    data2 << "000009430897004106000810950200000780009207600074000003025078000903100872018900000";
    data2 << "050002080009783010004000002100508600006070100007104008900000500020946800040800020";
    data2 << "700410006009080015010000002192030000406000103000060298900000060320040800600057009";
    data2 << "046080370000047205002001000200700930000209000093004002000400100408690000029070680";
    data2 << "000609835000700100000020407007034002035000940800190700406010000009005000513407000";
    data2 << "006000080000070260019408030050310800008604700002089040080206370025090000090000600";
    data2 << "100500060002608700000320480000019047004000100830450000075063000008902500040005006";

    newserver = new QTcpServer(this);
    connect(newserver, SIGNAL(newConnection()), this, SLOT(connection()));
    if(!newserver->listen(QHostAddress::Any, 8080)) {
        qDebug() << "Server initiated";
    }
    else
        qDebug() << "Failed";

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Implementation of solve button
void MainWindow::on_pushButton_clicked()
{

//  Assign values from input panel
//  to 2d array a
    a[1][1] = ui->s11->value();
    a[1][2] = ui->s12->value();
    a[1][3] = ui->s13->value();
    a[1][4] = ui->s14->value();
    a[1][5] = ui->s15->value();
    a[1][6] = ui->s16->value();
    a[1][7] = ui->s17->value();
    a[1][8] = ui->s18->value();
    a[1][9] = ui->s19->value();

    a[2][1] = ui->s21->value();
    a[2][2] = ui->s22->value();
    a[2][3] = ui->s23->value();
    a[2][4] = ui->s24->value();
    a[2][5] = ui->s25->value();
    a[2][6] = ui->s26->value();
    a[2][7] = ui->s27->value();
    a[2][8] = ui->s28->value();
    a[2][9] = ui->s29->value();

    a[3][1] = ui->s31->value();
    a[3][2] = ui->s32->value();
    a[3][3] = ui->s33->value();
    a[3][4] = ui->s34->value();
    a[3][5] = ui->s35->value();
    a[3][6] = ui->s36->value();
    a[3][7] = ui->s37->value();
    a[3][8] = ui->s38->value();
    a[3][9] = ui->s39->value();

    a[4][1] = ui->s41->value();
    a[4][2] = ui->s42->value();
    a[4][3] = ui->s43->value();
    a[4][4] = ui->s44->value();
    a[4][5] = ui->s45->value();
    a[4][6] = ui->s46->value();
    a[4][7] = ui->s47->value();
    a[4][8] = ui->s48->value();
    a[4][9] = ui->s49->value();

    a[5][1] = ui->s51->value();
    a[5][2] = ui->s52->value();
    a[5][3] = ui->s53->value();
    a[5][4] = ui->s54->value();
    a[5][5] = ui->s55->value();
    a[5][6] = ui->s56->value();
    a[5][7] = ui->s57->value();
    a[5][8] = ui->s58->value();
    a[5][9] = ui->s59->value();

    a[6][1] = ui->s61->value();
    a[6][2] = ui->s62->value();
    a[6][3] = ui->s63->value();
    a[6][4] = ui->s64->value();
    a[6][5] = ui->s65->value();
    a[6][6] = ui->s66->value();
    a[6][7] = ui->s67->value();
    a[6][8] = ui->s68->value();
    a[6][9] = ui->s69->value();

    a[7][1] = ui->s71->value();
    a[7][2] = ui->s72->value();
    a[7][3] = ui->s73->value();
    a[7][4] = ui->s74->value();
    a[7][5] = ui->s75->value();
    a[7][6] = ui->s76->value();
    a[7][7] = ui->s77->value();
    a[7][8] = ui->s78->value();
    a[7][9] = ui->s79->value();

    a[8][1] = ui->s81->value();
    a[8][2] = ui->s82->value();
    a[8][3] = ui->s83->value();
    a[8][4] = ui->s84->value();
    a[8][5] = ui->s85->value();
    a[8][6] = ui->s86->value();
    a[8][7] = ui->s87->value();
    a[8][8] = ui->s88->value();
    a[8][9] = ui->s89->value();

    a[9][1] = ui->s91->value();
    a[9][2] = ui->s92->value();
    a[9][3] = ui->s93->value();
    a[9][4] = ui->s94->value();
    a[9][5] = ui->s95->value();
    a[9][6] = ui->s96->value();
    a[9][7] = ui->s97->value();
    a[9][8] = ui->s98->value();
    a[9][9] = ui->s99->value();



//  Get path of application directory
    QString path = QCoreApplication::applicationDirPath ();

    path.append("/sud.out");

//    QString program = "var/mentor/sud";
    QStringList arguments;

//      Convert array a to QStringList
    for (int ko = 1; ko < 10; ko++) {
        for (int ko2 = 1; ko2 < 10; ko2++) {
            arguments << QString::number(a[ko][ko2]);
        }
    }

    int numThread = ui->thread->value();
    arguments << QString::number(numThread);



    QProcess *ps = new QProcess;
    QByteArray ba, ca;

//          Start eternal process at "path" with arguments
    ps->start(path,arguments);
    if (ps->waitForStarted(-1)) {
        ps->waitForFinished(-1);

    }

}

// Reset button
void MainWindow::on_pushButton_2_clicked()
{

//    Reset input panel to zero
    ui->s11->setValue(0);
    ui->s12->setValue(0);
    ui->s13->setValue(0);
    ui->s14->setValue(0);
    ui->s15->setValue(0);
    ui->s16->setValue(0);
    ui->s17->setValue(0);
    ui->s18->setValue(0);
    ui->s19->setValue(0);

    ui->s21->setValue(0);
    ui->s22->setValue(0);
    ui->s23->setValue(0);
    ui->s24->setValue(0);
    ui->s25->setValue(0);
    ui->s26->setValue(0);
    ui->s27->setValue(0);
    ui->s28->setValue(0);
    ui->s29->setValue(0);

    ui->s31->setValue(0);
    ui->s32->setValue(0);
    ui->s33->setValue(0);
    ui->s34->setValue(0);
    ui->s35->setValue(0);
    ui->s36->setValue(0);
    ui->s37->setValue(0);
    ui->s38->setValue(0);
    ui->s39->setValue(0);

    ui->s41->setValue(0);
    ui->s42->setValue(0);
    ui->s43->setValue(0);
    ui->s44->setValue(0);
    ui->s45->setValue(0);
    ui->s46->setValue(0);
    ui->s47->setValue(0);
    ui->s48->setValue(0);
    ui->s49->setValue(0);

    ui->s51->setValue(0);
    ui->s52->setValue(0);
    ui->s53->setValue(0);
    ui->s54->setValue(0);
    ui->s55->setValue(0);
    ui->s56->setValue(0);
    ui->s57->setValue(0);
    ui->s58->setValue(0);
    ui->s59->setValue(0);

    ui->s61->setValue(0);
    ui->s62->setValue(0);
    ui->s63->setValue(0);
    ui->s64->setValue(0);
    ui->s65->setValue(0);
    ui->s66->setValue(0);
    ui->s67->setValue(0);
    ui->s68->setValue(0);
    ui->s69->setValue(0);

    ui->s71->setValue(0);
    ui->s72->setValue(0);
    ui->s73->setValue(0);
    ui->s74->setValue(0);
    ui->s75->setValue(0);
    ui->s76->setValue(0);
    ui->s77->setValue(0);
    ui->s78->setValue(0);
    ui->s79->setValue(0);

    ui->s81->setValue(0);
    ui->s82->setValue(0);
    ui->s83->setValue(0);
    ui->s84->setValue(0);
    ui->s85->setValue(0);
    ui->s86->setValue(0);
    ui->s87->setValue(0);
    ui->s88->setValue(0);
    ui->s89->setValue(0);

    ui->s91->setValue(0);
    ui->s92->setValue(0);
    ui->s93->setValue(0);
    ui->s94->setValue(0);
    ui->s95->setValue(0);
    ui->s96->setValue(0);
    ui->s97->setValue(0);
    ui->s98->setValue(0);
    ui->s99->setValue(0);
}
// Implentation of generate button
void MainWindow::on_pushButton_3_clicked()
{


    int listnum = gencount++ % data2.size();

    // Assign values from any string in data2 QStringList

    ui->s11->setValue((data2.at(listnum))[0].digitValue());
    ui->s12->setValue((data2.at(listnum))[1].digitValue());
    ui->s13->setValue((data2.at(listnum))[2].digitValue());
    ui->s14->setValue((data2.at(listnum))[3].digitValue());
    ui->s15->setValue((data2.at(listnum))[4].digitValue());
    ui->s16->setValue((data2.at(listnum))[5].digitValue());
    ui->s17->setValue((data2.at(listnum))[6].digitValue());
    ui->s18->setValue((data2.at(listnum))[7].digitValue());
    ui->s19->setValue((data2.at(listnum))[8].digitValue());
    ui->s21->setValue((data2.at(listnum))[9].digitValue());
    ui->s22->setValue((data2.at(listnum))[10].digitValue());
    ui->s23->setValue((data2.at(listnum))[11].digitValue());
    ui->s24->setValue((data2.at(listnum))[12].digitValue());
    ui->s25->setValue((data2.at(listnum))[13].digitValue());
    ui->s26->setValue((data2.at(listnum))[14].digitValue());
    ui->s27->setValue((data2.at(listnum))[15].digitValue());
    ui->s28->setValue((data2.at(listnum))[16].digitValue());
    ui->s29->setValue((data2.at(listnum))[17].digitValue());

    ui->s31->setValue((data2.at(listnum))[18].digitValue());
    ui->s32->setValue((data2.at(listnum))[19].digitValue());
    ui->s33->setValue((data2.at(listnum))[20].digitValue());
    ui->s34->setValue((data2.at(listnum))[21].digitValue());
    ui->s35->setValue((data2.at(listnum))[22].digitValue());
    ui->s36->setValue((data2.at(listnum))[23].digitValue());
    ui->s37->setValue((data2.at(listnum))[24].digitValue());
    ui->s38->setValue((data2.at(listnum))[25].digitValue());
    ui->s39->setValue((data2.at(listnum))[26].digitValue());

    ui->s41->setValue((data2.at(listnum))[27].digitValue());
    ui->s42->setValue((data2.at(listnum))[28].digitValue());
    ui->s43->setValue((data2.at(listnum))[29].digitValue());
    ui->s44->setValue((data2.at(listnum))[30].digitValue());
    ui->s45->setValue((data2.at(listnum))[31].digitValue());
    ui->s46->setValue((data2.at(listnum))[32].digitValue());
    ui->s47->setValue((data2.at(listnum))[33].digitValue());
    ui->s48->setValue((data2.at(listnum))[34].digitValue());
    ui->s49->setValue((data2.at(listnum))[35].digitValue());

    ui->s51->setValue((data2.at(listnum))[36].digitValue());
    ui->s52->setValue((data2.at(listnum))[37].digitValue());
    ui->s53->setValue((data2.at(listnum))[38].digitValue());
    ui->s54->setValue((data2.at(listnum))[39].digitValue());
    ui->s55->setValue((data2.at(listnum))[40].digitValue());
    ui->s56->setValue((data2.at(listnum))[41].digitValue());
    ui->s57->setValue((data2.at(listnum))[42].digitValue());
    ui->s58->setValue((data2.at(listnum))[43].digitValue());
    ui->s59->setValue((data2.at(listnum))[44].digitValue());

    ui->s61->setValue((data2.at(listnum))[45].digitValue());
    ui->s62->setValue((data2.at(listnum))[46].digitValue());
    ui->s63->setValue((data2.at(listnum))[47].digitValue());
    ui->s64->setValue((data2.at(listnum))[48].digitValue());
    ui->s65->setValue((data2.at(listnum))[49].digitValue());
    ui->s66->setValue((data2.at(listnum))[50].digitValue());
    ui->s67->setValue((data2.at(listnum))[51].digitValue());
    ui->s68->setValue((data2.at(listnum))[52].digitValue());
    ui->s69->setValue((data2.at(listnum))[53].digitValue());

    ui->s71->setValue((data2.at(listnum))[54].digitValue());
    ui->s72->setValue((data2.at(listnum))[55].digitValue());
    ui->s73->setValue((data2.at(listnum))[56].digitValue());
    ui->s74->setValue((data2.at(listnum))[57].digitValue());
    ui->s75->setValue((data2.at(listnum))[58].digitValue());
    ui->s76->setValue((data2.at(listnum))[59].digitValue());
    ui->s77->setValue((data2.at(listnum))[60].digitValue());
    ui->s78->setValue((data2.at(listnum))[61].digitValue());
    ui->s79->setValue((data2.at(listnum))[62].digitValue());

    ui->s81->setValue((data2.at(listnum))[63].digitValue());
    ui->s82->setValue((data2.at(listnum))[64].digitValue());
    ui->s83->setValue((data2.at(listnum))[65].digitValue());
    ui->s84->setValue((data2.at(listnum))[66].digitValue());
    ui->s85->setValue((data2.at(listnum))[67].digitValue());
    ui->s86->setValue((data2.at(listnum))[68].digitValue());
    ui->s87->setValue((data2.at(listnum))[69].digitValue());
    ui->s88->setValue((data2.at(listnum))[70].digitValue());
    ui->s89->setValue((data2.at(listnum))[71].digitValue());

    ui->s91->setValue((data2.at(listnum))[72].digitValue());
    ui->s92->setValue((data2.at(listnum))[73].digitValue());
    ui->s93->setValue((data2.at(listnum))[74].digitValue());
    ui->s94->setValue((data2.at(listnum))[75].digitValue());
    ui->s95->setValue((data2.at(listnum))[76].digitValue());
    ui->s96->setValue((data2.at(listnum))[77].digitValue());
    ui->s97->setValue((data2.at(listnum))[78].digitValue());
    ui->s98->setValue((data2.at(listnum))[79].digitValue());
    ui->s99->setValue((data2.at(listnum))[80].digitValue());



}

// Function called when window is resized
void MainWindow::resizeEvent(QResizeEvent *event) {

    QWidget::resizeEvent(event);


//    Change font size of spinboxes on resizing
    int pointSize = (event->size().width()) / 70;
    QFont sg("DejaVu Sans", pointSize);

    ui->s11->setFont(sg);
    ui->s12->setFont(sg);
    ui->s13->setFont(sg);
    ui->s14->setFont(sg);
    ui->s15->setFont(sg);
    ui->s16->setFont(sg);
    ui->s17->setFont(sg);
    ui->s18->setFont(sg);
    ui->s19->setFont(sg);

    ui->s21->setFont(sg);
    ui->s22->setFont(sg);
    ui->s23->setFont(sg);
    ui->s24->setFont(sg);
    ui->s25->setFont(sg);
    ui->s26->setFont(sg);
    ui->s27->setFont(sg);
    ui->s28->setFont(sg);
    ui->s29->setFont(sg);

    ui->s31->setFont(sg);
    ui->s32->setFont(sg);
    ui->s33->setFont(sg);
    ui->s34->setFont(sg);
    ui->s35->setFont(sg);
    ui->s36->setFont(sg);
    ui->s37->setFont(sg);
    ui->s38->setFont(sg);
    ui->s39->setFont(sg);

    ui->s41->setFont(sg);
    ui->s42->setFont(sg);
    ui->s43->setFont(sg);
    ui->s44->setFont(sg);
    ui->s45->setFont(sg);
    ui->s46->setFont(sg);
    ui->s47->setFont(sg);
    ui->s48->setFont(sg);
    ui->s49->setFont(sg);

    ui->s51->setFont(sg);
    ui->s52->setFont(sg);
    ui->s53->setFont(sg);
    ui->s54->setFont(sg);
    ui->s55->setFont(sg);
    ui->s56->setFont(sg);
    ui->s57->setFont(sg);
    ui->s58->setFont(sg);
    ui->s59->setFont(sg);

    ui->s61->setFont(sg);
    ui->s62->setFont(sg);
    ui->s63->setFont(sg);
    ui->s64->setFont(sg);
    ui->s65->setFont(sg);
    ui->s66->setFont(sg);
    ui->s67->setFont(sg);
    ui->s68->setFont(sg);
    ui->s69->setFont(sg);

    ui->s71->setFont(sg);
    ui->s72->setFont(sg);
    ui->s73->setFont(sg);
    ui->s74->setFont(sg);
    ui->s75->setFont(sg);
    ui->s76->setFont(sg);
    ui->s77->setFont(sg);
    ui->s78->setFont(sg);
    ui->s79->setFont(sg);

    ui->s81->setFont(sg);
    ui->s82->setFont(sg);
    ui->s83->setFont(sg);
    ui->s84->setFont(sg);
    ui->s85->setFont(sg);
    ui->s86->setFont(sg);
    ui->s87->setFont(sg);
    ui->s88->setFont(sg);
    ui->s89->setFont(sg);

    ui->s91->setFont(sg);
    ui->s92->setFont(sg);
    ui->s93->setFont(sg);
    ui->s94->setFont(sg);
    ui->s95->setFont(sg);
    ui->s96->setFont(sg);
    ui->s97->setFont(sg);
    ui->s98->setFont(sg);
    ui->s99->setFont(sg);
}


// Function called when new client connects to server
void MainWindow::connection() {

//    Allocate pending client to QTCPSocket newsocket
    newsocket = newserver->nextPendingConnection();
    connect(newsocket, SIGNAL(readyRead()), this, SLOT(dataReceive()));
    connect(newsocket,SIGNAL(disconnected()), this, SLOT(disconnected()));

}

// Function called when client sends data to server
void MainWindow::dataReceive() {
    QByteArray rec;

    // Read data and allocate to recStr
    while(newsocket->bytesAvailable()>0) {
        rec = newsocket->readAll();
    }
    QString recStr = rec.data();

    // Convert received string to 2d integer matrix
    QStringList result3 = recStr.split(QRegExp("\\s+"));
    int il = 0;
    for (int uu = 1; uu < 10; uu++) {
        for (int uuu = 1; uuu < 10; uuu++) {
            b1[uu][uuu] = result3.at(il).toInt();
            il++;
        }
    }

    double time3 = result3.at(il).toDouble();


    SecWind s;

    s.setModal(true);

    // Display received data in second window
    s.dispresult(&b1[0][0], time3);
    s.outresult();
    s.exec();
}

// Function called when client disconnected
void MainWindow::disconnected() {
    newsocket->close();
}
