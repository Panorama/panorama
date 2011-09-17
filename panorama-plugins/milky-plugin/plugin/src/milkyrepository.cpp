#include "milkyrepository.h"

MilkyRepository::MilkyRepository(pnd_repo* repository, QObject *parent) :
    QObject(parent), name(repository->name), url(repository->url),
    merge(repository->merge), timestamp(QDateTime::fromMSecsSinceEpoch(repository->timestamp))
{
}

QString MilkyRepository::getName()
{
    return name;
}

QString MilkyRepository::getUrl()
{
    return url;
}

QString MilkyRepository::getMerge()
{
    return merge;
}

QDateTime MilkyRepository::getTimestamp()
{
    return timestamp;
}
