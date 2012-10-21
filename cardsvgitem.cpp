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


#include "cardsvgitem.h"

CardSvgItem::CardSvgItem(QGraphicsItem* parentItem) : QGraphicsSvgItem(parentItem)
{
	lastPos = scenePos();
	suit = 0;
	rank = 0;
	open = false;
	setAccessible(false);
	literal = "";
	oldZ = 0;
}

CardSvgItem::~CardSvgItem()
{
	
}

QPointF CardSvgItem::getLastPos() const
{
	return lastPos;
}

void CardSvgItem::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	lastPos = scenePos();
	if(accessible)
	{
		oldZ = zValue();
		setZValue(100);
	}
	QGraphicsItem::mousePressEvent(event);
}

bool CardSvgItem::getOpen() const
{
	return open;
}

quint32 CardSvgItem::getRank() const
{
	return rank;
}

quint32 CardSvgItem::getSuit() const
{
	return suit;
}

void CardSvgItem::setAccessible(bool accessible)
{
	this->accessible = accessible;
	setFlag(QGraphicsItem::ItemIsMovable, this->accessible);
}

void CardSvgItem::setOpen(bool opened)
{
	this->open = opened;
	if(opened)
		setElementId(literal.toLatin1());
	else
		setElementId(QLatin1String("back"));
}

void CardSvgItem::setRank(quint32 rank)
{
	this->rank = rank;
}

void CardSvgItem::setSuit(quint32 suit)
{
	this->suit = suit;
}

void CardSvgItem::setLiteral(const QString& literal)
{
	this->literal = literal;
	setElementId(this->literal.toLatin1());
}

qint32 CardSvgItem::getOldZ() const
{
	return oldZ;
}

#include "cardsvgitem.moc"