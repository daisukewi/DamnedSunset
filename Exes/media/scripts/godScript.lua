--Creando tabla de datos de God
God = {
	Selected = 0
}

function processSelection(target, point_x, point_y, point_z)
	print("Se ha seleccionado la entidad " .. target)
	God.Selected = target
end

function processAction(target, point_x, point_y, point_z)
	if point_y ~= -1 then
		if God.Selected ~= -1 then
			if target ~= -1 then
				local mensaje = LUA_MAttackDistance()
				mensaje:setEntity(target)
				mensaje:setAttack(true)
				mensaje:setEntityTo(God.Selected)
				mensaje:send()
			else
				local mensaje = LUA_MAStarRoute()
				mensaje:setDestPointX(point_x)
				mensaje:setDestPointY(point_y)
				mensaje:setDestPointZ(point_z)
				mensaje:setEntityTo(God.Selected)
				mensaje:send()
			end
		end
	end
end