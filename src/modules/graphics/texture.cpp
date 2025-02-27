#include <raylib.h>
#include "core/collections/hashmap.hpp"
#include "core/collections/list.hpp"
#include "core/collections/tuple.hpp"
#include "core/math/vec2i.hpp"
#include "core/ref.hpp"
#include "core/string.hpp"
#include "texture.hpp"

namespace starry {

HashMap<String, Ref<Texture>>* __textures;

void Texture::__init_subsystem()
{
    __textures = new HashMap<String, Ref<Texture>>();
}

void Texture::__free_subsystem()
{
    Ref<List<Tuple2<String*, Ref<Texture>*>>> god = __textures->items();
    for (nint i = 0; i < god->length; i++) {
        Texture::force_free(*god->at(i)->item2);
    }
    delete __textures;
}

Ref<Texture> Texture::load(String path)
{
    Texture2D die = LoadTexture(path);
    Ref<Texture> mate = Ref<Texture>(new Texture {
        .__data = {die.id, die.width, die.height, die.mipmaps, die.format},
        .path = path,
        .size = Vec2i(die.width, die.height),
    });

    __textures->set(path, mate);
    return newref<Texture>(mate);
}

void Texture::force_free(Ref<Texture> texture)
{
    Texture2D die = {
        .id = texture->__data.id,
        .width = texture->__data.width,
        .height = texture->__data.height,
        .mipmaps = texture->__data.mipmaps,
        .format = texture->__data.format,
    };
    UnloadTexture(die);
    __textures->remove(texture->path);
}

}