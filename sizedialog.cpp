#include "sizedialog.h"
#include "ui_sizedialog.h"
#include <QMessageBox>
#include <QCloseEvent>

/**
 * @brief The initial size dialog window which sets the canvas size in pixels
 *
 * @author Alex Lancaster
 * @date March 29, 2025
 *
 * Checked by Alex Lancaster
 */

SizeDialog::SizeDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SizeDialog) {

    ui->setupUi(this);
    setModal(true);
    connect(ui->applyButton, &QDialogButtonBox::clicked, this, &QDialog::accept);
    connect(ui->applyButton, &QDialogButtonBox::clicked, this, &SizeDialog::emitSetSize);
}

SizeDialog::~SizeDialog() {
    delete ui;
}

void SizeDialog::emitSetSize() {
    emit setSize(ui->dimensionSpinBox->value());
}

void SizeDialog::closeEvent(QCloseEvent *event) {
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Quit", "Are you sure you want to quit?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        exit(0);
    }

    else {
        event->ignore();
    }
}
