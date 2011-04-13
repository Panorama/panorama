#ifndef TEXTFILE_H
#define TEXTFILE_H

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <qdeclarative.h>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>

class TextFile : public QObject
{
Q_OBJECT
Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
Q_PROPERTY(QString data READ data NOTIFY dataChanged);
public:
    explicit TextFile(QObject *parent = 0);

    QString source() const;
    void setSource(const QString &);

    QString data() const;

signals:
    void sourceChanged(const QString &value);
    void dataChanged(const QString &value);

private:
    void loadFile(const QString &source);
    QString _source;
    QString _data;
};

QML_DECLARE_TYPE(TextFile);

#endif // TEXTFILE_H
