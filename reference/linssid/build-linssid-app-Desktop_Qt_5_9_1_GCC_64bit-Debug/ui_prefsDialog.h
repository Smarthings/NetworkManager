/********************************************************************************
** Form generated from reading UI file 'prefsDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PREFSDIALOG_H
#define UI_PREFSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_prefsDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *dbMinlbl;
    QSpinBox *dbMinsb;
    QLabel *plotGridlbl;
    QCheckBox *plotGridcbx;
    QLabel *dbMaxlbl;
    QSpinBox *dbMaxsb;
    QLabel *logoLbl;
    QDialogButtonBox *buttonBox;
    QCheckBox *logDatacbx;
    QLabel *logDatalbl;

    void setupUi(QDialog *prefsDialog)
    {
        if (prefsDialog->objectName().isEmpty())
            prefsDialog->setObjectName(QStringLiteral("prefsDialog"));
        prefsDialog->resize(334, 186);
        gridLayout = new QGridLayout(prefsDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        dbMinlbl = new QLabel(prefsDialog);
        dbMinlbl->setObjectName(QStringLiteral("dbMinlbl"));

        gridLayout->addWidget(dbMinlbl, 1, 0, 1, 1);

        dbMinsb = new QSpinBox(prefsDialog);
        dbMinsb->setObjectName(QStringLiteral("dbMinsb"));
        dbMinsb->setMinimum(-100);
        dbMinsb->setMaximum(-60);
        dbMinsb->setSingleStep(10);
        dbMinsb->setValue(-100);

        gridLayout->addWidget(dbMinsb, 1, 1, 1, 1);

        plotGridlbl = new QLabel(prefsDialog);
        plotGridlbl->setObjectName(QStringLiteral("plotGridlbl"));

        gridLayout->addWidget(plotGridlbl, 2, 0, 1, 1);

        plotGridcbx = new QCheckBox(prefsDialog);
        plotGridcbx->setObjectName(QStringLiteral("plotGridcbx"));
        plotGridcbx->setChecked(true);

        gridLayout->addWidget(plotGridcbx, 2, 1, 1, 1);

        dbMaxlbl = new QLabel(prefsDialog);
        dbMaxlbl->setObjectName(QStringLiteral("dbMaxlbl"));

        gridLayout->addWidget(dbMaxlbl, 0, 0, 1, 1);

        dbMaxsb = new QSpinBox(prefsDialog);
        dbMaxsb->setObjectName(QStringLiteral("dbMaxsb"));
        dbMaxsb->setMinimum(-50);
        dbMaxsb->setMaximum(0);
        dbMaxsb->setSingleStep(10);
        dbMaxsb->setValue(-20);

        gridLayout->addWidget(dbMaxsb, 0, 1, 1, 1);

        logoLbl = new QLabel(prefsDialog);
        logoLbl->setObjectName(QStringLiteral("logoLbl"));
        logoLbl->setPixmap(QPixmap(QString::fromUtf8("linssid48.png")));
        logoLbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(logoLbl, 4, 0, 1, 1);

        buttonBox = new QDialogButtonBox(prefsDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 4, 1, 1, 1);

        logDatacbx = new QCheckBox(prefsDialog);
        logDatacbx->setObjectName(QStringLiteral("logDatacbx"));

        gridLayout->addWidget(logDatacbx, 3, 1, 1, 1);

        logDatalbl = new QLabel(prefsDialog);
        logDatalbl->setObjectName(QStringLiteral("logDatalbl"));

        gridLayout->addWidget(logDatalbl, 3, 0, 1, 1);


        retranslateUi(prefsDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), prefsDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), prefsDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(prefsDialog);
    } // setupUi

    void retranslateUi(QDialog *prefsDialog)
    {
        prefsDialog->setWindowTitle(QApplication::translate("prefsDialog", "Preferences", Q_NULLPTR));
        dbMinlbl->setText(QApplication::translate("prefsDialog", "Plot Min db", Q_NULLPTR));
        plotGridlbl->setText(QApplication::translate("prefsDialog", "Show plot grid lines", Q_NULLPTR));
        dbMaxlbl->setText(QApplication::translate("prefsDialog", "Plot Max db", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        logDatacbx->setToolTip(QApplication::translate("prefsDialog", "<html><head/><body><p>Log data to file &quot;~/LinSSID.datalog&quot;</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        logDatacbx->setText(QString());
#ifndef QT_NO_TOOLTIP
        logDatalbl->setToolTip(QApplication::translate("prefsDialog", "<html><head/><body><p>Log data to file &quot;~/LinSSID.datalog&quot;</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        logDatalbl->setText(QApplication::translate("prefsDialog", "Log Data", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class prefsDialog: public Ui_prefsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PREFSDIALOG_H
