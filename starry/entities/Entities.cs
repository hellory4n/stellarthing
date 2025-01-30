using System;
using System.Collections.Concurrent;
using System.Linq;
using System.Threading.Tasks;
namespace starry;

/// <summary>
/// it manages entities
/// </summary>
public static class Entities {
    /// <summary>
    /// entities of the game world type
    /// </summary>
    public const string GAME_WORLD_GROUP = "starry.Entities.WORLD_GROUP";
    /// <summary>
    /// entities of the always running type
    /// </summary>
    public const string ALWAYS_RUNNING_GROUP = "starry.Entities.ALWAYS_GROUP";
    /// <summary>
    /// entities of the ui type
    /// </summary>
    public const string UI_GROUP = "starry.Entities.UI_GROUP";
    /// <summary>
    /// entities of the paused ui type
    /// </summary>
    public const string PAUSED_UI_GROUP = "starry.Entities.PAUSED_UI_GROUP";
    /// <summary>
    /// entities of the manager type
    /// </summary>
    public const string MANAGER_GROUP = "starry.Entities.MANAGER_GROUP";
    /// <summary>
    /// entities of the paused manager type
    /// </summary>
    public const string PAUSED_MANAGER_GROUP = "starry.Entities.PAUSED_MANAGER_GROUP";

    /// <summary>
    /// if true, the game is paused. not all entities get paused, see EntityType
    /// </summary>
    public static bool paused { get; set; } = false;

    public static ConcurrentDictionary<string, IEntity> entities { get; internal set; } = new();
    public static ConcurrentDictionary<int, string> entrefs { get; internal set; } = new();
    public static ConcurrentDictionary<string, ConcurrentHashSet<string>> groups { get; internal set; } = new();
    public static ConcurrentDictionary<string, ConcurrentHashSet<IComponent>> components { get; internal set; } = new();
    public static ConcurrentDictionary<string, ConcurrentDictionary<string, object?>> meta { get; internal set; } = new();
    public static ConcurrentDictionary<string, ConcurrentHashSet<string>> entgroups { get; set; } = new();

    /// <summary>
    /// adds an entity.
    /// </summary>
    public static void addEntity(IEntity entity)
    {
        // ref is a keyword
        string regh = StMath.randomBase64(10);
        entities.TryAdd(regh, entity);
        entrefs.TryAdd(entity.GetHashCode(), regh);
        meta.TryAdd(regh, new());
        entgroups.TryAdd(regh, []);

        string elgrupo = entity.entityType switch {
            EntityType.GAME_WORLD => GAME_WORLD_GROUP,
            EntityType.ALWAYS_RUNNING => ALWAYS_RUNNING_GROUP,
            EntityType.UI => UI_GROUP,
            EntityType.PAUSED_UI => PAUSED_UI_GROUP,
            EntityType.MANAGER => MANAGER_GROUP,
            EntityType.PAUSED_MANAGER => PAUSED_MANAGER_GROUP,
            _ => throw new Exception("man"),
        };
        addToGroup(elgrupo, ent2ref(entity));

        string[] losgrupos = entity.initGroups;
        foreach (string group in losgrupos) {
            addToGroup(group, ent2ref(entity));
        }

        components.TryAdd(ent2ref(entity), []);
        entity.create();
    }

    /// <summary>
    /// gets the group, and creates the group if it doesn't exist yet
    /// </summary>
    public static ConcurrentHashSet<string> getGroup(string group) => groups.GetOrAdd(group, []);

    /// <summary>
    /// adds an entity to the group, and creates the group if it doesn't exist yet
    /// </summary>
    public static void addToGroup(string group, string entity)
    {
        var jjj = groups.GetOrAdd(group, []);
        jjj.Add(entity);
        entgroups[entity].Add(group);
    }

    /// <summary>
    /// if true, the entity is in that group
    /// </summary>
    public static bool isInGroup(string group, string entity)
    {
        if (!groups.ContainsKey(group)) return false;
        return groups[group].Contains(entity);
    }
    
