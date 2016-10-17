#include <QDir>

#include "util.h"

Util::Util(QObject *parent) : QObject(parent)
{
}

QString Util::convertUrlToNativeFilePath(const QUrl& urlStylePath)
{
    return QDir::toNativeSeparators(urlStylePath.toLocalFile());
}
