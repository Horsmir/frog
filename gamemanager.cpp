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


#include "gamemanager.h"

GameManager::GameManager(QObject* parent) : QObject(parent), scale(1)
{
	scene = new CardGraphicsScene(this);
	pack = new PilePack(this);
	reserve = new PileReserve(this);
	activeReserve = new PileReserve(this);
	end = 0;
	
	connect(scene, SIGNAL(cardDroped(QPointF,CardSvgItem*)), SLOT(moveCard(QPointF,CardSvgItem*)));
}

GameManager::~GameManager()
{
}

void GameManager::initCards()
{
	QStringList cardsNames, c1, c2;
	int i = 0, j = 0, k = 0;
	
	c1 << "king" << "queen" << "jack";
	c2 << "club" << "diamond" << "heart" << "spade"; 
	
	for(i = 0; i < c2.count(); i++)
	{
		for(j = 0; j < c1.count(); j++)
			cardsNames << c1.at(j) + "_" + c2.at(i);
		for(k = 1; k <= 10; k++)
			cardsNames << QString().setNum(k) + "_" + c2.at(i);
	}
	cardsNames += cardsNames;
	
	shuflleCards(cardsNames);
	setCards(cardsNames);
	
	connect(&(basePiles.at(0)) , SIGNAL(fullPileBase()), SLOT(endGame()));
	connect(&(basePiles.at(1)) , SIGNAL(fullPileBase()), SLOT(endGame()));
	connect(&(basePiles.at(2)) , SIGNAL(fullPileBase()), SLOT(endGame()));
	connect(&(basePiles.at(3)) , SIGNAL(fullPileBase()), SLOT(endGame()));
	connect(&(basePiles.at(4)) , SIGNAL(fullPileBase()), SLOT(endGame()));
	connect(&(basePiles.at(5)) , SIGNAL(fullPileBase()), SLOT(endGame()));
	connect(&(basePiles.at(6)) , SIGNAL(fullPileBase()), SLOT(endGame()));
	connect(&(basePiles.at(7)) , SIGNAL(fullPileBase()), SLOT(endGame()));
}

void GameManager::shuflleCards(QStringList& cardNames)
{
	int swapIndex1, swapIndex2, listSize = cardNames.count();
	qsrand(QTime::currentTime().msec());
	
	for(int i = 0; i < NUM_SWAPS; i++)
	{
		swapIndex1 = qrand() % listSize;
		swapIndex2 = qrand() % listSize;
		
		if (swapIndex1 == swapIndex2)
			i--;
		else
			cardNames.swap(swapIndex1, swapIndex2);
	}
}

void GameManager::setCards(const QStringList& cardNames)
{
	qint32 i = 0, j = 0;
	QStringList c2;
	c2 << "club" << "diamond" << "heart" << "spade";
	
	for(i = 0; i < cardNames.count(); i++)
	{
		QString cardName = cardNames.at(i);
		cardsImgs << new CardSvgItem();
		cardsImgs[i]->setSharedRenderer(render);
		cardsImgs[i]->setElementId(cardName.toLatin1());
		cardsImgs[i]->setLiteral(cardName);
		
		quint32 rank, suit;
		QStringList rankSuit = cardName.split("_");
		if(rankSuit.at(0) == "jack")
			rank = 11;
		else if(rankSuit.at(0) == "queen")
			rank = 12;
		else if(rankSuit.at(0) == "king")
			rank = 13;
		else
			rank = rankSuit.at(0).toUInt();
		if(rankSuit.at(1) == "club")
			suit = 1;
		if(rankSuit.at(1) == "diamond")
			suit  = 2;
		if(rankSuit.at(1) == "heart")
			suit = 3;
		if(rankSuit.at(1) == "spade")
			suit = 4;
		
		cardsImgs[i]->setRank(rank);
		cardsImgs[i]->setSuit(suit);
	}
	QRectF rc = cardsImgs.at(0)->boundingRect();
	qreal a = (scene->width() - 10.0) / 9;
	qreal b = a - 10.0;
	scale = b / rc.width();
	for(i = 0; i < cardsImgs.count(); i++)
		cardsImgs[i]->setScale(scale);
	
	QPen startPen(QColor(128, 128, 128));
	QBrush startBrush(QColor(128, 128, 128), Qt::DiagCrossPattern);
	
	reserve->setZone((scene->width() / 2) * (-1) + 10, (scene->height() / 2) * (-1) + 10, b, rc.height() * scale);
	reserve->setBaseRect(startPen, startBrush, scene);
	QList<quint32> numAces;
	for(i = 0; i < 13; i++)
	{
		if(cardsImgs[i]->getRank() == 1)
		{
			numAces << i;
			continue;
		}
		reserve->addCard(cardsImgs[i]);
	}
	
	for(i = 0; i < NUM_PILES_BASE; i++)
	{
		PileBase p;
		p.setZone((scene->width() / 2) * (-1) + 10 + (i + 1) * a, (scene->height() / 2) * (-1) + 10, b, rc.height() * scale);
		p.setBaseRect(startPen, startBrush, scene);
		basePiles.append(p);
	}
	if(numAces.count() > 0)
	{
		for(i = 0; i < numAces.count(); i++)
			basePiles[i].addCard(cardsImgs[numAces.at(i)]);
	}
	else
	{
		for(i = 13; i < cardsImgs.count(); i++)
		{
			if(cardsImgs.at(i)->getRank() == 1)
			{
				basePiles[0].addCard(cardsImgs[i]);
				numAces << i;
				break;
			}
		}
	}
	
	pack->setZone((scene->width() / 2) * (-1) + 10, (scene->height() / 2) - 10 - rc.height() * scale, b, rc.height() * scale);
	pack->setBaseRect(startPen, startBrush, scene);
	activeReserve->setZone((scene->width() / 2) * (-1) + 20 + b, (scene->height() / 2)- 10 - rc.height() * scale, b, rc.height() * scale);
	activeReserve->setBaseRect(startPen, startBrush, scene);
	for(int i = 13; i < cardsImgs.count(); i++)
	{
		if(numAces.indexOf(i) != -1)
			continue;
		pack->addCard(cardsImgs[i]);
	}
	
	for(i = 0; i < NUM_PILES_FAULT; i++)
	{
		PileFault p;
		p.setZone((scene->width() / 2) * (-1) + 40 + b * 2 + a * i, (scene->height() / 2)- 10 - rc.height() * scale, b, rc.height() * scale);
		p.setBaseRect(startPen, startBrush, scene);
		faultPiles.append(p);
	}
	
	for(i = 0; i < cardsImgs.count(); i++)
		scene->addItem(cardsImgs[i]);
	
	activeReserve->addCard(pack->lastCard());
	pack->removeCard(pack->getCardIndex(pack->lastCard()));
}

