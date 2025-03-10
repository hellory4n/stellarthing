// entity
package entities

import (
	"github.com/hellory4n/stellarthing/core"
	"github.com/hellory4n/stellarthing/platform"
)

// as the name implies, it's an entity type
type EntityType int

const (
	// pausable object in the game world
	EntityTypeGameWorld EntityType = iota
	// pausable 2d interface
	EntityTypePausableUi
	// pausable manager, which is an entity running in the background and, well, managing
	EntityTypePausableManager
	// ui that only runs when paused
	EntityTypePausedUi
	// manager that only manages when paused
	EntityTypePausedManager
)

// it's an entity
type Entity interface {
	EntityType() EntityType
	OnCreate(entity EntityRef)
	OnGui(entity EntityRef)
	OnUpdate(entity EntityRef, delta float64)
	OnDraw(entity EntityRef)
	OnFree(entity EntityRef)
}

type Component interface {
	ComponentType() ComponentType
	OnCreate(entity EntityRef)
	OnGui(entity EntityRef)
	OnUpdate(entity EntityRef, delta float64)
	OnDraw(entity EntityRef)
	OnFree(entity EntityRef)
}

const (
	// pausable object in the game world
	GroupGameWorld Group = "starry.GAME_WORLD"
	// pausable 2d interface
	GroupPausableUi = "starry.PAUSABLE_UI"
	// pausable manager, which is an entity running in the background and, well, managing
	GroupPausableManager = "starry.PAUSABLE_MANAGER"
	// ui that only runs when paused
	GroupPausedUi = "starry.PAUSED_UI"
	// manager that only manages when paused
	GroupPausedManager = "starry.PAUSED_MANAGER"
)

// if true, the game is paused. not all entities get paused, see EntityType
var Paused bool = false

// random number used to reference entities
type EntityRef uint32

// entity group
type Group string

// type of component
type ComponentType string

var entities map[EntityRef]Entity
var components map[EntityRef]map[ComponentType]Component
var meta map[EntityRef]map[string]any

// the value isn't used, go doesn't have a hash set
var groups map[Group]map[EntityRef]byte
var entgroups map[EntityRef]map[Group]byte

func Init() {
	entities = make(map[EntityRef]Entity)
	groups = make(map[Group]map[EntityRef]byte)
	components = make(map[EntityRef]map[ComponentType]Component)
	meta = make(map[EntityRef]map[string]any)
	entgroups = make(map[EntityRef]map[Group]byte)
}

func Free() {
	for id := range entities {
		RemoveEntity(id)
	}
}

// adds an entity and returns its ID
func AddEntity(entity Entity) EntityRef {
	var ref EntityRef = EntityRef(core.RandUint32(0, core.Uint32Max))
	entities[ref] = entity
	meta[ref] = make(map[string]any)
	entgroups[ref] = make(map[Group]byte)
	components[ref] = make(map[ComponentType]Component)

	var group Group = ""
	switch entity.EntityType() {
		case EntityTypeGameWorld: group = GroupGameWorld
		case EntityTypePausableUi: group = GroupPausableUi
		case EntityTypePausableManager: group = GroupPausableManager
		case EntityTypePausedUi: group = GroupPausedUi
		case EntityTypePausedManager: group = GroupPausedManager
		default: panic("mate\n")
	}
	AddToGroup(group, ref)

	entity.OnCreate(ref)
	return ref
}

// returns all entities in a group, and creates the group if it doesn't exist yet
func GetGroup(group Group) []EntityRef {
	// get rid of the byte :)
	var hhgjjhg []EntityRef = make([]EntityRef, len(groups[group]))

	var i int = 0
	for k := range groups[group] {
		hhgjjhg[i] = k
		i++
	}

	return hhgjjhg
}

// adds an entity to the group, and creates the group if it doesn't exist yet
func AddToGroup(group Group, entity EntityRef) {
	groups[group] = make(map[EntityRef]byte)
	groups[group][entity] = 0
	entgroups[entity] = make(map[Group]byte)
	entgroups[entity][group] = 0
}

// if true, the entity is in that group
func IsInGroup(group Group, entity EntityRef) bool {
	groupm, ok := groups[group]
	if !ok {
		return false
	}
	_, okok := groupm[entity]
	return okok
}

// adds a component to an entity
func AddComponent(entity EntityRef, component Component) {
	components[entity][component.ComponentType()] = component
	component.OnCreate(entity)
}

// if true, the entity has that component
func HasComponent(entity EntityRef, comptype ComponentType) bool {
	for _, v := range components[entity] {
		if v.ComponentType() == comptype {
			return true
		}
	}
	return false
}

// gets the component, or nil if it's not there yet.
func GetComponent(entity EntityRef, comptype ComponentType) any {
	for _, v := range components[entity] {
		if v.ComponentType() == comptype {
			return v
		}
	}
	return nil
}

// adds or a sets a key in the entity's metadata
func SetMeta(entity EntityRef, key string, val any) {
	meta[entity][key] = val
}

// if the key exists, returns the value, otherwise it sets the value to the defaultVal parameter.
func GetMeta(entity EntityRef, key string, defaultVal any) any {
	someta, ok := meta[entity][key]
	if !ok {
		someta = defaultVal
	}
	return someta
}

// as the name implies, it removes an entity
func RemoveEntity(entity EntityRef) {
	entities[entity].OnFree(entity)
	delete(meta, entity)
	delete(components, entity)
	for group := range entgroups[entity] {
		delete(groups[group], entity)
	}
	delete(entgroups, entity)
	delete(entities, entity)
}

func updateEntity(entity Entity, ref EntityRef) {
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
func UpdateAllEntities() {
	if (Paused) {
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