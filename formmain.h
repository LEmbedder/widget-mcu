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
#include "formprogress.h"
#include "formpassword.h"
#include "communicationtomcu.h"
#include "printinformation.h"

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
    QString fileName;
    communicationToMCU *communication;
    void updateLabelSucess(int next);
    void disp_test_press(double value);
    void disp_test_result(double value);
    void updateSeries(int position, double value);
//    ProgressBar *progressBar;
    FormProgress *formProgress;
    void loadConfigArgs();
    void saveConfigArgs();
    FormPassword *fps;
    PrintInformation *printInformation;
    void setViewData();
    bool loadXmlFile(void);
    QSerialPort *serialPort;
    QTimer *timer;
public slots:
    void receiveInfo();
    void update_args_config(Args_config *config);
    void update_mcu();
    void updateLabelSucessOrFailed(bool value);
    void channel_update_start_timer();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_lineEdit_up_limit_editingFinished();

    void on_lineEdit_down_limit_editingFinished();

    void updateForm();

    void on_pushButton_set_channel_number_clicked();

    void channel_update();

    void on_textEdit_workpiece_number_textChanged();

private:
    Ui::FormMain *ui;
    void witchButtonChecked(QPushButton *button);
    FormChannelSettings *formChannleSettings;
    FormArguSetting *formArguSetting;
    FormViewData *formViewData;
    FormVolumeTest *formVolumeTest;
    FormCalibrationTest *formCalibrationTest;



    QLineSeries *series ;
    QChart *chart;
    QChartView *chartView;


    int labelSucess[10];
    int save_index;
};

#endif // FORMMAIN_H
