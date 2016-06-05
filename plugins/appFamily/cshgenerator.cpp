/* Copyright 2016 Gudoshnikova Anna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "cshgenerator.h"

#include <QtCore/QProcess>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QDesktopWidget>

#include <qrkernel/settingsManager.h>
#include <qrmc/metaCompiler.h>

using namespace qReal;
using namespace cshGenerator;

CshGenerator::CshGenerator()
		: mCshGenerateAction(nullptr), mJavaGenerateAction(nullptr)
{
}

CshGenerator::~CshGenerator()
{
}

void CshGenerator::init(const PluginConfigurator &configurator)
{
	mMainWindowInterface = &configurator.mainWindowInterpretersInterface();
	mLogicalRepoApi = &configurator.logicalModelApi().mutableLogicalRepoApi();
}

QList<ActionInfo> CshGenerator::actions()
{
	mCshGenerateAction.setText(tr("Generate code c#"));
	mJavaGenerateAction.setText(tr("Generate code Java"));
	ActionInfo cshGenerateActionInfo(&mCshGenerateAction, "generators", "tools");
	ActionInfo javaGenerateActionInfo(&mJavaGenerateAction, "generators", "tools");
	QObject::connect(&mCshGenerateAction, &QAction::triggered, this, &CshGenerator::cshGenerateAction);
	QObject::connect(&mJavaGenerateAction, &QAction::triggered, this, &CshGenerator::javaGenerateAction);
	return {cshGenerateActionInfo, javaGenerateActionInfo};
}

void CshGenerator::cshGenerateAction()
{
    QFile testFile("test.txt");
    if (testFile.open(QIODevice::WriteOnly)) {
        QTextStream stream(&testFile);
        IdList const metamodels = mLogicalRepoApi->children(Id::rootId());
        for (const Id &key : metamodels) {
			if (!mLogicalRepoApi->isLogicalElement(key)) {
                continue;
            }
			if (mLogicalRepoApi->name(key) == "Pads" ){
				PadQuantity = mLogicalRepoApi->stringProperty(key,"Quantity");
			}
			if (mLogicalRepoApi->name(key) == "Buttons" ){
				ButtonQuantity = mLogicalRepoApi->stringProperty(key,"Quantity");
			}
        }
		loadTemplateFromFile(gamePageTemplate,mGamePageTemplate);
		loadTemplateFromFile(mediatorTemplate,mMediatorTemplate);
		bool ok;
		int quantP = PadQuantity.toInt(&ok,10);
		mDirectory.mkdir("/plugins/appFamily/Joystick");
		generateCodeForPads(quantP);
		generateCodeForButtons(ButtonQuantity);
        testFile.close();
		QMessageBox::information(nullptr, QObject::tr("Генерация"), QObject::tr("Исходники сгенерировались"));
        if (stream.status() != QTextStream::Ok) {
            qDebug() << "File writing erorr";
        }
    }
}

void CshGenerator::javaGenerateAction(){
	openFile = false;
	cutcopypaste = false;
	wordWrap = false;
	font = false;
	saveFile = false;
	undo = false;
	redo = false;
	find = false;
	findNext = false;
	selectAll = false;

	QFile testFile("test2.txt");
	if (testFile.open(QIODevice::WriteOnly)) {
		QTextStream stream(&testFile);
		IdList const metamodels = mLogicalRepoApi->children(Id::rootId());
		for (const Id &key : metamodels) {
			if (!mLogicalRepoApi->isLogicalElement(key)) {
				continue;
			}
			if (mLogicalRepoApi->name(key) == "OpenFile" ){
				openButton = mLogicalRepoApi->stringProperty(key,"Button");
				openFile = true;
			}
			if (mLogicalRepoApi->name(key) == "SaveFile" ){
				saveButton = mLogicalRepoApi->stringProperty(key,"Button");
				saveFile = true;
			}
			if (mLogicalRepoApi->name(key) == "CutCopyPaste") {
				cutCopyPasteButton = mLogicalRepoApi->stringProperty(key,"Button");
				popupCopyCutPaste = mLogicalRepoApi->stringProperty(key,"PopupMenu");
				cutcopypaste = true;
			}
			if (mLogicalRepoApi->name(key) == "Undo") {
				popupUndo = mLogicalRepoApi->stringProperty(key,"PopupMenu");
				undo = true;
			}
			if (mLogicalRepoApi->name(key) == "Redo") {
				popupRedo = mLogicalRepoApi->stringProperty(key,"PopupMenu");
				redo = true;
			}
			if (mLogicalRepoApi->name(key) == "FindFirst") {
				find = true;
			}
			if (mLogicalRepoApi->name(key) == "FindNext") {
				findNext = true;
			}
			if (mLogicalRepoApi->name(key) == "Font") {font = true;}
			if (mLogicalRepoApi->name(key) == "WordWrap") {wordWrap = true;}
			if (mLogicalRepoApi->name(key) == "SelectAll") {selectAll = true;}
		}
		loadTemplateFromFile(editorTemplate,mEditorTemplate);
		qDebug() << openFile, saveFile;
		if (openFile == true) {
			mEditorTemplate.replace(openFileTag, openFileTag.mid(1,openFileTag.length()-2));
		}
		else {
			mEditorTemplate.replace(openFileTag, "");
		}

		if (saveFile == true) {
			mEditorTemplate.replace(saveFileTag, saveFileTag.mid(1,saveFileTag.length()-2));
			mEditorTemplate.replace(saveAsFileTag, saveAsFileTag.mid(1,saveAsFileTag.length()-2));
		}
		else {
			mEditorTemplate.replace(saveFileTag, "");
			mEditorTemplate.replace(saveAsFileTag,"");
		}

		if (cutcopypaste == true) {
			mEditorTemplate.replace(menuItemCopyTag, menuItemCopyTag.mid(1,menuItemCopyTag.length()-2));
			mEditorTemplate.replace(menucutTag, menucutTag.mid(1,menucutTag.length()-2));
			mEditorTemplate.replace(menupasteTag, menupasteTag.mid(1,menupasteTag.length()-2));
			mEditorTemplate.replace(cutEditTag, cutEditTag.mid(1,cutEditTag.length()-2));
			mEditorTemplate.replace(copyEditTag, copyEditTag.mid(1,copyEditTag.length()-2));
			mEditorTemplate.replace(pasteEditTag, pasteEditTag.mid(1,pasteEditTag.length()-2));
		}
		else {
			mEditorTemplate.replace(menuItemCopyTag, "");
			mEditorTemplate.replace(menucutTag, "");
			mEditorTemplate.replace(menupasteTag, "");
			mEditorTemplate.replace(cutEditTag, "");
			mEditorTemplate.replace(copyEditTag, "");
			mEditorTemplate.replace(pasteEditTag, "");
		}
		if (cutcopypaste == true || find == true || findNext == true || selectAll == true) {
			mEditorTemplate.replace(menuEditTag, menuEditTag.mid(1,menuEditTag.length()-2));
		}
		if (cutcopypaste == false && find == false && findNext == false && selectAll == false){
			mEditorTemplate.replace(menuEditTag, "");
		}
		if (undo == true) {
			mEditorTemplate.replace(undoEditTag, undoEditTag.mid(1,undoEditTag.length()-2));
		}
		else {
			mEditorTemplate.replace(undoEditTag, "");
		}
		if (redo == true) {
			mEditorTemplate.replace(redoEditTag, redoEditTag.mid(1,redoEditTag.length()-2));
		}
		else {
			mEditorTemplate.replace(redoEditTag, "");
		}
		if (find == true) {
			mEditorTemplate.replace(separatorEditTag, separatorEditTag.mid(1,separatorEditTag.length()-2));
			mEditorTemplate.replace(findEditTag, findEditTag.mid(1,findEditTag.length()-2));
		}
		else {
			mEditorTemplate.replace(separatorEditTag, "");
			mEditorTemplate.replace(findEditTag, "");
		}
		if (findNext == true) {
			mEditorTemplate.replace(separatorEditTag, separatorEditTag.mid(1,separatorEditTag.length()-2));
			mEditorTemplate.replace(findNextEditTag, findNextEditTag.mid(1,findNextEditTag.length()-2));
		}
		else {
			mEditorTemplate.replace(separatorEditTag, "");
			mEditorTemplate.replace(findNextEditTag, "");
		}
		if (selectAll == true) {
			mEditorTemplate.replace(selectAllEditTag, selectAllEditTag.mid(1,selectAllEditTag.length()-2));
		}
		else {
			mEditorTemplate.replace(selectAllEditTag, "");
		}
		if (wordWrap == true || font == true) {
			mEditorTemplate.replace(menuBarFormatTag, menuBarFormatTag.mid(1,menuBarFormatTag.length()-2));
		}
		if (wordWrap == true) {
			mEditorTemplate.replace(formatWordTag, formatWordTag.mid(1,formatWordTag.length()-2));
			mEditorTemplate.replace(selectFormatWordTag, selectFormatWordTag.mid(1,selectFormatWordTag.length()-2));
		}
		else {
			mEditorTemplate.replace(formatWordTag, "");
			mEditorTemplate.replace(selectFormatWordTag, "");
		}
		if (font == true) {
			mEditorTemplate.replace(fontFormatTag, fontFormatTag.mid(1,fontFormatTag.length()-2));
		}
		else {
			mEditorTemplate.replace(fontFormatTag, "");
		}
		if (font == true || wordWrap == true) {
			mEditorTemplate.replace(formatMenuTag, formatMenuTag.mid(1,formatMenuTag.length()-2));
			mEditorTemplate.replace(menuBarFormatTag, menuBarFormatTag.mid(1,menuBarFormatTag.length()-2));

		}
		if (font == false && wordWrap == false) {
			mEditorTemplate.replace(formatMenuTag, "");
			mEditorTemplate.replace(menuBarFormatTag, "");
		}
		generateEditorCode(openButton, saveButton, cutCopyPasteButton, popupCopyCutPaste,popupUndo,popupRedo);
		testFile.close();
		QMessageBox::information(nullptr, QObject::tr("Генерация"), QObject::tr("Исходники сгенерировались"));
		if (stream.status() != QTextStream::Ok) {
			qDebug() << "File writing erorr";
		}
	}
}

bool CshGenerator::changeDir(const QString &path)
{
	if (!mDirectory.exists(path)) {
		qDebug() << "cannot find directory " << path;
		return false;
	}
	mDirectory.cd(path);
	return true;
}

bool CshGenerator::loadTemplateFromFile(const QString &templateFileName, QString &loadedTemplate)
{
	//if (!changeDir(mLocalDir))
	//	return false;
	mDirectory.cdUp();
	mDirectory.cdUp();
	QString fileName = "C:/Users/Anna/Documents/Study/qreal/qreal/plugins/appFamily/" + templateFileName;
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "cannot load file \"" << fileName << "\"";
		return false;
	}
	QTextStream in(&file);
	loadedTemplate = in.readAll();
	file.close();
	return true;
}

void CshGenerator::generateCodeForPads(int &padQuant)
{
	qDebug() << "loaded templates: ";
	qDebug() << "===";
	if (padQuant == 1) {
		mGamePageTemplate.replace(dPad2Tag, "");
	}
	else {
		mGamePageTemplate.replace(substr, "");
	}
	QFile gamePageFile("GamePage.xaml");
	if (gamePageFile.open(QIODevice::WriteOnly)) {
		QTextStream stream(&gamePageFile);
		stream << mGamePageTemplate;
	}
	return;
}

void CshGenerator::generateCodeForButtons(QString &buttonQuant)
{
	mMediatorTemplate.replace(buttonTag, buttonQuant);
	QFile gamePageFile("Mediator.cs");
	if (gamePageFile.open(QIODevice::WriteOnly)) {
		QTextStream stream(&gamePageFile);
		stream << mMediatorTemplate;
	}
	return;
}

void CshGenerator::generateEditorCode(QString &openButtonS, QString &saveButtonS
									   , QString &cutCopyPasteButtonS
									   , QString &popupCopyCutPasteS
									   , QString &popupUndoS
									   , QString &popupRedoS)
{
	qDebug() << "loaded templates: ";
	qDebug() << "===";
	if (openButtonS == "True") {
		mEditorTemplate.replace(toolBarOpenTag, toolBarOpenTag.mid(1,toolBarOpenTag.length()-2));
	}
	else {
		mEditorTemplate.replace(toolBarOpenTag, "");
	}
	if (saveButtonS == "True") {
		mEditorTemplate.replace(toolBarSaveTag, toolBarSaveTag.mid(1,toolBarSaveTag.length()-2));
	}
	else {
		mEditorTemplate.replace(toolBarSaveTag, "");
	}
	if (cutCopyPasteButtonS == "True") {
		mEditorTemplate.replace(toolBarCopyTag, toolBarCopyTag.mid(1,toolBarCopyTag.length()-2));
		mEditorTemplate.replace(toolBarCutTag, toolBarCutTag.mid(1,toolBarCutTag.length()-2));
		mEditorTemplate.replace(toolBarPasteTag, toolBarPasteTag.mid(1,toolBarPasteTag.length()-2));
	}
	else {
		mEditorTemplate.replace(toolBarCutTag, "");
		mEditorTemplate.replace(toolBarCopyTag, "");
		mEditorTemplate.replace(toolBarPasteTag, "");
	}
	if (popupCopyCutPasteS == "True") {
		mEditorTemplate.replace(popupCopyTag, popupCopyTag.mid(1,popupCopyTag.length()-2));
		mEditorTemplate.replace(popupCutTag, popupCutTag.mid(1,popupCutTag.length()-2));
		mEditorTemplate.replace(popupPasteTag, popupPasteTag.mid(1,popupPasteTag.length()-2));
	}
	else {
		mEditorTemplate.replace(popupCopyTag, "");
		mEditorTemplate.replace(popupCutTag, "");
		mEditorTemplate.replace(popupPasteTag, "");
	}
	if (popupUndoS == "True") {
		mEditorTemplate.replace(popupUndoTag, popupUndoTag.mid(1,popupUndoTag.length()-2));
	}
	else {
		mEditorTemplate.replace(popupUndoTag, "");
	}
	if (popupRedoS == "True") {
		mEditorTemplate.replace(popupRedoTag, popupRedoTag.mid(1,popupRedoTag.length()-2));
	}
	else {
		mEditorTemplate.replace(popupRedoTag, "");
	}

	QFile editorFile("Editor.java");
	if (editorFile.open(QIODevice::WriteOnly)) {
		QTextStream stream(&editorFile);
		stream << mEditorTemplate;
	}
	return;
}

