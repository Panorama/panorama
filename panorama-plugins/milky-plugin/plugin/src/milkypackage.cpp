#include "milkypackage.h"

MilkyPackage::MilkyPackage(QObject *parent) :
    QObject(parent)
{
}

QString MilkyPackage::getId()
{
    return id;
}
QString MilkyPackage::getTitle()
{
    return title;
}
QString MilkyPackage::getDescription()
{
    return description;
}
QString MilkyPackage::getInfo()
{
    return info;
}
QString MilkyPackage::getIcon()
{
    return icon;
}
QString MilkyPackage::getUri()
{
    return uri;
}
QString MilkyPackage::getmd5()
{
    return md5;
}
QString MilkyPackage::getVendor()
{
    return vendor;
}
QString MilkyPackage::getGroup()
{
    return group;
}
QDateTime MilkyPackage::getModified()
{
    return modified;
}

int MilkyPackage::getRating()
{
    return rating;
}
int MilkyPackage::getSize()
{
    return size;
}

QString MilkyPackage::getAuthorName()
{
    return author.name;
}
QString MilkyPackage::getAuthorSite()
{
    return author.site;
}
QString MilkyPackage::getAuthorEmail()
{
    return author.email;
}

QString MilkyPackage::getInstalledVersionMajor()
{
    return installedVersion.major;
}
QString MilkyPackage::getInstalledVersionMinor()
{
    return installedVersion.minor;
}
QString MilkyPackage::getInstalledVersionRelease()
{
    return installedVersion.release;
}
QString MilkyPackage::getInstalledVersionBuild()
{
    return installedVersion.build;
}
QString MilkyPackage::getInstalledVersionType()
{
    return installedVersion.type;
}

QString MilkyPackage::getCurrentVersionMajor()
{
    return currentVersion.major;
}
QString MilkyPackage::getCurrentVersionMinor()
{
    return currentVersion.minor;
}
QString MilkyPackage::getCurrentVersionRelease()
{
    return currentVersion.release;
}
QString MilkyPackage::getCurrentVersionBuild()
{
    return currentVersion.build;
}
QString MilkyPackage::getCurrentVersionType()
{
    return currentVersion.type;
}

bool MilkyPackage::getInstalled()
{
    return installed;
}
bool MilkyPackage::getHasUpdate()
{
    return hasUpdate;
}
QString MilkyPackage::getInstallPath()
{
    return installPath;
}

void MilkyPackage::setId(QString newId)
{
    id = newId;
    emit idChanged(id);
}
void MilkyPackage::setTitle(QString newTitle)
{
    title = newTitle;
    emit titleChanged(title);
}
void MilkyPackage::setDescription(QString newDescription)
{
    description = newDescription;
    emit descriptionChanged(description);
}
void MilkyPackage::setInfo(QString newInfo)
{
    info = newInfo;
    emit infoChanged(info);
}
void MilkyPackage::setIcon(QString newIcon)
{
    icon = newIcon;
    emit iconChanged(icon);
}
void MilkyPackage::setUri(QString newUri)
{
    uri = newUri;
    emit uriChanged(uri);
}
void MilkyPackage::setmd5(QString newMd5)
{
    md5 = newMd5;
    emit md5Changed(md5);
}
void MilkyPackage::setVendor(QString newVendor)
{
    vendor = newVendor;
    emit vendorChanged(vendor);
}
void MilkyPackage::setGroup(QString newGroup)
{
    group = newGroup;
    emit groupChanged(group);
}
void MilkyPackage::setModified(QDateTime newModified)
{
    modified = newModified;
    emit modifiedChanged(modified);
}

void MilkyPackage::setRating(int newRating)
{
    rating = newRating;
    emit ratingChanged(rating);
}
void MilkyPackage::setSize(int newSize)
{
    size = newSize;
    emit sizeChanged(size);
}

void MilkyPackage::setAuthorName(QString newAuthorName)
{
    author.name = newAuthorName;
    emit authorNameChanged(author.name);
}
void MilkyPackage::setAuthorSite(QString newAuthorSite)
{
    author.site = newAuthorSite;
    emit authorSiteChanged(author.site);
}
void MilkyPackage::setAuthorEmail(QString newAuthorEmail)
{
    author.email = newAuthorEmail;
    emit authorEmailChanged(author.email);
}

void MilkyPackage::setInstalledVersionMajor(QString newInstalledVersionMajor)
{
    installedVersion.major = newInstalledVersionMajor;
    emit installedVersionMajorChanged(installedVersion.major);
}
void MilkyPackage::setInstalledVersionMinor(QString newInstalledVersionMinor)
{
    installedVersion.minor = newInstalledVersionMinor;
    emit installedVersionMinorChanged(installedVersion.minor);
}
void MilkyPackage::setInstalledVersionRelease(QString newInstalledVersionRelease)
{
    installedVersion.release = newInstalledVersionRelease;
    emit installedVersionReleaseChanged(installedVersion.release);
}
void MilkyPackage::setInstalledVersionBuild(QString newInstalledVersionBuild)
{
    installedVersion.build = newInstalledVersionBuild;
    emit installedVersionBuildChanged(installedVersion.build);
}
void MilkyPackage::setInstalledVersionType(QString newInstalledVersionType)
{
    installedVersion.type = newInstalledVersionType;
    emit installedVersionTypeChanged(installedVersion.type);
}

void MilkyPackage::setCurrentVersionMajor(QString newCurrentVersionMajor)
{
    currentVersion.major = newCurrentVersionMajor;
    emit currentVersionMajorChanged(currentVersion.major);
}
void MilkyPackage::setCurrentVersionMinor(QString newCurrentVersionMinor)
{
    currentVersion.minor = newCurrentVersionMinor;
    emit currentVersionMinorChanged(currentVersion.minor);
}
void MilkyPackage::setCurrentVersionRelease(QString newCurrentVersionRelease)
{
    currentVersion.release = newCurrentVersionRelease;
    emit currentVersionReleaseChanged(currentVersion.release);
}
void MilkyPackage::setCurrentVersionBuild(QString newCurrentVersionBuild)
{
    currentVersion.build = newCurrentVersionBuild;
    emit currentVersionBuildChanged(currentVersion.build);
}
void MilkyPackage::setCurrentVersionType(QString newCurrentVersionType)
{
    currentVersion.type = newCurrentVersionType;
    emit currentVersionTypeChanged(currentVersion.type);
}

void MilkyPackage::setInstalled(bool newInstalled)
{
    installed = newInstalled;
    emit installedChanged(installed);
}
void MilkyPackage::setHasUpdate(bool newHasUpdate)
{
    hasUpdate = newHasUpdate;
    emit hasUpdateChanged(hasUpdate);
}
void MilkyPackage::setInstallPath(QString newInstallPath)
{
    installPath = newInstallPath;
    emit installPathChanged(installPath);
}
