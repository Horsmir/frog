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


#include "pilepack.h"

PilePack::PilePack(QObject* parent): Pile(parent)
{

}

PilePack::~PilePack()
{

}

bool PilePack::addCard(CardSvgItem* card)
{
	Q_ASSERT(card != 0);
	
	card->setPos(zone.x(), zone.y());
	card->setOpen(false);
	card->setAccessible(false);
	if(cards.count() > 0)
	{
		card->setZValue(cards.last()->zValue() + 1);
	}
	else
	{
		card->setZValue(1);
	}
	
	return Pile::addCard(card);
}

#include "pilepack.moc"