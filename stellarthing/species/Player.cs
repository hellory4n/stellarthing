using System;
using System.Threading.Tasks;
using Newtonsoft.Json;
using starry;
using static starry.Starry;
namespace stellarthing;

/// <summary>
/// player
/// </summary>
public class Player : IEntity {
    public EntityType entityType => EntityType.GAME_WORLD;
    public string name => "Player";
    public string[] initGroups =>
        [Groups.PLAYER_GROUP, Groups.HUMAN_GROUP, Groups.SPECIES_GROUP];

    readonly double speed = 3.5;

    public void create() {}

    public void update(double delta) {}

    public void draw() {}
}