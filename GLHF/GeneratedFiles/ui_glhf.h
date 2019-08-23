/********************************************************************************
** Form generated from reading UI file 'glhf.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLHF_H
#define UI_GLHF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GLHFClass
{
public:

    void setupUi(QWidget *GLHFClass)
    {
        if (GLHFClass->objectName().isEmpty())
            GLHFClass->setObjectName(QString::fromUtf8("GLHFClass"));
        GLHFClass->resize(600, 400);

        retranslateUi(GLHFClass);

        QMetaObject::connectSlotsByName(GLHFClass);
    } // setupUi

    void retranslateUi(QWidget *GLHFClass)
    {
        GLHFClass->setWindowTitle(QApplication::translate("GLHFClass", "GLHF", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GLHFClass: public Ui_GLHFClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLHF_H
