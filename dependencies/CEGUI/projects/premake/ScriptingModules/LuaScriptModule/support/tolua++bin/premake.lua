--
-- tolua++cegui premake script
--

cegui_dynamic("tolua++cegui", "c", "exe")

package.files =
{
	matchfiles(rootdir.."cegui/src/"..pkgdir.."*.c"),
	matchfiles(rootdir.."cegui/src/"..pkgdir.."*.h"),
}

--include(rootdir.."cegui/include/"..pkgdir)
include(rootdir.."cegui/include/"..pkgdir.."../tolua++")

dependency("tolua++")
library("lua51","")
library_static("lua51","", "")
tinsert(debug.libpaths, rootdir.."../lib/Debug")
tinsert(release.libpaths, rootdir.."../lib/Release")

if TOLUA_STATIC then
    define("TOLUA_STATIC")
end
