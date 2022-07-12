// Copyright (c) 2019-2020 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DEFAULTOTPDIALOG_H
#define DEFAULTOTPDIALOG_H

#include "qt/pivx/focuseddialog.h"
#include <QPixmap>

namespace Ui {
class DefaultOtpDialog;
}

class DefaultOtpDialog : public FocusedDialog
{
    Q_OBJECT

public:
    explicit DefaultOtpDialog(QWidget *parent = nullptr);
    ~DefaultOtpDialog();

    void setText(const QString& title = "", const QString& message = "", const QString& okBtnText = "", const QString& cancelBtnText = "");
    void setQrCode(QPixmap qrStr);

    bool isOk = false;

public Q_SLOTS:
    void accept() override;

private:
    Ui::DefaultOtpDialog *ui;
    QPixmap *qrImage;
};

#endif // DEFAULTDIALOG_H
