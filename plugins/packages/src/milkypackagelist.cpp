#include "milkypackagelist.h"

#include "packagefiltermethods.h"

MilkyPackageList::MilkyPackageList(QObject *parent) :
    QAbstractListModel(parent), packages()
{
    QHash<int, QByteArray> roles;
    roles[Id] = QString("identifier").toLocal8Bit();
    roles[Title] = QString("title").toLocal8Bit();
    roles[Description] = QString("description").toLocal8Bit();
    roles[Info] = QString("info").toLocal8Bit();
    roles[Icon] = QString("icon").toLocal8Bit();
    roles[Uri] = QString("uri").toLocal8Bit();
    roles[MD5] = QString("md5").toLocal8Bit();
    roles[Vendor] = QString("vendor").toLocal8Bit();
    roles[Group] = QString("group").toLocal8Bit();
    roles[Modified] = QString("modified").toLocal8Bit();
    roles[LastUpdatedString] = QString("lastUpdatedString").toLocal8Bit();
    roles[Rating] = QString("rating").toLocal8Bit();
    roles[Size] = QString("size").toLocal8Bit();
    roles[SizeString] = QString("sizeString").toLocal8Bit();
    roles[AuthorName] = QString("authorName").toLocal8Bit();
    roles[AuthorSite] = QString("authorSite").toLocal8Bit();
    roles[AuthorEmail] = QString("authorEmail").toLocal8Bit();
    roles[InstalledVersionMajor] = QString("installedVersionMajor").toLocal8Bit();
    roles[InstalledVersionMinor] = QString("installedVersionMinor").toLocal8Bit();
    roles[InstalledVersionRelease] = QString("installedVersionRelease").toLocal8Bit();
    roles[InstalledVersionBuild] = QString("installedVersionBuild").toLocal8Bit();
    roles[InstalledVersionType] = QString("installedVersionType").toLocal8Bit();
    roles[CurrentVersionMajor] = QString("currentVersionMajor").toLocal8Bit();
    roles[CurrentVersionMinor] = QString("currentVersionMinor").toLocal8Bit();
    roles[CurrentVersionRelease] = QString("currentVersionRelease").toLocal8Bit();
    roles[CurrentVersionBuild] = QString("currentVersionBuild").toLocal8Bit();
    roles[CurrentVersionType] = QString("currentVersionType").toLocal8Bit();
    roles[Installed] = QString("installed").toLocal8Bit();
    roles[HasUpdate] = QString("hasUpdate").toLocal8Bit();
    roles[InstallPath] = QString("installPath").toLocal8Bit();
    roles[Categories] = QString("categories").toLocal8Bit();
    roles[CategoriesString] = QString("categoriesString").toLocal8Bit();
    roles[PreviewPics] = QString("previewPics").toLocal8Bit();
    roles[Licenses] = QString("licenses").toLocal8Bit();
    roles[SourceLinks] = QString("sourceLinks").toLocal8Bit();
    setRoleNames(roles);
}

QVariant MilkyPackageList::inCategory(const QString &category)
{
    return PackageFilterMethods::inCategory(this, category);
}

QVariant MilkyPackageList::matching(const QString &role, const QString &value)
{
    return PackageFilterMethods::matching(this, role, value);
}

QVariant MilkyPackageList::sortedBy(const QString &role, bool ascending)
{
    return PackageFilterMethods::sortedBy(this, role, ascending);
}

QVariant MilkyPackageList::drop(int count)
{
    return PackageFilterMethods::drop(this, count);
}

QVariant MilkyPackageList::take(int count)
{
    return PackageFilterMethods::take(this, count);
}

int MilkyPackageList::rowCount(const QModelIndex &) const
{
    return packages.count();
}

