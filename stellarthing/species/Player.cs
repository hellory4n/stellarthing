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

    Object3D? bob;

    public async void create()
    {
        bob = new Object3D() {
            model = await load<Model>("bob_guy.obj"),
            rotationEuler = (125, 125, 125)
        };
    }

    public void update(double delta) {}

    public void draw()
    {
        Graphics.drawObject3D(bob!);
    }
}