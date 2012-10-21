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


#ifndef PILE_H
#define PILE_H

#include <QtCore/QObject>
#include <QtGui/QGraphicsScene>
#include "cardsvgitem.h"

class Pile : public QObject
{
	Q_OBJECT
public:
    Pile(QObject *parent = 0);
    Pile(const Pile& other);
    virtual ~Pile();
    virtual Pile& operator=(const Pile& other);
	
	virtual bool addCard(CardSvgItem* card);
	CardSvgItem *lastCard() const;
	void setZone(qreal lx, qreal ly, qreal rx, qreal ty);
	void setBaseRect(QPen &pen, QBrush &brush, QGraphicsScene *scene);
	void setOpened(bool opened);
	
	CardSvgItem *getCard(qint32 index) const;
	CardSvgItem *getCard(quint32 suit, quint32 rank) const;
	   QRectF getZone() const;
	qint32 getCardIndex(CardSvgItem *card) const;
	bool isOpened() const;
	
	virtual void removeCard(qint32 index);
	virtual void removeCard(quint32 suit, quint32 rank);
	void clear();
	
	qint32 count() const;
	
protected:
	QList<CardSvgItem*> cards;
	QRectF zone;
	QGraphicsRectItem *baseRect; // прямоугольник отмечающий куда класть карты
	bool opened; // true - можно ложить карту, false - нельзя ложить карту
};

#endif // PILE_H
