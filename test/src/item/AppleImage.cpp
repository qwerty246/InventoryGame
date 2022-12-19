#include <database/SqlQueryManager.h>
#include <item/AppleImage.h>

const QPixmap& AppleImage::GetImage(int type)
{
    static AppleImage image;
    if (image._pixmap.isNull())
    {
        image._pixmap = SqlQueryManager::GetImage(type);
    }
    return image._pixmap;
}
