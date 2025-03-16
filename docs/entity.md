# Entities

Once upon a time, some guy wrote a whole game in Assembly. That wasn't ideal.

In the modern world, developers require new ways of architecturing their shitty code.

That's where the entity system comes in

## Basic entity

To make an entity, you need to implement the `entity.Entity` interface

```go
type John struct {
    // ...
}

func (j *John) EntityType() entity.Type {
	return entity.TypeGameWorld
}

func (j *John) OnCreate(ent entity.Ref) {
	fmt.Println("Good morning.")
}

func (j *John) OnUpdate(ent entity.Ref, delta float64) {
    // OnUpdate() runs every frame
    // John is in constant agony.
    fmt.Println("AAAAAAAAAAAAA")
}

// just put your ui here lmao
func (p *Player) OnGui(ent entity.Ref) {}

// other drawing stuff i guess
func (p *Player) OnDraw(ent entity.Ref) {}

func (p *Player) OnFree(ent entity.Ref) {
	fmt.Println("rip john")
}
```

If you don't need one of those functions just leave it empty

`entity.Ref`, as the name implies, is used to reference other entities. It's just a random uint32.

Every entity has types. Just look at the enum:

```go
const (
	// pausable object in the game world
	TypeGameWorld Type = iota
	// pausable 2d interface
	TypePausableUi
	// pausable manager, which is an entity running in the background and, well, managing
	TypePausableManager
	// ui that only runs when paused
	TypePausedUi
	// manager that only manages when paused
	TypePausedManager
)
```

Then you can actually make the entity exist:

```go
john := &John{}
entity.Add(john)
```

## Components

Sometimes you need to share functionality between entities. To do that, use components

Components have the same functions as entities:

```go
type Component interface {
	ComponentType() ComponentType
	OnCreate(ent Ref)
	OnGui(ent Ref)
	OnUpdate(ent Ref, delta float64)
	OnDraw(ent Ref)
	OnFree(ent Ref)
}
```

Except `ComponentType` is used to get the component's type because Go generics don't work

You can return pretty much anything there, it's just a string

```go
const HandsomeComponentType string = "the_edge_of_the_universe.HandsomeComponent"

func (h *HandsomeComponent) ComponentType() entity.ComponentType {
    return HandsomeComponentType
}
```

Then you can add components with `entity.AddComp`

```go
sexy := &HandsomeComponent{}
entity.AddComp(john, sexy)
```

And get components with `entity.GetComp`

```go
mayBeSexy := entity.AddComp(johnsBrother, HandsomeComponentType)
// it returns nil if it's not there
if mayBeSexy != nil {
    sexy := mayBeSexy.(*HandsomeComponent)
}
```

## Groups

As the name implies, it's used to group entities. For example entities that die can go in
`entity.GroupMereMortal`.

Entities can have multiple groups.

They're also pretty fast since it's all maps and stuff

You can start segregating your entities with `entity.AddToGroup`

```go
// John is hot.
entity.AddToGroup("hot", john)
```

Then you can check if an entity is in a group:

```go
if entity.IsInGroup("idfk", john) {
    panic("AAAAAAAAAAAAAAAAAAAAAAAAAaaaaaAAAAAAAAAAAAA")
}
```

Or get every entity in a group:

```go
var people []Ref = entity.GetGroup("people")
```

Pretty fancy innit mate bollocks i apologize

## Metadata

Entities can have metadata too because why the fuck not

```go
entity.SetMeta(john, "agony", 99999999999999)
// atLeast3 is the default
fmt.Println(entity.GetMeta(john, "agony", atLeast3))
```

So meta.