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


#include "pilebase.h"

PileBase::PileBase(QObject* parent): Pile(parent)
{
	opened = true;
	baseRank = 1; // туз
	baseSuit = 0;
}

PileBase::PileBase(const PileBase& other): Pile(other)
{
	baseRank = other.baseRank;
	baseSuit = other.baseSuit;
}


PileBase::~PileBase()
{
	
}

bool PileBase::addCard(CardSvgItem* card)
{
	if(!card)
		return false;
	if(!opened)
	{
		card->setPos(card->getLastPos());
		return false;
	}
	
	if(card->getRank() == baseRank)
	{
		if(cards.count() > 0)
		{
			card->setPos(zone.x(), zone.y());
			card->setAccessible(false);
			card->setZValue(cards.last()->zValue() + 1);
			baseRank++;
			if(baseRank >= 14)
				emit fullPileBase();
			return Pile::addCard(card);
		}
		else
		{
			card->setPos(zone.x(), zone.y());
			card->setAccessible(false);
			card->setZValue(1);
			baseRank++;
			baseSuit = card->getSuit();
			return Pile::addCard(card);
		}
	}
	card->setPos(card->getLastPos());
	return false;
}

quint32 PileBase::getBaseRank() const
{
	return baseRank;
}

quint32 PileBase::getBaseSuit() const
{
	return baseSuit;
}

PileBase& PileBase::operator=(const PileBase& other)
{
	if(&other == this)
		return *this;
	baseRank = other.baseRank;
	baseSuit = other.baseSuit;
	Pile::operator=(other);
	return *this;
}

#include "pilebase.moc"