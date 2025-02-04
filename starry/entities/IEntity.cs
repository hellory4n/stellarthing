using System;
namespace starry;

/// <summary>
/// its an entity lmao
/// </summary>
public interface IEntity {
    /// <summary>
    /// ran when the bloody entity is bloody created bloody hell mate. this is ran right after the entity is added to the entities stuffs
    /// </summary>
    public void create() {}
    /// <summary>
    /// ran every frame
    /// </summary
    public void update(double delta) {}
    /// <summary>
    /// also ran every frame but youre supposed to draw stuff here
    /// </summary>
    public void draw() {}

    /// <summary>
    /// returns the entity type what did you expect
    /// </summary>
    public EntityType entityType { get; }
    /// <summary>
    /// returns the name what did you expect. idk why this exists but the game's actual behavior shouldn't depend on this
    /// </summary>
    public string name { get; }
    /// <summary>
    /// groups the entity is assigned to when created. you should use constants so there's any ide support ever
    /// </summary>
    public string[] initGroups { get; }
}

/// <summary>
/// type of the entity; affects rendering, input, and pausing. update functions are called in this order: pausable/paused manager -> pausable/pause ui -> always running -> game world
/// </summary>
public enum EntityType {
    /// <summary>
    /// pausable 3d-ish object
    /// </summary>
    GAME_WORLD,
    /// <summary>
    /// pausable 2d interface
    /// </summary>
    UI,
    /// <summary>
    /// 2d interface only ran when paused
    /// </summary>
    PAUSED_UI,
    /// <summary>
    /// entity that isn't rendered or interacted with (doesn't receive input) and just manages stuff, can be paused
    /// </summary>
    MANAGER,
    /// <summary>
    /// entity that isn't rendered or interacted with (doesn't receive input) and just manages stuff, only rendered on pause
    /// </summary>
    PAUSED_MANAGER,
    /// <summary>
    /// similar to <c>gameWorld</c> but it's always running no matter the chunk or world. convenient for factories, as forcing players to fit factories in a single chunk and then stay there for the factory to work would be very stupid. note that this actually can be paused, so it's not always running
    /// </summary>
    ALWAYS_RUNNING,
}