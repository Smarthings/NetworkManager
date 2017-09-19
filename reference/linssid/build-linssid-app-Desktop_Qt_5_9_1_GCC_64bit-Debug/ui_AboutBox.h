/********************************************************************************
** Form generated from reading UI file 'AboutBox.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTBOX_H
#define UI_ABOUTBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_aboutBox
{
public:
    QGridLayout *gridLayout;
    QLabel *aboutVersion;
    QSpacerItem *horizontalSpacer;
    QPushButton *aboutCloseBtn;
    QLabel *aboutLogoLabel;
    QLabel *aboutLabel;

    void setupUi(QDialog *aboutBox)
    {
        if (aboutBox->objectName().isEmpty())
            aboutBox->setObjectName(QStringLiteral("aboutBox"));
        aboutBox->resize(379, 387);
        QIcon icon;
        icon.addFile(QStringLiteral("linssid.png"), QSize(), QIcon::Normal, QIcon::Off);
        aboutBox->setWindowIcon(icon);
        aboutBox->setModal(true);
        gridLayout = new QGridLayout(aboutBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        aboutVersion = new QLabel(aboutBox);
        aboutVersion->setObjectName(QStringLiteral("aboutVersion"));

        gridLayout->addWidget(aboutVersion, 3, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(447, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 1, 1, 1);

        aboutCloseBtn = new QPushButton(aboutBox);
        aboutCloseBtn->setObjectName(QStringLiteral("aboutCloseBtn"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(aboutCloseBtn->sizePolicy().hasHeightForWidth());
        aboutCloseBtn->setSizePolicy(sizePolicy);

        gridLayout->addWidget(aboutCloseBtn, 3, 2, 1, 1);

        aboutLogoLabel = new QLabel(aboutBox);
        aboutLogoLabel->setObjectName(QStringLiteral("aboutLogoLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(aboutLogoLabel->sizePolicy().hasHeightForWidth());
        aboutLogoLabel->setSizePolicy(sizePolicy1);
        aboutLogoLabel->setMaximumSize(QSize(64, 64));
        aboutLogoLabel->setFrameShape(QFrame::StyledPanel);
        aboutLogoLabel->setText(QStringLiteral(""));
        aboutLogoLabel->setPixmap(QPixmap(QString::fromUtf8("../../../../usr/share/pixmaps/linssid.png")));
        aboutLogoLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(aboutLogoLabel, 0, 0, 1, 1);

        aboutLabel = new QLabel(aboutBox);
        aboutLabel->setObjectName(QStringLiteral("aboutLabel"));
        aboutLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        aboutLabel->setWordWrap(true);

        gridLayout->addWidget(aboutLabel, 1, 0, 1, 3);


        retranslateUi(aboutBox);
        QObject::connect(aboutCloseBtn, SIGNAL(clicked()), aboutBox, SLOT(close()));

        QMetaObject::connectSlotsByName(aboutBox);
    } // setupUi

    void retranslateUi(QDialog *aboutBox)
    {
        aboutBox->setWindowTitle(QApplication::translate("aboutBox", "About linssid...", Q_NULLPTR));
        aboutVersion->setText(QApplication::translate("aboutBox", "Version:", Q_NULLPTR));
        aboutCloseBtn->setText(QApplication::translate("aboutBox", "Close", Q_NULLPTR));
        aboutLabel->setText(QApplication::translate("aboutBox", "LinSSID is authored by Warren Severin. It borrows from the graphic design ideas of the Windows program Inssider, but it is otherwise completely built from scratch.\n"
"\n"
"The LinSSID program is licensed under the terms of the GPL version 3. LinSSID version 2.2 and above are built using Qt5. LinSSID links to libraries of the Qwt project (http://qwt.sf.net). The LinSSID program also links to the Boost C++ libraries. The license to use these components is included in the program binary distribution.\n"
"\n"
"Hint: LinSSID will run faster when your interface is not connected to an attach point.", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class aboutBox: public Ui_aboutBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTBOX_H
