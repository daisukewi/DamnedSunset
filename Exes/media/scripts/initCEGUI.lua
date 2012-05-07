-- get CEGUI singletons
local logger = CEGUI.Logger:getSingleton()
logger:logEvent( ">>> Init script says hello" )
--logger:setLoggingLevel( CEGUI.Informative )

GUI = {
    System = CEGUI.System:getSingleton(),
    Schemes = CEGUI.SchemeManager:getSingleton(),
    Windows = CEGUI.WindowManager:getSingleton(),
    Images = CEGUI.ImagesetManager:getSingleton(),
    Mouse = CEGUI.MouseCursor:getSingleton(),
}

-- Schemes
GUI.Schemes:create("WindowsLook.scheme")
-- load schemes
schememan:loadScheme( "../datafiles/schemes/TaharezLook.scheme" )
schememan:loadScheme( "../datafiles/schemes/WindowsLook.scheme" )

-- Texturas
GUI.Images:create("Javy.imageset")

-- set default mouse cursor
GUI.System:setDefaultMouseCursor( "TaharezLook","MouseArrow" )
-- set default mouse cursor
system:setDefaultMouseCursor( "TaharezLook","MouseArrow" )

-- precision del raton
GUI.System:setMouseMoveScaling(18)

-- load a default font
local font = fontman:createFont( "../datafiles/fonts/Commonwealth-10.font" )


logger:logEvent( "<<< Init script says goodbye" )
