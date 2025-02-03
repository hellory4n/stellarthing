using System;
using System.Collections.Generic;
namespace starry;

/// <summary>
/// particels but with tile coordinates :)
/// </summary>
public class TileParticles: IParticles {
    class Particle {
        public Timer? timer;
        public vec3 pos = vec3.zero;
        public vec3 posstart = vec3.zero;
        public vec3 posend = vec3.zero;
        public double rot = 0;
        public double rotstart = 0;
        public double rotend = 0;
        public color color = color.white;
        public color colorstart = color.white;
        public color colorend = color.white;
        public double lerptime = 0;
        public double start = 0;
    }

    /// <summary>
    /// sprite used for the particles
    /// </summary>
    public required ISprite particle { get; set; }
    public required Func<uint> amountFunc { get; set; }
    public required Func<double> durationFunc { get; set; }
    public required Func<vec3> positionStartFunc { get; set; }
    public required Func<vec3> positionEndFunc { get; set; }
    public required Func<double> rotationStartFunc { get; set; }
    public required Func<double> rotationEndFunc { get; set; }
    public required Func<color> colorStartFunc { get; set; }
    public required Func<color> colorEndFunc { get; set; }

    ConcurrentHashSet<Particle> particles = [];

    /// <summary>
    /// makes a bunch of particles
    /// </summary>
    public void emit()
    {
        uint amount = amountFunc();
        for (int i = 0; i < amount; i++) {
            Timer timetimetimetimetimetimetimetimetime = new(durationFunc(), false);
            Particle laparticula = new() {
                timer = timetimetimetimetimetimetimetimetime,
                posstart = positionStartFunc(),
                posend = positionEndFunc(),
                rotstart = rotationStartFunc(),
                rotend = rotationEndFunc(),
                colorstart = colorStartFunc(),
                colorend = colorEndFunc(),
                start = Window.elapsedTime,
            };
            laparticula.pos = laparticula.posstart;
            laparticula.rot = laparticula.rotstart;
            laparticula.color = laparticula.colorstart;

            particles.Add(laparticula);
            timetimetimetimetimetimetimetimetime.timeout += () => particles.Remove(laparticula);
        }
    }

    /// <summary>
    /// renders the particles
    /// </summary>
    public void draw()
    {
        Queue<Particle> queuedForAnnihilation = [];
        foreach (Particle article in particles) {
            vec2 globalPos = ((article.pos.as2d() - Tilemap.camPosition) * Starry.settings.tileSize) +
                Tilemap.camOffset;
            
            // don't kill your pc
            if (globalPos < (0, 0) || globalPos > Starry.settings.renderSize || article.color.a == 0) {
                queuedForAnnihilation.Enqueue(article);
                continue;
            }

            // first lerp the fuckers
            article.lerptime = (Window.elapsedTime - article.start) / article.timer!.duration;
            article.pos = StMath.lerp(article.posstart.as2d(), (article.posstart + article.posend).as2d(),
                article.lerptime).as3d(article.pos.z);
            article.rot = StMath.lerp(article.rotstart, article.rotend, article.lerptime);
            article.color = StMath.lerp(article.colorstart, article.colorend, article.lerptime);

            // you can't see explosions in the underground from the surface
            if (article.pos.round().z != Tilemap.currentLayers[Tilemap.currentWorld]) continue;

            // then fucking draw the fuckers
            // this is separate from the tilemap because
            // 1. making tiles is a bit of an overhead since they're classes
            // 2. you may want to save the tilemap, saving particles is pointless and would make it
            //    really big
            Graphics.drawSprite(
                particle,
                (((article.pos.as2d() - Tilemap.camPosition) * Starry.settings.tileSize) + Tilemap.camOffset,
                particle.getSize() * Tilemap.camScale),
                particle.getSize() / (2, 2),
                article.rot, article.color
            );
        }

        // die
        while (queuedForAnnihilation.Count > 0) {
            particles.Remove(queuedForAnnihilation.Dequeue());
        }
    }
}