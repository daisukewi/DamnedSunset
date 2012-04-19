function goTo(pointX, pointY, pointZ, entity)
	local mensaje = LUA_MAStarRoute()
	mensaje:setDestPointX(pointX)
	mensaje:setDestPointY(pointY)
	mensaje:setDestPointZ(pointZ)
	mensaje:setEntityTo(entity)
	mensaje:send()
end