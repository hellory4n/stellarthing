package platform

type Key int32
type MouseButton int32

const (
	KeyUnknown = 0
	// '
	KeyApostrophe = 39
	// ,
	KeyComma = 44
	// -
	KeyMinus = 45
	// .
	KeyPeriod = 46
	// /
	KeySlash = 47
	KeyNum0 = 48
	KeyNum1 = 49
	KeyNum2 = 50
	KeyNum3 = 51
	KeyNum4 = 52
	KeyNum5 = 53
	KeyNum6 = 54
	KeyNum7 = 55
	KeyNum8 = 56
	KeyNum9 = 57
	// ;
	KeySemicolon = 59
	//  = 
	KeyEqual = 61
	Keya = 65
	KeyB = 66
	KeyC = 67
	KeyD = 68
	KeyE = 69
	KeyF = 70
	KeyG = 71
	KeyH = 72
	KeyI = 73
	KeyJ = 74
	KeyK = 75
	KeyL = 76
	KeyM = 77
	KeyN = 78
	KeyO = 79
	KeyP = 80
	KeyQ = 81
	KeyR = 82
	KeyS = 83
	KeyT = 84
	KeyU = 85
	KeyV = 86
	KeyW = 87
	KeyX = 88
	KeyY = 89
	KeyZ = 90
	// [
	KeyLeftBracket = 91
	// \
	KeyBackslash = 92
	// ]
	KeyRightBracket = 93
	// `
	KeyGrave = 96
	// 
	KeySpace = 32
	KeyEscape = 256
	KeyEnter = 257
	KeyTab = 258
	KeyBackspace = 259
	KeyInsert = 260
	KeyDelete = 261
	KeyRight = 262
	KeyLeft = 263
	KeyDown = 264
	KeyUp = 265
	KeyPageUp = 266
	KeyPageDown = 267
	KeyHome = 268
	KeyEnd = 269
	KeyCapsLock = 280
	KeyScrollLock = 281
	KeyNumLock = 282
	KeyPrintScreen = 283
	KeyPause = 284
	KeyF1 = 290
	KeyF2 = 291
	KeyF3 = 292
	KeyF4 = 293
	KeyF5 = 294
	KeyF6 = 295
	KeyF7 = 296
	KeyF8 = 297
	KeyF9 = 298
	KeyF10 = 299
	KeyF11 = 300
	KeyF12 = 301
	KeyLeftShift = 340
	KeyLeftControl = 341
	KeyLeftAlt = 342
	KeyLeftSuper = 343
	KeyRightShift = 344
	KeyRightControl = 345
	KeyRightAlt = 346
	KeyRightSuper = 347
	KeyKbMenu = 348
	KeyKp0 = 320
	KeyKp1 = 321
	KeyKp2 = 322
	KeyKp3 = 323
	KeyKp4 = 324
	KeyKp5 = 325
	KeyKp6 = 326
	KeyKp7 = 327
	KeyKp8 = 328
	KeyKp9 = 329
	KeyKpDecimal = 330
	KeyKpDivide = 331
	KeyKpMultiply = 332
	KeyKpSubtract = 333
	KeyKpAdd = 334
	KeyKpEnter = 335
	KeyKpEqual = 336
	KeyBack = 4
	KeyMenu = 82
	KeyVolumeUp = 24
	KeyVolumeDown = 25
)
const (
	MouseButtonLeft = iota
	MouseButtonRight
	MouseButtonMiddle
	// only on fancy mouses
	MouseButtonSide
	// only on fancy mouses
	MouseButtonExtra
	// only on fancy mouses
	MouseButtonForward
	// only on fancy mouses
	MouseButtonBack
)