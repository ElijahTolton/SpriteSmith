#include "sizedialog.h"
#include "ui_sizedialog.h"

SizeDialog::SizeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SizeDialog)
{
    ui->setupUi(this);
    setModal(true);
    connect(ui->applyButton, &QDialogButtonBox::clicked, this, &QDialog::accept);
    connect(ui->applyButton, &QDialogButtonBox::clicked, this, &SizeDialog::emitSetSize);
}

SizeDialog::~SizeDialog()
{
    delete ui;
}

void SizeDialog::emitSetSize() {
    emit setSize(ui->dimensionSpinBox->value());
}
