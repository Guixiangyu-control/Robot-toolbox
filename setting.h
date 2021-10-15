#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <QPushButton>

namespace Ui {
class setting;
}

class setting : public QWidget
{
    Q_OBJECT

public:
    explicit setting(QWidget *parent = nullptr);
    ~setting();
    QPushButton* pushButton1;
    QPushButton* pushButton2;

private:
     Ui::setting *ui;
};

#endif // SETTING_H
