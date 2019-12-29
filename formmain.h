#ifndef FORMMAIN_H
#define FORMMAIN_H

#include <QWidget>
#include <QPushButton>
#include "formchannelsettings.h"
#include "formargusetting.h"
#include "formviewdata.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
QT_CHARTS_USE_NAMESPACE

namespace Ui {
class FormMain;
}

/* 模式 */
enum Mode{
  AUTO,
  manual,
};

struct Main_Form{
    double test_pressure;       /* 测试压力  */
    QString workpiece_number;   /* 工号     */
    QString worker_number;      /* 工件号   */
    enum Mode mode;             /* 模式    */
};

class FormMain : public QWidget
{
    Q_OBJECT

public:
    explicit FormMain(QWidget *parent = 0);
    ~FormMain();
    struct Main_Form main_Form_Infor;

    void updateForm();
public slots:
    void receiveInfo();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::FormMain *ui;
    void witchButtonChecked(QPushButton *button);
    FormChannelSettings *formChannleSettings;
    FormArguSetting *formArguSetting;
    FormViewData *formViewData;

    QSerialPort *serialPort;

    QLineSeries *series ;
    QChart *chart;
    QChartView *chartView;
};

#endif // FORMMAIN_H
