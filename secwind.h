#ifndef SECWIND_H
#define SECWIND_H

#include <QDialog>

namespace Ui {
class SecWind;
}

class SecWind : public QDialog
{
    Q_OBJECT

public:
    explicit SecWind(QWidget *parent = 0);
    ~SecWind();
    void dispresult(int *a, double t2);
    void outresult();

private:
    Ui::SecWind *ui;
};

#endif // SECWIND_H
