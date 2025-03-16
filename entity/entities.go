// entity
package entity

import (
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/platform"
)

// as the name implies, it's an entity type
type Type int

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

// it's an entity
type Entity interface {
	EntityType() Type
	OnCreate(ent Ref)
	OnGui(ent Ref)
	OnUpdate(ent Ref, delta float64)
	OnDraw(ent Ref)
	OnFree(ent Ref)
}

// compoentn
type Component interface {
	ComponentType() ComponentType
	OnCreate(ent Ref)
	OnGui(ent Ref)
	OnUpdate(ent Ref, delta float64)
	OnDraw(ent Ref)
	OnFree(ent Ref)
}

// if true, the game is paused. not all entities get paused, see EntityType
var Paused bool = false

// random number used to reference entities
type Ref uint32

// entity group
type Group string

// type of component
type ComponentType string

var entities map[Ref]Entity
var components map[Ref]map[ComponentType]Component
var meta map[Ref]map[string]any

// the value isn't used, go doesn't have a hash set
var groups map[Group]map[Ref]byte
var entgroups map[Ref]map[Group]byte

func Init() {
	entities = make(map[Ref]Entity)
	groups = make(map[Group]map[Ref]byte)
	components = make(map[Ref]map[ComponentType]Component)
	meta = make(map[Ref]map[string]any)
	entgroups = make(map[Ref]map[Group]byte)
}

func Free() {
	for id := range entities {
		Remove(id)
	}
}

// adds an entity and returns its ID
func Add(entity Entity) Ref {
	var ref Ref = Ref(core.RandUint32(0, core.Uint32Max))
	entities[ref] = entity
	meta[ref] = make(map[string]any)
	entgroups[ref] = make(map[Group]byte)
	components[ref] = make(map[ComponentType]Component)

	var group Group = ""
	switch entity.EntityType() {
	case TypeGameWorld:
		group = GroupGameWorld
	case TypePausableUi:
		group = GroupPausableUi
	case TypePausableManager:
		group = GroupPausableManager
	case TypePausedUi:
		group = GroupPausedUi
	case TypePausedManager:
		group = GroupPausedManager
	default:
		panic("mate\n")
	}
	AddToGroup(group, ref)

	entity.OnCreate(ref)
	return ref
}

// returns all entities in a group, and creates the group if it doesn't exist yet
func GetGroup(group Group) []Ref {
	// get rid of the byte :)
	var hhgjjhg []Ref = make([]Ref, len(groups[group]))

	var i int = 0
	for k := range groups[group] {
		hhgjjhg[i] = k
		i++
	}

	return hhgjjhg
}

// adds an entity to the group, and creates the group if it doesn't exist yet
func AddToGroup(group Group, entity Ref) {
	groups[group] = make(map[Ref]byte)
	groups[group][entity] = 0
	entgroups[entity] = make(map[Group]byte)
	entgroups[entity][group] = 0
}

// if true, the entity is in that group
func IsInGroup(group Group, entity Ref) bool {
	groupm, ok := groups[group]
	if !ok {
		return false
	}
	_, okok := groupm[entity]
	return okok
}

// adds a component to an entity
func AddComp(entity Ref, component Component) {
	components[entity][component.ComponentType()] = component
	component.OnCreate(entity)
}

// if true, the entity has that component
func HasComp(entity Ref, comptype ComponentType) bool {
	for _, v := range components[entity] {
		if v.ComponentType() == comptype {
			return true
		}
	}
	return false
}

// gets the component (as a pointer), or nil if it's not there yet.
func GetComp(entity Ref, comptype ComponentType) any {
	for _, v := range components[entity] {
		if v.ComponentType() == comptype {
			return &v
		}
	}
	return nil
}

// adds or a sets a key in the entity's metadata
func SetMeta(entity Ref, key string, val any) {
	meta[entity][key] = val
}

// if the key exists, returns the value, otherwise it sets the value to the defaultVal parameter.
func GetMeta(entity Ref, key string, defaultVal any) any {
	someta, ok := meta[entity][key]
	if !ok {
		someta = defaultVal
	}
	return someta
}

// as the name implies, it removes an entity
func Remove(entity Ref) {
	entities[entity].OnFree(entity)
	delete(meta, entity)
	delete(components, entity)
	for group := range entgroups[entity] {
		delete(groups[group], entity)
	}
	delete(entgroups, entity)
	delete(entities, entity)
}

func updateEntity(entity Entity, ref Ref) {
	// :(
	core.InternalInputFieldFocus = false
	entity.OnGui(ref)
	entity.OnUpdate(ref, platform.DeltaTime())
	entity.OnDraw(ref)
	for _, v := range components[ref] {
		v.OnUpdate(ref, platform.DeltaTime())
		v.OnDraw(ref)
	}
}

// updates entities duh
func UpdateAll() {
	if Paused {
		for _, ref := range GetGroup(GroupPausedManager) {
			updateEntity(entities[ref], ref)
		}

		for _, ref := range GetGroup(GroupPausedUi) {
			updateEntity(entities[ref], ref)
		}
	} else {
		for _, ref := range GetGroup(GroupPausableManager) {
			updateEntity(entities[ref], ref)
		}

		for _, ref := range GetGroup(GroupPausableUi) {
			updateEntity(entities[ref], ref)
		}

		for _, ref := range GetGroup(GroupGameWorld) {
			updateEntity(entities[ref], ref)
		}
	}
}
