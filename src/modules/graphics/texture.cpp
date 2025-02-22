#include <stdio.h>
#include "raylib.hpp"
#include "core/collections/hashmap.hpp"
#include "texture.hpp"

namespace starry {

HashMap<const char*, rl::Texture2D>* __textures;

void Texture::__init_subsystem()
{
    __textures = new HashMap<const char*, rl::Texture>();
    printf("[ASSETS] Setup texture subsystem\n");
}

void Texture::__free_subsystem()
{
    // help me axon dendrite
    List<Tuple2<const char**, rl::Texture2D*>>* lositens = __textures->items();
    for (nint i = 0; i < lositens->length; i++) {
        delete (lositens->at(i)->item2);
    }
    delete lositens;

    delete __textures;
    printf("[ASSETS] Rip textures\n");
}

Texture::Texture(const char* path)
{
    // loading the same files 375827529 times isn't very salubrious
    if (!__textures->contains(path)) {
        rl::Texture2D* mate = __textures->get(path);
        this->id = mate->id;
        this->width = mate->width;
        this->height = mate->height;
        this->mipmaps = mate->mipmaps;
        this->format = mate->format;
        return;
    }

    rl::Texture2D mate = rl::LoadTexture(path);
    this->id = mate.id;
    this->width = mate.width;
    this->height = mate.height;
    this->mipmaps = mate.mipmaps;
    this->format = mate.format;
    __textures->set(path, mate);

    printf("[ASSETS] Loaded texture at %s\n", path);
}

Texture::~Texture()
{
    rl::Texture2D texture_but_raylib = {
        .id = this->id,
        .width = this->width,
        .height = this->height,
        .mipmaps = this->mipmaps,
        .format = this->format,
    };
    rl::UnloadTexture(texture_but_raylib);
}

}