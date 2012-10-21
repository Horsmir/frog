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


#ifndef PILEBASE_H
#define PILEBASE_H

#include "pile.h"


class PileBase : public Pile
{
	Q_OBJECT
public:
    PileBase(QObject* parent = 0);
    PileBase(const PileBase& other);
    virtual ~PileBase();
	
	virtual bool addCard(CardSvgItem* card);
	
	quint32 getBaseRank() const;
	quint32 getBaseSuit() const;
	
	PileBase &operator=(const PileBase& other);
	
signals:
	void fullPileBase();
	
private:
	quint32 baseRank; // ранг карты которую можно положить в стопку
	quint32 baseSuit; // масть стопки
};

#endif // PILEBASE_H
