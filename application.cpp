#include <application.h>

bool Application::operator ==(const Application &app) const
{
    //Each .desktop file is loaded only once, so we compare by file
    return app.relatedFile == this->relatedFile;
}
