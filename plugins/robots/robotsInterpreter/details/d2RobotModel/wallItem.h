#pragma once

#include <QtWidgets/QGraphicsItem>
#include <QtGui/QPainter>
#include <QtXml/QDomDocument>

#include "lineItem.h"

namespace qReal {
namespace interpreters {
namespace robots {
namespace details {
namespace d2Model {

class WallItem : public LineItem
{
	Q_OBJECT

public:
	WallItem(QPointF const &begin, QPointF const &end);
	QPointF begin();
	QPointF end();
	bool isDragged() const;
	bool isCircle() const;
	qreal width() const;

	/// Draws selection rect around sensorBoundingBox
	virtual void drawExtractionForItem(QPainter *painter);
	virtual void drawItem(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

	virtual QDomElement serialize(QDomDocument &document, QPoint const &topLeftPicture);
	virtual void deserializePenBrush(QDomElement const &element);

	void onOverlappedWithRobot(bool overlapped = true);

	QPointF center() const;
	QLineF line(int i) const;
	QPointF point(int i) const;

	QPainterPath mWallPath;

	void setLines();
	void setWallPath();

signals:
	void wallDragged(WallItem *item, QPainterPath const &shape, QPointF const& oldPos);

protected:
	virtual void setPrivateData();

private:
	bool mDragged;
	bool mOverlappedWithRobot;
	QImage mImage;

	bool mIsCircle;

	QPointF mPoints[4];
	QPointF mCenter;

	int mOldX1;
	int mOldY1;

	QList<QLineF> mLines;
};

}
}
}
}
}
