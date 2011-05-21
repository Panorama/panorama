#ifndef TEXTFILE_H
#define TEXTFILE_H

#include "panoramainternal.h"

#include <QObject>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <qdeclarative.h>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>

class TextFilePrivate;

class TextFile : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QString data   READ data                   NOTIFY dataChanged)
    PANORAMA_DECLARE_PRIVATE(TextFile)
public:
    explicit TextFile(QObject *parent = 0);
    ~TextFile();

    QString source() const;
    void setSource(const QString &);

    QString data() const;

signals:
    void sourceChanged(const QString &value);
    void dataChanged(const QString &value);
};

QML_DECLARE_TYPE(TextFile);

#endif // TEXTFILE_H
