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

#include "drawLineBlockGenerator.h"

using namespace nxt::simple;

DrawLineBlockGenerator::DrawLineBlockGenerator(const qrRepo::RepoApi &repo
		, generatorBase::GeneratorCustomizer &customizer
		, const qReal::Id &id
		, QObject *parent)
	: DrawBlockGenerator(repo, customizer, id, parent)
{
}

void DrawLineBlockGenerator::drawBmp(QPainter *painter)
{
	const int x1 = mRepo.property(mId, "X1CoordinateLine").toInt();
	const int y1 = mRepo.property(mId, "Y1CoordinateLine").toInt();
	const int x2 = mRepo.property(mId, "X2CoordinateLine").toInt();
	const int y2 = mRepo.property(mId, "Y2CoordinateLine").toInt();

	painter->drawLine(x1, y1, x2, y2);
}