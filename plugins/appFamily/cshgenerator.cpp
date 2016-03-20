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
		: mCshGenerateAction(nullptr)
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
	ActionInfo cshGenerateActionInfo(&mCshGenerateAction, "generators", "tools");
    QObject::connect(&mCshGenerateAction, &QAction::triggered, this, &CshGenerator::cshGenerateAction);
    return {cshGenerateActionInfo};
}

void CshGenerator::cshGenerateAction()
{
    QMessageBox::information(nullptr, QObject::tr("olo"), QObject::tr("olol2"));
}
