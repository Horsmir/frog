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


#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QTime>
#include <QtSvg/QSvgRenderer>
#include "pilebase.h"
#include "pilefault.h"
#include "pilepack.h"
#include "pilereserve.h"
#include "cardgraphicsscene.h"

const quint32 NUM_SWAPS = 1000; // количесто итераций при перемешивании карт
const quint32 NUM_PILES_BASE = 8; // количество базовых стопок карт 
const quint32 NUM_PILES_FAULT = 5; // количество стопок сброса карт 

class GameManager : public QObject
{
	Q_OBJECT
public:
    explicit GameManager(QObject* parent = 0);
    virtual ~GameManager();
	
	void setScale(qreal scale);
	void setRender(QSvgRenderer *render);
	void setSizeScene(qreal w, qreal h);
	
	qreal getScale() const;
	CardGraphicsScene *getScene();
	
	void initCards(); // создание карточной колоды
	void newCards(); // новый расклад
	
public slots:
	void moveCard(QPointF point, CardSvgItem* card);
	void endGame();
	
private:
	QList<CardSvgItem*> cardsImgs;
	qreal scale;
	QSvgRenderer *render;
	QList<PileBase> basePiles;
	QList<PileFault> faultPiles;
	PilePack *pack; // колода
	PileReserve *reserve; // резерв
	PileReserve *activeReserve; // активный резерв	
	CardGraphicsScene *scene;
	quint32 end;
	
	void shuflleCards(QStringList &cardNames); // премешивание идентификаторов карт
	void setCards(const QStringList &cardNames); // создание стопок карт
	void setActiveReserveCard(CardSvgItem *card);
	bool setBaseCard(const QPointF &point, CardSvgItem *card);
	bool setFaultCard(const QPointF &point, CardSvgItem *card);
};

#endif // GAMEMANAGER_H
