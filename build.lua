-- i hate every build system
-- the solution is lua fuck you

-- TODO dont make windows users suffer that much
-- someone please think of the windows users
-- TODO use a build system

-- put all of the source files here lmao
srcs = {
	"vendor/libtrippin/libtrippin.c",
	"vendor/FastNoiseLite.c",
	"vendor/rlFPCamera.c",
	"vendor/stb_ds.c",
	"main.c",
	"core/graphics.c",
	"player/control/player_controller.c",
	""
}

platform = "linux"
buildmode = "debug"
cc = "clang"

-- ran before any building stuff is done
function prebuild()
	if platform == "linux" then
		-- gcc or clang?
		-- clang is preferred
		if os.execute("command -v clang") then
			cc = "clang"
		elseif os.execute("command -v gcc") then
			cc = "gcc"
		else
			error("no C compiler could be found. it's recommended you install clang")
		end
	else
		if os.execute("command -v x86_64-w64-mingw32-gcc") then
			cc = "x86_64-w64-mingw32-gcc"
		else
			error("no cross-compiler could be found. make sure you have mingw64-gcc installed (command x86_64-w64-mingw32-gcc)")
		end
	end
end

-- build.
function build()
	print("H")
end

-- run.
function run()
end

-- clean.
function clean()
	print("mm")
end

-- handle commands
if arg[1] == "clean" then
	prebuild()
	clean()
elseif arg[1] == "build" then
	if arg[2] == nil then
		error("expected build mode (either debug, release, or debugasan)")
	else
		buildmode = arg[2]
	end

	if arg[3] ~= nil then
		platform = arg[3]
	end

	prebuild()
	build()
elseif arg[1] == "run" then
	if arg[2] ~= nil then
		buildmode = arg[2]
	end

	prebuild()
	build()
	run()
else
	print("Stellarthing buildificator\n\nUsage:\n- clean: cleans lol\n- build <debug|release|debugasan> [linux|windows]\n- run [debug|release|debugasan]")
end
