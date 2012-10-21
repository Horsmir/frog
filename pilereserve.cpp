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


#include "pilereserve.h"

PileReserve::PileReserve(QObject* parent): Pile(parent)
{
	opened = true;
}

PileReserve::~PileReserve()
{
	
}

bool PileReserve::addCard(CardSvgItem* card)
{
	Q_ASSERT(card != 0);
	
	card->setPos(zone.x(), zone.y());
	card->setOpen(true);
	card->setAccessible(true);
	
	if(cards.count() > 0)
	{
		card->setZValue(cards.last()->zValue() + 1);
		cards.last()->setAccessible(false);
	}
	else
	{
		card->setZValue(1);
	}
	
	return Pile::addCard(card);
}

void PileReserve::removeCard(qint32 index)
{
	Q_ASSERT(index >= 0 && index < cards.count());
	
	Pile::removeCard(index);
	if(cards.count() > 0)
		cards.last()->setAccessible(true);
}

void PileReserve::removeCard(quint32 suit, quint32 rank)
{
    Pile::removeCard(suit, rank);
	if(cards.count() > 0)
		cards.last()->setAccessible(true);
}

#include "pilereserve.moc"