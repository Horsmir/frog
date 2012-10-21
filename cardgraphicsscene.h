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


#ifndef CARDGRAPHICSSCENE_H
#define CARDGRAPHICSSCENE_H

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsSceneEvent>
#include "cardsvgitem.h"


class CardGraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:
    CardGraphicsScene(QObject* parent = 0);
    virtual ~CardGraphicsScene();
	
protected:
	virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *mouseEvent);
	
signals:
	void cardDroped(QPointF point, CardSvgItem *card);
};

#endif // CARDGRAPHICSSCENE_H
