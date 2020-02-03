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