QVariant MilkyPackageList::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && index.row() < packages.size())
    {
        const QSharedPointer<MilkyPackage> value = packages.at(index.row());
        switch(role)
        {
        case Id:
            return value->getId();
        case Title:
            return value->getTitle();
        case Description:
            return value->getDescription();
        case Info:
            return value->getInfo();
        case Icon:
            return value->getIcon();
        case Uri:
            return value->getUri();
        case MD5:
            return value->getMD5();
        case Vendor:
            return value->getVendor();
        case Group:
            return value->getGroup();
        case Modified:
            return value->getModified();
        case LastUpdatedString:
            return value->getLastUpdatedString();
        case Rating:
            return value->getRating();
        case Size:
            return value->getSize();
        case SizeString:
            return value->getSizeString();
        case AuthorName:
            return value->getAuthorName();
        case AuthorSite:
            return value->getAuthorSite();
        case AuthorEmail:
            return value->getAuthorEmail();
        case InstalledVersionMajor:
            return value->getInstalledVersionMajor();
        case InstalledVersionMinor:
            return value->getInstalledVersionMinor();
        case InstalledVersionRelease:
            return value->getInstalledVersionRelease();
        case InstalledVersionBuild:
            return value->getInstalledVersionBuild();
        case InstalledVersionType:
            return value->getInstalledVersionType();
        case CurrentVersionMajor:
            return value->getCurrentVersionMajor();
        case CurrentVersionMinor:
            return value->getCurrentVersionMinor();
        case CurrentVersionRelease:
            return value->getCurrentVersionRelease();
        case CurrentVersionBuild:
            return value->getCurrentVersionBuild();
        case CurrentVersionType:
            return value->getCurrentVersionType();
        case Installed:
            return value->getInstalled();
        case HasUpdate:
            return value->getHasUpdate();
        case InstallPath:
            return value->getInstallPath();
        case Categories:
            return value->getCategories();
        case CategoriesString:
            return value->getCategoriesString();
        case PreviewPics:
            return value->getPreviewPics();
        case Licenses:
            return value->getLicenses();
        case SourceLinks:
            return value->getSourceLinks();
        default:
            return QVariant();
        }
    }

    return QVariant();
}

QVariant MilkyPackageList::headerData(int, Qt::Orientation, int role) const
{
    switch(role)
    {
    case Id:
        return QString("Id");
    case Title:
        return QString("Title");
    case Description:
        return QString("Description");
    case Info:
        return QString("Info");
    case Icon:
        return QString("Icon");
    case Uri:
        return QString("Uri");
    case MD5:
        return QString("MD5");
    case Vendor:
        return QString("Vendor");
    case Group:
        return QString("Group");
    case Modified:
        return QString("Modified");
    case LastUpdatedString:
        return QString("LastUpdatedString");
    case Rating:
        return QString("Rating");
    case Size:
        return QString("Size");
    case SizeString:
        return QString("SizeString");
    case AuthorName:
        return QString("AuthorName");
    case AuthorSite:
        return QString("AuthorSite");
    case AuthorEmail:
        return QString("AuthorEmail");
    case InstalledVersionMajor:
        return QString("InstalledVersionMajor");
    case InstalledVersionMinor:
        return QString("InstalledVersionMinor");
    case InstalledVersionRelease:
        return QString("InstalledVersionRelease");
    case InstalledVersionBuild:
        return QString("InstalledVersionBuild");
    case InstalledVersionType:
        return QString("InstalledVersionType");
    case CurrentVersionMajor:
        return QString("CurrentVersionMajor");
    case CurrentVersionMinor:
        return QString("CurrentVersionMinor");
    case CurrentVersionRelease:
        return QString("CurrentVersionRelease");
    case CurrentVersionBuild:
        return QString("CurrentVersionBuild");
    case CurrentVersionType:
        return QString("CurrentVersionType");
    case Installed:
        return QString("Installed");
    case HasUpdate:
        return QString("HasUpdate");
    case InstallPath:
        return QString("InstallPath");
    case Categories:
        return QString("Categories");
    case CategoriesString:
        return QString("CategoriesString");
    case PreviewPics:
        return QString("PreviewPics");
    case Licenses:
        return QString("Licenses");
    case SourceLinks:
        return QString("SourceLinks");
    default:
        return QVariant();
    }
}

void MilkyPackageList::addPackage(MilkyPackage* package)
{
    packages.append(QSharedPointer<MilkyPackage>(package));
}

void MilkyPackageList::clear()
{
    packages.clear();
}
