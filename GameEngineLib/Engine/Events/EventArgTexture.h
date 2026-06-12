#ifndef EVENT_ARG_TEXTURE_H
#define EVENT_ARG_TEXTURE_H

#include <Engine/Events/EventArg.h>

namespace GameEngine
{
    class TextureComponent;
    struct EventArgTexture final : public EventArg
    {
        TextureComponent* TextureComponent;
    };
}

#endif