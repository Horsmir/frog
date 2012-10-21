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


#include "pilefault.h"

PileFault::PileFault(QObject* parent): Pile(parent)
{
	opened = true;
}

PileFault::~PileFault()
{

}

bool PileFault::addCard(CardSvgItem* card)
{
	if(!card)
		return false;
	
	card->setPos(zone.x(), zone.y());
	if(cards.count() > 0)
	{
		cards.last()->setAccessible(false);
		card->setAccessible(true);
		card->setZValue(cards.last()->zValue() + 1);
	}
	else
	{
		card->setAccessible(true);
		card->setZValue(1);
	}
	
	return Pile::addCard(card);
}

void PileFault::removeCard(qint32 index)
{
    Pile::removeCard(index);
	if(cards.count() > 0)
		cards.last()->setAccessible(true);
}

void PileFault::removeCard(quint32 suit, quint32 rank)
{
    Pile::removeCard(suit, rank);
	if(cards.count() > 0)
		cards.last()->setAccessible(true);
}

#include "pilefault.moc"