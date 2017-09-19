/********************************************************************************
** Form generated from reading UI file 'passBox.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PASSBOX_H
#define UI_PASSBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_passBox
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *passLabel;
    QLineEdit *passEntry;
    QDialogButtonBox *passBtnBox;

    void setupUi(QDialog *passBox)
    {
        if (passBox->objectName().isEmpty())
            passBox->setObjectName(QStringLiteral("passBox"));
        passBox->resize(400, 101);
        passBox->setToolTipDuration(-1);
        verticalLayout = new QVBoxLayout(passBox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        passLabel = new QLabel(passBox);
        passLabel->setObjectName(QStringLiteral("passLabel"));

        verticalLayout->addWidget(passLabel);

        passEntry = new QLineEdit(passBox);
        passEntry->setObjectName(QStringLiteral("passEntry"));
        passEntry->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passEntry);

        passBtnBox = new QDialogButtonBox(passBox);
        passBtnBox->setObjectName(QStringLiteral("passBtnBox"));
        passBtnBox->setOrientation(Qt::Horizontal);
        passBtnBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(passBtnBox);


        retranslateUi(passBox);
        QObject::connect(passBtnBox, SIGNAL(accepted()), passBox, SLOT(accept()));
        QObject::connect(passBtnBox, SIGNAL(rejected()), passBox, SLOT(reject()));

        QMetaObject::connectSlotsByName(passBox);
    } // setupUi

    void retranslateUi(QDialog *passBox)
    {
        passBox->setWindowTitle(QApplication::translate("passBox", "iw utility requires password", Q_NULLPTR));
        passLabel->setText(QApplication::translate("passBox", "TextLabel", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        passEntry->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        passEntry->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class passBox: public Ui_passBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PASSBOX_H
