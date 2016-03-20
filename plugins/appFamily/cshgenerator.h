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

private:
	QAction mCshGenerateAction;

	qReal::gui::MainWindowInterpretersInterface *mMainWindowInterface;  // Does not have ownership

	qrRepo::LogicalRepoApi *mLogicalRepoApi;  // Does not have ownership

};

}
