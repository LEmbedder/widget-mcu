#include "formsystemsetting.h"
#include "ui_formsystemsetting.h"

/* 模式控制 */
QStringList model_select = {"自动模式","手动模式"};

/* 工位选择 */
QStringList work_space = {"A工位","B工位","A-B工位","A/B工位"};

/* A工位模式 */
QStringList a_worker = {"正压","负压","正负压","负正压"};
/* 产品 */
QStringList product_model= {"总成模式","分离模式"};
/* 保留小数位 */
QStringList decimal_bit = {"0","1","2","3"};
/* 测试模式 */
QStringList test_mode = {"检查","容积测试","定标测试"};
/* 构建 */
FormSystemSetting::FormSystemSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSystemSetting)
{
    ui->setupUi(this);

    /* 默认选择 */
    ui->comboBoxModelSelect->addItems(model_select);
    ui->comboBox_worker->addItems(work_space);
    ui->comboBox_a_worker->addItems(a_worker);
    ui->comboBox_b_worker->addItems(a_worker);
    ui->comboBox_product_model->addItems(product_model);
    ui->comboBox_decimal_reveal->addItems(decimal_bit);
    ui->comboBox_decimal_test_press->addItems(decimal_bit);
    ui->comboBox_test_mode->addItems(test_mode);
    ui->lineEdit_work_number->setMaxLength(20);
    ui->lineEdit_work_number->setValidator(new QRegExpValidator(QRegExp("^[A-Za-z0-9]+$"), this));

}

FormSystemSetting::~FormSystemSetting()
{
    delete ui;
}
/* 返回当前模式 */
QString FormSystemSetting::return_model()
{
    if (systemData.args_config.model >= model_select.size())
    {
        printf("model_select error at = %d",systemData.args_config.model);
    }
    return model_select.at( systemData.args_config.model);
}
/* 返回当前工位 */
QString FormSystemSetting::return_worker_space()
{
    if (systemData.args_config.worker_space >= work_space.size())
    {
        printf("worker_space error at = %d",systemData.args_config.model);
    }
    return work_space.at(systemData.args_config.worker_space);
}
/* 更新界面 */
void FormSystemSetting::update_system_setting()
{
    ui->comboBoxModelSelect->setCurrentIndex(systemData.args_config.model);
    ui->comboBox_a_worker->setCurrentIndex(systemData.args_config.A_model);
    ui->comboBox_b_worker->setCurrentIndex(systemData.args_config.B_model);
    ui->comboBox_worker->setCurrentIndex(systemData.args_config.worker_space);
    ui->comboBox_product_model->setCurrentIndex(systemData.args_config.product_model);
    ui->comboBox_decimal_reveal->setCurrentIndex(systemData.args_config.reveal_decimal_bit);
    ui->comboBox_decimal_test_press->setCurrentIndex(systemData.args_config.test_press_decimal_bit);
    ui->comboBox_test_mode->setCurrentIndex(systemData.args_config.test_mode);
    ui->lineEdit_work_number->setText(QString(systemData.args_config.work_number));

}
/*
 * settings.ini配置文件里获取配置参数
 */
void FormSystemSetting::loadConfigArgs()
{
    QString fileName = QApplication::applicationDirPath() + "/settings.ini";
    QSettings setting(fileName, QSettings::IniFormat);

    QStringList tagList;
    if (QFile(fileName).exists())
    {
        setting.beginGroup("Config Args");
        tagList = setting.childKeys();
        if (tagList.indexOf("model_select") != -1)
        {
            systemData.args_config.model = setting.value("model_select").toInt();
        }
        if (tagList.indexOf("work_space") != -1)
        {
            systemData.args_config.worker_space = setting.value("work_space").toInt();
        }
        if (tagList.indexOf("A_model") != -1)
        {
            systemData.args_config.A_model = setting.value("A_model").toInt();
        }
        if (tagList.indexOf("B_model") != -1)
        {
            systemData.args_config.B_model = setting.value("B_model").toInt();
        }
        if (tagList.indexOf("product_model") != -1)
        {
            systemData.args_config.product_model = setting.value("product_model").toInt();
        }
        if (tagList.indexOf("reveal_decimal") != -1)
        {
            systemData.args_config.reveal_decimal_bit = setting.value("reveal_decimal").toInt();
        }
        if (tagList.indexOf("test_press_decimal") != -1)
        {
            systemData.args_config.test_press_decimal_bit = setting.value("test_press_decimal").toInt();
        }

        if (tagList.indexOf("work_number") != -1)
        {
            QString string = setting.value("work_number").toString();
            strcpy(systemData.args_config.work_number,string.toStdString().c_str());
        }
        if (tagList.indexOf("test_mode") != -1)
        {
            systemData.args_config.test_mode = setting.value("test_mode").toInt();
        }
    }
}
void FormSystemSetting::saveConfigArgs()
{
    QString fileName = QApplication::applicationDirPath() + "/settings.ini";
    QSettings setting(fileName, QSettings::IniFormat);

    setting.beginGroup("Config Args");
    setting.setValue("model_select",systemData.args_config.model);
    setting.setValue("work_space",systemData.args_config.worker_space);
    setting.setValue("A_model",systemData.args_config.A_model);
    setting.setValue("B_model",systemData.args_config.A_model);
    setting.setValue("product_model",systemData.args_config.product_model);
    setting.setValue("reveal_decimal",systemData.args_config.reveal_decimal_bit);
    setting.setValue("test_press_decimal",systemData.args_config.test_press_decimal_bit);
    setting.setValue("work_number",systemData.args_config.work_number);
    setting.setValue("test_mode",systemData.args_config.test_mode);
}
void FormSystemSetting::on_pushButton_return_clicked()
{
    this->close();
    memcpy(&args_config_temp,&systemData.args_config,sizeof(struct Args_config));
}
/* 保存参数 */
void FormSystemSetting::on_comboBoxModelSelect_currentIndexChanged(int index)
{
    args_config_temp.model = index;
}

void FormSystemSetting::on_pushButton_save_clicked()
{
    memcpy(&systemData.args_config,&args_config_temp,sizeof(struct Args_config));
    saveConfigArgs();
    emit emit_update_config(&systemData.args_config);
}

void FormSystemSetting::on_comboBox_worker_currentIndexChanged(int index)
{
    args_config_temp.worker_space = index;
}

void FormSystemSetting::on_comboBox_a_worker_currentIndexChanged(int index)
{
    args_config_temp.A_model = index;
}

void FormSystemSetting::on_comboBox_b_worker_currentIndexChanged(int index)
{
    args_config_temp.B_model = index;
}

void FormSystemSetting::on_comboBox_product_model_currentIndexChanged(int index)
{
    args_config_temp.product_model = index;
}

void FormSystemSetting::on_comboBox_decimal_reveal_currentIndexChanged(int index)
{
    args_config_temp.reveal_decimal_bit = index;
}

void FormSystemSetting::on_comboBox_decimal_test_press_currentIndexChanged(int index)
{
    args_config_temp.test_press_decimal_bit = index;
}

void FormSystemSetting::on_lineEdit_work_number_textChanged(const QString &arg1)
{
    strcpy(args_config_temp.work_number,arg1.toStdString().c_str());
    args_config_temp.work_number[20] = '\0';
}

void FormSystemSetting::on_comboBox_test_mode_currentIndexChanged(int index)
{
    args_config_temp.test_mode = index;
}



void FormSystemSetting::on_lineEdit_device_number_textChanged(const QString &arg1)
{
    strcpy(args_config_temp.device_number,arg1.toStdString().c_str());
    args_config_temp.device_number[20] = '\0';
}
