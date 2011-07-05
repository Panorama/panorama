#ifndef MILKYPACKAGE_H
#define MILKYPACKAGE_H

#include <QObject>
#include <QDateTime>
#include <QStringList>
#include "milky/milky.h"

class MilkyPackage : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ getId WRITE setId NOTIFY idChanged);
    Q_PROPERTY(QString title READ getTitle WRITE setTitle NOTIFY titleChanged);
    Q_PROPERTY(QString description READ getDescription WRITE setDescription NOTIFY descriptionChanged);
    Q_PROPERTY(QString info READ getInfo WRITE setInfo NOTIFY infoChanged);
    Q_PROPERTY(QString icon READ getIcon WRITE setIcon NOTIFY iconChanged);
    Q_PROPERTY(QString uri READ getUri WRITE setUri NOTIFY uriChanged);
    Q_PROPERTY(QString md5 READ getMD5 WRITE setMD5 NOTIFY md5Changed);
    Q_PROPERTY(QString vendor READ getVendor WRITE setVendor NOTIFY vendorChanged);
    Q_PROPERTY(QString group READ getGroup WRITE setGroup NOTIFY groupChanged);
    Q_PROPERTY(QDateTime modified READ getModified WRITE setModified NOTIFY modifiedChanged);

    Q_PROPERTY(int rating READ getRating WRITE setRating NOTIFY ratingChanged);
    Q_PROPERTY(int size READ getSize WRITE setSize NOTIFY sizeChanged);

    Q_PROPERTY(QString authorName READ getAuthorName WRITE setAuthorName NOTIFY authorNameChanged);
    Q_PROPERTY(QString authorSite READ getAuthorSite WRITE setAuthorSite NOTIFY authorSiteChanged);
    Q_PROPERTY(QString authorEmail READ getAuthorEmail WRITE setAuthorEmail NOTIFY authorEmailChanged);

    Q_PROPERTY(QString installedVersionMajor READ getInstalledVersionMajor WRITE setInstalledVersionMajor NOTIFY installedVersionMajorChanged);
    Q_PROPERTY(QString installedVersionMinor READ getInstalledVersionMinor WRITE setInstalledVersionMinor NOTIFY installedVersionMinorChanged);
    Q_PROPERTY(QString installedVersionRelease READ getInstalledVersionRelease WRITE setInstalledVersionRelease NOTIFY installedVersionReleaseChanged);
    Q_PROPERTY(QString installedVersionBuild READ getInstalledVersionBuild WRITE setInstalledVersionBuild NOTIFY installedVersionBuildChanged);
    Q_PROPERTY(QString installedVersionType READ getInstalledVersionType WRITE setInstalledVersionType NOTIFY installedVersionTypeChanged);

    Q_PROPERTY(QString currentVersionMajor READ getCurrentVersionMajor WRITE setCurrentVersionMajor NOTIFY currentVersionMajorChanged);
    Q_PROPERTY(QString currentVersionMinor READ getCurrentVersionMinor WRITE setCurrentVersionMinor NOTIFY currentVersionMinorChanged);
    Q_PROPERTY(QString currentVersionRelease READ getCurrentVersionRelease WRITE setCurrentVersionRelease NOTIFY currentVersionReleaseChanged);
    Q_PROPERTY(QString currentVersionBuild READ getCurrentVersionBuild WRITE setCurrentVersionBuild NOTIFY currentVersionBuildChanged);
    Q_PROPERTY(QString currentVersionType READ getCurrentVersionType WRITE setCurrentVersionType NOTIFY currentVersionTypeChanged);

    Q_PROPERTY(bool installed READ getInstalled WRITE setInstalled NOTIFY installedChanged);
    Q_PROPERTY(bool hasUpdate READ getHasUpdate WRITE setHasUpdate NOTIFY hasUpdateChanged);
    Q_PROPERTY(QString installPath READ getInstallPath WRITE setInstallPath NOTIFY installPathChanged);
    Q_PROPERTY(QStringList categories READ getCategories WRITE setCategories NOTIFY categoriesChanged);
    Q_PROPERTY(QString categoriesString READ getCategoriesString WRITE setCategoriesString NOTIFY categoriesStringChanged);
    Q_PROPERTY(QStringList previewPics READ getPreviewPics WRITE setPreviewPics NOTIFY previewPicsChanged);
    Q_PROPERTY(QStringList licenses READ getLicenses WRITE setLicenses NOTIFY licensesChanged);
    Q_PROPERTY(QStringList sourceLinks READ getSourceLinks WRITE setSourceLinks NOTIFY sourceLinksChanged);

public:
    explicit MilkyPackage(QObject *parent = 0);
    MilkyPackage(_pnd_package* p, QObject* parent = 0);
    MilkyPackage(MilkyPackage const& other);
    MilkyPackage const& operator=(MilkyPackage const& other);

