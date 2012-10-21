/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Роман Браун <firdragon76@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef CARDSVGITEM_H
#define CARDSVGITEM_H

#include <QtSvg/QGraphicsSvgItem>
#include <QtGui/QGraphicsSceneEvent>

class CardSvgItem : public QGraphicsSvgItem
{
	Q_OBJECT
public:
    CardSvgItem(QGraphicsItem* parentItem = 0);
    virtual ~CardSvgItem();
	
	void setSuit(quint32 suit);
	void setRank(quint32 rank);
	void setOpen(bool opened);
	void setAccessible(bool accessible);
	void setLiteral(const QString &literal);
	
	QPointF getLastPos() const;
	quint32 getSuit() const;
	quint32 getRank() const;
	bool getOpen() const;
	qint32 getOldZ() const;
	
protected:
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	
private:
	QPointF lastPos;
	quint32 suit; // масть 1 - 
	quint32 rank; // ранг 1 - 13
	bool open; // true - открыта, false - закрыта
	QString literal;
	qint32 oldZ;
	bool accessible;
};

#endif // CARDSVGITEM_H
