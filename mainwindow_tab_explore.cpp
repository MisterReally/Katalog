/*LICENCE
    This file is part of Katalog

    Copyright (C) 2020, the Katalog Development team

    Author: Stephane Couturier (Symbioxy)

    Katalog is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Katalog is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Katalog; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
/*FILE DESCRIPTION
/////////////////////////////////////////////////////////////////////////////
// Application: Katalog
// File Name:   mainwindow_tab_explore.cpp
// Purpose:     methods for the scren Collection AND the screen Explore
// Description:
// Author:      Stephane Couturier
// Modified by: Stephane Couturier
// Created:     2020-10-10
// Version:     0.1
/////////////////////////////////////////////////////////////////////////////
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "collection.h"
#include "catalog.h"

#include "treemodel.h"
#include "treeitem.h"

#include <QTextStream>
#include <QDesktopServices>
#include <QFileDialog>
#include <QSortFilterProxyModel>

//#include <KMessageBox>
//#include <KLocalizedString>

//----------------------------------------------------------------------
void MainWindow::exploreLoadDirectories()
{

//Explore_treeview_Directories

    //KMessageBox::information(this,"method read.\n");

    //QString testFilePath = collectionFolder + "/" + "default.txt";
    QString testFilePath = collectionFolder + "/" + "storage.csv";

    //const QStringList headers({tr("Title"), tr("Description")});

    QFile file(testFilePath);
    file.open(QIODevice::ReadOnly);
        //KMessageBox::information(this,"test\n");
//    TreeModel *model = new TreeModel(headers, file.readAll());

    //TreeModel treeModel(file.readAll());
    TreeModel *treeModel = new TreeModel(file.readAll());

    file.close();

    //ui->Explore_treeview_Directories->setModel(treeModel);
    ui->test_treeView->setModel(treeModel);
    //ui->test_treeView->show();
    //for (int column = 0; column < model->columnCount(); ++column)
        //view->resizeColumnToContents(column);

}

//Context menu
void MainWindow::on_TrV_FileList_customContextMenuRequested(const QPoint &pos)
{
    // for most widgets
    QPoint globalPos = ui->TrV_FileList->mapToGlobal(pos);

    QMenu fileContextMenu;

//            QAction *menuAction1 = new QAction(QIcon::fromTheme("document-open-data"),(tr("Open file")), this);
//            connect(menuAction1, &QAction::triggered, this, &MainWindow::contextOpenFile);
//            fileContextMenu.addAction(menuAction1);

//            QAction *menuAction2 = new QAction(QIcon::fromTheme("document-open-data"),(tr("Open folder")), this);
//            connect(menuAction2, &QAction::triggered, this, &MainWindow::contextOpenFolder);
//            fileContextMenu.addAction(menuAction2);

//            fileContextMenu.addSeparator();

    QAction *menuAction3 = new QAction(QIcon::fromTheme("edit-copy"),(tr("Copy absolute path")), this);
    connect( menuAction3,&QAction::triggered, this, &MainWindow::context2CopyAbsolutePath);
    fileContextMenu.addAction(menuAction3);

//            QAction *menuAction4 = new QAction(QIcon::fromTheme("edit-copy"),(tr("Copy file name with extension")), this);
//            connect( menuAction4,&QAction::triggered, this, &MainWindow::contextCopyFileNameWithExtension);
//            fileContextMenu.addAction(menuAction4);

//            QAction *menuAction5 = new QAction(QIcon::fromTheme("edit-copy"),(tr("Copy file name without extension")), this);
//            connect( menuAction5,&QAction::triggered, this, &MainWindow::contextCopyFileNameWithoutExtension);
//            fileContextMenu.addAction(menuAction5);

    //fileContextMenu.addSeparator();

    // TEST:  copy file to..., cut file, move file to..., trash, delete, the full Dolphin menu!
    //QAction *menuAction30 = new QAction(QIcon::fromTheme("edit-copy"),(tr("TEST")), this);
    //fileContextMenu.addAction(menuAction30);

    QAction* selectedItem = fileContextMenu.exec(globalPos);
    if (selectedItem)
    {
        //something
    }
    else
    {
        //KMessageBox::information(this,"test:\n did nothing.");
    }
}
//----------------------------------------------------------------------

void MainWindow::context2CopyAbsolutePath()
{
    QModelIndex index=ui->TrV_FileList->currentIndex();
    QString selectedFileName   = ui->TrV_FileList->model()->index(index.row(), 0, QModelIndex()).data().toString();
    QString selectedFileFolder = ui->TrV_FileList->model()->index(index.row(), 3, QModelIndex()).data().toString();
    QString selectedFileAbsolutePath = selectedFileFolder+"/"+selectedFileName;
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString originalText = clipboard->text();
    clipboard->setText(selectedFileAbsolutePath);
}
//----------------------------------------------------------------------
