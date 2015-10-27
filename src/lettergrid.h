#ifndef ACROSTICA_LETTERGRID_H
#define ACROSTICA_LETTERGRID_H

#include <QList>
#include <QMap>
#include <QGroupBox>

class QLabel;
class QString;

class LetterGrid : public QGroupBox
{
    Q_OBJECT

public:
    LetterGrid(const QString& title, QWidget *parent = 0);

public slots:
    void setText(const QString& str, uint hash);

private:
    QList<QLabel*> letters;
    QMap<uint, QString> widgetCaches;
};

#endif
