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
    
    Tile? tile;
    Tile? lol;
    AnimationSprite? walkDown;
    AnimationSprite? walkUp;
    AnimationSprite? walkRight;
    AnimationSprite? walkLeft;
    TileParticles? lasparticulas;

    readonly double speed = 3.5;

    public async void create()
    {
        walkDown = new AnimationSprite(0.25,
            await load<Sprite>("species/bobdown1.png"),
            await load<Sprite>("species/bobdown2.png"),
            await load<Sprite>("species/bobdown3.png"),
            await load<Sprite>("species/bobdown4.png")
        );
        walkUp = new AnimationSprite(0.25,
            await load<Sprite>("species/bobup1.png"),
            await load<Sprite>("species/bobup2.png"),
            await load<Sprite>("species/bobup3.png"),
            await load<Sprite>("species/bobup4.png")
        );
        walkRight = new AnimationSprite(0.25,
            await load<Sprite>("species/bobright1.png"),
            await load<Sprite>("species/bobright2.png"),
            await load<Sprite>("species/bobright3.png"),
            await load<Sprite>("species/bobright4.png")
        );
        walkLeft = new AnimationSprite(0.25,
            await load<Sprite>("species/bobleft1.png"),
            await load<Sprite>("species/bobleft2.png"),
            await load<Sprite>("species/bobleft3.png"),
            await load<Sprite>("species/bobleft4.png")
        );
        
        tile = Entities.addComponent<Tile>(ent2ref(this));
        tile.sprite = new TileSprite(walkLeft, walkRight, walkUp, walkDown);
        
        lol = new() {
            sprite = new(await load<Sprite>("tiles/testl.png"),
                         await load<Sprite>("tiles/testr.png"),
                         await load<Sprite>("tiles/testt.png"),
                         await load<Sprite>("tiles/testb.png")),
            position = (1, 2, 0),
        };

        lasparticulas = new() {
            particle = await load<Sprite>("white.png"),
            amountFunc = () => (uint)StMath.randint(200, 6000),
            durationFunc = () => StMath.randfloat(1, 5),
            positionStartFunc = () => tile.position,
            positionEndFunc = () => StMath.randvec2((-10, -10), (10, 10)).as3d(tile.position.z),
            rotationStartFunc = () => 0,
            rotationEndFunc = () => StMath.randfloat(-360, 360),
            colorStartFunc = () => color.white,
            colorEndFunc = () => (255, 255, 255, 0),
        };
    }

    public async void update(double delta)
    {
        vec2i dir = (0, 0);
        // it's adding so you can move diagonally
        if (Input.isKeymapHeld("move_left")) dir += (-1, 0);
        if (Input.isKeymapHeld("move_right")) dir += (1, 0);
        if (Input.isKeymapHeld("move_up")) dir += (0, -1);
        if (Input.isKeymapHeld("move_down")) dir += (0, 1);

        // actually move
        tile!.position += (dir * (vec2)(speed, speed) * (vec2)(delta, delta)).as3d(tile.position.z);

        // animation stuff
        // it shouldn't go back to looking down when you didn't press anything
        if (dir != (0, 0)) {
            tile.side = dir switch {
                (1, 0) => TileSide.RIGHT,
                (-1, 0) => TileSide.LEFT,
                (0, 1) => TileSide.BOTTOM,
                (0, -1) => TileSide.TOP,
                _ => tile.side
            };

            // haha
            tile.sprite!.bottom = walkDown!;
            if (!walkDown!.playing) walkDown.start();
            if (!walkUp!.playing) walkUp.start();
            if (!walkLeft!.playing) walkLeft.start();
            if (!walkRight!.playing) walkRight.start();
        }
        else {
            // haha
            tile.sprite!.bottom = await load<Sprite>("species/bobdown0.png");
            walkDown!.stop();
            walkUp!.stop();
            walkLeft!.stop();
            walkRight!.stop();
            walkDown.currentFrame = 0;
            walkUp.currentFrame = 0;
            walkLeft.currentFrame = 0;
            walkRight.currentFrame = 0;
        }

        // the famous camera
        Tilemap.camPosition = tile.position.as2d();

        // why though
        if (Input.isKeyJustPressed(Key.SPACE)) {
            lasparticulas!.emit();
        }

        if (Input.isMouseButtonJustPressed(MouseButton.LEFT)) {
            await Music.play("music/" + StMath.randomChoice([
                "lava1.mp3",
                "Legacy-Menu.mp3",
                "menu.mp3",
                "outsidetheuniverse.mp3",
                "ruins1.mp3",
                "space1.mp3",
                "twilight-forest1-_4_.mp3",
                "wasteland1.mp3"
            ]));
        }
    }

    public void draw()
    {
        Tilemap.pushTile(lol!);
        lasparticulas!.draw();
    }
}