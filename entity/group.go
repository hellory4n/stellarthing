package entity

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
