/* Copyright 2007-2015 QReal Research Group
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

#pragma once

#include <qrgui/plugins/toolPluginInterface/toolPluginInterface.h>
#include <qrgui/plugins/toolPluginInterface/pluginConfigurator.h>

//#include "compilerPage.h"
#include <QtCore/QDir>
#include "../qrrepo/repoApi.h"

namespace cshGenerator {

/// Main plugin class for metaeditor support code. Provides generation of editor
/// by metamodel specified in .xml file or in QReal save file, compilation of
/// generated editor and loading it to QReal, and parsing of existing .xml metamodel.
class CshGenerator : public QObject, public qReal::ToolPluginInterface
{
	Q_OBJECT
	Q_INTERFACES(qReal::ToolPluginInterface)
	Q_PLUGIN_METADATA(IID "appFamily.CshGenerator")

public:
	CshGenerator();
	virtual ~CshGenerator();

    virtual void init(const qReal::PluginConfigurator &configurator);
	virtual QList<qReal::ActionInfo> actions();

private slots:
    void cshGenerateAction();
	void javaGenerateAction();

private:
	QAction mCshGenerateAction;
	QAction mJavaGenerateAction;
	QString mLocalDir;
	QDir mDirectory;
	const QString substr = "@@";
	const QString gamePageTemplate = "GamePage.xaml.template";
	const QString SettingPageTemplate = "SettingPage.xaml.template";
	const QString mediatorTemplate = "Mediator.cs.template";
	const QString dPad2Tag = "@@<Image x:Name=\"dPad2\" HorizontalAlignment=\"Left\" Height=\"130\" VerticalAlignment=\"Top\" Width=\"130\" Source=\"Assets/dPad.png\" PointerPressed=\"dPadPressed\" Grid.Column=\"1\" Margin=\"335.167,69,0,0\" PointerReleased=\"dPadReleased\"/>@@";
	const QString buttonTag = "@@0@@";


	QString mGamePageTemplate;
	QString mMediatorTemplate;
	QString mSettingPageTemplate;
	QString PadQuantity;
	QString ButtonQuantity;
	qReal::gui::MainWindowInterpretersInterface *mMainWindowInterface;  // Does not have ownership

	qrRepo::LogicalRepoApi *mLogicalRepoApi;  // Does not have ownership


	const QString substr2 = "@";
	const QString editorTemplate = "Editor.java.template";
	const QString menuEditTag = "@JMenu menu = new JMenu(\"Edit\");@";
	const QString menuItemCopyTag = "@JMenuItem menuItem = new JMenuItem(\"copy\");@";
	const QString menucutTag = "@JMenuItem menucut = new JMenuItem(\"cut\");@";
	const QString menupasteTag = "@JMenuItem menupaste = new JMenuItem(\"paste\");@";

	const QString formatMenuTag = "@JMenu format = new JMenu(\"Format\");@";


	const QString openFileTag = "@file.add(openfile);@";
	const QString saveFileTag = "@file.add(savefile);@";
	const QString saveAsFileTag = "@file.add(saveasfile);@";

	const QString undoEditTag = "@edit.add(undoAction);@";
	const QString redoEditTag = "@edit.add(redoAction);@";
	const QString cutEditTag = "@edit.add(cut);@";
	const QString copyEditTag = "@edit.add(copy);@";
	const QString pasteEditTag = "@edit.add(paste);@";
	const QString separatorEditTag = "@edit.addSeparator();@";
	const QString findEditTag = "@edit.add(find);@";
	const QString findNextEditTag = "@edit.add(findnext);@";
	const QString selectAllEditTag = "@edit.add(selectall);@";

	const QString formatWordTag = "@format.add(word_format);@";
	const QString selectFormatWordTag = "@word_format.setSelected(true);@";
	const QString fontFormatTag = "@format.add(font);@";

	const QString menuBarFormatTag = "@menuBar.add(format);@";

	const QString popupUndoTag = "@popmenu.add(undoAction);@";
	const QString popupRedoTag = "@popmenu.add(redoAction);popmenu.addSeparator();@";
	const QString popupCopyTag = "@popmenu.add(menuItem);@";
	const QString popupCutTag = "@popmenu.add(menucut);@";
	const QString popupPasteTag = "@popmenu.add(menupaste);@";

	const QString toolBarOpenTag = "@toolBar.add(openFileB);openFileB.setToolTipText(\"Open file\");@";
	const QString toolBarSaveTag = "@toolBar.add(saveFileB);saveFileB.setToolTipText(\"Save file\");toolBar.addSeparator();@";
	const QString toolBarCutTag = "@toolBar.add(cutFileB);cutFileB.setToolTipText(\"Cut\");@";
	const QString toolBarCopyTag = "@toolBar.add(copyFileB);copyFileB.setToolTipText(\"Copy\");@";
	const QString toolBarPasteTag = "@toolBar.add(pasteFileB);pasteFileB.setToolTipText(\"Paste\");@";


	QString mEditorTemplate;
	QString openButton;
	QString saveButton;
	QString cutCopyPasteButton;
	QString popupUndo;
	QString popupRedo;
	QString popupCopyCutPaste;

	bool openFile;
	bool cutcopypaste;
	bool wordWrap;
	bool font;
	bool saveFile;
	bool undo;
	bool redo;
	bool find;
	bool findNext;
	bool selectAll;

	bool changeDir(const QString &path);
	bool loadTemplateFromFile(const QString &templateFileName, QString &loadedTemplate);
	void generateCodeForPads(int &padQuant);
	void generateCodeForButtons(QString &buttonQuant);
	void generateEditorCode(QString &openButtonS, QString &saveButtonS
										   , QString &cutCopyPasteButtonS
										   , QString &popupCopyCutPasteS
										   , QString &popupUndoS
										   , QString &popupRedoS);
};

}
