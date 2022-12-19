#include <item/ItemMimeData.h>

QStringList ItemMimeData::formats() const
{
    return {"application/apple"};
}

bool ItemMimeData::hasFormat(const QString& mimeType) const
{
    return mimeType == "application/apple";
}

int ItemMimeData::GetType() const
{
    return _type;
}
