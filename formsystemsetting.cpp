#include "formsystemsetting.h"
#include "ui_formsystemsetting.h"

/* 模式控制 */
QStringList model_select = {"自动模式","手动模式"};

/* 工位选择 */
QStringList work_model = {"A工位","B工位","A-B工位","A/B工位"};

/* A工位模式 */
QStringList a_worker = {"正压","负压","正负压","负正压"};
/* 产品 */
QStringList product_model= {"总成模式","分离模式"};

/* 构建 */
FormSystemSetting::FormSystemSetting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormSystemSetting)
{
    ui->setupUi(this);

    /* 默认选择0 */
    memset(&args_config,0,sizeof(struct Args_config));
    ui->comboBoxModelSelect->addItems(model_select);
    ui->comboBox_worker->addItems(work_model);
    ui->comboBox_a_worker->addItems(a_worker);
    ui->comboBox_b_worker->addItems(a_worker);
    ui->comboBox_product_model->addItems(product_model);

}

FormSystemSetting::~FormSystemSetting()
{
    delete ui;
}
/* 返回当前模式 */
QString FormSystemSetting::return_model()
{
    return model_select.at(args_config.model);
}
/* 返回当前工位 */
QString FormSystemSetting::return_worker_space()
{
    return work_model.at(args_config.worker_space);
}
/* 更新界面 */
void FormSystemSetting::update_system_setting()
{
    ui->comboBoxModelSelect->setCurrentIndex(args_config.model);
    ui->comboBox_a_worker->setCurrentIndex(args_config.A_model);
    ui->comboBox_b_worker->setCurrentIndex(args_config.B_model);
    ui->comboBox_worker->setCurrentIndex(args_config.worker_space);
    ui->comboBox_product_model->setCurrentIndex(args_config.product_model);
}
void FormSystemSetting::on_pushButton_return_clicked()
{
    this->close();
    memcpy(&args_config_temp,&args_config,sizeof(struct Args_config));
}
/* 保存参数 */
void FormSystemSetting::on_comboBoxModelSelect_currentIndexChanged(int index)
{
    args_config_temp.model = index;
    qDebug()<<model_select.at(index);
}

void FormSystemSetting::on_pushButton_save_clicked()
{
    memcpy(&args_config,&args_config_temp,sizeof(struct Args_config));
    emit emit_update_config(&args_config);
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
