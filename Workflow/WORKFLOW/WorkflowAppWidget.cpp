#include <WorkflowAppWidget.h>
#include "MainWindowWorkflowApp.h"
#include <QWidget>
#include <RemoteService.h>
#include <Utils/PythonProgressDialog.h>

#include <QMenuBar>
#include <QDebug>

PythonProgressDialog *WorkflowAppWidget::progressDialog = nullptr;

WorkflowAppWidget::WorkflowAppWidget(RemoteService *theService, QWidget *parent)
    :QWidget(parent), theRemoteService(theService)
{
    this->setContentsMargins(0,0,0,0);

    progressDialog = new PythonProgressDialog(parent);
}

WorkflowAppWidget::~WorkflowAppWidget()
{

}


void WorkflowAppWidget::showOutputDialog(void)
{
    progressDialog->showDialog(true);
}



void
WorkflowAppWidget::setMainWindow(MainWindowWorkflowApp* window) {
    theMainWindow = window;

    // Show progress dialog
    QMenu *windowsMenu = theMainWindow->menuBar()->addMenu(tr("&Windows"));
    windowsMenu->addAction("Show Output Dialog", this, &WorkflowAppWidget::showOutputDialog);
}


void
WorkflowAppWidget::statusMessage(const QString msg){
    qDebug() << "WorkflowAppWidget::statusMessage" << msg;
    emit sendStatusMessage(msg);
}


void
WorkflowAppWidget::errorMessage(const QString msg){
    qDebug() << "WorkflowAppWidget::errorMessage" << msg;

    emit sendErrorMessage(msg);
}


void
WorkflowAppWidget::fatalMessage(const QString msg){
    emit sendFatalMessage(msg);
}

MainWindowWorkflowApp *WorkflowAppWidget::getTheMainWindow() const
{
    return theMainWindow;
}


PythonProgressDialog *WorkflowAppWidget::getProgressDialog()
{
    return progressDialog;
}

