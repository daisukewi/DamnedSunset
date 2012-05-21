-- Creacion de la tabla para manejar CEGUI desde lua
GUI = {
    System = CEGUI.System:getSingleton(),
    Schemes = CEGUI.SchemeManager:getSingleton(),
    Windows = CEGUI.WindowManager:getSingleton(),
    Images = CEGUI.ImagesetManager:getSingleton(),
    Mouse = CEGUI.MouseCursor:getSingleton(),
	Fonts = CEGUI.FontManager:getSingleton(),
}

-- Carga de Schemes
GUI.Schemes:create("TaharezLook.scheme")
GUI.Schemes:create("OgreTray.scheme")
GUI.Schemes:create("VanillaSkin.scheme")
GUI.Schemes:create("Interfaz.scheme")
GUI.Schemes:create("WindowsLook.scheme")

-- Load fonts
GUI.Fonts:create("DejaVuSans-10.font")
GUI.Fonts:create("FairChar-30.font")
GUI.Fonts:create("Batang-26.font")

