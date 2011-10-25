#ifndef MILKYPACKAGELIST_H
#define MILKYPACKAGELIST_H

#include <QAbstractListModel>
#include <QSharedPointer>

#include "milkypackage.h"

class MilkyPackageList : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit MilkyPackageList(QObject *parent = 0);

    enum Roles
    {
        Id = Qt::UserRole,
        Title,
        Description,
        Info,
        Icon,
        Uri,
        MD5,
        Vendor,
        Group,
        Modified,
        LastUpdatedString,
        Rating,
        Size,
        SizeString,
        AuthorName,
        AuthorSite,
        AuthorEmail,
        InstalledVersionMajor,
        InstalledVersionMinor,
        InstalledVersionRelease,
        InstalledVersionBuild,
        InstalledVersionType,
        CurrentVersionMajor,
        CurrentVersionMinor,
        CurrentVersionRelease,
        CurrentVersionBuild,
        CurrentVersionType,
        Installed,
        HasUpdate,
        InstallPath,
        Categories,
        CategoriesString,
        PreviewPics,
        Licenses,
        SourceLinks
    };

    /** QML helper method that applies a filter to this model */
    Q_INVOKABLE QVariant inCategory(const QString &category);

    /** QML helper method that applies a filter to this model */
    Q_INVOKABLE QVariant matching(const QString &role, const QString &value);

    /** QML helper method that sorts this model */
    Q_INVOKABLE QVariant sortedBy(const QString &role, bool ascending);

    Q_INVOKABLE QVariant drop(int count);

    Q_INVOKABLE QVariant take(int count);


    /** Returns the number of items in this model */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /** Returns the data at the specified index. */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /** Returns the header for each role */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

signals:

public slots:
    void addPackage(MilkyPackage* package);
    void clear();

protected:
    QList< QSharedPointer<MilkyPackage> > packages;

};

#endif // MILKYPACKAGELIST_H
