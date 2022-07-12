// Copyright (c) 2019-2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "qt/pivx/defaultotpdialog.h"
#include "qt/pivx/qtutils.h"
#include "qt/pivx/forms/ui_defaultotpdialog.h"
#include "guiutil.h"

#include <QPixmap>
#include <QString>

DefaultOtpDialog::DefaultOtpDialog(QWidget *parent) :
    FocusedDialog(parent),
    ui(new Ui::DefaultOtpDialog)
{
    ui->setupUi(this);

    // Stylesheet
    this->setStyleSheet(parent ? parent->styleSheet() : GUIUtil::loadStyleSheet());

    // Container
    ui->frame->setProperty("cssClass", "container-dialog");

    // Text
    ui->labelTitle->setProperty("cssClass", "text-title-dialog");
    ui->labelMessage->setProperty("cssClass", "text-main-grey");

    // QrCode
    ui->labelOtp->setText("");

    // Buttons
    ui->btnEsc->setText("");
    ui->btnEsc->setProperty("cssClass", "ic-close");

    ui->btnCancel->setProperty("cssClass", "btn-dialog-cancel");
    ui->btnSave->setProperty("cssClass", "btn-primary");

    connect(ui->btnEsc, &QPushButton::clicked, this, &DefaultOtpDialog::close);
    connect(ui->btnCancel, &QPushButton::clicked, this, &DefaultOtpDialog::close);
    connect(ui->btnSave, &QPushButton::clicked, this, &DefaultOtpDialog::accept);
}

void DefaultOtpDialog::setText(const QString& title, const QString& message, const QString& okBtnText, const QString& cancelBtnText)
{
    if (!okBtnText.isNull()) ui->btnSave->setText(okBtnText);
    if (!cancelBtnText.isNull()) {
        ui->btnCancel->setVisible(true);
        ui->btnCancel->setText(cancelBtnText);
    } else {
        ui->btnCancel->setVisible(false);
    }
    if (!message.isNull()) ui->labelMessage->setText(message);
    if (!title.isNull()) ui->labelTitle->setText(title);
}

void DefaultOtpDialog::setQrCode(QPixmap qrStr)
{
    QString error;
    //QPixmap otpQr = encodeToQr(qrStr, error);
    if (!qrStr.isNull()) {
        qrImage = &qrStr;
        ui->labelOtp->setPixmap(qrImage->scaled(ui->labelOtp->width(), ui->labelOtp->height()));
    } else{
        ui->labelOtp->setText(!error.isEmpty() ? error : "Error encoding Seedphrase.");
    }
}

void DefaultOtpDialog::accept()
{
    this->isOk = true;
    QDialog::accept();
}

DefaultOtpDialog::~DefaultOtpDialog()
{
    delete ui;
}
