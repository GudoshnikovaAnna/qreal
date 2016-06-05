# Copyright 2007-2015 QReal Research Group
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

include(../../global.pri)

QT += xml widgets

#QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH += \
        $$PWD/../.. \
        $$PWD/../../qrgui/ \

DESTDIR = $$DESTDIR/plugins/tools/

links(qrkernel qrutils qrmc)

HEADERS += \
    cshgenerator.h


SOURCES += \
    cshgenerator.cpp
	#javagenerator.cpp


#FORMS += \
#	compilerPage.ui \

DISTFILES += \
    GamePage.xaml.template \
	Mediator.cs.template \
	Editor.java.template \
    Editor/copy.JPG \
    Editor/cut.JPG \
    Editor/new.JPG \
    Editor/open.JPG \
    Editor/paste.JPG \
    Editor/save.JPG \
    Editor/fontSelector.java \
    Joystick/StoreManifest.xml \
    Joystick/AccelerometerPage.xaml \
    Joystick/App.xaml \
    Joystick/GamepadSemester.csproj \
    Joystick/GamepadSemester.csproj.user \
    Joystick/Package.appxmanifest \
    Joystick/SettingsPage.xaml \
    Joystick/AccelerometerPage.xaml.cs \
    Joystick/App.xaml.cs \
    Joystick/Exceptions.cs \
    Joystick/GamepadPage.xaml.cs \
    Joystick/RecordMaker.cs \
    Joystick/SettingsPage.xaml.cs \
    Joystick/SocketClient.cs