public slots:
    QString getId() const;
    QString getTitle() const;
    QString getDescription() const;
    QString getInfo() const;
    QString getIcon() const;
    QString getUri() const;
    QString getMD5() const;
    QString getVendor() const;
    QString getGroup() const;
    QDateTime getModified() const;
    int getRating() const;
    int getSize() const;
    QString getAuthorName() const;
    QString getAuthorSite() const;
    QString getAuthorEmail() const;
    QString getInstalledVersionMajor() const;
    QString getInstalledVersionMinor() const;
    QString getInstalledVersionRelease() const;
    QString getInstalledVersionBuild() const;
    QString getInstalledVersionType() const;
    QString getCurrentVersionMajor() const;
    QString getCurrentVersionMinor() const;
    QString getCurrentVersionRelease() const;
    QString getCurrentVersionBuild() const;
    QString getCurrentVersionType() const;
    bool getInstalled() const;
    bool getHasUpdate() const;
    QString getInstallPath() const;
    QStringList getCategories() const;
    QString getCategoriesString() const;
    QStringList getPreviewPics() const;
    QStringList getLicenses() const;
    QStringList getSourceLinks() const;

    void setId(QString newId);
    void setTitle(QString newTitle);
    void setDescription(QString newDescription);
    void setInfo(QString newInfo);
    void setIcon(QString newIcon);
    void setUri(QString newUri);
    void setMD5(QString newMD5);
    void setVendor(QString newVendor);
    void setGroup(QString newGroup);
    void setModified(QDateTime newModified);
    void setRating(int newRating);
    void setSize(int newSize);
    void setAuthorName(QString newAuthorName);
    void setAuthorSite(QString newAuthorSite);
    void setAuthorEmail(QString newAuthorEmail);
    void setInstalledVersionMajor(QString newInstalledVersionMajor);
    void setInstalledVersionMinor(QString newInstalledVersionMinor);
    void setInstalledVersionRelease(QString newInstalledVersionRelease);
    void setInstalledVersionBuild(QString newInstalledVersionBuild);
    void setInstalledVersionType(QString newInstalledVersionType);
    void setCurrentVersionMajor(QString newCurrentVersionMajor);
    void setCurrentVersionMinor(QString newCurrentVersionMinor);
    void setCurrentVersionRelease(QString newCurrentVersionRelease);
    void setCurrentVersionBuild(QString newCurrentVersionBuild);
    void setCurrentVersionType(QString newCurrentVersionType);
    void setInstalled(bool newInstalled);
    void setHasUpdate(bool newHasUpdate);
    void setInstallPath(QString newInstallPath);
    void setCategories(QStringList newCategories);
    void setCategoriesString(QString newCategoriesString);
    void setPreviewPics(QStringList newPreviewPics);
    void setLicenses(QStringList newLicenses);
    void setSourceLinks(QStringList newSourceLinks);

signals:
    void idChanged(QString);
    void titleChanged(QString);
    void descriptionChanged(QString);
    void infoChanged(QString);
    void iconChanged(QString);
    void uriChanged(QString);
    void md5Changed(QString);
    void vendorChanged(QString);
    void groupChanged(QString);
    void modifiedChanged(QDateTime);
    void ratingChanged(int);
    void sizeChanged(int);
    void authorNameChanged(QString);
    void authorSiteChanged(QString);
    void authorEmailChanged(QString);
    void installedVersionMajorChanged(QString);
    void installedVersionMinorChanged(QString);
    void installedVersionReleaseChanged(QString);
    void installedVersionBuildChanged(QString);
    void installedVersionTypeChanged(QString);
    void currentVersionMajorChanged(QString);
    void currentVersionMinorChanged(QString);
    void currentVersionReleaseChanged(QString);
    void currentVersionBuildChanged(QString);
    void currentVersionTypeChanged(QString);
    void installedChanged(bool);
    void hasUpdateChanged(bool);
    void installPathChanged(QString);
    void categoriesChanged(QStringList);
    void categoriesStringChanged(QString);
    void previewPicsChanged(QStringList);
    void licensesChanged(QStringList);
    void sourceLinksChanged(QStringList);

private:
    static QStringList alpmListToQStringList(alpm_list_t* list);

    struct Author {
        QString name;
        QString site;
        QString email;
    };

    struct Version {
        QString major;
        QString minor;
        QString release;
        QString build;
        QString type;
    };

    QString id;
    QString title;
    QString description;
    QString info;
    QString icon;
    QString uri;
    QString md5;
    QString vendor;
    QString group;
    QDateTime modified;
    int rating;
    int size;

    Author author;
    Version installedVersion;
    Version currentVersion;

    bool installed;
    bool hasUpdate;
    QString installPath;
    QStringList categories;
    QStringList previewPics;
    QStringList licenses;
    QStringList sourceLinks;
};

#endif // MILKYPACKAGE_H
