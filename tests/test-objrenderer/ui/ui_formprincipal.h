/********************************************************************************
** Form generated from reading UI file 'formprincipal.ui'
**
** Created: Tue Feb 28 21:26:47 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMPRINCIPAL_H
#define UI_FORMPRINCIPAL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormPrincipal
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_3;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QTextEdit *codigo_txt;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *limpar_btn;
    QPushButton *criar_btn;
    QLabel *label_2;

    void setupUi(QMainWindow *FormPrincipal)
    {
        if (FormPrincipal->objectName().isEmpty())
            FormPrincipal->setObjectName(QString::fromUtf8("FormPrincipal"));
        FormPrincipal->resize(887, 600);
        centralwidget = new QWidget(FormPrincipal);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(490, 490));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        gridLayout_3->addWidget(frame, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        codigo_txt = new QTextEdit(centralwidget);
        codigo_txt->setObjectName(QString::fromUtf8("codigo_txt"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier 10 Pitch"));
        codigo_txt->setFont(font);

        gridLayout_2->addWidget(codigo_txt, 1, 0, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 0, 1, 1);

        limpar_btn = new QPushButton(centralwidget);
        limpar_btn->setObjectName(QString::fromUtf8("limpar_btn"));

        gridLayout_2->addWidget(limpar_btn, 2, 1, 1, 1);

        criar_btn = new QPushButton(centralwidget);
        criar_btn->setObjectName(QString::fromUtf8("criar_btn"));

        gridLayout_2->addWidget(criar_btn, 2, 2, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 1, 1, 1);

        FormPrincipal->setCentralWidget(centralwidget);

        retranslateUi(FormPrincipal);

        QMetaObject::connectSlotsByName(FormPrincipal);
    } // setupUi

    void retranslateUi(QMainWindow *FormPrincipal)
    {
        FormPrincipal->setWindowTitle(QApplication::translate("FormPrincipal", "MainWindow", 0, QApplication::UnicodeUTF8));
        limpar_btn->setText(QApplication::translate("FormPrincipal", "Limpar", 0, QApplication::UnicodeUTF8));
        criar_btn->setText(QApplication::translate("FormPrincipal", "Criar", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FormPrincipal", "XML Objeto:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FormPrincipal: public Ui_FormPrincipal {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMPRINCIPAL_H
