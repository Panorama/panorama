#include "application.h"

bool Application::operator ==(const Application &app) const
{
    return app.id == this->id;
}