    /// <summary>
    /// updates entities duh
    /// </summary>
    public static async Task update()
    {
        static void mate(IEntity entity) {
            entity.update(Window.deltaTime);
            entity.draw();
            foreach (IComponent component in components[ent2ref(entity)]) {
                component.update(entity, Window.deltaTime);
                component.draw(entity);
            }
        }

        if (paused) {
            // i know
            await Parallel.ForEachAsync(getGroup(PAUSED_MANAGER_GROUP), async (entity, ct) => {
                await Task.Run(() => mate(ref2ent(entity)));
            });

            await Parallel.ForEachAsync(getGroup(PAUSED_UI_GROUP), async (entity, ct) => {
                await Task.Run(() => mate(ref2ent(entity)));
            });
        }
        else {
            await Parallel.ForEachAsync(getGroup(MANAGER_GROUP), async (entity, ct) => {
                await Task.Run(() => mate(ref2ent(entity)));
            });

            await Parallel.ForEachAsync(getGroup(UI_GROUP), async (entity, ct) => {
                await Task.Run(() => mate(ref2ent(entity)));
            });

            await Parallel.ForEachAsync(getGroup(ALWAYS_RUNNING_GROUP), async (entity, ct) => {
                await Task.Run(() => mate(ref2ent(entity)));
            });
            
            await Parallel.ForEachAsync(getGroup(GAME_WORLD_GROUP), async (entity, ct) => {
                // chunk stuff :)
                // its generally not a good idea to process everythin\g on the other side of the galaxy
                /*if (hasComponent<Tile>(entity)) {
                    Tile tile = getComponent<Tile>(entity);
                    vec2i chunk = (tile.position.as2d() / (Tilemap.CHUNK_DIMENSIONS, Tilemap.CHUNK_DIMENSIONS)).floor();
                    if (chunk != Tilemap.currentChunks[Tilemap.currentWorld]) return;
                }*/
                await Task.Run(() => mate(ref2ent(entity)));
            });
        }
    }

    /// <summary>
    /// it adds a component to the entity, and returns the added component
    /// </summary>
    public static T addComponent<T>(string entity) where T: class, IComponent, new()
    {
        T tee = new();
        components[entity].Add(tee);
        tee.create(ref2ent(entity));
        return tee;
    }
    
    /// <summary>
    /// if true, the entity has that component
    /// </summary>
    public static bool hasComponent<T>(string entity) where T: class, IComponent, new() =>
        components[entity].OfType<T>().Any();

    /// <summary>
    /// gets component or adds it if it's not there
    /// </summary>
    public static T getComponent<T>(string entity) where T: class, IComponent, new()
    {
        if (hasComponent<T>(entity)) return components[entity].OfType<T>().First();
        
        addComponent<T>(entity);
        return components[entity].OfType<T>().First();
    }

    /// <summary>
    /// gets the reference thingy for an entity
    /// </summary>
    public static string ent2ref(IEntity entity) => entrefs[entity.GetHashCode()];

    /// <summary>
    /// gets an entity from a reference thingy
    /// </summary>
    public static IEntity ref2ent(string entref) => entities[entref];

    /// <summary>
    /// adds or a sets a key in the entity's metadata
    /// </summary>
    public static void setMeta(string entref, string key, object value)
        => meta[entref].AddOrUpdate(key, value, (ma, te) => value);
    
    /// <summary>
    /// if the key exists, returns the value, otherwise it sets the value to the defaultval parameter. keep in mind the metadata system isn't guaranteed to be type-safe, it's just casting from object
    /// </summary>
    public static T? getMeta<T>(string entref, string key, T? defaultval)
    {
        if (meta[entref].ContainsKey(key)) return (T?)meta[entref][key];
        else {
            meta[entref].TryAdd(key, defaultval);
            return defaultval;
        }
    }

    /// <summary>
    /// it fucking removes a fucking entity
    /// </summary>
    public static void removeEntity(string entref)
    {
        entrefs.TryRemove(entities[entref].GetHashCode(), out _);
        meta.TryRemove(entref, out _);
        components.TryRemove(entref, out _);

        foreach (string losgrupos in entgroups[entref]) {
            groups[losgrupos].Remove(entref);
        }
        
        entgroups.TryRemove(entref, out _);
        entities.TryRemove(entref, out _);
    }
}