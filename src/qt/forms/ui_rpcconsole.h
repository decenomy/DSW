/********************************************************************************
** Form generated from reading UI file 'rpcconsole.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RPCCONSOLE_H
#define UI_RPCCONSOLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "trafficgraphwidget.h"

QT_BEGIN_NAMESPACE

class Ui_RPCConsole
{
public:
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab_info;
    QGridLayout *gridLayout;
    QLabel *generalHeader;
    QLabel *clientNameLabel;
    QLabel *clientName;
    QLabel *clientVersionLabel;
    QLabel *clientVersion;
    QLabel *berkeleyDBVersionLabel;
    QLabel *berkeleyDBVersion;
    QLabel *buildDateLabel;
    QLabel *buildDate;
    QLabel *startupTimeLabel;
    QLabel *startupTime;
    QLabel *dataDirLabel;
    QLabel *dataDir;
    QLabel *networkHeader;
    QLabel *networkNameLabel;
    QLabel *networkName;
    QLabel *numberOfConnectionsLabel;
    QLabel *numberOfConnections;
    QLabel *masternodeCountLabel;
    QLabel *masternodeCount;
    QLabel *blockchainHeader;
    QLabel *numberOfBlocksLabel;
    QLabel *numberOfBlocks;
    QLabel *lastBlockTimeLabel;
    QLabel *lastBlockTime;
    QLabel *lastBlockHashLabel;
    QLabel *lastBlockHash;
    QSpacerItem *verticalSpacer_2;
    QLabel *debugLogFileHeader;
    QPushButton *openDebugLogfileButton;
    QWidget *tab_console;
    QVBoxLayout *verticalLayout_3;
    QTextEdit *messagesWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *clearButton;
    QWidget *tab_nettraffic;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_4;
    TrafficGraphWidget *trafficGraph;
    QHBoxLayout *horizontalLayout_2;
    QSlider *sldGraphRange;
    QLabel *lblGraphRange;
    QPushButton *btnClearTrafficGraph;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QFrame *line;
    QLabel *label_16;
    QLabel *lblBytesIn;
    QHBoxLayout *horizontalLayout_5;
    QFrame *line_2;
    QLabel *label_17;
    QLabel *lblBytesOut;
    QSpacerItem *verticalSpacer_4;
    QWidget *tab_peers;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_101;
    QTableView *peerWidget;
    QLabel *banHeading;
    QTableView *banlistWidget;
    QLabel *peerHeading;
    QWidget *detailWidget;
    QGridLayout *gridLayout_3;
    QLabel *label_30;
    QLabel *peerWhitelisted;
    QLabel *label_23;
    QLabel *peerDirection;
    QLabel *label_21;
    QLabel *peerVersion;
    QLabel *label_28;
    QLabel *peerSubversion;
    QLabel *label_4;
    QLabel *peerServices;
    QLabel *label_29;
    QLabel *peerHeight;
    QLabel *label_27;
    QLabel *peerSyncHeight;
    QLabel *label_25;
    QLabel *peerCommonHeight;
    QLabel *label_24;
    QLabel *peerBanScore;
    QLabel *label_22;
    QLabel *peerConnTime;
    QLabel *label_15;
    QLabel *peerLastSend;
    QLabel *label_19;
    QLabel *peerLastRecv;
    QLabel *label_18;
    QLabel *peerBytesSent;
    QLabel *label_20;
    QLabel *peerBytesRecv;
    QLabel *label_26;
    QLabel *peerPingTime;
    QLabel *peerPingWaitLabel;
    QLabel *peerPingWait;
    QLabel *label_timeoffset;
    QLabel *timeoffset;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_repair;
    QGridLayout *gridLayout_4;
    QLabel *label_repair_header;
    QLabel *label_repair_helptext;
    QLabel *wallet_path_label;
    QLabel *wallet_path;
    QLabel *wallet_custombackuppath_label;
    QLabel *wallet_custombackuppath;
    QLabel *wallet_custombackupthreshold_label;
    QLabel *wallet_custombackupthreshold;
    QSpacerItem *verticalSpacer_repair1;
    QPushButton *btn_salvagewallet;
    QLabel *label_repair_salvage_command;
    QLabel *label_repair_salvage;
    QPushButton *btn_rescan;
    QLabel *label_repair_rescan_command;
    QLabel *label_repair_rescan;
    QPushButton *btn_zapwallettxes1;
    QLabel *label_repair_zap1_command;
    QLabel *label_repair_zap1;
    QPushButton *btn_zapwallettxes2;
    QLabel *label_repair_zap2_command;
    QLabel *label_repair_zap2;
    QPushButton *btn_upgradewallet;
    QLabel *label_repair_upgrade_command;
    QLabel *label_repair_upgrade;
    QPushButton *btn_reindex;
    QLabel *label_repair_reindex_command;
    QLabel *label_repair_reindex;
    QPushButton *btn_resync;
    QLabel *label_repair_resync_command;
    QLabel *label_repair_resync;
    QPushButton *btn_bootstrap;
    QLabel *label_repair_bootstrap_command;
    QLabel *label_repair_bootstrap;
    QSpacerItem *verticalSpacer_repair2;
    QWidget *tab_status;
    QLabel *ROI;
    QLabel *stakingROI;
    QLabel *smooth_staking;
    QLabel *staked_coins;
    QLabel *masternode_ROI;
    QLabel *masternode_coins;
    QLabel *masternode_count;
    QLabel *total;
    QLabel *stable;
    QLabel *enabled;
    QLabel *inqueue;
    QLabel *ipv4;
    QLabel *ipv6;
    QLabel *onion;
    QLabel *stkroi;
    QLabel *ssroi;
    QLabel *stkcoins;
    QLabel *mnroi;
    QLabel *mncoins;
    QLabel *totalmn;
    QLabel *stablemn;
    QLabel *enabledmn;
    QLabel *inqmn;
    QLabel *ipv4mn;
    QLabel *ipv6mn;
    QLabel *onionmn;
    QLabel *my_masternodes;
    QLabel *mytotal;
    QLabel *myactive;
    QLabel *mytotalmn;
    QLabel *myactivemn;
    QLabel *bststamp;
    QPushButton *btn_refresh;

    void setupUi(QDialog *RPCConsole)
    {
        if (RPCConsole->objectName().isEmpty())
            RPCConsole->setObjectName(QStringLiteral("RPCConsole"));
        RPCConsole->resize(769, 520);
        verticalLayout_2 = new QVBoxLayout(RPCConsole);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        tabWidget = new QTabWidget(RPCConsole);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_info = new QWidget();
        tab_info->setObjectName(QStringLiteral("tab_info"));
        gridLayout = new QGridLayout(tab_info);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(12);
        generalHeader = new QLabel(tab_info);
        generalHeader->setObjectName(QStringLiteral("generalHeader"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        generalHeader->setFont(font);

        gridLayout->addWidget(generalHeader, 0, 0, 1, 1);

        clientNameLabel = new QLabel(tab_info);
        clientNameLabel->setObjectName(QStringLiteral("clientNameLabel"));

        gridLayout->addWidget(clientNameLabel, 1, 0, 1, 1);

        clientName = new QLabel(tab_info);
        clientName->setObjectName(QStringLiteral("clientName"));
        clientName->setCursor(QCursor(Qt::IBeamCursor));
        clientName->setTextFormat(Qt::PlainText);
        clientName->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(clientName, 1, 1, 1, 1);

        clientVersionLabel = new QLabel(tab_info);
        clientVersionLabel->setObjectName(QStringLiteral("clientVersionLabel"));

        gridLayout->addWidget(clientVersionLabel, 2, 0, 1, 1);

        clientVersion = new QLabel(tab_info);
        clientVersion->setObjectName(QStringLiteral("clientVersion"));
        clientVersion->setCursor(QCursor(Qt::IBeamCursor));
        clientVersion->setTextFormat(Qt::PlainText);
        clientVersion->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(clientVersion, 2, 1, 1, 1);

        berkeleyDBVersionLabel = new QLabel(tab_info);
        berkeleyDBVersionLabel->setObjectName(QStringLiteral("berkeleyDBVersionLabel"));
        berkeleyDBVersionLabel->setIndent(10);

        gridLayout->addWidget(berkeleyDBVersionLabel, 3, 0, 1, 1);

        berkeleyDBVersion = new QLabel(tab_info);
        berkeleyDBVersion->setObjectName(QStringLiteral("berkeleyDBVersion"));
        berkeleyDBVersion->setCursor(QCursor(Qt::IBeamCursor));
        berkeleyDBVersion->setTextFormat(Qt::PlainText);
        berkeleyDBVersion->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(berkeleyDBVersion, 3, 1, 1, 1);

        buildDateLabel = new QLabel(tab_info);
        buildDateLabel->setObjectName(QStringLiteral("buildDateLabel"));

        gridLayout->addWidget(buildDateLabel, 4, 0, 1, 1);

        buildDate = new QLabel(tab_info);
        buildDate->setObjectName(QStringLiteral("buildDate"));
        buildDate->setCursor(QCursor(Qt::IBeamCursor));
        buildDate->setTextFormat(Qt::PlainText);
        buildDate->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(buildDate, 4, 1, 1, 1);

        startupTimeLabel = new QLabel(tab_info);
        startupTimeLabel->setObjectName(QStringLiteral("startupTimeLabel"));

        gridLayout->addWidget(startupTimeLabel, 5, 0, 1, 1);

        startupTime = new QLabel(tab_info);
        startupTime->setObjectName(QStringLiteral("startupTime"));
        startupTime->setCursor(QCursor(Qt::IBeamCursor));
        startupTime->setTextFormat(Qt::PlainText);
        startupTime->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(startupTime, 5, 1, 1, 1);

        dataDirLabel = new QLabel(tab_info);
        dataDirLabel->setObjectName(QStringLiteral("dataDirLabel"));

        gridLayout->addWidget(dataDirLabel, 6, 0, 1, 1);

        dataDir = new QLabel(tab_info);
        dataDir->setObjectName(QStringLiteral("dataDir"));

        gridLayout->addWidget(dataDir, 6, 1, 1, 1);

        networkHeader = new QLabel(tab_info);
        networkHeader->setObjectName(QStringLiteral("networkHeader"));
        networkHeader->setFont(font);

        gridLayout->addWidget(networkHeader, 7, 0, 1, 1);

        networkNameLabel = new QLabel(tab_info);
        networkNameLabel->setObjectName(QStringLiteral("networkNameLabel"));

        gridLayout->addWidget(networkNameLabel, 8, 0, 1, 1);

        networkName = new QLabel(tab_info);
        networkName->setObjectName(QStringLiteral("networkName"));
        networkName->setCursor(QCursor(Qt::IBeamCursor));
        networkName->setTextFormat(Qt::PlainText);
        networkName->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(networkName, 8, 1, 1, 1);

        numberOfConnectionsLabel = new QLabel(tab_info);
        numberOfConnectionsLabel->setObjectName(QStringLiteral("numberOfConnectionsLabel"));

        gridLayout->addWidget(numberOfConnectionsLabel, 9, 0, 1, 1);

        numberOfConnections = new QLabel(tab_info);
        numberOfConnections->setObjectName(QStringLiteral("numberOfConnections"));
        numberOfConnections->setCursor(QCursor(Qt::IBeamCursor));
        numberOfConnections->setTextFormat(Qt::PlainText);
        numberOfConnections->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(numberOfConnections, 9, 1, 1, 1);

        masternodeCountLabel = new QLabel(tab_info);
        masternodeCountLabel->setObjectName(QStringLiteral("masternodeCountLabel"));

        gridLayout->addWidget(masternodeCountLabel, 10, 0, 1, 1);

        masternodeCount = new QLabel(tab_info);
        masternodeCount->setObjectName(QStringLiteral("masternodeCount"));
        masternodeCount->setCursor(QCursor(Qt::IBeamCursor));
        masternodeCount->setTextFormat(Qt::PlainText);
        masternodeCount->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(masternodeCount, 10, 1, 1, 1);

        blockchainHeader = new QLabel(tab_info);
        blockchainHeader->setObjectName(QStringLiteral("blockchainHeader"));
        blockchainHeader->setFont(font);

        gridLayout->addWidget(blockchainHeader, 11, 0, 1, 1);

        numberOfBlocksLabel = new QLabel(tab_info);
        numberOfBlocksLabel->setObjectName(QStringLiteral("numberOfBlocksLabel"));

        gridLayout->addWidget(numberOfBlocksLabel, 12, 0, 1, 1);

        numberOfBlocks = new QLabel(tab_info);
        numberOfBlocks->setObjectName(QStringLiteral("numberOfBlocks"));
        numberOfBlocks->setCursor(QCursor(Qt::IBeamCursor));
        numberOfBlocks->setTextFormat(Qt::PlainText);
        numberOfBlocks->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(numberOfBlocks, 12, 1, 1, 1);

        lastBlockTimeLabel = new QLabel(tab_info);
        lastBlockTimeLabel->setObjectName(QStringLiteral("lastBlockTimeLabel"));

        gridLayout->addWidget(lastBlockTimeLabel, 13, 0, 1, 1);

        lastBlockTime = new QLabel(tab_info);
        lastBlockTime->setObjectName(QStringLiteral("lastBlockTime"));
        lastBlockTime->setCursor(QCursor(Qt::IBeamCursor));
        lastBlockTime->setTextFormat(Qt::PlainText);
        lastBlockTime->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout->addWidget(lastBlockTime, 13, 1, 1, 1);

        lastBlockHashLabel = new QLabel(tab_info);
        lastBlockHashLabel->setObjectName(QStringLiteral("lastBlockHashLabel"));

        gridLayout->addWidget(lastBlockHashLabel, 14, 0, 1, 1);

        lastBlockHash = new QLabel(tab_info);
        lastBlockHash->setObjectName(QStringLiteral("lastBlockHash"));

        gridLayout->addWidget(lastBlockHash, 14, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 15, 0, 1, 1);

        debugLogFileHeader = new QLabel(tab_info);
        debugLogFileHeader->setObjectName(QStringLiteral("debugLogFileHeader"));
        debugLogFileHeader->setFont(font);

        gridLayout->addWidget(debugLogFileHeader, 16, 0, 1, 1);

        openDebugLogfileButton = new QPushButton(tab_info);
        openDebugLogfileButton->setObjectName(QStringLiteral("openDebugLogfileButton"));
        openDebugLogfileButton->setAutoDefault(false);

        gridLayout->addWidget(openDebugLogfileButton, 17, 0, 1, 1);

        tabWidget->addTab(tab_info, QString());
        tab_console = new QWidget();
        tab_console->setObjectName(QStringLiteral("tab_console"));
        verticalLayout_3 = new QVBoxLayout(tab_console);
        verticalLayout_3->setSpacing(3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        messagesWidget = new QTextEdit(tab_console);
        messagesWidget->setObjectName(QStringLiteral("messagesWidget"));
        messagesWidget->setMinimumSize(QSize(0, 100));
        messagesWidget->setReadOnly(true);
        messagesWidget->setProperty("tabKeyNavigation", QVariant(false));
        messagesWidget->setProperty("columnCount", QVariant(2));

        verticalLayout_3->addWidget(messagesWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(tab_console);
        label->setObjectName(QStringLiteral("label"));
        label->setText(QStringLiteral(">"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(tab_console);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        clearButton = new QPushButton(tab_console);
        clearButton->setObjectName(QStringLiteral("clearButton"));
        clearButton->setMaximumSize(QSize(24, 24));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icons/remove"), QSize(), QIcon::Normal, QIcon::Off);
        clearButton->setIcon(icon);
#ifndef QT_NO_SHORTCUT
        clearButton->setShortcut(QStringLiteral("Ctrl+L"));
#endif // QT_NO_SHORTCUT
        clearButton->setAutoDefault(false);

        horizontalLayout->addWidget(clearButton);


        verticalLayout_3->addLayout(horizontalLayout);

        tabWidget->addTab(tab_console, QString());
        tab_nettraffic = new QWidget();
        tab_nettraffic->setObjectName(QStringLiteral("tab_nettraffic"));
        horizontalLayout_3 = new QHBoxLayout(tab_nettraffic);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        trafficGraph = new TrafficGraphWidget(tab_nettraffic);
        trafficGraph->setObjectName(QStringLiteral("trafficGraph"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(trafficGraph->sizePolicy().hasHeightForWidth());
        trafficGraph->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(trafficGraph);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        sldGraphRange = new QSlider(tab_nettraffic);
        sldGraphRange->setObjectName(QStringLiteral("sldGraphRange"));
        sldGraphRange->setMinimum(1);
        sldGraphRange->setMaximum(288);
        sldGraphRange->setPageStep(12);
        sldGraphRange->setValue(6);
        sldGraphRange->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(sldGraphRange);

        lblGraphRange = new QLabel(tab_nettraffic);
        lblGraphRange->setObjectName(QStringLiteral("lblGraphRange"));
        lblGraphRange->setMinimumSize(QSize(100, 0));
        lblGraphRange->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(lblGraphRange);

        btnClearTrafficGraph = new QPushButton(tab_nettraffic);
        btnClearTrafficGraph->setObjectName(QStringLiteral("btnClearTrafficGraph"));
        btnClearTrafficGraph->setAutoDefault(false);

        horizontalLayout_2->addWidget(btnClearTrafficGraph);


        verticalLayout_4->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(tab_nettraffic);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        verticalLayout_5 = new QVBoxLayout(groupBox);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy1);
        line->setMinimumSize(QSize(10, 0));
        QPalette palette;
        QBrush brush(QColor(0, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush);
        line->setPalette(palette);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_4->addWidget(line);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QStringLiteral("label_16"));

        horizontalLayout_4->addWidget(label_16);

        lblBytesIn = new QLabel(groupBox);
        lblBytesIn->setObjectName(QStringLiteral("lblBytesIn"));
        lblBytesIn->setMinimumSize(QSize(50, 0));
        lblBytesIn->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(lblBytesIn);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QStringLiteral("line_2"));
        sizePolicy1.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy1);
        line_2->setMinimumSize(QSize(10, 0));
        QPalette palette1;
        QBrush brush1(QColor(255, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        line_2->setPalette(palette1);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_5->addWidget(line_2);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QStringLiteral("label_17"));

        horizontalLayout_5->addWidget(label_17);

        lblBytesOut = new QLabel(groupBox);
        lblBytesOut->setObjectName(QStringLiteral("lblBytesOut"));
        lblBytesOut->setMinimumSize(QSize(50, 0));
        lblBytesOut->setAlignment(Qt::AlignRight|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(lblBytesOut);


        verticalLayout_5->addLayout(horizontalLayout_5);

        verticalSpacer_4 = new QSpacerItem(20, 407, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_4);


        verticalLayout->addWidget(groupBox);


        horizontalLayout_3->addLayout(verticalLayout);

        tabWidget->addTab(tab_nettraffic, QString());
        tab_peers = new QWidget();
        tab_peers->setObjectName(QStringLiteral("tab_peers"));
        gridLayout_2 = new QGridLayout(tab_peers);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_101 = new QVBoxLayout();
        verticalLayout_101->setSpacing(0);
        verticalLayout_101->setObjectName(QStringLiteral("verticalLayout_101"));
        peerWidget = new QTableView(tab_peers);
        peerWidget->setObjectName(QStringLiteral("peerWidget"));
        peerWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        peerWidget->setSortingEnabled(true);
        peerWidget->horizontalHeader()->setHighlightSections(false);

        verticalLayout_101->addWidget(peerWidget);

        banHeading = new QLabel(tab_peers);
        banHeading->setObjectName(QStringLiteral("banHeading"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(banHeading->sizePolicy().hasHeightForWidth());
        banHeading->setSizePolicy(sizePolicy2);
        banHeading->setMinimumSize(QSize(300, 32));
        banHeading->setMaximumSize(QSize(16777215, 32));
        QFont font1;
        font1.setPointSize(12);
        banHeading->setFont(font1);
        banHeading->setCursor(QCursor(Qt::IBeamCursor));
        banHeading->setAlignment(Qt::AlignBottom|Qt::AlignLeading|Qt::AlignLeft);
        banHeading->setWordWrap(true);
        banHeading->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout_101->addWidget(banHeading);

        banlistWidget = new QTableView(tab_peers);
        banlistWidget->setObjectName(QStringLiteral("banlistWidget"));
        sizePolicy.setHeightForWidth(banlistWidget->sizePolicy().hasHeightForWidth());
        banlistWidget->setSizePolicy(sizePolicy);
        banlistWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        banlistWidget->setSortingEnabled(true);
        banlistWidget->horizontalHeader()->setHighlightSections(false);

        verticalLayout_101->addWidget(banlistWidget);


        gridLayout_2->addLayout(verticalLayout_101, 0, 0, 2, 1);

        peerHeading = new QLabel(tab_peers);
        peerHeading->setObjectName(QStringLiteral("peerHeading"));
        sizePolicy2.setHeightForWidth(peerHeading->sizePolicy().hasHeightForWidth());
        peerHeading->setSizePolicy(sizePolicy2);
        peerHeading->setMinimumSize(QSize(300, 32));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        peerHeading->setFont(font2);
        peerHeading->setCursor(QCursor(Qt::IBeamCursor));
        peerHeading->setAlignment(Qt::AlignCenter);
        peerHeading->setWordWrap(true);
        peerHeading->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_2->addWidget(peerHeading, 0, 1, 1, 1);

        detailWidget = new QWidget(tab_peers);
        detailWidget->setObjectName(QStringLiteral("detailWidget"));
        detailWidget->setMinimumSize(QSize(300, 0));
        gridLayout_3 = new QGridLayout(detailWidget);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_30 = new QLabel(detailWidget);
        label_30->setObjectName(QStringLiteral("label_30"));

        gridLayout_3->addWidget(label_30, 0, 0, 1, 1);

        peerWhitelisted = new QLabel(detailWidget);
        peerWhitelisted->setObjectName(QStringLiteral("peerWhitelisted"));
        peerWhitelisted->setCursor(QCursor(Qt::IBeamCursor));
        peerWhitelisted->setTextFormat(Qt::PlainText);
        peerWhitelisted->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerWhitelisted, 0, 2, 1, 1);

        label_23 = new QLabel(detailWidget);
        label_23->setObjectName(QStringLiteral("label_23"));

        gridLayout_3->addWidget(label_23, 1, 0, 1, 1);

        peerDirection = new QLabel(detailWidget);
        peerDirection->setObjectName(QStringLiteral("peerDirection"));
        peerDirection->setCursor(QCursor(Qt::IBeamCursor));
        peerDirection->setTextFormat(Qt::PlainText);
        peerDirection->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerDirection, 1, 2, 1, 1);

        label_21 = new QLabel(detailWidget);
        label_21->setObjectName(QStringLiteral("label_21"));

        gridLayout_3->addWidget(label_21, 2, 0, 1, 1);

        peerVersion = new QLabel(detailWidget);
        peerVersion->setObjectName(QStringLiteral("peerVersion"));
        peerVersion->setCursor(QCursor(Qt::IBeamCursor));
        peerVersion->setTextFormat(Qt::PlainText);
        peerVersion->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerVersion, 2, 2, 1, 1);

        label_28 = new QLabel(detailWidget);
        label_28->setObjectName(QStringLiteral("label_28"));

        gridLayout_3->addWidget(label_28, 3, 0, 1, 1);

        peerSubversion = new QLabel(detailWidget);
        peerSubversion->setObjectName(QStringLiteral("peerSubversion"));
        peerSubversion->setCursor(QCursor(Qt::IBeamCursor));
        peerSubversion->setTextFormat(Qt::PlainText);
        peerSubversion->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerSubversion, 3, 2, 1, 1);

        label_4 = new QLabel(detailWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 4, 0, 1, 1);

        peerServices = new QLabel(detailWidget);
        peerServices->setObjectName(QStringLiteral("peerServices"));
        peerServices->setCursor(QCursor(Qt::IBeamCursor));
        peerServices->setTextFormat(Qt::PlainText);
        peerServices->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerServices, 4, 2, 1, 1);

        label_29 = new QLabel(detailWidget);
        label_29->setObjectName(QStringLiteral("label_29"));

        gridLayout_3->addWidget(label_29, 5, 0, 1, 1);

        peerHeight = new QLabel(detailWidget);
        peerHeight->setObjectName(QStringLiteral("peerHeight"));
        peerHeight->setCursor(QCursor(Qt::IBeamCursor));
        peerHeight->setTextFormat(Qt::PlainText);
        peerHeight->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerHeight, 5, 2, 1, 1);

        label_27 = new QLabel(detailWidget);
        label_27->setObjectName(QStringLiteral("label_27"));

        gridLayout_3->addWidget(label_27, 6, 0, 1, 1);

        peerSyncHeight = new QLabel(detailWidget);
        peerSyncHeight->setObjectName(QStringLiteral("peerSyncHeight"));
        peerSyncHeight->setCursor(QCursor(Qt::IBeamCursor));
        peerSyncHeight->setTextFormat(Qt::PlainText);
        peerSyncHeight->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerSyncHeight, 6, 2, 1, 1);

        label_25 = new QLabel(detailWidget);
        label_25->setObjectName(QStringLiteral("label_25"));

        gridLayout_3->addWidget(label_25, 7, 0, 1, 1);

        peerCommonHeight = new QLabel(detailWidget);
        peerCommonHeight->setObjectName(QStringLiteral("peerCommonHeight"));
        peerCommonHeight->setCursor(QCursor(Qt::IBeamCursor));
        peerCommonHeight->setTextFormat(Qt::PlainText);
        peerCommonHeight->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerCommonHeight, 7, 2, 1, 1);

        label_24 = new QLabel(detailWidget);
        label_24->setObjectName(QStringLiteral("label_24"));

        gridLayout_3->addWidget(label_24, 8, 0, 1, 1);

        peerBanScore = new QLabel(detailWidget);
        peerBanScore->setObjectName(QStringLiteral("peerBanScore"));
        peerBanScore->setCursor(QCursor(Qt::IBeamCursor));
        peerBanScore->setTextFormat(Qt::PlainText);
        peerBanScore->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerBanScore, 8, 2, 1, 1);

        label_22 = new QLabel(detailWidget);
        label_22->setObjectName(QStringLiteral("label_22"));

        gridLayout_3->addWidget(label_22, 9, 0, 1, 1);

        peerConnTime = new QLabel(detailWidget);
        peerConnTime->setObjectName(QStringLiteral("peerConnTime"));
        peerConnTime->setCursor(QCursor(Qt::IBeamCursor));
        peerConnTime->setTextFormat(Qt::PlainText);
        peerConnTime->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerConnTime, 9, 2, 1, 1);

        label_15 = new QLabel(detailWidget);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_3->addWidget(label_15, 10, 0, 1, 1);

        peerLastSend = new QLabel(detailWidget);
        peerLastSend->setObjectName(QStringLiteral("peerLastSend"));
        peerLastSend->setCursor(QCursor(Qt::IBeamCursor));
        peerLastSend->setTextFormat(Qt::PlainText);
        peerLastSend->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerLastSend, 10, 2, 1, 1);

        label_19 = new QLabel(detailWidget);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout_3->addWidget(label_19, 11, 0, 1, 1);

        peerLastRecv = new QLabel(detailWidget);
        peerLastRecv->setObjectName(QStringLiteral("peerLastRecv"));
        peerLastRecv->setCursor(QCursor(Qt::IBeamCursor));
        peerLastRecv->setTextFormat(Qt::PlainText);
        peerLastRecv->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerLastRecv, 11, 2, 1, 1);

        label_18 = new QLabel(detailWidget);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout_3->addWidget(label_18, 12, 0, 1, 1);

        peerBytesSent = new QLabel(detailWidget);
        peerBytesSent->setObjectName(QStringLiteral("peerBytesSent"));
        peerBytesSent->setCursor(QCursor(Qt::IBeamCursor));
        peerBytesSent->setTextFormat(Qt::PlainText);
        peerBytesSent->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerBytesSent, 12, 2, 1, 1);

        label_20 = new QLabel(detailWidget);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout_3->addWidget(label_20, 13, 0, 1, 1);

        peerBytesRecv = new QLabel(detailWidget);
        peerBytesRecv->setObjectName(QStringLiteral("peerBytesRecv"));
        peerBytesRecv->setCursor(QCursor(Qt::IBeamCursor));
        peerBytesRecv->setTextFormat(Qt::PlainText);
        peerBytesRecv->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerBytesRecv, 13, 2, 1, 1);

        label_26 = new QLabel(detailWidget);
        label_26->setObjectName(QStringLiteral("label_26"));

        gridLayout_3->addWidget(label_26, 14, 0, 1, 1);

        peerPingTime = new QLabel(detailWidget);
        peerPingTime->setObjectName(QStringLiteral("peerPingTime"));
        peerPingTime->setCursor(QCursor(Qt::IBeamCursor));
        peerPingTime->setTextFormat(Qt::PlainText);
        peerPingTime->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerPingTime, 14, 2, 1, 1);

        peerPingWaitLabel = new QLabel(detailWidget);
        peerPingWaitLabel->setObjectName(QStringLiteral("peerPingWaitLabel"));

        gridLayout_3->addWidget(peerPingWaitLabel, 15, 0, 1, 1);

        peerPingWait = new QLabel(detailWidget);
        peerPingWait->setObjectName(QStringLiteral("peerPingWait"));
        peerPingWait->setCursor(QCursor(Qt::IBeamCursor));
        peerPingWait->setTextFormat(Qt::PlainText);
        peerPingWait->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(peerPingWait, 15, 2, 1, 1);

        label_timeoffset = new QLabel(detailWidget);
        label_timeoffset->setObjectName(QStringLiteral("label_timeoffset"));

        gridLayout_3->addWidget(label_timeoffset, 16, 0, 1, 1);

        timeoffset = new QLabel(detailWidget);
        timeoffset->setObjectName(QStringLiteral("timeoffset"));
        timeoffset->setCursor(QCursor(Qt::IBeamCursor));
        timeoffset->setTextFormat(Qt::PlainText);
        timeoffset->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_3->addWidget(timeoffset, 16, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_3->addItem(verticalSpacer_3, 17, 1, 1, 1);


        gridLayout_2->addWidget(detailWidget, 1, 1, 1, 1);

        tabWidget->addTab(tab_peers, QString());
        tab_repair = new QWidget();
        tab_repair->setObjectName(QStringLiteral("tab_repair"));
        gridLayout_4 = new QGridLayout(tab_repair);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(12);
        label_repair_header = new QLabel(tab_repair);
        label_repair_header->setObjectName(QStringLiteral("label_repair_header"));
        label_repair_header->setFont(font);

        gridLayout_4->addWidget(label_repair_header, 0, 0, 1, 4);

        label_repair_helptext = new QLabel(tab_repair);
        label_repair_helptext->setObjectName(QStringLiteral("label_repair_helptext"));
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        label_repair_helptext->setFont(font3);
        label_repair_helptext->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_helptext, 1, 0, 1, 4);

        wallet_path_label = new QLabel(tab_repair);
        wallet_path_label->setObjectName(QStringLiteral("wallet_path_label"));

        gridLayout_4->addWidget(wallet_path_label, 2, 0, 1, 1);

        wallet_path = new QLabel(tab_repair);
        wallet_path->setObjectName(QStringLiteral("wallet_path"));
        wallet_path->setCursor(QCursor(Qt::IBeamCursor));
        wallet_path->setTextFormat(Qt::PlainText);
        wallet_path->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_4->addWidget(wallet_path, 2, 1, 1, 3);

        wallet_custombackuppath_label = new QLabel(tab_repair);
        wallet_custombackuppath_label->setObjectName(QStringLiteral("wallet_custombackuppath_label"));
        wallet_custombackuppath_label->setVisible(false);

        gridLayout_4->addWidget(wallet_custombackuppath_label, 3, 0, 1, 1);

        wallet_custombackuppath = new QLabel(tab_repair);
        wallet_custombackuppath->setObjectName(QStringLiteral("wallet_custombackuppath"));
        wallet_custombackuppath->setCursor(QCursor(Qt::IBeamCursor));
        wallet_custombackuppath->setVisible(false);
        wallet_custombackuppath->setTextFormat(Qt::PlainText);
        wallet_custombackuppath->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_4->addWidget(wallet_custombackuppath, 3, 1, 1, 3);

        wallet_custombackupthreshold_label = new QLabel(tab_repair);
        wallet_custombackupthreshold_label->setObjectName(QStringLiteral("wallet_custombackupthreshold_label"));
        wallet_custombackupthreshold_label->setVisible(false);

        gridLayout_4->addWidget(wallet_custombackupthreshold_label, 5, 0, 1, 1);

        wallet_custombackupthreshold = new QLabel(tab_repair);
        wallet_custombackupthreshold->setObjectName(QStringLiteral("wallet_custombackupthreshold"));
        wallet_custombackupthreshold->setCursor(QCursor(Qt::IBeamCursor));
        wallet_custombackupthreshold->setVisible(false);
        wallet_custombackupthreshold->setTextFormat(Qt::PlainText);
        wallet_custombackupthreshold->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_4->addWidget(wallet_custombackupthreshold, 5, 1, 1, 3);

        verticalSpacer_repair1 = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_repair1, 6, 0, 1, 1);

        btn_salvagewallet = new QPushButton(tab_repair);
        btn_salvagewallet->setObjectName(QStringLiteral("btn_salvagewallet"));
        btn_salvagewallet->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_salvagewallet, 7, 0, 1, 2);

        label_repair_salvage_command = new QLabel(tab_repair);
        label_repair_salvage_command->setObjectName(QStringLiteral("label_repair_salvage_command"));
        label_repair_salvage_command->setText(QStringLiteral("-salvagewallet:"));

        gridLayout_4->addWidget(label_repair_salvage_command, 7, 2, 1, 1);

        label_repair_salvage = new QLabel(tab_repair);
        label_repair_salvage->setObjectName(QStringLiteral("label_repair_salvage"));
        label_repair_salvage->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_salvage, 7, 3, 1, 1);

        btn_rescan = new QPushButton(tab_repair);
        btn_rescan->setObjectName(QStringLiteral("btn_rescan"));
        btn_rescan->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_rescan, 8, 0, 1, 2);

        label_repair_rescan_command = new QLabel(tab_repair);
        label_repair_rescan_command->setObjectName(QStringLiteral("label_repair_rescan_command"));
        label_repair_rescan_command->setText(QStringLiteral("-rescan:"));

        gridLayout_4->addWidget(label_repair_rescan_command, 8, 2, 1, 1);

        label_repair_rescan = new QLabel(tab_repair);
        label_repair_rescan->setObjectName(QStringLiteral("label_repair_rescan"));
        label_repair_rescan->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_rescan, 8, 3, 1, 1);

        btn_zapwallettxes1 = new QPushButton(tab_repair);
        btn_zapwallettxes1->setObjectName(QStringLiteral("btn_zapwallettxes1"));
        btn_zapwallettxes1->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_zapwallettxes1, 9, 0, 1, 2);

        label_repair_zap1_command = new QLabel(tab_repair);
        label_repair_zap1_command->setObjectName(QStringLiteral("label_repair_zap1_command"));
        label_repair_zap1_command->setText(QStringLiteral("-zapwallettxes=1:"));

        gridLayout_4->addWidget(label_repair_zap1_command, 9, 2, 1, 1);

        label_repair_zap1 = new QLabel(tab_repair);
        label_repair_zap1->setObjectName(QStringLiteral("label_repair_zap1"));
        label_repair_zap1->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_zap1, 9, 3, 1, 1);

        btn_zapwallettxes2 = new QPushButton(tab_repair);
        btn_zapwallettxes2->setObjectName(QStringLiteral("btn_zapwallettxes2"));
        btn_zapwallettxes2->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_zapwallettxes2, 10, 0, 1, 2);

        label_repair_zap2_command = new QLabel(tab_repair);
        label_repair_zap2_command->setObjectName(QStringLiteral("label_repair_zap2_command"));
        label_repair_zap2_command->setText(QStringLiteral("-zapwallettxes=2:"));

        gridLayout_4->addWidget(label_repair_zap2_command, 10, 2, 1, 1);

        label_repair_zap2 = new QLabel(tab_repair);
        label_repair_zap2->setObjectName(QStringLiteral("label_repair_zap2"));
        label_repair_zap2->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_zap2, 10, 3, 1, 1);

        btn_upgradewallet = new QPushButton(tab_repair);
        btn_upgradewallet->setObjectName(QStringLiteral("btn_upgradewallet"));
        btn_upgradewallet->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_upgradewallet, 11, 0, 1, 2);

        label_repair_upgrade_command = new QLabel(tab_repair);
        label_repair_upgrade_command->setObjectName(QStringLiteral("label_repair_upgrade_command"));
        label_repair_upgrade_command->setText(QStringLiteral("-upgradewallet:"));

        gridLayout_4->addWidget(label_repair_upgrade_command, 11, 2, 1, 1);

        label_repair_upgrade = new QLabel(tab_repair);
        label_repair_upgrade->setObjectName(QStringLiteral("label_repair_upgrade"));
        label_repair_upgrade->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_upgrade, 11, 3, 1, 1);

        btn_reindex = new QPushButton(tab_repair);
        btn_reindex->setObjectName(QStringLiteral("btn_reindex"));
        btn_reindex->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_reindex, 12, 0, 1, 2);

        label_repair_reindex_command = new QLabel(tab_repair);
        label_repair_reindex_command->setObjectName(QStringLiteral("label_repair_reindex_command"));
        label_repair_reindex_command->setText(QStringLiteral("-reindex:"));

        gridLayout_4->addWidget(label_repair_reindex_command, 12, 2, 1, 1);

        label_repair_reindex = new QLabel(tab_repair);
        label_repair_reindex->setObjectName(QStringLiteral("label_repair_reindex"));
        label_repair_reindex->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_reindex, 12, 3, 1, 1);

        btn_resync = new QPushButton(tab_repair);
        btn_resync->setObjectName(QStringLiteral("btn_resync"));
        btn_resync->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_resync, 13, 0, 1, 2);

        label_repair_resync_command = new QLabel(tab_repair);
        label_repair_resync_command->setObjectName(QStringLiteral("label_repair_resync_command"));

        gridLayout_4->addWidget(label_repair_resync_command, 13, 2, 1, 1);

        label_repair_resync = new QLabel(tab_repair);
        label_repair_resync->setObjectName(QStringLiteral("label_repair_resync"));
        label_repair_resync->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_resync, 13, 3, 1, 1);

        btn_bootstrap = new QPushButton(tab_repair);
        btn_bootstrap->setObjectName(QStringLiteral("btn_bootstrap"));
        btn_bootstrap->setMinimumSize(QSize(100, 23));

        gridLayout_4->addWidget(btn_bootstrap, 13, 0, 1, 2);

        label_repair_bootstrap_command = new QLabel(tab_repair);
        label_repair_bootstrap_command->setObjectName(QStringLiteral("label_repair_bootstrap_command"));

        gridLayout_4->addWidget(label_repair_bootstrap_command, 13, 2, 1, 1);

        label_repair_bootstrap = new QLabel(tab_repair);
        label_repair_bootstrap->setObjectName(QStringLiteral("label_repair_bootstrap"));
        label_repair_bootstrap->setWordWrap(true);

        gridLayout_4->addWidget(label_repair_bootstrap, 13, 3, 1, 1);

        verticalSpacer_repair2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_repair2, 15, 0, 1, 1);

        tabWidget->addTab(tab_repair, QString());
        tab_status = new QWidget();
        tab_status->setObjectName(QStringLiteral("tab_status"));
        ROI = new QLabel(tab_status);
        ROI->setObjectName(QStringLiteral("ROI"));
        ROI->setGeometry(QRect(60, 20, 181, 17));
        ROI->setFont(font);
        stakingROI = new QLabel(tab_status);
        stakingROI->setObjectName(QStringLiteral("stakingROI"));
        stakingROI->setGeometry(QRect(70, 40, 171, 17));
        smooth_staking = new QLabel(tab_status);
        smooth_staking->setObjectName(QStringLiteral("smooth_staking"));
        smooth_staking->setGeometry(QRect(70, 60, 171, 17));
        staked_coins = new QLabel(tab_status);
        staked_coins->setObjectName(QStringLiteral("staked_coins"));
        staked_coins->setGeometry(QRect(70, 80, 171, 17));
        masternode_ROI = new QLabel(tab_status);
        masternode_ROI->setObjectName(QStringLiteral("masternode_ROI"));
        masternode_ROI->setGeometry(QRect(70, 110, 171, 17));
        masternode_coins = new QLabel(tab_status);
        masternode_coins->setObjectName(QStringLiteral("masternode_coins"));
        masternode_coins->setGeometry(QRect(70, 130, 171, 17));
        masternode_count = new QLabel(tab_status);
        masternode_count->setObjectName(QStringLiteral("masternode_count"));
        masternode_count->setGeometry(QRect(60, 170, 181, 17));
        masternode_count->setFont(font);
        total = new QLabel(tab_status);
        total->setObjectName(QStringLiteral("total"));
        total->setGeometry(QRect(70, 190, 171, 17));
        stable = new QLabel(tab_status);
        stable->setObjectName(QStringLiteral("stable"));
        stable->setGeometry(QRect(70, 210, 171, 17));
        enabled = new QLabel(tab_status);
        enabled->setObjectName(QStringLiteral("enabled"));
        enabled->setGeometry(QRect(70, 230, 171, 17));
        inqueue = new QLabel(tab_status);
        inqueue->setObjectName(QStringLiteral("inqueue"));
        inqueue->setGeometry(QRect(70, 250, 171, 17));
        ipv4 = new QLabel(tab_status);
        ipv4->setObjectName(QStringLiteral("ipv4"));
        ipv4->setGeometry(QRect(70, 270, 171, 17));
        ipv6 = new QLabel(tab_status);
        ipv6->setObjectName(QStringLiteral("ipv6"));
        ipv6->setGeometry(QRect(70, 290, 171, 17));
        onion = new QLabel(tab_status);
        onion->setObjectName(QStringLiteral("onion"));
        onion->setGeometry(QRect(70, 310, 171, 17));
        stkroi = new QLabel(tab_status);
        stkroi->setObjectName(QStringLiteral("stkroi"));
        stkroi->setGeometry(QRect(260, 40, 121, 17));
        stkroi->setCursor(QCursor(Qt::IBeamCursor));
        stkroi->setTextFormat(Qt::PlainText);
        stkroi->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        stkroi->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        ssroi = new QLabel(tab_status);
        ssroi->setObjectName(QStringLiteral("ssroi"));
        ssroi->setGeometry(QRect(260, 60, 121, 17));
        ssroi->setCursor(QCursor(Qt::IBeamCursor));
        ssroi->setTextFormat(Qt::PlainText);
        ssroi->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        ssroi->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        stkcoins = new QLabel(tab_status);
        stkcoins->setObjectName(QStringLiteral("stkcoins"));
        stkcoins->setGeometry(QRect(260, 80, 121, 17));
        stkcoins->setCursor(QCursor(Qt::IBeamCursor));
        stkcoins->setTextFormat(Qt::PlainText);
        stkcoins->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        stkcoins->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        mnroi = new QLabel(tab_status);
        mnroi->setObjectName(QStringLiteral("mnroi"));
        mnroi->setGeometry(QRect(260, 110, 121, 17));
        mnroi->setCursor(QCursor(Qt::IBeamCursor));
        mnroi->setTextFormat(Qt::PlainText);
        mnroi->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        mnroi->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        mncoins = new QLabel(tab_status);
        mncoins->setObjectName(QStringLiteral("mncoins"));
        mncoins->setGeometry(QRect(260, 130, 121, 17));
        mncoins->setCursor(QCursor(Qt::IBeamCursor));
        mncoins->setTextFormat(Qt::PlainText);
        mncoins->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        mncoins->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        totalmn = new QLabel(tab_status);
        totalmn->setObjectName(QStringLiteral("totalmn"));
        totalmn->setGeometry(QRect(260, 190, 121, 17));
        totalmn->setCursor(QCursor(Qt::IBeamCursor));
        totalmn->setTextFormat(Qt::PlainText);
        totalmn->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        totalmn->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        stablemn = new QLabel(tab_status);
        stablemn->setObjectName(QStringLiteral("stablemn"));
        stablemn->setGeometry(QRect(260, 210, 121, 17));
        stablemn->setCursor(QCursor(Qt::IBeamCursor));
        stablemn->setTextFormat(Qt::PlainText);
        stablemn->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        stablemn->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        enabledmn = new QLabel(tab_status);
        enabledmn->setObjectName(QStringLiteral("enabledmn"));
        enabledmn->setGeometry(QRect(260, 230, 121, 17));
        enabledmn->setCursor(QCursor(Qt::IBeamCursor));
        enabledmn->setTextFormat(Qt::PlainText);
        enabledmn->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        enabledmn->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        inqmn = new QLabel(tab_status);
        inqmn->setObjectName(QStringLiteral("inqmn"));
        inqmn->setGeometry(QRect(260, 250, 121, 17));
        inqmn->setCursor(QCursor(Qt::IBeamCursor));
        inqmn->setTextFormat(Qt::PlainText);
        inqmn->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        inqmn->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        ipv4mn = new QLabel(tab_status);
        ipv4mn->setObjectName(QStringLiteral("ipv4mn"));
        ipv4mn->setGeometry(QRect(260, 270, 121, 17));
        ipv4mn->setCursor(QCursor(Qt::IBeamCursor));
        ipv4mn->setTextFormat(Qt::PlainText);
        ipv4mn->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        ipv4mn->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        ipv6mn = new QLabel(tab_status);
        ipv6mn->setObjectName(QStringLiteral("ipv6mn"));
        ipv6mn->setGeometry(QRect(260, 290, 121, 17));
        ipv6mn->setCursor(QCursor(Qt::IBeamCursor));
        ipv6mn->setTextFormat(Qt::PlainText);
        ipv6mn->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        ipv6mn->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        onionmn = new QLabel(tab_status);
        onionmn->setObjectName(QStringLiteral("onionmn"));
        onionmn->setGeometry(QRect(260, 310, 121, 17));
        onionmn->setCursor(QCursor(Qt::IBeamCursor));
        onionmn->setTextFormat(Qt::PlainText);
        onionmn->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        onionmn->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        my_masternodes = new QLabel(tab_status);
        my_masternodes->setObjectName(QStringLiteral("my_masternodes"));
        my_masternodes->setGeometry(QRect(60, 350, 181, 17));
        my_masternodes->setFont(font);
        mytotal = new QLabel(tab_status);
        mytotal->setObjectName(QStringLiteral("mytotal"));
        mytotal->setGeometry(QRect(70, 370, 171, 17));
        myactive = new QLabel(tab_status);
        myactive->setObjectName(QStringLiteral("myactive"));
        myactive->setGeometry(QRect(70, 390, 171, 17));
        mytotalmn = new QLabel(tab_status);
        mytotalmn->setObjectName(QStringLiteral("mytotalmn"));
        mytotalmn->setGeometry(QRect(260, 370, 121, 17));
        mytotalmn->setCursor(QCursor(Qt::IBeamCursor));
        mytotalmn->setTextFormat(Qt::PlainText);
        mytotalmn->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        mytotalmn->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        myactivemn = new QLabel(tab_status);
        myactivemn->setObjectName(QStringLiteral("myactivemn"));
        myactivemn->setGeometry(QRect(260, 390, 121, 17));
        myactivemn->setCursor(QCursor(Qt::IBeamCursor));
        myactivemn->setTextFormat(Qt::PlainText);
        myactivemn->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
        myactivemn->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        bststamp = new QLabel(tab_status);
        bststamp->setObjectName(QStringLiteral("bststamp"));
        bststamp->setGeometry(QRect(260, 20, 451, 17));
        bststamp->setCursor(QCursor(Qt::IBeamCursor));
        bststamp->setTextFormat(Qt::PlainText);
        bststamp->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        bststamp->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);
        btn_refresh = new QPushButton(tab_status);
        btn_refresh->setObjectName(QStringLiteral("btn_refresh"));
        btn_refresh->setGeometry(QRect(530, 370, 97, 33));
        tabWidget->addTab(tab_status, QString());

        verticalLayout_2->addWidget(tabWidget);


        retranslateUi(RPCConsole);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(RPCConsole);
    } // setupUi

    void retranslateUi(QDialog *RPCConsole)
    {
        RPCConsole->setWindowTitle(QApplication::translate("RPCConsole", "Tools window", Q_NULLPTR));
        generalHeader->setText(QApplication::translate("RPCConsole", "General", Q_NULLPTR));
        clientNameLabel->setText(QApplication::translate("RPCConsole", "Client name", Q_NULLPTR));
        clientName->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        clientVersionLabel->setText(QApplication::translate("RPCConsole", "Client version", Q_NULLPTR));
        clientVersion->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        berkeleyDBVersionLabel->setText(QApplication::translate("RPCConsole", "Using BerkeleyDB version", Q_NULLPTR));
        berkeleyDBVersion->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        buildDateLabel->setText(QApplication::translate("RPCConsole", "Build date", Q_NULLPTR));
        buildDate->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        startupTimeLabel->setText(QApplication::translate("RPCConsole", "Startup time", Q_NULLPTR));
        startupTime->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        dataDirLabel->setText(QApplication::translate("RPCConsole", "Data Directory", Q_NULLPTR));
        dataDir->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        networkHeader->setText(QApplication::translate("RPCConsole", "Network", Q_NULLPTR));
        networkNameLabel->setText(QApplication::translate("RPCConsole", "Name", Q_NULLPTR));
        networkName->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        numberOfConnectionsLabel->setText(QApplication::translate("RPCConsole", "Number of connections", Q_NULLPTR));
        numberOfConnections->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        masternodeCountLabel->setText(QApplication::translate("RPCConsole", "Number of Masternodes", Q_NULLPTR));
        masternodeCount->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        blockchainHeader->setText(QApplication::translate("RPCConsole", "Block chain", Q_NULLPTR));
        numberOfBlocksLabel->setText(QApplication::translate("RPCConsole", "Current number of blocks", Q_NULLPTR));
        numberOfBlocks->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        lastBlockTimeLabel->setText(QApplication::translate("RPCConsole", "Last block time", Q_NULLPTR));
        lastBlockTime->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        lastBlockHashLabel->setText(QApplication::translate("RPCConsole", "Last block hash", Q_NULLPTR));
        lastBlockHash->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        debugLogFileHeader->setText(QApplication::translate("RPCConsole", "Debug log file", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        openDebugLogfileButton->setToolTip(QApplication::translate("RPCConsole", "Open the KYAN debug log file from the current data directory. This can take a few seconds for large log files.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        openDebugLogfileButton->setText(QApplication::translate("RPCConsole", "&Open", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_info), QApplication::translate("RPCConsole", "&Information", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        clearButton->setToolTip(QApplication::translate("RPCConsole", "Clear console", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        clearButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_console), QApplication::translate("RPCConsole", "&Console", Q_NULLPTR));
        btnClearTrafficGraph->setText(QApplication::translate("RPCConsole", "&Clear", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("RPCConsole", "Totals", Q_NULLPTR));
        label_16->setText(QApplication::translate("RPCConsole", "Received", Q_NULLPTR));
        label_17->setText(QApplication::translate("RPCConsole", "Sent", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_nettraffic), QApplication::translate("RPCConsole", "&Network Traffic", Q_NULLPTR));
        banHeading->setText(QApplication::translate("RPCConsole", "Banned peers", Q_NULLPTR));
        peerHeading->setText(QApplication::translate("RPCConsole", "Select a peer to view detailed information.", Q_NULLPTR));
        label_30->setText(QApplication::translate("RPCConsole", "Whitelisted", Q_NULLPTR));
        peerWhitelisted->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_23->setText(QApplication::translate("RPCConsole", "Direction", Q_NULLPTR));
        peerDirection->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_21->setText(QApplication::translate("RPCConsole", "Protocol", Q_NULLPTR));
        peerVersion->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_28->setText(QApplication::translate("RPCConsole", "Version", Q_NULLPTR));
        peerSubversion->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_4->setText(QApplication::translate("RPCConsole", "Services", Q_NULLPTR));
        peerServices->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_29->setText(QApplication::translate("RPCConsole", "Starting Block", Q_NULLPTR));
        peerHeight->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_27->setText(QApplication::translate("RPCConsole", "Synced Headers", Q_NULLPTR));
        peerSyncHeight->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_25->setText(QApplication::translate("RPCConsole", "Synced Blocks", Q_NULLPTR));
        peerCommonHeight->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_24->setText(QApplication::translate("RPCConsole", "Ban Score", Q_NULLPTR));
        peerBanScore->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_22->setText(QApplication::translate("RPCConsole", "Connection Time", Q_NULLPTR));
        peerConnTime->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_15->setText(QApplication::translate("RPCConsole", "Last Send", Q_NULLPTR));
        peerLastSend->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_19->setText(QApplication::translate("RPCConsole", "Last Receive", Q_NULLPTR));
        peerLastRecv->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_18->setText(QApplication::translate("RPCConsole", "Bytes Sent", Q_NULLPTR));
        peerBytesSent->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_20->setText(QApplication::translate("RPCConsole", "Bytes Received", Q_NULLPTR));
        peerBytesRecv->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_26->setText(QApplication::translate("RPCConsole", "Ping Time", Q_NULLPTR));
        peerPingTime->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        peerPingWaitLabel->setToolTip(QApplication::translate("RPCConsole", "The duration of a currently outstanding ping.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        peerPingWaitLabel->setText(QApplication::translate("RPCConsole", "Ping Wait", Q_NULLPTR));
        peerPingWait->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        label_timeoffset->setText(QApplication::translate("RPCConsole", "Time Offset", Q_NULLPTR));
        timeoffset->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_peers), QApplication::translate("RPCConsole", "&Peers", Q_NULLPTR));
        label_repair_header->setText(QApplication::translate("RPCConsole", "Wallet repair options.", Q_NULLPTR));
        label_repair_helptext->setText(QApplication::translate("RPCConsole", "The buttons below will restart the wallet with command-line options to repair the wallet, fix issues with corrupt blockhain files or missing/obsolete transactions.", Q_NULLPTR));
        wallet_path_label->setText(QApplication::translate("RPCConsole", "Wallet In Use:", Q_NULLPTR));
        wallet_path->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        wallet_custombackuppath_label->setText(QApplication::translate("RPCConsole", "Custom Backup Path:", Q_NULLPTR));
        wallet_custombackuppath->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        wallet_custombackupthreshold_label->setText(QApplication::translate("RPCConsole", "Custom Backups Threshold:", Q_NULLPTR));
        wallet_custombackupthreshold->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        btn_salvagewallet->setText(QApplication::translate("RPCConsole", "Salvage wallet", Q_NULLPTR));
        label_repair_salvage->setText(QApplication::translate("RPCConsole", "Attempt to recover private keys from a corrupt wallet.dat.", Q_NULLPTR));
        btn_rescan->setText(QApplication::translate("RPCConsole", "Rescan blockchain files", Q_NULLPTR));
        label_repair_rescan->setText(QApplication::translate("RPCConsole", "Rescan the block chain for missing wallet transactions.", Q_NULLPTR));
        btn_zapwallettxes1->setText(QApplication::translate("RPCConsole", "Recover transactions 1", Q_NULLPTR));
        label_repair_zap1->setText(QApplication::translate("RPCConsole", "Recover transactions from blockchain (keep meta-data, e.g. account owner).", Q_NULLPTR));
        btn_zapwallettxes2->setText(QApplication::translate("RPCConsole", "Recover transactions 2", Q_NULLPTR));
        label_repair_zap2->setText(QApplication::translate("RPCConsole", "Recover transactions from blockchain (drop meta-data).", Q_NULLPTR));
        btn_upgradewallet->setText(QApplication::translate("RPCConsole", "Upgrade wallet format", Q_NULLPTR));
        label_repair_upgrade->setText(QApplication::translate("RPCConsole", "Upgrade wallet to latest format on startup. (Note: this is NOT an update of the wallet itself!)", Q_NULLPTR));
        btn_reindex->setText(QApplication::translate("RPCConsole", "Rebuild index", Q_NULLPTR));
        label_repair_reindex->setText(QApplication::translate("RPCConsole", "Rebuild block chain index from current blk000??.dat files.", Q_NULLPTR));
        btn_resync->setText(QApplication::translate("RPCConsole", "Delete local Blockchain Folders", Q_NULLPTR));
        label_repair_resync_command->setText(QApplication::translate("RPCConsole", "-resync:", Q_NULLPTR));
        label_repair_resync->setText(QApplication::translate("RPCConsole", "Deletes all local blockchain folders so the wallet synchronizes from scratch.", Q_NULLPTR));
        btn_bootstrap->setText(QApplication::translate("RPCConsole", "Bootstrap Blockchain", Q_NULLPTR));
        label_repair_bootstrap_command->setText(QApplication::translate("RPCConsole", "-bootstrap:", Q_NULLPTR));
        label_repair_bootstrap->setText(QApplication::translate("RPCConsole", "Deletes all local blockchain folders and loads blockchain from source.", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_repair), QApplication::translate("RPCConsole", "&Wallet Repair", Q_NULLPTR));
        ROI->setText(QApplication::translate("RPCConsole", "Return on Investment", Q_NULLPTR));
        stakingROI->setText(QApplication::translate("RPCConsole", "Staking ROI", Q_NULLPTR));
        smooth_staking->setText(QApplication::translate("RPCConsole", "Smooth Staking ROI", Q_NULLPTR));
        staked_coins->setText(QApplication::translate("RPCConsole", "Staked Coins", Q_NULLPTR));
        masternode_ROI->setText(QApplication::translate("RPCConsole", "Masternoding ROI", Q_NULLPTR));
        masternode_coins->setText(QApplication::translate("RPCConsole", "Masternoded Coins", Q_NULLPTR));
        masternode_count->setText(QApplication::translate("RPCConsole", "Masternode Count", Q_NULLPTR));
        total->setText(QApplication::translate("RPCConsole", "Total", Q_NULLPTR));
        stable->setText(QApplication::translate("RPCConsole", "Stable", Q_NULLPTR));
        enabled->setText(QApplication::translate("RPCConsole", "Enabled", Q_NULLPTR));
        inqueue->setText(QApplication::translate("RPCConsole", "In Queue", Q_NULLPTR));
        ipv4->setText(QApplication::translate("RPCConsole", "ipV4", Q_NULLPTR));
        ipv6->setText(QApplication::translate("RPCConsole", "ipV6", Q_NULLPTR));
        onion->setText(QApplication::translate("RPCConsole", "Onion", Q_NULLPTR));
        stkroi->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        ssroi->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        stkcoins->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        mnroi->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        mncoins->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        totalmn->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        stablemn->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        enabledmn->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        inqmn->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        ipv4mn->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        ipv6mn->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        onionmn->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        my_masternodes->setText(QApplication::translate("RPCConsole", "My Masternodes", Q_NULLPTR));
        mytotal->setText(QApplication::translate("RPCConsole", "Total", Q_NULLPTR));
        myactive->setText(QApplication::translate("RPCConsole", "Active", Q_NULLPTR));
        mytotalmn->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        myactivemn->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        bststamp->setText(QApplication::translate("RPCConsole", "N/A", Q_NULLPTR));
        btn_refresh->setText(QApplication::translate("RPCConsole", "Refresh", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_status), QApplication::translate("RPCConsole", "&Blockchain Status", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RPCConsole: public Ui_RPCConsole {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RPCCONSOLE_H
