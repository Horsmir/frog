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


#include "pile.h"

Pile::Pile(QObject *parent) : QObject(parent)
{
	opened = false;
}

Pile::Pile(const Pile& other) : QObject(other.parent())
{
	cards = other.cards;
	zone = other.zone;
	opened = other.opened;
	baseRect = other.baseRect;
}

Pile::~Pile()
{
	
}

Pile& Pile::operator=(const Pile& other)
{
	zone = other.zone;
	opened = other.opened;
	cards = other.cards;
	baseRect = other.baseRect;
	return *this;
}

bool Pile::addCard(CardSvgItem* card)
{
	cards.append(card);
	return true;
}

CardSvgItem *Pile::lastCard() const
{
	if(cards.isEmpty())
		return 0;
	return cards.last();
}

void Pile::setZone(qreal lx, qreal ly, qreal rx, qreal ty)
{
	zone.setRect(lx, ly, rx, ty);
}

void Pile::setBaseRect(QPen &pen, QBrush &brush, QGraphicsScene *scene)
{
	baseRect = scene->addRect(zone, pen, brush);
}

void Pile::setOpened(bool opened)
{
	this->opened = opened;
}

CardSvgItem *Pile::getCard(qint32 index) const
{
	Q_ASSERT(index >= 0 && index < cards.count());
	return cards.at(index);
}

CardSvgItem *Pile::getCard(quint32 suit, quint32 rank) const
{
	for(int i = 0; i < cards.count(); i++)
	{
		if((cards.at(i)->getSuit() == suit) && (cards.at(i)->getRank() == rank))
			return getCard(i);
	}
	return 0;
}

QRectF Pile::getZone() const
{
	return zone;
}

qint32 Pile::getCardIndex(CardSvgItem *card) const
{
	return cards.indexOf(card);
}

bool Pile::isOpened() const
{
	return opened;
}

void Pile::removeCard(qint32 index)
{
	Q_ASSERT(index >= 0 && index < cards.count());
	cards.removeAt(index);
}

void Pile::removeCard(quint32 suit, quint32 rank)
{
	for(int i = 0; i < cards.count(); i++)
	{
		if((cards.at(i)->getSuit() == suit) && (cards.at(i)->getRank() == rank))
		{
			removeCard(i);
			break;
		}
	}
}

void Pile::clear()
{
	opened = false;
	cards.clear();
}

qint32 Pile::count() const
{
	return cards.count();
}

//==================================================================================================================//


#include "pile.moc"