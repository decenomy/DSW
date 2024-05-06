// Copyright (c) 2011-2014 The Bitcoin developers
// Copyright (c) 2017-2019 The PIVX developers
// Copyright (c) 2021-2022 The DECENOMY Core Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_UTILITYDIALOG_H
#define BITCOIN_QT_UTILITYDIALOG_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winit-list-lifetime"

#include <QDialog>
#include <QObject>
#include <QMainWindow>

#pragma GCC diagnostic pop

class ClientModel;

namespace Ui
{
class HelpMessageDialog;
}

/** "Help message" dialog box */
class HelpMessageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpMessageDialog(QWidget* parent, bool about);
    ~HelpMessageDialog();

    void printToConsole();
    void showOrPrint();

private:
    Ui::HelpMessageDialog* ui;
    QString text;
};


/** "Shutdown" window */
class ShutdownWindow : public QWidget
{
    Q_OBJECT

public:
    ShutdownWindow(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::Widget);
    static void showShutdownWindow(QMainWindow* window);

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // BITCOIN_QT_UTILITYDIALOG_H
