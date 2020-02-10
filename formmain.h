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
#include "formvolumetest.h"
#include "formcalibrationtest.h"
#include "progressbar.h"

QT_CHARTS_USE_NAMESPACE


namespace Ui {
class FormMain;
}

class FormMain : public QWidget
{
    Q_OBJECT

public:
    explicit FormMain(QWidget *parent = 0);
    ~FormMain();


    void updateLabelSucess(int next);
    void disp_test_press(double value);
    void disp_test_result(double value);
    void updateSeries(int position, double value);
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

    void updateForm();

private:
    Ui::FormMain *ui;
    void witchButtonChecked(QPushButton *button);
    FormChannelSettings *formChannleSettings;
    FormArguSetting *formArguSetting;
    FormViewData *formViewData;
    FormVolumeTest *formVolumeTest;
    FormCalibrationTest *formCalibrationTest;

    QSerialPort *serialPort;

    QLineSeries *series ;
    QChart *chart;
    QChartView *chartView;
    ProgressBar *progressBar;

    int labelSucess[10];
};

#endif // FORMMAIN_H
