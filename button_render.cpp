/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "button_render.h"

//! [0]
CButtonRender::CButtonRender(const QPainterPath &path, QWidget *parent)
    : QWidget(parent), mPath(path)
{
    penWidth = 1;
    rotationAngle = 0;
    m_iPressed = false;
    bShow = true;

    fillColor = Qt::red;

    penColorPressed = QColor(255,255,255);

    fillBrush = QBrush(Qt::yellow,Qt::Dense3Pattern);

    setGeometry(0,0,0,0);
    setVisible(false);

}
void CButtonRender::setFillColor(Qt::GlobalColor color)
{
    fillBrush.setColor(color);
    fillColor = color;
}

Qt::GlobalColor CButtonRender::getFillColor()
{
    return fillColor;
}

bool CButtonRender::BeShow()
{
    return bShow;
}
void CButtonRender::setBeShow(bool show)
{
    bShow = show;
}
QPainterPath CButtonRender::getPainterPath()
{
    return mPath;
}

//! [5]
void CButtonRender::setPenWidth(int width)
{
    penWidth = width;
}
//! [5]

//! [6]
void CButtonRender::setPenColor(const QColor &color)
{
    penColor = color;
}
QColor  CButtonRender::getPenColor()
{
    if(m_iPressed)
        return penColorPressed;
    else
        return penColor;
}

void CButtonRender::setBrush(const QBrush &brush)
{
    fillBrush = brush;
}

QBrush  CButtonRender::getBrush()
{
    return fillBrush;
}

//! [6]

void CButtonRender::setCornerPoints(QPolygon * cornerPt)
{
    mCornerPoints = *cornerPt;
}
QPolygon CButtonRender::getCornerPoints()
{
    return mCornerPoints;
}

void CButtonRender::setPolygon(QPolygon * borderPt)
{
    mBorderPolygon = *borderPt;
}

QPolygon * CButtonRender::getPolygon()
{
    return &mBorderPolygon;
}

