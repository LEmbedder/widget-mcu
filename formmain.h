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
#include <qpixmap.h>

#include <string.h>
#include "globalvariable.h"

QT_CHARTS_USE_NAMESPACE


namespace Ui {
class FormMain;
}

/* 模式 */
enum Mode{
  AUTO,
  MANUAL,
};

struct Main_Form{
    double test_pressure;       /* 测试压力 */
    QString workpiece_number;   /* 工号    */
    QString worker_number;      /* 工件号      */
    enum Mode mode;             /* 模式       */
};

class FormMain : public QWidget
{
    Q_OBJECT

public:
    explicit FormMain(QWidget *parent = 0);
    ~FormMain();

    void updateForm();
    void updateLabelSucess(int next);
    void disp_test_press(double value);
    void disp_test_result(double value);
public slots:
    void receiveInfo();
    void update_args_config(Args_config *config);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_channel_number_currentIndexChanged(int index);

    void on_lineEdit_up_limit_editingFinished();

    void on_lineEdit_down_limit_editingFinished();

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

    int labelSucess[10];
};

#endif // FORMMAIN_H