qreal GameManager::getScale() const
{
	return scale;
}

CardGraphicsScene* GameManager::getScene()
{
	return scene;
}

void GameManager::setScale(qreal scale)
{
	this->scale = scale;
}

void GameManager::setRender(QSvgRenderer* render)
{
	this->render = render;
}

void GameManager::newCards()
{
	end = 0;
	scene->clear();
	basePiles.clear();
	faultPiles.clear();
	pack->clear();
	activeReserve->clear();
	reserve->clear();
	cardsImgs.clear();
	initCards();
}

void GameManager::setSizeScene(qreal w, qreal h)
{
	QRectF sRect;
	sRect.setX((w / 2) * (-1));
	sRect.setY((h / 2) * (-1));
	sRect.setWidth(w);
	sRect.setHeight(h);
	scene->setSceneRect(sRect);
}

void GameManager::moveCard(QPointF point, CardSvgItem* card)
{
	bool ok = false;
	QRectF rc = pack->getZone();
	if(rc.contains(point))
	{
		return;
	}
	
	if(!card)
		return;
	
	if(setBaseCard(point, card))
		return;
	
	setFaultCard(point, card);
}

void GameManager::setActiveReserveCard(CardSvgItem* card)
{
	if(!card)
	{
		for(int i = activeReserve->count() - 1; i >= 0; i--)
		{
			CardSvgItem *nCard = activeReserve->getCard(i);
			pack->addCard(nCard);
		}
		activeReserve->clear();
	}
	else
	{
		activeReserve->addCard(card);
		pack->removeCard(pack->getCardIndex(card));
	}
}

bool GameManager::setBaseCard(const QPointF& point, CardSvgItem* card)
{
	qint32 indexPileEnd = -1, indexPileStart = -1, i;
	QRectF rc;
	
	for(i = 0; i < NUM_PILES_BASE; i++)
	{
		rc = basePiles.at(i).getZone();
		if(rc.contains(point))
		{
			indexPileEnd = i;
		}
		if(rc.contains(card->getLastPos()))
		{
			indexPileStart = i;
		}
	}
	if(indexPileEnd == -1)
	{
		return false;
	}
	
	if(indexPileEnd == indexPileStart)
		return true;
	
	if(basePiles[indexPileEnd].addCard(card))
	{
		for(i = 0; i < NUM_PILES_FAULT; i++)
		{
			rc = faultPiles.at(i).getZone();
			if(rc.contains(card->getLastPos()))
			{
				faultPiles[i].removeCard(faultPiles[i].getCardIndex(card));
				return true;
			}
		}
		
		rc = reserve->getZone();
		if(rc.contains(card->getLastPos()))
		{
			reserve->removeCard(reserve->getCardIndex(card));
			return true;
		}
		
		rc = activeReserve->getZone();
		if(rc.contains(card->getLastPos()))
		{
			activeReserve->removeCard(activeReserve->getCardIndex(card));
			if(pack->count() > 0)
			{
				activeReserve->addCard(pack->lastCard());
				pack->removeCard(pack->count() - 1);
			}
			return true;
		}
	}
	card->setPos(card->getLastPos());
	card->setZValue(card->getOldZ());
	return true;
}

bool GameManager::setFaultCard(const QPointF& point, CardSvgItem* card)
{
	qint32 indexPileEnd = -1;
	QRectF rc;
	
	rc = activeReserve->getZone();
	if(!rc.contains(card->getLastPos()))
	{
		card->setPos(card->getLastPos());
		card->setZValue(card->getOldZ());
		return true;
	}
	
	for(int i = 0; i < NUM_PILES_FAULT; i++)
	{
		rc = faultPiles.at(i).getZone();
		if(rc.contains(point))
		{
			indexPileEnd = i;
			break;
		}
	}
	
	if(indexPileEnd == -1)
	{
		card->setPos(card->getLastPos());
		card->setZValue(card->getOldZ());
		return false;
	}
	
	if(faultPiles[indexPileEnd].addCard(card))
	{
		activeReserve->removeCard(activeReserve->getCardIndex(card));
		if(pack->count() > 0)
		{
			activeReserve->addCard(pack->lastCard());
			pack->removeCard(pack->count() - 1);
		}
		return true;
	}
	card->setPos(card->getLastPos());
	card->setPos(card->getLastPos());
	return true;
}

void GameManager::endGame()
{
	end++;
	if(end == NUM_PILES_BASE)
	{
		QFont font("Dejavu", 24, QFont::Bold);
		scene->addText(trUtf8("Вы выйграли!!!"), font);
	}
}

#include "gamemanager.moc"