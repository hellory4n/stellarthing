#pragma once
#include "core/core.h"
#include "core/collections/stlist.h"
#include "groups.h"

typedef enum {
    /// pausable object in the game world
    ST_ENTITY_TYPE_GAME_WORLD,
    /// pausable 2d interface
    ST_ENTITY_TYPE_UI,
    /// 2d interface only ran when paused
    ST_ENTITY_TYPE_PAUSED_UI,
    /// entity that isn't rendered or interacted with, can be paused
    ST_ENTITY_TYPE_MANAGER,
    /// entity that isn't rendered or interacted with, only ran when paused
    ST_ENTITY_TYPE_PAUSED_MANAGER,
    /// similar to `GAME_WORLD` but it's always running no matter the chunk or world. convenient for factories, as forcing players to fit factories in a single chunk and then stay there for the factory to work would be very stupid. note that this actually can be paused, so it's not always running
    ST_ENTITY_TYPE_ALWAYS_RUNNING,
} StEntityType;

/// random 10 character base64 string :)
typedef const char* StEntityId;

/// entity group :)
typedef const char* StGroup;

/// component type bcuz this is C
typedef const char* StComponentType;

/// entity. you should usually pass `StEntityId`s instead
typedef struct {
    /// tpye
    StEntityType type;
    /// called when the entity is initialized
    void (*new)(StEntityId);
    /// called every frame unless the entity is paused. the float64 argument is the delta time
    void (*update)(StEntityId, float64);
    /// called every frame, even if the entity is paused. you're supposed to put drawing stuff (if any) here.
    void (*draw)(StEntityId);
} StEntity;

/// it's a component
typedef struct {
    /// called when the component is initialized
    void (*new)(StEntityId);
    /// called every frame unless the entity is paused. the float64 argument is the delta time
    void (*update)(StEntityId, float64);
    /// called every frame, even if the entity is paused. you're supposed to put drawing stuff (if any) here.
    void (*draw)(StEntityId);
    /// returns the type of the component since this is C
    StComponentType (*get_type)();
} StComponent;

/// pauses entities. not every entity is paused, see `StEntityType`
void StEntity_pause(bool pause);

/// adds a new entity and returns the id for the entity
StEntityId StEntity_new(StEntity entity);

/// gets or adds a group of entities
StList* StEntity_get_group(StGroup group);

/// adds an entity to a group
void StEntity_add_to_group(StEntityId entity, StGroup group);

/// returns true if the entity is in that group
bool StEntity_is_in_group(StEntityId entity, StGroup group);

/// returns the component
void* StEntity_get_component(StEntityId entity, StComponentType component);

void __st_update_entities__();