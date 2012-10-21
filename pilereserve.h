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


#ifndef PILERESERVE_H
#define PILERESERVE_H

#include "pile.h"


class PileReserve : public Pile
{
	Q_OBJECT
public:
    PileReserve(QObject* parent = 0);
    virtual ~PileReserve();
	
	virtual bool addCard(CardSvgItem* card);
	virtual void removeCard(qint32 index);
	virtual void removeCard(quint32 suit, quint32 rank);
	
};

#endif // PILERESERVE_H
