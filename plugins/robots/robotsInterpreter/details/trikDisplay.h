#pragma once

#include <QtWidgets/QLabel>

#include <qrutils/graphicsUtils/painterInterface.h>
#include <qrutils/graphicsUtils/paintWidget.h>

namespace Ui {
class TrikDisplay;
}

namespace qReal {
namespace interpreters {
namespace robots {
namespace details {

class TrikDisplay : public QLabel
{
	Q_OBJECT
	
public:
	explicit TrikDisplay(QWidget *parent = 0);
	~TrikDisplay();

	virtual void setPainter(graphicsUtils::PainterInterface *painter);
	QSize displaySize() const;

	void repaintDisplay();

private:
	Ui::TrikDisplay *mUi;
};

}
}
}
}
